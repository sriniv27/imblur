cmake_minimum_required(VERSION 3.11)
project(screen-lock VERSION 0.10)

find_package( Boost 
  COMPONENTS
  program_options REQUIRED)
find_package( OpenCV REQUIRED)
include_directories(${Boost_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS})
message(STATUS "OpenCV library status:")
message(STATUS "    config: ${OpenCV_DIR}")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

message(STATUS "Boost library status")
message(STATUS "libraries: ${Boost_LIBRARIES}")
add_executable(imblur main.cpp)
# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

target_link_libraries(imblur PRIVATE ${OpenCV_LIBS} ${Boost_LIBRARIES})
