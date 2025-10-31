#include "Model.h"
#include "tiny_obj_loader.h"

Model::Model(VulkanDevice* device, VkCommandPool commandPool, const std::string& filepath)
	: device(device), commandPool(commandPool) {
	loadModel(filepath);
	createVertexBuffer();
	createIndexBuffer();
}

Model::~Model() {
	vkDestroyBuffer(device->logicalDevice, vertexBuffer, nullptr);
	vkFreeMemory(device->logicalDevice, vertexBufferMemory, nullptr);

	vkDestroyBuffer(device->logicalDevice, indexBuffer, nullptr);
	vkFreeMemory(device->logicalDevice, indexBufferMemory, nullptr);
}

void Model::bind(VkCommandBuffer commandBuffer) {
	VkBuffer vertexBuffers[] = { vertexBuffer };
	VkDeviceSize offsets[] = { 0 };
	vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers, offsets);
	vkCmdBindIndexBuffer(commandBuffer, indexBuffer, 0, VK_INDEX_TYPE_UINT32);
}

void Model::draw(VkCommandBuffer commandBuffer) {
	vkCmdDrawIndexed(commandBuffer, static_cast<uint32_t>(indices.size()), 1, 0, 0, 0);
}

void Model::loadModel(const std::string& filepath) {
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string warn, err;

	if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filepath.c_str())) {
		throw std::runtime_error(warn + err);
	}

	for (const auto& shape : shapes) {
		for (const auto& index : shape.mesh.indices) {
			Vertex vertex{};
			vertex.pos = {
				attrib.vertices[3 * index.vertex_index + 0],
				attrib.vertices[3 * index.vertex_index + 1],
				attrib.vertices[3 * index.vertex_index + 2]
			};
			if (!attrib.normals.empty()) {
				vertex.normal = {
					attrib.normals[3 * index.normal_index + 0],
					attrib.normals[3 * index.normal_index + 1],
					attrib.normals[3 * index.normal_index + 2]
				};
			}
			if (!attrib.texcoords.empty()) {
				vertex.texCoord = {
					attrib.texcoords[2 * index.texcoord_index + 0],
					1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
				};
			}
			vertices.push_back(vertex);
			indices.push_back(static_cast<uint32_t>(indices.size()));
		}
	}
}

void Model::createVertexBuffer() {
	// Здесь создаёшь VkBuffer + VkDeviceMemory для вершин
}

void Model::createIndexBuffer() {
	// Здесь создаёшь VkBuffer + VkDeviceMemory для индексов
}
