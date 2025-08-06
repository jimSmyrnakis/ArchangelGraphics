#pragma once


#include <vulkan/vulkan.h>
#include <vector>
#define GLFW_INCLUDE_VULKAN
#define GLFW_STATIC
#include <GLFW/glfw3.h>





struct SwapChainSupportDetails {
	VkSurfaceCapabilitiesKHR capabilities; // capabilities of the swap chain, like min/max image count, extent, etc.
	std::vector<VkSurfaceFormatKHR> formats; // formats of the swap chain images, like color space, format, etc.
	std::vector<VkPresentModeKHR> presentModes; // double buffering , triple buffering, etc.
};

SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR surface);
VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
VkPresentModeKHR chooseSwapPresentMode(const	std::vector<VkPresentModeKHR>& availablePresentModes);
VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, GLFWwindow* win);