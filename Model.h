#pragma once

#include "Mesh.h"
#include <string>
#include <vector>

class VulkanDevice;

class Model {
public:
	Model(VulkanDevice* device, VkCommandPool commandPool, const std::string& filepath);
	~Model();

	void bind(VkCommandBuffer commandBuffer);
	void draw(VkCommandBuffer commandBuffer);

	uint32_t getIndexCount() const { return static_cast<uint32_t>(indices.size()); }
	uint32_t getVertexCount() const { return static_cast<uint32_t>(vertices.size()); }

private:
	void loadModel(const std::string& filepath);
	void createVertexBuffer();
	void createIndexBuffer();

	VulkanDevice* device;
	VkCommandPool commandPool;

	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;

	VkBuffer vertexBuffer;
	VkDeviceMemory vertexBufferMemory;

	VkBuffer indexBuffer;
	VkDeviceMemory indexBufferMemory;
};