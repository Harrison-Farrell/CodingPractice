macro(AddPractice target)
	add_executable(${target}
		${target}.cpp
	)
	target_link_libraries(${target}
		PUBLIC spdlog::spdlog)
	set_target_properties(${target} PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/practice"
)
endmacro()
