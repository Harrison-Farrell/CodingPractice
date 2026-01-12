# ==============================================================================
# DeploymentScripts.cmake
# Contains the core logic for copying and restoring files.
# Called via 'cmake -P' with ACTION, SOURCE, and DESTINATION variables set.
# ==============================================================================

set(ORIGINAL_BACKUP "${DESTINATION}.original")

if ("${ACTION}" STREQUAL "INSTALL")
    # --- INSTALL/COPY LOGIC ---
    
    if (EXISTS "${DESTINATION}")
        message(STATUS "Destination file exists: ${DESTINATION}")
        
        # Check if a previous backup already exists and remove it to prevent clutter
        if (EXISTS "${ORIGINAL_BACKUP}")
            message(STATUS "Removing old backup file: ${ORIGINAL_BACKUP}")
            file(REMOVE "${ORIGINAL_BACKUP}")
        endif()
        
        # Rename the existing file to .original
        message(STATUS "Renaming existing file to: ${ORIGINAL_BACKUP}")
        file(RENAME "${DESTINATION}" "${ORIGINAL_BACKUP}")
        
        if (NOT EXISTS "${ORIGINAL_BACKUP}")
            message(FATAL_ERROR "Failed to rename ${DESTINATION}. Aborting installation.")
        endif()
    endif()

    # Perform the actual copy operation
    message(STATUS "Installing ${SOURCE} to ${DESTINATION}")
    file(COPY "${SOURCE}" DESTINATION "${DESTINATION}")

    if (NOT EXISTS "${DESTINATION}")
        message(FATAL_ERROR "Installation failed. Could not copy ${SOURCE} to ${DESTINATION}")
    endif()
    message(STATUS "Successfully installed ${SOURCE} to ${DESTINATION}")

elseif("${ACTION}" STREQUAL "RESTORE")
    # --- RESTORE/ROLLBACK LOGIC ---

    if (NOT EXISTS "${ORIGINAL_BACKUP}")
        message(STATUS "No backup file found at: ${ORIGINAL_BACKUP}. Nothing to restore.")
        return()
    endif()

    message(STATUS "Backup file found: ${ORIGINAL_BACKUP}")

    # If the current destination file exists, remove it
    if (EXISTS "${DESTINATION}")
        message(STATUS "Removing existing file: ${DESTINATION}")
        file(REMOVE "${DESTINATION}")
        if (EXISTS "${DESTINATION}")
            message(FATAL_ERROR "Failed to remove ${DESTINATION}. Aborting restoration.")
        endif()
    endif()

    # Rename the .original file back to the destination file name
    message(STATUS "Restoring ${ORIGINAL_BACKUP} to ${DESTINATION}")
    file(RENAME "${ORIGINAL_BACKUP}" "${DESTINATION}")

    if (NOT EXISTS "${DESTINATION}")
        message(FATAL_ERROR "Restoration failed. ${ORIGINAL_BACKUP} was not renamed to ${DESTINATION}")
    endif()
    message(STATUS "Successfully restored ${DESTINATION} from backup.")

else()
    message(FATAL_ERROR "Unknown action: ${ACTION}. Script must be called with ACTION=INSTALL or ACTION=RESTORE.")
endif()