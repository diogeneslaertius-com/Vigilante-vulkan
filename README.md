# Vulkan Portfolio Renderer


![Demo Screenshot](demo/sh.gif)
Минимальный, но функциональный 3D-рендер на Vulkan для демонстрации навыков рендеринг-инженера.

## Особенности

- ✅ Полная инициализация Vulkan (Instance, Physical Device, Logical Device, Swapchain)
- ✅ 3D-рендеринг индексированного куба
- ✅ Blinn-Phong освещение (ambient + diffuse + specular)
- ✅ Управляемая камера (мышь для вращения, колесо для зума)
- ✅ Индексированные буферы для оптимизации
- ✅ Uniform buffers для матриц и параметров освещения
- ✅ Кроссплатформенность (Windows/Linux)

## Архитектура

```
src/
├── main.cpp              # Точка входа, основной цикл
├── VulkanApp.h/cpp       # Главный класс приложения
├── VulkanDevice.h/cpp    # Абстракция устройства Vulkan
├── VulkanSwapchain.h/cpp # Управление swapchain
├── VulkanPipeline.h/cpp  # Графический pipeline
├── VulkanBuffer.h/cpp    # Хелпер для буферов
├── Camera.h/cpp          # Камера с управлением
└── Mesh.h/cpp            # Геометрия куба

shaders/
├── shader.vert           # Vertex shader
├── shader.frag           # Fragment shader
└── compile.sh            # Скрипт компиляции шейдеров
```

## Требования

- **Vulkan SDK** 1.2+: [https://vulkan.lunarg.com/](https://vulkan.lunarg.com/)
- **GLFW** 3.3+: для создания окна
- **GLM**: математическая библиотека
- **CMake** 3.15+
- **C++17** компилятор

### Установка зависимостей

**Ubuntu/Debian:**
```bash
sudo apt install vulkan-sdk libglfw3-dev libglm-dev cmake g++
```

**Fedora:**
```bash
sudo dnf install vulkan-loader-devel vulkan-validation-layers-devel glfw-devel glm-devel cmake gcc-c++
```

**Windows:**
- Скачай и установи Vulkan SDK
- GLFW и GLM будут загружены через CMake FetchContent

## Сборка

```bash
# Склонировать репозиторий
git clone https://github.com/yourusername/vulkan-portfolio-renderer.git
cd vulkan-portfolio-renderer

# Компилировать шейдеры
cd shaders
./compile.sh  # Linux/Mac
compile.bat   # Windows
cd ..

# Сборка проекта
mkdir build && cd build
cmake ..
cmake --build . --config Release

# Запуск
./VulkanDemo          # Linux/Mac
.\Release\VulkanDemo.exe  # Windows
```

## Управление

- **ЛКМ + движение мыши**: вращение камеры вокруг объекта
- **Колесо мыши**: приближение/отдаление
- **ESC**: выход

## Технические детали

### Vulkan Pipeline
- **Vertex Input**: Position (vec3) + Normal (vec3) + Color (vec3)
- **Topology**: Triangle List с индексами
- **Rasterization**: Front face culling, fill mode
- **Depth Test**: Включен (depth buffer format D32_SFLOAT)

### Освещение
Blinn-Phong модель с параметрами:
- Ambient: 0.1
- Diffuse: от направленного света
- Specular: с shininess = 32

### Uniform Buffers
```glsl
// UBO для матриц
layout(binding = 0) uniform UniformBufferObject {
    mat4 model;
    mat4 view;
    mat4 proj;
} ubo;

// UBO для освещения
layout(binding = 1) uniform LightingUBO {
    vec3 lightPos;
    vec3 viewPos;
    vec3 lightColor;
} light;
```

## Оптимизации

1. **Индексированная геометрия**: 24 вершины вместо 36 для куба
2. **Один draw call**: вся геометрия в одном вызове
3. **Uniform buffers**: динамическое обновление без пересоздания буферов
4. **Double buffering**: синхронизация с 2 frame-in-flight

## Расширение проекта

Идеи для дальнейшего развития:

- [ ] Загрузка моделей из `.obj` файлов
- [ ] Поддержка текстур через `stb_image`
- [ ] Shadow mapping для теней
- [ ] Normal mapping для детализации
- [ ] PBR (Physically Based Rendering)
- [ ] Post-processing эффекты
- [ ] ImGui для отладочного UI

## Лицензия

MIT License - смотри [LICENSE](LICENSE)

## Автор

Создано как портфолио-проект для демонстрации навыков работы с Vulkan API.

## Ссылки

- [Vulkan Tutorial](https://vulkan-tutorial.com/)
- [Vulkan Spec](https://www.khronos.org/registry/vulkan/)
- [Sascha Willems Examples](https://github.com/SaschaWillems/Vulkan)
