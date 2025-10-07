#include "Mesh.h"
#include "VulkanDevice.h"
#include <stdexcept>

Mesh::Mesh(VulkanDevice* device, VkCommandPool commandPool) 
    : device(device), commandPool(commandPool) {
    generateCube();
    createVertexBuffer();
    createIndexBuffer();
}

Mesh::~Mesh() {
    vkDestroyBuffer(device->getDevice(), indexBuffer, nullptr);
    vkFreeMemory(device->getDevice(), indexBufferMemory, nullptr);
    vkDestroyBuffer(device->getDevice(), vertexBuffer, nullptr);
    vkFreeMemory(device->getDevice(), vertexBufferMemory, nullptr);
}

void Mesh::generateCube() {
    // Куб с нормалями и цветами (24 вершины для корректных нормалей на гранях)
    vertices = {
        // Front face (Z+) - Красный
        {{-1.0f, -1.0f,  1.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.3f, 0.3f}},
        {{ 1.0f, -1.0f,  1.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.3f, 0.3f}},
        {{ 1.0f,  1.0f,  1.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.3f, 0.3f}},
        {{-1.0f,  1.0f,  1.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.3f, 0.3f}},
        
        // Back face (Z-) - Зеленый
        {{ 1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, -1.0f}, {0.3f, 1.0f, 0.3f}},
        {{-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, -1.0f}, {0.3f, 1.0f, 0.3f}},
        {{-1.0f,  1.0f, -1.0f}, {0.0f, 0.0f, -1.0f}, {0.3f, 1.0f, 0.3f}},
        {{ 1.0f,  1.0f, -1.0f}, {0.0f, 0.0f, -1.0f}, {0.3f, 1.0f, 0.3f}},
        
        // Top face (Y+) - Синий
        {{-1.0f,  1.0f,  1.0f}, {0.0f, 1.0f, 0.0f}, {0.3f, 0.3f, 1.0f}},
        {{ 1.0f,  1.0f,  1.0f}, {0.0f, 1.0f, 0.0f}, {0.3f, 0.3f, 1.0f}},
        {{ 1.0f,  1.0f, -1.0f}, {0.0f, 1.0f, 0.0f}, {0.3f, 0.3f, 1.0f}},
        {{-1.0f,  1.0f, -1.0f}, {0.0f, 1.0f, 0.0f}, {0.3f, 0.3f, 1.0f}},
        
        // Bottom face (Y-) - Желтый
        {{-1.0f, -1.0f, -1.0f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f, 0.3f}},
        {{ 1.0f, -1.0f, -1.0f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f, 0.3f}},
        {{ 1.0f, -1.0f,  1.0f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f, 0.3f}},
        {{-1.0f, -1.0f,  1.0f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f, 0.3f}},
        
        // Right face (X+) - Фиолетовый
        {{ 1.0f, -1.0f,  1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.3f, 1.0f}},
        {{ 1.0f, -1.0f, -1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.3f, 1.0f}},
        {{ 1.0f,  1.0f, -1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.3f, 1.0f}},
        {{ 1.0f,  1.0f,  1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.3f, 1.0f}},
        
        // Left face (X-) - Голубой
        {{-1.0f, -1.0f, -1.0f}, {-1.0f, 0.0f, 0.0f}, {0.3f, 1.0f, 1.0f}},
        {{-1.0f, -1.0f,  1.0f}, {-1.0f, 0.0f, 0.0f}, {0.3f, 1.0f, 1.0f}},
        {{-1.0f,  1.0f,  1.0f}, {-1.0f, 0.0f, 0.0f}, {0.3f, 1.0f, 1.0f}},
        {{-1.0f,  1.0f, -1.0f}, {-1.0f, 0.0f, 0.0f}, {0.3f, 1.0f, 1.0f}}
    };
    
    // Индексы для всех граней
    indices = {
        0, 1, 2, 2, 3, 0,       // Front
        4, 5, 6, 6, 7, 4,       // Back
        8, 9, 10, 10, 11, 8,    // Top
        12, 13, 14, 14, 15, 12, // Bottom
        16, 17, 18, 18, 19, 16, // Right
        20, 21, 22, 22, 23, 20  // Left
    };
}

void Mesh::createVertexBuffer() {
    VkDeviceSize bufferSize = sizeof(vertices[0]) * vertices.size();
    
    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;
    device->createBuffer(bufferSize, 
                        VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                        stagingBuffer, stagingBufferMemory);
    
    void* data;
    vkMapMemory(device->getDevice(), stagingBufferMemory, 0, bufferSize, 0, &data);
    memcpy(data, vertices.data(), (size_t)bufferSize);
    vkUnmapMemory(device->getDevice(), stagingBufferMemory);
    
    device->createBuffer(bufferSize,
                        VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
                        VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
                        vertexBuffer, vertexBufferMemory);
    
    device->copyBuffer(stagingBuffer, vertexBuffer, bufferSize, commandPool);
    
    vkDestroyBuffer(device->getDevice(), stagingBuffer, nullptr);
    vkFreeMemory(device->getDevice(), stagingBufferMemory, nullptr);
}

void Mesh::createIndexBuffer() {
    VkDeviceSize bufferSize = sizeof(indices[0]) * indices.size();
    
    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;
    device->createBuffer(bufferSize,
                        VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                        stagingBuffer, stagingBufferMemory);
    
    void* data;
    vkMapMemory(device->getDevice(), stagingBufferMemory, 0, bufferSize, 0, &data);
    memcpy(data, indices.data(), (size_t)bufferSize);
    vkUnmapMemory(device->getDevice(), stagingBufferMemory);
    
    device->createBuffer(bufferSize,
                        VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
                        VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
                        indexBuffer, indexBufferMemory);
    
    device->copyBuffer(stagingBuffer, indexBuffer, bufferSize, commandPool);
    
    vkDestroyBuffer(device->getDevice(), stagingBuffer, nullptr);
    vkFreeMemory(device->getDevice(), stagingBufferMemory, nullptr);
}

void Mesh::bind(VkCommandBuffer commandBuffer) {
    VkBuffer vertexBuffers[] = {vertexBuffer};
    VkDeviceSize offsets[] = {0};
    vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers, offsets);
    vkCmdBindIndexBuffer(commandBuffer, indexBuffer, 0, VK_INDEX_TYPE_UINT16);
}

void Mesh::draw(VkCommandBuffer commandBuffer) {
    vkCmdDrawIndexed(commandBuffer, static_cast<uint32_t>(indices.size()), 1, 0, 0, 0);
}