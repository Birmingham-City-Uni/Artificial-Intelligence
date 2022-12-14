cmake_minimum_required (VERSION 3.8)
project (ArtificialIntelligenceDLL)
set (CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DLOGGING")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -DLOGGING")
file(GLOB_RECURSE SOURCE "include/*.*")

add_library(${PROJECT_NAME} SHARED ${SOURCE})

set_target_properties(${PROJECT_NAME}
  PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../library_binaries/lib"
  LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../library_binaries/lib"
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../library_binaries/bin"
)

function (SetFolder src dst var )
    FILE(GLOB src
    ${PROJECT_SOURCE_DIR}/${var}
    )
    SOURCE_GROUP(${dst} FILES ${src})
endfunction()

SetFolder(BT, bt include/bt/*/*.*)
SetFolder(BT, bt include/bt/*.*)
SetFolder(FSM, fsm include/fsm/*.*)
SetFolder(PATHFINDING, pathfinding include/pathfinding/*.*)
SetFolder(MATH, math include/math/*.*)
