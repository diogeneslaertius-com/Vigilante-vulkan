//#include "pch.h"
#include "VulkanCore.h"

#include <iostream>
#include <vector>
#include <string>


inline void CHECK_VK_RESULT(VkResult result,const std::string msg)
{
	if (result != VK_SUCCESS) {
		throw std::runtime_error("Vulkan call failed with code " + std::to_string(result));
	}
}


VulkanApp::VulkanApp()
{
	
}
	
VulkanApp::~VulkanApp()
{
	vkDestroyInstance(m_Instance, NULL);
}

void VulkanApp::RenderScene()
{

}

void VulkanApp::Init(const char* appName)
{
	CreateInstance(appName);
}

static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCall(
	VkDebugUtilsMessageSeverityFlagBitsEXT severity,
	VkDebugUtilsMessageTypeFlagBitsEXT type,
	const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
	void* pUserData)
{
	std::cout << "Debug Callbacks " << pCallbackData->pMessage << std::endl;
	std::cout << "Severity " << pCallbackData->pMessage << std::endl;
	std::cout << "Debug Callbacks " << pCallbackData->pMessage << std::endl;
	std::cout << "Objects " << pCallbackData->pMessage << std::endl;


}


void VulkanApp::CreateInstance(const char* appName)
{
	std::vector<const char*> Layers =
	{
		"VK_LAYER_KHRONOS_validation"
	};

	std::vector<const char*> Extensions =
	{
		VK_KHR_SURFACE_EXTENSION_NAME,
#if defined (_WIN32)
		"VK_KHR_win32_surface",
#endif // __WIN32__

#if defined (__MACOS__)
		"VK_MVC_macos_surface",
#endif // MAC
#if defined (__linux__)
		"VK_KHR_xcb_surface",
#endif // linux
		VK_EXT_DEBUG_UTILS_EXTENSION_NAME,
		VK_EXT_DEBUG_REPORT_EXTENSION_NAME,

	};
	VkApplicationInfo AppInfo{};
	AppInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	AppInfo.pNext = NULL;
	AppInfo.pApplicationName = appName;
	AppInfo.applicationVersion = VK_MAKE_API_VERSION(0,1,0,0);
	AppInfo.pEngineName = "Renderer engine";
	AppInfo.engineVersion = VK_MAKE_API_VERSION(0,1,0,0);
	AppInfo.apiVersion = VK_API_VERSION_1_0;

	VkInstanceCreateInfo CreateInfo{};
	CreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	CreateInfo.pApplicationInfo = &AppInfo;
	CreateInfo.enabledLayerCount = static_cast<uint32_t>(Layers.size());
	CreateInfo.ppEnabledLayerNames = Layers.data();
	CreateInfo.enabledExtensionCount = static_cast<uint32_t>(Extensions.size());
	CreateInfo.ppEnabledExtensionNames = Extensions.data();


	VkResult result = vkCreateInstance(&CreateInfo,nullptr,&m_Instance);
	CHECK_VK_RESULT(result, "Create Instance");
	std::cout << "Instance is created " << m_Instance << std::endl;

}

void VulkanApp::LayersInfo()
{
	uint32_t layerCount = 0;
	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
	std::vector<VkLayerProperties> layers(layerCount);
	vkEnumerateInstanceLayerProperties(&layerCount, layers.data());

	for (auto& l : layers) 
	{
		std::cout << l.layerName << " - " << l.description << std::endl;
	}
}

void VulkanApp::CreateDebugCallback()
{
	VkDebugUtilsMessengerCreateInfoEXT msgCreateInfo{};
	msgCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	msgCreateInfo.pNext = nullptr;
	msgCreateInfo.pUserData = nullptr;
}