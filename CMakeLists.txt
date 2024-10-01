cmake_minimum_required(VERSION 3.10)

# Set the project name
project(SampleProject)

# Specify the C standard
set(CMAKE_C_STANDARD 11)

# Add the executable
add_executable(sample sample.c)

# Specify the path to the dynamic library
set(LIBRARY_PATH ${CMAKE_CURRENT_SOURCE_DIR})

# Link the dynamic library
target_link_libraries(sample PRIVATE ${LIBRARY_PATH}/EdgeSync360.EdgeHub.Edge.C.SDK.1.0.2.dylib)

# Optionally, set the output directory for the executable
set_target_properties(sample PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
)
