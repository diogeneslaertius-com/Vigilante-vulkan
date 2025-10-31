#!/bin/bash

# Компиляция шейдеров с помощью glslc (часть Vulkan SDK)

echo "Compiling shaders..."

# Проверка наличия glslc
if ! command -v glslc &> /dev/null
then
    echo "glslc not found. Please install Vulkan SDK."
    exit 1
fi

# Компиляция vertex shader
glslc shader.vert -o vert.spv
if [ $? -eq 0 ]; then
    echo "✓ Vertex shader compiled successfully"
else
    echo "✗ Failed to compile vertex shader"
    exit 1
fi

# Компиляция fragment shader
glslc shader.frag -o frag.spv
if [ $? -eq 0 ]; then
    echo "✓ Fragment shader compiled successfully"
else
    echo "✗ Failed to compile fragment shader"
    exit 1
fi

echo "All shaders compiled successfully!"