#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include <glm/glm.hpp>

#include <vector>
#include <memory>
#include <optional>

class VulkanDevice;
class VulkanSwapchain;
class VulkanPipeline;
class Camera;
class Mesh;

class VulkanApp {
public:
    VulkanApp();
    ~VulkanApp();

    void run();

private:
    // Инициализация
    void initWindow();
    void initVulkan();
    void createInstance();
    void setupDebugMessenger();
    void createSurface();
    void createSyncObjects();
    void createCommandPool();
    void createCommandBuffers();
    void createUniformBuffers();
    void createDescriptorPool();
    void createDescriptorSets();
    
    // Основной цикл
    void mainLoop();
    void drawFrame();
    void updateUniformBuffer(uint32_t currentImage);
    
    // Очистка
    void cleanup();
    
    // Callbacks
    static void framebufferResizeCallback(GLFWwindow* window, int width, int height);
    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
    static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
    
    // Вспомогательные методы
    void recreateSwapchain();
    void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
    
    // Validation layers
    bool checkValidationLayerSupport();
    std::vector<const char*> getRequiredExtensions();
    
    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT messageType,
        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
        void* pUserData);

    // Константы
    const uint32_t WIDTH = 1280;
    const uint32_t HEIGHT = 720;
    const int MAX_FRAMES_IN_FLIGHT = 2;
    
    #ifdef NDEBUG
        const bool enableValidationLayers = false;
    #else
        const bool enableValidationLayers = true;
    #endif
    
    const std::vector<const char*> validationLayers = {
        "VK_LAYER_KHRONOS_validation"
    };
    
    const std::vector<const char*> deviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };
    
    // GLFW
    GLFWwindow* window;
    
    // Vulkan основные объекты
    VkInstance instance;
    VkDebugUtilsMessengerEXT debugMessenger;
    VkSurfaceKHR surface;
    
    std::unique_ptr<VulkanDevice> device;
    std::unique_ptr<VulkanSwapchain> swapchain;
    std::unique_ptr<VulkanPipeline> pipeline;
    
    // Команды
    VkCommandPool commandPool;
    std::vector<VkCommandBuffer> commandBuffers;
    
    // Синхронизация
    std::vector<VkSemaphore> imageAvailableSemaphores;
    std::vector<VkSemaphore> renderFinishedSemaphores;
    std::vector<VkFence> inFlightFences;
    uint32_t currentFrame = 0;
    
    // Uniform buffers
    struct UniformBufferObject {
        alignas(16) glm::mat4 model;
        alignas(16) glm::mat4 view;
        alignas(16) glm::mat4 proj;
    };
    
    struct LightingUBO {
        alignas(16) glm::vec3 lightPos;
        alignas(16) glm::vec3 viewPos;
        alignas(16) glm::vec3 lightColor;
    };
    
    std::vector<VkBuffer> uniformBuffers;
    std::vector<VkDeviceMemory> uniformBuffersMemory;
    std::vector<void*> uniformBuffersMapped;
    
    std::vector<VkBuffer> lightingBuffers;
    std::vector<VkDeviceMemory> lightingBuffersMemory;
    std::vector<void*> lightingBuffersMapped;
    
    VkDescriptorPool descriptorPool;
    VkDescriptorSetLayout descriptorSetLayout;
    std::vector<VkDescriptorSet> descriptorSets;
    
    // Геометрия и камера
    std::unique_ptr<Mesh> mesh;
    std::unique_ptr<Camera> camera;
    
    // Управление
    bool framebufferResized = false;
    bool mousePressed = false;
    double lastMouseX = 0.0;
    double lastMouseY = 0.0;
};