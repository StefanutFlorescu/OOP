cmake_minimum_required(VERSION 3.29)
project(OOP-main)

enable_testing()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find OpenCV package dynamically
find_package(OpenCV REQUIRED)
if(OpenCV_FOUND)
    message(STATUS "OpenCV found: ${OpenCV_VERSION}")
else()
    message(FATAL_ERROR "OpenCV not found.")
endif()

# Find SFML package dynamically
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Create the main executable
add_executable(OOP-main
        main.cpp
        generated/src/Image.cpp
        generated/src/Filter.cpp
        generated/src/Button.cpp
        generated/src/Frame.cpp
        generated/src/TextFrame.cpp
        generated/src/Helper.cpp
        generated/include/LoadManager.h
        generated/include/Command.h
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
        generated/include/LoadManager.cpp
        generated/include/LoadManager.h
        generated/include/Command.h
)

# Specify include directories
target_include_directories(OOP-main PRIVATE
        src
        ${OpenCV_INCLUDE_DIRS}
        ${SFML_INCLUDE_DIRS}
)

target_include_directories(my_tests PRIVATE
        src
        ${OpenCV_INCLUDE_DIRS}
        ${SFML_INCLUDE_DIRS}
)

# Link OpenCV and SFML libraries
target_link_libraries(OOP-main PRIVATE
        ${OpenCV_LIBS}
        sfml-graphics
        sfml-window
        sfml-system
)

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
