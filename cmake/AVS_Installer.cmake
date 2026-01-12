function(AVS_Installer TARGET DEST_DIR CUSTOM_TARGET_NAME)
    get_target_property(TARGET_LOCATION TARGET LOCATION)

    if(NOT TARGET_LOCATION)
        message(FATAL_ERROR "Target ${TARGET} does not have a LOCATION property. Is it an executable/library?")
    endif()

    get_filename_component(SOURCE_FILE_NAME ${TARGET_LOCATION} NAME)
    set(DEST_PATH "${DEST_DIR}/${SOURCE_FILE_NAME}")
    set(BACKUP_PATH "${DEST_DIR}/${SOURCE_FILE_NAME}.original")

    add_custom_command(
        OUTPUT  ${DEST_PATH}
        COMMAND ${CMAKE_COMMAND} -E make_directory ${DEST_DIR}
        COMMAND_EXPAND_LISTS
        COMMAND ${CMAKE_COMMAND} -E remove -f ${DEST_PATH}.tmp
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:${TARGET}> ${DEST_PATH}.tmp

        # Generate a temporary script name
        set(TEMP_SCRIPT_NAME "${CMAKE_CURRENT_BINARY_DIR}/install_${TARGET}_logic.cmake")
        file(WRITE ${TEMP_SCRIPT_NAME}
    "
if(EXISTS \"${DEST_PATH}\")
    message(STATUS \"${DEST_PATH} exists. Backing up to ${BACKUP_PATH}\")
    file(RENAME \"${DEST_PATH}\" \"${BACKUP_PATH}\")
endif()

message(STATUS \"Installing target ${TARGET} to ${DEST_PATH}\")
file(COPY \"$<TARGET_FILE:${TARGET}>\" DESTINATION \"${DEST_DIR}\")
"
    )

        # Execute the generated script
        COMMAND ${CMAKE_COMMAND} -P ${TEMP_SCRIPT_NAME}

        # Dependencies: Ensure the target is built before we try to install it.
        DEPENDS ${TARGET}
    )

    add_custom_target(${CUSTOM_TARGET_NAME}_${TARGET}_install ALL
        DEPENDS ${DEST_PATH}
        COMMENT "Custom installation of ${TARGET} completed."
    )

    add_dependencies(${CUSTOM_TARGET_NAME} ${CUSTOM_TARGET_NAME}_${TARGET}_install)
endfunction()