@echo off

REM Crear directorio de construcción
if not exist build mkdir build
cd build

REM Configurar con CMake
cmake ..

REM Compilar
cmake --build . --config Release

echo Compilacion completada. Ejecutable en build/bin/
pause