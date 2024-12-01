cmake_minimum_required(VERSION 3.29)
project(OOP-main)

enable_testing()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Use FetchContent for dependencies
include(FetchContent)

# Fetch OpenCV
FetchContent_Declare(
        OpenCV
        GIT_REPOSITORY https://github.com/opencv/opencv.git
        #GIT_TAG 4.x  # You can specify a specific version, e.g., 4.10.0
)
FetchContent_MakeAvailable(OpenCV)

# Fetch SFML
FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.5.1  # You can specify a specific version
)
FetchContent_MakeAvailable(SFML)

# Create the main executable
add_executable(OOP-main
        main.cpp
        generated/src/Image.cpp
        generated/src/Filter.cpp
        generated/src/Button.cpp
        generated/src/Frame.cpp
        generated/src/TextFrame.cpp
        generated/src/Helper.cpp
)

# Create the test executable
add_executable(my_tests
        generated/src/test.cpp
        generated/include/test.h
        generated/include/doctest.h
        generated/src/Image.cpp
        generated/src/Filter.cpp
        generated/src/Button.cpp
        generated/src/Frame.cpp
        generated/src/TextFrame.cpp
        generated/src/Helper.cpp
        generated/include/Exception.cpp
        generated/include/Exception.h
)

# Specify include directories for the main project
target_include_directories(OOP-main PRIVATE
        src
        ${OpenCV_INCLUDE_DIRS}
        ${SFML_INCLUDE_DIR}
)

# Specify include directories for your tests
target_include_directories(my_tests PRIVATE
        src
        ${OpenCV_INCLUDE_DIRS}
        ${SFML_INCLUDE_DIR}
)

# Link OpenCV and SFML libraries to your main executable
target_link_libraries(OOP-main PRIVATE
        ${OpenCV_LIBS}
        sfml-graphics
        sfml-window
        sfml-system
)

# Link OpenCV and SFML libraries to your test executable
target_link_libraries(my_tests PRIVATE
        ${OpenCV_LIBS}
        sfml-graphics
        sfml-window
        sfml-system
)

# Install the executables
install(TARGETS OOP-main
        RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

install(TARGETS my_tests
        RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

# Optionally, specify installation of other files (e.g., headers, resources)
# install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_PREFIX}/include)
