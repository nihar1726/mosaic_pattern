cmake_minimum_required(VERSION 3.16)
project(MosaicPatternCreator VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
find_package(OpenCV REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${OpenCV_INCLUDE_DIRS})

# Source files
set(SOURCES
    src/main.cpp
    src/ImageProcessor.cpp
    src/MosaicGenerator.cpp
    src/UI.cpp
    src/Utils.cpp
)

set(HEADERS
    include/ImageProcessor.h
    include/MosaicGenerator.h
    include/UI.h
    include/Utils.h
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Link libraries
target_link_libraries(${PROJECT_NAME}
    Qt6::Core
    Qt6::Widgets
    ${OpenCV_LIBS}
)

# Set output directory
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
