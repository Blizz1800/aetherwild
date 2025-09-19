cmake_minimum_required(VERSION 4.1.1)
project(Aetherwild VERSION 1.0.0)

# Configuración del estándar C
set(CMAKE_C_STANDARD 23)

# Configuración del estándar C++
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BUILD_SHARED_LIBS ON)

# Configuración de directorios
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Incluir directorios
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/src)

# Buscar SDL3
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL3 REQUIRED sdl3)
pkg_check_modules(SDL_IMAGE REQUIRED sdl3-image)
pkg_check_modules(SDL_TTF REQUIRED sdl3-ttf)
pkg_check_modules(SDL_MIXER REQUIRED SDL_mixer)

# Recopilar archivos fuente
file(GLOB_RECURSE SOURCES 
    "src/*.cpp"
    "src/*.c"
)

message(DEBUG ${SOURCES})

file(GLOB_RECURSE HEADERS 
    "src/*.h"
    "src/*.hpp"
    "include/*.h"
    "include/*.hpp"
)
message(DEBUG ${HEADERS})

# Crear ejecutable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} 
    ${SDL3_LIBRARIES}
    ${SDL_IMAGE_LIBRARIES}
    ${SDL_TTF_LIBRARIES}
    ${SDL_MIXER_LIBRARIES}
)

target_include_directories(${PROJECT_NAME} PRIVATE 
    ${SDL3_INCLUDE_DIRS}
    ${SDL_IMAGE_INCLUDE_DIRS}
    ${SDL_TTF_INCLUDE_DIRS}
    ${SDL_MIXER_INCLUDE_DIRS}
)

# TODO: Si CMAKE_BUILD_TYPE es "Release" deberia ser -O3
target_compile_options(${PROJECT_NAME} PRIVATE 
    ${SDL3_CFLAGS_OTHER}
    -Wall -Wextra -O2
)

function(copy_dynamic_libraries target)
    if(WIN32)
        # Windows - buscar y copiar DLLs de SDL3
        find_file(SDL_DLL NAMES SDL3.dll PATHS ${SDL3_LIBRARY_DIRS} PATH_SUFFIXES bin)
        find_file(SDL_IMAGE_DLL NAMES SDL3_image.dll PATHS ${SDL_IMAGE_LIBRARY_DIRS} PATH_SUFFIXES bin)
        find_file(SDL_TTF_DLL NAMES SDL3_ttf.dll PATHS ${SDL_TTF_LIBRARY_DIRS} PATH_SUFFIXES bin)
        find_file(SDL_MIXER_DLL NAMES SDL_mixer.dll PATHS ${SDL_MIXER_LIBRARY_DIRS} PATH_SUFFIXES bin)

        if(SDL_DLL)
            add_custom_command(TARGET ${target} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SDL_DLL} $<TARGET_FILE_DIR:${target}>)
        endif()
        if(SDL_IMAGE_DLL)
            add_custom_command(TARGET ${target} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SDL_IMAGE_DLL} $<TARGET_FILE_DIR:${target}>)
        endif()
        if(SDL_TTF_DLL)
            add_custom_command(TARGET ${target} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SDL_TTF_DLL} $<TARGET_FILE_DIR:${target}>)
        endif()
        if(SDL_MIXER_DLL)
            add_custom_command(TARGET ${target} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SDL_MIXER_DLL} $<TARGET_FILE_DIR:${target}>)
        endif()
        
    elseif(APPLE)
        # macOS - buscar y copiar dylibs de SDL3
        foreach(lib ${SDL_LIBRARIES} ${SDL_IMAGE_LIBRARIES} ${SDL_TTF_LIBRARIES} ${SDL_MIXER_LIBRARIES})
            get_filename_component(lib_name ${lib} NAME_WE)
            find_library(${lib_name}_DYLIB NAMES ${lib_name}.dylib PATHS ${SDL3_LIBRARY_DIRS} ${SDL_IMAGE_LIBRARY_DIRS} ${SDL_TTF_LIBRARY_DIRS} ${SDL_MIXER_LIBRARY_DIRS})
            if(${lib_name}_DYLIB)
                add_custom_command(TARGET ${target} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${${lib_name}_DYLIB} $<TARGET_FILE_DIR:${target}>)
            endif()
        endforeach()
        
    else()
        # Linux - buscar y copiar .so files de SDL3
        foreach(lib_dir ${SDL3_LIBRARY_DIRS} ${SDL_IMAGE_LIBRARY_DIRS} ${SDL_TTF_LIBRARY_DIRS} ${SDL_MIXER_LIBRARY_DIRS})
            file(GLOB SO_FILES "${lib_dir}/*.so*")
            foreach(so_file ${SO_FILES})
                get_filename_component(so_name ${so_file} NAME)
                if(so_name MATCHES "^lib(SDL3|SDL_image|SDL_ttf|SDL_mixer)")
                    add_custom_command(TARGET ${target} POST_BUILD
                        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${so_file} $<TARGET_FILE_DIR:${target}>)
                endif()
            endforeach()
        endforeach()
    endif()
endfunction()

copy_dynamic_libraries(${PROJECT_NAME})

# Copiar assets al directorio de salida
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E remove_directory $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
)

if(UNIX AND NOT APPLE)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INSTALL_RPATH "$ORIGIN"
        BUILD_WITH_INSTALL_RPATH TRUE
    )
elseif(APPLE)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INSTALL_RPATH "@executable_path"
        BUILD_WITH_INSTALL_RPATH TRUE
    )
endif()

# Configuración para diferentes sistemas operativos
if(WIN32)
    # Configuración específica para Windows
    target_compile_definitions(${PROJECT_NAME} PRIVATE WINDOWS)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        VS_DEBUGGER_WORKING_DIRECTORY $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )

    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        set_target_properties(${PROJECT_NAME} PROPERTIES 
        WIN32_EXECUTABLE TRUE)
    endif()
elseif(APPLE)
    # Configuración específica para macOS
    target_compile_definitions(${PROJECT_NAME} PRIVATE MACOS)
else()
    # Configuración específica para Linux
    target_compile_definitions(${PROJECT_NAME} PRIVATE LINUX)
endif()

add_custom_target(clean-libs
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    COMMENT "Cleaning copied libraries and executables"
)

message(STATUS "SDL3 Libraries: ${SDL3_LIBRARIES}")
message(STATUS "SDL3 Library Dirs: ${SDL3_LIBRARY_DIRS}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Output directory: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
