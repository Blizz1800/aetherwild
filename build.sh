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

# Si el primer argumento es 'run', ejecutar el binario
if [[ "$1" == "run" ]]; then
    cd bin
    echo "Ejecutando el programa..."
    ./Aetherwild
fi