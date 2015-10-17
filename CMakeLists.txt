cmake_minimum_required(VERSION 2.8)
project(boost_mpi_examples)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

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

#set(utils_src
#
#)

foreach(example ${examples})
    list(APPEND ${example}_src ${example}.cpp)
    add_executable(${example}
            ${${example}_src}
#            ${utils_src}
    )
endforeach()

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost REQUIRED mpi serialization)
include_directories(${Boost_INCLUDE_DIRS})
foreach(example ${examples})
    target_link_libraries(${example} ${Boost_LIBRARIES})
endforeach()

find_package(MPI REQUIRED)
include_directories(${MPI_CXX_INCLUDE_PATH})
foreach(example ${examples})
    target_link_libraries(${example} ${MPI_CXX_LIBRARIES})
endforeach()