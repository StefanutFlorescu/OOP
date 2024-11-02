cmake_minimum_required(VERSION 3.29)
project(OOP-main)
enable_testing()

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


