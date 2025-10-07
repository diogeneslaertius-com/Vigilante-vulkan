#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include <optional>

struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;
    
    bool isComplete() const {
        return graphicsFamily.has_value() && presentFamily.has_value();
    }
};

struct SwapchainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

class VulkanDevice {
public:
    VulkanDevice(VkInstance instance, VkSurfaceKHR surface, 
                 const std::vector<const char*>& deviceExtensions,
                 const std::vector<const char*>& validationLayers,
                 bool enableValidationLayers);
    ~VulkanDevice();
    
    // Геттеры
    VkPhysicalDevice getPhysicalDevice() const { return physicalDevice; }
    VkDevice getDevice() const { return device; }
    VkQueue getGraphicsQueue() const { return graphicsQueue; }
    VkQueue getPresentQueue() const { return presentQueue; }
    QueueFamilyIndices getQueueFamilies() const { return queueFamilies; }
    
    // Вспомогательные методы
    SwapchainSupportDetails querySwapchainSupport(VkPhysicalDevice device) const;
    uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties) const;
    
    void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage,
                     VkMemoryPropertyFlags properties,
                     VkBuffer& buffer, VkDeviceMemory& bufferMemory);
    
    void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size,
                   VkCommandPool commandPool);
    
    VkCommandBuffer beginSingleTimeCommands(VkCommandPool commandPool);
    void endSingleTimeCommands(VkCommandBuffer commandBuffer, VkCommandPool commandPool);

private:
    void pickPhysicalDevice();
    void createLogicalDevice();
    
    bool isDeviceSuitable(VkPhysicalDevice device);
    bool checkDeviceExtensionSupport(VkPhysicalDevice device);
    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device) const;
    
    VkInstance instance;
    VkSurfaceKHR surface;
    
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkDevice device;
    
    VkQueue graphicsQueue;
    VkQueue presentQueue;
    
    QueueFamilyIndices queueFamilies;
    
    const std::vector<const char*>& deviceExtensions;
    const std::vector<const char*>& validationLayers;
    bool enableValidationLayers;
};