#!/bin/bash

# Crear directorio de construcción
mkdir -p build
cd build

# Configurar con CMake
cmake ..

# Compilar
make -j$(nproc)

echo "Compilación completada. Ejecutable en build/bin/"