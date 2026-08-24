# Define minimal required version of CMake.
cmake_minimum_required(VERSION "3.25")

# Project definition
project(
	MatterSensorOverWiFi
	VERSION 1.0
	LANGUAGES C CXX ASM
)

# Include the definition of the slc_MatterSensorOverWiFi target,
# which contains the content of the SLC project
include(MatterSensorOverWiFi.cmake)

target_sources(slc PRIVATE
    ../src/aws_cloud.c
    ../src/dsp_module.c
    ../src/light_sensor.c
    ../src/mic_audio.c
    ../src/ml_model.c
    ../src/network_manager.c
    ../src/security_module.c
)

target_include_directories(slc PUBLIC
    ../include
)

add_executable(MatterSensorOverWiFi
    # Add additional sources here
)

target_include_directories(MatterSensorOverWiFi PUBLIC
    # Add additional include paths here
    ../include
)

target_compile_definitions(MatterSensorOverWiFi PUBLIC
    # Add additional macros here
)

target_compile_options(MatterSensorOverWiFi PUBLIC
    # Set additional compiler flags here
)

target_link_options(MatterSensorOverWiFi PUBLIC
    # Set additional linker flags here
)

# Link with the content defined in the SLC project
target_link_libraries(MatterSensorOverWiFi PRIVATE
    slc
)

# Include managed project content if available
include(MatterSensorOverWiFi_project.cmake OPTIONAL RESULT_VARIABLE managed_project)
if(managed_project)
    message(STATUS "Using managed project content from ${managed_project}")
endif()

# Force the gcc linker command
set_target_properties(MatterSensorOverWiFi PROPERTIES LINKER_LANGUAGE C)

# Create .bin, .hex and .s37 artifacts after building the project
add_custom_command(TARGET MatterSensorOverWiFi
    POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} ${OBJCOPY_SREC_CMD} "$<TARGET_FILE:MatterSensorOverWiFi>" "$<TARGET_FILE_DIR:MatterSensorOverWiFi>/$<TARGET_FILE_BASE_NAME:MatterSensorOverWiFi>.s37"
    COMMAND ${CMAKE_OBJCOPY} ${OBJCOPY_IHEX_CMD} "$<TARGET_FILE:MatterSensorOverWiFi>" "$<TARGET_FILE_DIR:MatterSensorOverWiFi>/$<TARGET_FILE_BASE_NAME:MatterSensorOverWiFi>.hex"
    COMMAND ${CMAKE_OBJCOPY} ${OBJCOPY_BIN_CMD}  "$<TARGET_FILE:MatterSensorOverWiFi>" "$<TARGET_FILE_DIR:MatterSensorOverWiFi>/$<TARGET_FILE_BASE_NAME:MatterSensorOverWiFi>.bin" 
)

# Run post-build pipeline to perform additional post-processing
if(post_build_command)
add_custom_command(TARGET MatterSensorOverWiFi
    POST_BUILD
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/..
    COMMAND ${post_build_command}
)
endif()
