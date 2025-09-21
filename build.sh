#!/bin/bash

# Crear directorio de construcción
mkdir -p build
cd build

# Configurar con CMake
if [[ "$1" == "debug" ]]; then
    cmake .. -DCMAKE_BUILD_TYPE=Debug
else
    cmake .. -DCMAKE_BUILD_TYPE=Release
fi

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