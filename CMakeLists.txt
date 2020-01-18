cmake_minimum_required(VERSION 3.11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
find_program(PKG_CONFIG pkg-config)
find_package(PkgConfig)
include(CPack)
set(CMAKE_C_FLAGS "-Wall -Wextra -ggdb3 -fPIC" )
set(CMAKE_CXX_FLAGS "-std=c++0x -fPIC" )
set(CMAKE_BUILD_TYPE "Debug")
set(CXX g++)
set(CC gcc)
# Project Specific Options
project(screen-lock C CXX )
find_package(Threads)
file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/*.cpp)
find_package( Boost 
  COMPONENTS
  program_options REQUIRED)
find_package( OpenCV 
  COMPONENTS
  core 
  imgproc
  highgui
  REQUIRED)
include_directories(${Boost_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS})
message(STATUS "OpenCV library status:")
message(STATUS "    config: ${OpenCV_DIR}")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

message(STATUS "Boost library status: ")
message(STATUS "    libraries: ${Boost_LIBRARIES}")
add_executable(imblur ${SRC_FILES})
# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(ImageManipulator SHARED ImageManipulator.cpp)

target_link_libraries(imblur PRIVATE ${CMAKE_DL_LIBS} ${CMAKE_THREAD_LIBS_INIT} ${OpenCV_LIBS} ${Boost_LIBRARIES}  ImageManipulator)
add_custom_target(graphviz ALL
  COMMAND "${CMAKE_COMMAND}" "--graphviz=deps.dot" .
  COMMAND dot -Tpng deps.dot -o deps.png
  COMMAND cp deps.png ${PROJECT_SOURCE_DIR}/doc
  WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")

  add_custom_command(TARGET imblur
  POST_BUILD
  COMMAND cp ${CMAKE_BINARY_DIR}/imblur ${PROJECT_SOURCE_DIR}
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  )
