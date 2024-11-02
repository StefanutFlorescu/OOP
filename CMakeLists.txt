cmake_minimum_required(VERSION 3.29)
project(OpenCVExample)
enable_testing()

# Find OpenCV package
find_package(OpenCV REQUIRED)
#find_package(GTest REQUIRED)
#include_directories(${GTEST_INCLUDE_DIRS})

# Find SFML package
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Create the executable
add_executable(OpenCVExample
        main.cpp
        generated/src/Image.cpp
        generated/src/Filter.cpp
        generated/src/Button.cpp
        generated/src/Frame.cpp
        generated/src/Text_Frame.cpp
        generated/src/Helper.cpp
)

#add_executable(image_editor_tests src/test.cpp src/test.h)

# Specify include directories for your project
target_include_directories(OpenCVExample PRIVATE
        src
        ${OpenCV_INCLUDE_DIRS}
        ${SFML_INCLUDE_DIRS}  # Include SFML headers
)

# Link OpenCV and SFML libraries to your executable
target_link_libraries(OpenCVExample PRIVATE
        ${OpenCV_LIBS}
        sfml-graphics
        sfml-window
        sfml-system
)

#target_link_libraries(image_editor_tests ${GTEST_LIBRARIES} pthread)



#cmake_minimum_required(VERSION 3.26)
#
## NOTE: update executable name in .github/workflows/cmake.yml:25 when changing executable name in this file
## for now, the project name is used as the executable name
#project(oop)
## set(CMAKE_PROJECT_VERSION_MAJOR 0)
## set(CMAKE_PROJECT_VERSION_MINOR 0)
## set(CMAKE_PROJECT_VERSION_PATCH 1)
#
#set(CMAKE_CXX_STANDARD 23)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_CXX_EXTENSIONS OFF)
#
#include(cmake/Options.cmake)
#
################################################################################
#
## external dependencies with FetchContent
## include(FetchContent)
##
## set(FETCHCONTENT_QUIET OFF)
## set(FETCHCONTENT_UPDATES_DISCONNECTED ON)
##
## NOTE: Also update env vars used for caching in
##         - .github/actions/configure-cmake/action.yml
##         - .github/workflows/cmake.yml
## FetchContent_Declare(
##         SomeLib
##         GIT_REPOSITORY https://github.com/<SomeUser>/<SomeLib>.git
##         GIT_TAG        <some_git_hash> # <which tag/branch @ <some_date>>
##         GIT_SHALLOW    1  # works only with branches or tags, not with arbitrary commit hashes
## )
##
## FetchContent_MakeAvailable(SomeLib)
#
################################################################################
#
## external dependencies with find_package
#
## find_package(Threads REQUIRED)
#
################################################################################
#
## NOTE: update executable name in .github/workflows/cmake.yml:25 when changing name here
#add_executable(${PROJECT_NAME}
#    main.cpp
#    generated/src/Helper.cpp
#)
#
#include(cmake/CompilerFlags.cmake)
#
################################################################################
#
## use SYSTEM so cppcheck and clang-tidy do not report warnings from these directories
#target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE generated/include)
## target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ext/<SomeHppLib>/include)
## target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${<SomeLib>_SOURCE_DIR}/include)
## target_link_directories(${PROJECT_NAME} PRIVATE ${<SomeLib>_BINARY_DIR}/lib)
## target_link_libraries(${PROJECT_NAME} <SomeLib>)
#
################################################################################
#
## copy binaries to "bin" folder; these are uploaded as artifacts on each release
## DESTINATION_DIR is set as "bin" in cmake/Options.cmake:6
#install(TARGETS ${PROJECT_NAME} DESTINATION ${DESTINATION_DIR})
#if(APPLE)
#    install(FILES launcher.command DESTINATION ${DESTINATION_DIR})
#endif()
#
#include(cmake/CopyHelper.cmake)
#copy_files(FILES tastatura.txt)
## copy_files(FILES tastatura.txt config.json DIRECTORY images sounds)
## copy_files(DIRECTORY images sounds)
