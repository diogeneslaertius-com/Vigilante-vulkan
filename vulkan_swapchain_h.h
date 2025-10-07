#pragma once

#include "VulkanDevice.h"
#include <vulkan/vulkan.h>
#include <vector>

class VulkanSwapchain {
public:
    VulkanSwapchain(VulkanDevice* device, VkSurfaceKHR surface, 
                    uint32_t width, uint32_t height);
    ~VulkanSwapchain();
    
    void recreate(uint32_t width, uint32_t height);
    
    VkSwapchainKHR getSwapchain() const { return swapchain; }
    VkFormat getImageFormat() const { return swapchainImageFormat; }
    VkExtent2D getExtent() const { return swapchainExtent; }
    const std::vector<VkImageView>& getImageViews() const { return swapchainImageViews; }
    const std::vector<VkFramebuffer>& getFramebuffers() const { return swapchainFramebuffers; }
    VkRenderPass getRenderPass() const { return renderPass; }
    
    void createFramebuffers();
    
private:
    void createSwapchain();
    void createImageViews();
    void createRenderPass();
    void createDepthResources();
    
    void cleanup();
    
    VkSurfaceFormatKHR chooseSwapSurfaceFormat(
        const std::vector<VkSurfaceFormatKHR>& availableFormats);
    VkPresentModeKHR chooseSwapPresentMode(
        const std::vector<VkPresentModeKHR>& availablePresentModes);
    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
    VkFormat findDepthFormat();
    VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates,
                                VkImageTiling tiling, VkFormatFeatureFlags features);
    
    VulkanDevice* device;
    VkSurfaceKHR surface;
    uint32_t width;
    uint32_t height;
    
    VkSwapchainKHR swapchain;
    std::vector<VkImage> swapchainImages;
    VkFormat swapchainImageFormat;
    VkExtent2D swapchainExtent;
    std::vector<VkImageView> swapchainImageViews;
    
    VkRenderPass renderPass;
    std::vector<VkFramebuffer> swapchainFramebuffers;
    
    VkImage depthImage;
    VkDeviceMemory depthImageMemory;
    VkImageView depthImageView;
};