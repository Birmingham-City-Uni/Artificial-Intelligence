cmake_minimum_required (VERSION 3.8)
project(ArtificialIntelligence VERSION 1.0)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
set (CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DLOGGING")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -DLOGGING")

add_subdirectory("${PROJECT_SOURCE_DIR}/external/ai-library")

find_package(SDL2_IMAGE REQUIRED PATHS ${PROJECT_SOURCE_DIR}/library_binaries)
find_package(SDL2_MIXER REQUIRED PATHS ${PROJECT_SOURCE_DIR}/library_binaries)
find_package(SDL2_TTF REQUIRED PATHS ${PROJECT_SOURCE_DIR}/library_binaries)
find_package(SDL2 REQUIRED PATHS ${PROJECT_SOURCE_DIR}/library_binaries)

include_directories(${PROJECT_SOURCE_DIR}/external/ai/include)
include_directories(${PROJECT_SOURCE_DIR}/library_binaries/include/SDL2)

file(GLOB_RECURSE SOURCE "src/*.*")
file(GLOB DLLS "library_binaries/bin/*.dll")
    
add_executable (${PROJECT_NAME} ${SOURCE})

set(SDL2_IMAGE_LIBRARIES "${PROJECT_SOURCE_DIR}/library_binaries/lib/SDL2_image.lib")
set(SDL2_MIXER_LIBRARIES "${PROJECT_SOURCE_DIR}/library_binaries/lib/SDL2_mixer.lib")
set(SDL2_TTF_LIBRARIES "${PROJECT_SOURCE_DIR}/library_binaries/lib/SDL2_ttf.lib")
set(LIBS "${PROJECT_SOURCE_DIR}/library_binaries/lib/ArtificialIntelligenceDLL.lib") 

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/library_binaries/bin"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>)

target_link_libraries(${PROJECT_NAME} ${SDL2_IMAGE_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${SDL2_MIXER_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${SDL2_TTF_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${LIBS})

function (SetFolder src dst var )
    FILE(GLOB src
    ${PROJECT_SOURCE_DIR}/${var}
    )
    SOURCE_GROUP(${dst} FILES ${src})
endfunction()

SetFolder(ENGINE_FILES, engine src/engine/*.*)
SetFolder(UI, ui src/ui/*.*)