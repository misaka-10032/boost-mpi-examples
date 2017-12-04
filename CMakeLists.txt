# -*- mode: cmake -*-
#
# [CMake](http://www.cmake.org/) Configuration
#
# Adapted from https://github.com/misaka-10032/boost-mpi-examples
#
cmake_minimum_required(VERSION 2.8)
project(BoostMPI-examples  CXX)

#SET(CMAKE_VERBOSE_MAKEFILE on )
#SET(CMAKE_BUILD_TYPE       Release)
SET(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_FLAGS  "-std=c++11")
#enable_testing()

# List of examples to build
set(examples
  example1-setup
  example2-synccomm
  example3-asynccomm
  example4-broadcast
  example5-gather
  example6-reduce
  example7-reduce
  example8-allreduce
  example9-allreduce
  example10-communicator
  example11-skeleton
  example12-datatype
  )

#====== pthreads =====
find_package (Threads)
list(APPEND EXTRALIBS ${CMAKE_THREAD_LIBS_INIT})

#====== [Boost](http://www.boost.org/) ======
# Note: uBlas is part of the 'numeric' library and is NOT a compiled library
set(Boost_USE_STATIC_LIBS    OFF)
set(Boost_USE_MULTITHREADED  ON)
set(Boost_USE_STATIC_RUNTIME OFF)
#add_definitions( -DNDEBUG -DBOOST_UBLAS_NDEBUG )
find_package(Boost COMPONENTS mpi serialization random program_options timer system unit_test_framework REQUIRED)
#message( INFO "Boost_INCLUDE_DIRS = '${Boost_INCLUDE_DIRS}'" )
#message( INFO "Boost_LIBRARIES = '${Boost_LIBRARIES}'"  )
include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
list(APPEND EXTRALIBS      ${Boost_LIBRARIES})

#==== MPI ====
find_package(MPI REQUIRED)
# set_property( DIRECTORY PROPERTY COMPILE_DEFINITIONS ${MPI_CXX_COMPILE_FLAGS} )
include_directories(SYSTEM ${MPI_CXX_INCLUDE_PATH})
list(APPEND EXTRALIBS ${MPI_CXX_LIBRARIES})

#======================================
#============ Let's go ================
#======================================
set(example12-datatype_HEADERS GpsPosition.h)
foreach(example ${examples})
  list(APPEND ${example}_src ${example}.cpp)
  add_executable(${example}
    ${${example}_src}
    )
  target_link_libraries(${example} ${EXTRALIBS})
endforeach()
