#!/bin/bash

# Crear directorio de construcción
mkdir -p build
cd build

# Configurar con CMake
cmake .. -DCMAKE_BUILD_TYPE=Release

# Compilar
make clean -j$(nproc)
make -j$(nproc)

echo "Compilación completada. Ejecutable en build/bin/"