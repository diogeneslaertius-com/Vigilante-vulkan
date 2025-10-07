#include "VulkanSwapchain.h"
#include <stdexcept>
#include <algorithm>
#include <limits>

VulkanSwapchain::VulkanSwapchain(VulkanDevice* device, VkSurfaceKHR surface,
                                 uint32_t width, uint32_t height)
    : device(device), surface(surface), width(width), height(height) {
    createSwapchain();
    createImageViews();
    createRenderPass();
    createDepthResources();
    createFramebuffers();
}

VulkanSwapchain::~VulkanSwapchain() {
    