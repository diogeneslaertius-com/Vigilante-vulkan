#pragma once
#include <vulkan/vulkan.h>


class Utils
{
public:
	const char* pGetDebugType(VkDebugUtilsMessageTypeFlagBitsEXT type);
	const char* pGetDebugSeverity(VkDebugUtilsMessageSeverityFlagBitsEXT severity);

};