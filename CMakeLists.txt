# For Visual Studio: File > Open > Folder... and choose this folder.
# FLTK must be installed for Visual Studio, for example with vcpkg:
#   vcpkg install fltk:x64-windows
cmake_minimum_required(VERSION 3.15)

# Use vcpkg's FLTK if vcpkg is installed in C:/vcpkg
if(NOT DEFINED CMAKE_TOOLCHAIN_FILE AND EXISTS "C:/vcpkg/scripts/buildsystems/vcpkg.cmake")
    set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake")
endif()

project(MazeRunner CXX)

set(CMAKE_CXX_STANDARD 11)

find_package(FLTK CONFIG QUIET)
if(NOT FLTK_FOUND)
    find_package(FLTK REQUIRED)
endif()

add_executable(mazerunner_gui
    main.cpp Maze.cpp Player.cpp Enemy.cpp Game.cpp Block.cpp Grid.cpp GameWindow.cpp)

if(TARGET fltk)
    target_link_libraries(mazerunner_gui PRIVATE fltk)
else()
    target_include_directories(mazerunner_gui PRIVATE ${FLTK_INCLUDE_DIR})
    target_link_libraries(mazerunner_gui PRIVATE ${FLTK_LIBRARIES})
endif()

# Copy maze.txt next to the program, so it is found when run from Visual Studio
configure_file(maze.txt ${CMAKE_CURRENT_BINARY_DIR}/maze.txt COPYONLY)
