#pragma once

#include <vulkan/vulkan.h>
#include <optional>
struct QueueFamilyIndices {
		std::optional<uint32_t> graphicsFamily;
		std::optional<uint32_t> presentFamily; 
		//this is where we draw , this is where they lighting  
		bool isComplete();
};
int ratePhysicalDevice(VkPhysicalDevice device);

QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR surface);
