cmake_minimum_required(VERSION 3.29)
project(OOP-main)
enable_testing()

set(CMAKE_CXX_STANDARD 20)  # Change this to 14, 17, or 20 as needed
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#TEST
set(OpenCV_DIR "/opt/homebrew/Cellar/opencv/4.10.0_12/lib/cmake/opencv4")

# Find OpenCV package
find_package(OpenCV REQUIRED)

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
        /Users/stefanutflorescu/Downloads/OOP-main/generated/src/test.cpp
        /Users/stefanutflorescu/Downloads/OOP-main/generated/include/test.h
        /Users/stefanutflorescu/Downloads/OOP-main/generated/include/doctest.h
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
        ${SFML_INCLUDE_DIRS}  # Include SFML headers
)

# Link OpenCV and SFML libraries to your executable
target_link_libraries(my_tests PRIVATE
        ${OpenCV_LIBS}
        sfml-graphics
        sfml-window
        sfml-system
)


# Specify include directories for your project
target_include_directories(OOP-main PRIVATE
        src
        ${OpenCV_INCLUDE_DIRS}
        ${SFML_INCLUDE_DIRS}  # Include SFML headers
)

# Link OpenCV and SFML libraries to your executable
target_link_libraries(OOP-main PRIVATE
        ${OpenCV_LIBS}
        sfml-graphics
        sfml-window
        sfml-system
)


