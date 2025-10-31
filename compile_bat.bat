@echo off
echo Compiling shaders...

REM Компиляция vertex shader
glslc shader.vert -o vert.spv
if %errorlevel% neq 0 (
    echo Failed to compile vertex shader
    exit /b 1
)
echo Vertex shader compiled successfully

REM Компиляция fragment shader
glslc shader.frag -o frag.spv
if %errorlevel% neq 0 (
    echo Failed to compile fragment shader
    exit /b 1
)
echo Fragment shader compiled successfully

echo All shaders compiled successfully!
pause