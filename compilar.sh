#!/bin/bash
echo "Compilación de todos los archivos con terminación .cpp"
echo "Nota: El programa de Salida se llama:\"Chat\""
echo "Compilando...(Si hay errores, se mostrarán abajo)"
g++ *cpp `wx-config --cxxflags --libs` -o Chat.out -std=c++11 -pthread
