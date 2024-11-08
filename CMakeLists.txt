cmake_minimum_required(VERSION 3.29)
project(OOP-main)

enable_testing()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find OpenCV package
set(OpenCV_DIR "/usr/local/lib/cmake/opencv4")
find_package(OpenCV REQUIRED)

if(OpenCV_FOUND)
    message(STATUS "OpenCV found: ${OpenCV_VERSION}")
else()
    message(FATAL_ERROR "OpenCV not found.")
endif()

# Find SFML package
set(SFML_DIR "/opt/homebrew/opt/sfml/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Create the main executable
add_executable(OOP-main
        main.cpp
        generated/src/Image.cpp
        generated/src/Filter.cpp
        generated/src/Button.cpp
        generated/src/Frame.cpp
        generated/src/Text_Frame.cpp
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
        generated/src/Text_Frame.cpp
        generated/src/Helper.cpp
)

# Specify include directories for the main project
target_include_directories(OOP-main PRIVATE
        src
        ${OpenCV_INCLUDE_DIRS}
        ${SFML_INCLUDE_DIRS}
)

# Specify include directories for your tests
target_include_directories(my_tests PRIVATE
        src
        ${OpenCV_INCLUDE_DIRS}
        ${SFML_INCLUDE_DIRS}
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
