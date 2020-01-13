cmake_minimum_required(VERSION 3.11)
project(screen-lock VERSION 0.10)
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
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(ImageManipulator STATIC ImageManipulator.cpp)

target_link_libraries(imblur PRIVATE ${OpenCV_LIBS} ${Boost_LIBRARIES} ImageManipulator)
add_custom_target(graphviz ALL
                  COMMAND "${CMAKE_COMMAND}" "--graphviz=deps.dot" .
                  COMMAND dot -Tpng deps.dot -o deps.png
                  WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")