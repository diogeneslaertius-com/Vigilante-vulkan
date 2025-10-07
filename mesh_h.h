#pragma once

#include <vulkan/vulkan.h>
#include <glm/glm.hpp>
#include <vector>
#include <array>

struct Vertex {
    glm::vec3 pos;
    glm::vec3 normal;
    glm::vec3 color;
    
    static VkVertexInputBindingDescription getBindingDescription() {
        VkVertexInputBindingDescription bindingDescription{};
        bindingDescription.binding = 0;
        bindingDescription.stride = sizeof(Vertex);
        bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
        return bindingDescription;
    }
    
    static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions() {
        std::array<VkVertexInputAttributeDescription, 3> attributeDescriptions{};
        
        // Position
        attributeDescriptions[0].binding = 0;
        attributeDescriptions[0].location = 0;
        attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[0].offset = offsetof(Vertex, pos);
        
        // Normal
        attributeDescriptions[1].binding = 0;
        attributeDescriptions[1].location = 1;
        attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[1].offset = offsetof(Vertex, normal);
        
        // Color
        attributeDescriptions[2].binding = 0;
        attributeDescriptions[2].location = 2;
        attributeDescriptions[2].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[2].offset = offsetof(Vertex, color);
        
        return attributeDescriptions;
    }
};

class VulkanDevice;

class Mesh {
public:
    Mesh(VulkanDevice* device, VkCommandPool commandPool);
    ~Mesh();
    
    void bind(VkCommandBuffer commandBuffer);
    void draw(VkCommandBuffer commandBuffer);
    
    uint32_t getIndexCount() const { return static_cast<uint32_t>(indices.size()); }
    
private:
    void createVertexBuffer();
    void createIndexBuffer();
    void generateCube();
    
    VulkanDevice* device;
    VkCommandPool commandPool;
    
    std::vector<Vertex> vertices;
    std::vector<uint16_t> indices;
    
    VkBuffer vertexBuffer;
    VkDeviceMemory vertexBufferMemory;
    
    VkBuffer indexBuffer;
    VkDeviceMemory indexBufferMemory;
};