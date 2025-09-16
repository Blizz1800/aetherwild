cmake_minimum_required(VERSION 4.1.1)
project(Arkadia VERSION 1.0.0)

# Configuración del estándar C
set(CMAKE_C_STANDARD 23)

# Configuración del estándar C++
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Configuración de directorios
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Incluir directorios
include_directories(${CMAKE_SOURCE_DIR}/include/**)
include_directories(${CMAKE_SOURCE_DIR}/src/**)

# Buscar SDL3
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL3 REQUIRED sdl3)
pkg_check_modules(SDL_IMAGE REQUIRED SDL_image)
pkg_check_modules(SDL_TTF REQUIRED SDL_ttf)
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

# Enlazar bibliotecas
target_link_libraries(${PROJECT_NAME} 
    ${SDL_LIBRARIES}
    ${SDL_IMAGE_LIBRARIES}
    ${SDL_TTF_LIBRARIES}
    ${SDL_MIXER_LIBRARIES}
)

# Incluir directorios de SDL3
target_include_directories(${PROJECT_NAME} PRIVATE 
    ${SDL_INCLUDE_DIRS}
    ${SDL_IMAGE_INCLUDE_DIRS}
    ${SDL_TTF_INCLUDE_DIRS}
    ${SDL_MIXER_INCLUDE_DIRS}
)

# Flags de compilación
target_compile_options(${PROJECT_NAME} PRIVATE 
    ${SDL_CFLAGS_OTHER}
    -Wall -Wextra -O2
)

# Copiar assets al directorio de salida
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
)

# Configuración para diferentes sistemas operativos
if(WIN32)
    # Configuración específica para Windows
    target_compile_definitions(${PROJECT_NAME} PRIVATE WINDOWS)
elseif(APPLE)
    # Configuración específica para macOS
    target_compile_definitions(${PROJECT_NAME} PRIVATE MACOS)
else()
    # Configuración específica para Linux
    target_compile_definitions(${PROJECT_NAME} PRIVATE LINUX)
endif()