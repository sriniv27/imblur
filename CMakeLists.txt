
########################################################
#####      CMake Level Configuration               #####
########################################################
cmake_minimum_required(VERSION 3.11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(CPack)
set(CMAKE_C_FLAGS "-Wall -Wextra -ggdb" )

# Add a custom CMake Modules directory
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules
                      ${CMAKE_MODULE_PATH})
########################################################
#####       Project & Language Options             #####
########################################################
project(screen-lock C CXX )
# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CXX g++)
set(CC gcc)

########################################################
#####      Package and Component Dependencies      #####
########################################################

find_package( Boost
  COMPONENTS
  program_options REQUIRED)

  find_package( OpenCV
  COMPONENTS
  core
  imgproc
  highgui
  imgcodecs
  REQUIRED)

find_package(Doxygen
REQUIRED dot
OPTIONAL_COMPONENTS mscgen dia)
find_package(Threads)

set(CLANG_FORMAT_BIN_NAME clang-format-3.6)
set(CLANG_FORMAT_EXCLUDE_PATTERNS  "build/" ${CMAKE_BINARY_DIR})

find_package(ClangFormat)

if(CLANG_FORMAT_BIN)
        message("clang-format executable: ${CLANG_FORMAT_BIN}")
        message("clang-format version: ${CLANG_FORMAT_VERSION}")
else()
        message("clang-format executable not found")
endif()


set(CMAKE_PREFIX_PATH ${PROJECT_SOURCE_DIR}/spdlog)




# Configure build
file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/**/*.cpp)

include_directories(${Boost_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS})
message(STATUS "OpenCV library status:")
message(STATUS "    config: ${OpenCV_DIR}")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

message(STATUS "Boost library status: ")
message(STATUS "    libraries: ${Boost_LIBRARIES}")


add_executable(imblur ${SRC_FILES})

find_package(spdlog)
install(TARGETS imblur)

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

  set(DOXYGEN_DENERATE_MAN NO)
  set(DOXYGEN_GENERATE_HTML YES)
  set(DOXYGEN_GENERATE_LATEX YES)
  set(DOXYGEN_GENERATE_XML NO)
  set(DOXYGEN_GENERATE_TREEVIEW YES)
  set(DOXYGEN_USE_MDFILE_AS_MAINPAGE YES)
  doxygen_add_docs(
    Documentation
    ${PROJECT_SOURCE_DIR}

  )
  
  add_custom_command(
    TARGET Documentation
  COMMAND scripts/publish-to-public.sh
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})


########################################################
#####      Final link phases of all targets        #####
########################################################
target_link_libraries(imblur PRIVATE spdlog::spdlog ${CMAKE_DL_LIBS} ${CMAKE_THREAD_LIBS_INIT} ${OpenCV_LIBS} ${Boost_LIBRARIES})
