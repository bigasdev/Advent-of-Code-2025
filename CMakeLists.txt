cmake_minimum_required(VERSION 3.28.3)
project(fte_project LANGUAGES CXX)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "" FORCE)
endif()

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG   ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/release)

find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)
find_package(SDL2_mixer CONFIG REQUIRED)

set(SRC_DIRS
    src/imgui
    src/core
    src/renderer
    src/res
    src/app
    src/tools
)

foreach(dir ${SRC_DIRS})
    file(GLOB TMP_SRC "${dir}/*.cpp")
    list(APPEND SOURCES ${TMP_SRC})
endforeach()

set(ICON_FILE "")
if(WIN32)
    set(ICON_FILE "${CMAKE_SOURCE_DIR}/res/icon/icon.res")
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_executable(${PROJECT_NAME}
        ${SOURCES}
        ${ICON_FILE}
    )
else()
    add_executable(${PROJECT_NAME} WIN32
        ${SOURCES}
        ${ICON_FILE}
    )
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE
    SDL2::SDL2
    SDL2::SDL2main
    SDL2_image::SDL2_image
    SDL2_ttf::SDL2_ttf
    SDL2_mixer::SDL2_mixer
)


include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/include
)



target_compile_definitions(${PROJECT_NAME} PRIVATE
    WIN_WIDTH=1024
    WIN_HEIGHT=768
    $<$<CONFIG:Debug>:_DEBUG>
)

target_compile_options(${PROJECT_NAME} PRIVATE
    -Wno-narrowing
    $<$<CONFIG:Debug>:-O0 -g -mconsole>
    $<$<CONFIG:Release>:-O3 -s -finline-functions -flto>
)

if(MINGW)
    target_link_options(${PROJECT_NAME} PRIVATE -static-libstdc++ -static-libgcc)
    target_link_libraries(${PROJECT_NAME} PRIVATE ole32 opengl32)
endif()


file(COPY ${CMAKE_SOURCE_DIR}/res DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG})


if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    if(WIN32 AND MINGW)
      target_link_libraries(${PROJECT_NAME} PRIVATE psapi pdh)
    endif()
endif()
