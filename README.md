# Aetherwild

Un juego estilo Pokémon desarrollado en C++ usando SDL3, con arquitectura modular y soporte para compilación multiplataforma.

## 📋 Tabla de Contenidos

- [Características](#características)
- [Arquitectura del Proyecto](#arquitectura-del-proyecto)
- [Requisitos del Sistema](#requisitos-del-sistema)
- [Instalación](#instalación)
- [Compilación](#compilación)
- [Estructura de Archivos](#estructura-de-archivos)
- [Configuración](#configuración)
- [Scripts Disponibles](#scripts-disponibles)
- [Desarrollo](#desarrollo)
- [Contribución](#contribución)

## ✨ Características

- **Motor gráfico moderno**: SDL3 con soporte para gráficos 2D avanzados
- **Arquitectura modular**: Separación clara entre sistemas (gráficos, entrada, entidades, mundo)
- **Compilación multiplataforma**: Windows, Linux y macOS
- **Bibliotecas dinámicas**: Distribución automática de dependencias
- **Estándares modernos**: C++26 y C23
- **Sistema de estados**: Gestión eficiente de diferentes pantallas del juego
- **Gestión de recursos**: Carga y manejo optimizado de sprites, sonidos y mapas

## 🏗️ Arquitectura del Proyecto

El proyecto sigue una arquitectura modular basada en sistemas independientes:

```
aetherwild/
├── 📁 src/                     # Código fuente principal
│   ├── 📄 main.cpp             # Punto de entrada del juego
│   ├── 📁 Game/                # Sistema principal del juego
│   │   ├── 📁 States/          # Estados del juego (menú, batalla, mundo)
│   │   ├── Game.h/cpp         # Clase principal del juego
│   │   ├── GameState.hpp      # Clase base para los estados del juego
│   │   └── StateManager.hpp   # Gestor de estados
│   ├── 📁 Graphics/            # Sistema de renderizado
│   │   ├── Texture.h/cpp      # Gestión de texturas
│   │   └── Sprite.h/cpp       # Sistema de sprites
│   ├── 📁 Input/               # Sistema de entrada
│   │   ├── InputEvent.hpp     # Structs para los eventos input
│   │   └── InputManager.h/cpp # Gestión de teclado/mouse/gamepad
│   ├── 📁 Entities/            # Entidades del juego
│   │   ├── Entity.hpp         # Clase base para entidades
│   │   ├── Player.h/cpp       # Jugador
│   │   ├── NPC.h/cpp          # Non Player Characters
│   │   └── Monster.h/cpp      # Sistema de Pokémon
│   ├── 📁 World/               # Sistema de mundo
│   │   ├── Map.h/cpp          # Mapas y tiles
│   │   ├── Tile.h/cpp         # Definición de tiles
│   │   └── Collision.h/cpp    # Sistema de colisiones
│   └── 📁 Utils/               # Utilidades
│       ├── Vector2.h/cpp      # Matemáticas vectoriales
│       ├── Timer.h/cpp        # Gestión de tiempo
│       └── Constants.hpp      # Constantes del juego
├── 📁 assets/                  # Recursos del juego
│   ├── 📁 sprites/             # Sprites de personajes y objetos
│   ├── 📁 maps/                # Archivos de mapas
│   ├── 📁 sounds/              # Efectos de sonido y música
│   └── 📁 fonts/               # Fuentes tipográficas
├── 📁 include/                 # Headers adicionales
├── 📁 lib/                     # Bibliotecas externas
└── 📁 build/                   # Archivos de compilación (generado)
    ├── 📁 bin/                 # Ejecutables
    └── 📁 lib/                 # Bibliotecas dinámicas
```

## 💻 Requisitos del Sistema

### Dependencias Principales

- **CMake** 4.1.1 o superior
- **Compilador C++**: GCC 15+, Clang 20+, o MSVC 2022+
- **SDL3**: Biblioteca gráfica principal
- **SDL3_image**: Carga de imágenes
- **SDL3_ttf**: Renderizado de texto
- **SDL3_mixer**: Audio y música

### Sistemas Operativos Soportados

- **Linux**: Ubuntu 22.04+, Fedora 38+, Arch Linux
- **Windows**: Windows 10/11 (MinGW-w64 o MSVC)
- **macOS**: macOS 12+ (Intel y Apple Silicon) \[UNTESTED\]

## 🚀 Instalación

### Linux (Ubuntu/Debian)

```bash
# Instalar dependencias del sistema
sudo apt update
sudo apt install build-essential cmake git pkg-config

# Instalar SDL3 (desde fuentes o repositorios)
sudo apt install libsdl3-dev libsdl3-image-dev libsdl3-ttf-dev libsdl3-mixer-dev

# Clonar el repositorio
git clone https://github.com/tu-usuario/aetherwild.git
cd aetherwild
```

### macOS

```bash
# Instalar Homebrew si no está instalado
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# Instalar dependencias
brew install cmake sdl3 sdl3_image sdl3_ttf sdl3_mixer

# Clonar el repositorio
git clone https://github.com/tu-usuario/aetherwild.git
cd aetherwild
```

### Windows (MinGW)

```bash
# Instalar MSYS2 desde https://www.msys2.org/
# En terminal MSYS2:
pacman -S mingw-w64-x86_64-toolchain mingw-w64-x86_64-cmake
pacman -S mingw-w64-x86_64-sdl3 mingw-w64-x86_64-sdl3-image mingw-w64-x86_64-sdl3-ttf mingw-w64-x86_64-SDL_mixer

# Clonar el repositorio
git clone https://github.com/tu-usuario/aetherwild.git
cd aetherwild
```

## 🔨 Compilación

### Compilación Básica

```bash
# Crear directorio de compilación
mkdir build && cd build

# Configurar con CMake
cmake -DCMAKE_BUILD_TYPE=Release ..

# Compilar
make -j$(nproc)  # Linux/macOS
# o
cmake --build . --config Release  # Windows
```

### Usando Scripts de Automatización

```bash
# Compilación rápida
./build.sh

# Compilación con limpieza previa
./build.sh clean

# Compilación en modo debug
./build.sh debug
```

## 📁 Estructura de Archivos

### Archivos de Configuración

#### `CMakeLists.txt`

Archivo principal de configuración de CMake con:

- Configuración de estándares C++26/C23
- Detección automática de SDL3
- Configuración de bibliotecas dinámicas
- Soporte multiplataforma
- Copia automática de assets y bibliotecas

#### `build.sh`

Script de compilación automatizada:

```bash
#!/bin/bash
# Compilación con detección automática de errores
# Soporte para diferentes modos (Release/Debug)
# Limpieza automática de builds anteriores
```
