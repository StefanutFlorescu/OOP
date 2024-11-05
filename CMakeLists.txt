cmake_minimum_required(VERSION 3.29)
project(OOP-main)
enable_testing()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set the OpenCV directory to where the OpenCVConfig.cmake is located
set(OpenCV_DIR "/opt/homebrew/Cellar/opencv/4.10.0_12/lib/cmake/opencv4")
# Set CMAKE_PREFIX_PATH
set(CMAKE_PREFIX_PATH "/opt/homebrew/Cellar/opencv/4.10.0_12/lib/cmake/opencv4")

# Find OpenCV package
find_package(OpenCV REQUIRED)

if(OpenCV_FOUND)
    message(STATUS "OpenCV found: ${OpenCV_VERSION}")
else()
    message(FATAL_ERROR "OpenCV not found.")
endif()

# Find SFML package
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Create the executable
add_executable(OOP-main
        main.cpp
        generated/src/Image.cpp
        generated/src/Filter.cpp
        generated/src/Button.cpp
        generated/src/Frame.cpp
        generated/src/Text_Frame.cpp
        generated/src/Helper.cpp
)

add_executable(my_tests
        generated/src/test.cpp
        generated/include/test.h
        generated/include/doctest.h
        generated/src/Image.cpp
        generated/src/Filter.cpp
        generated/src/Button.cpp
        generated/src/Frame.cpp
        generated/src/Text_Frame.cpp
        generated/src/Helper.cpp
)

# Specify include directories for your project
target_include_directories(my_tests PRIVATE
        src
        ${OpenCV_INCLUDE_DIRS}
        ${SFML_INCLUDE_DIRS}
)

# Link OpenCV and SFML libraries to your executable
target_link_libraries(my_tests PRIVATE
        ${OpenCV_LIBS}
        sfml-graphics
        sfml-window
        sfml-system
)

# Specify include directories for your main project
target_include_directories(OOP-main PRIVATE
        src
        ${OpenCV_INCLUDE_DIRS}
        ${SFML_INCLUDE_DIRS}
)

# Link OpenCV and SFML libraries to your main project
target_link_libraries(OOP-main PRIVATE
        ${OpenCV_LIBS}
        sfml-graphics
        sfml-window
        sfml-system
)
