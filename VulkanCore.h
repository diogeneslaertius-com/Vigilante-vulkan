#pragma once
#include <vulkan/vulkan.h>
#include <iostream>

class VulkanApp
{
public:
	VulkanApp();
	~VulkanApp();
	void RenderScene();
	void Init(const char* appName);
	void CreateDebugCallback();
	void LayersInfo();
private:
	VkInstance m_Instance = NULL;
	std::string m_AppName;
	void CreateInstance(const char* appName);
};