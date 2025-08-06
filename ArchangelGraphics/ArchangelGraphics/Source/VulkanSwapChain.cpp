#include "VulkanSwapChain.hpp"
#include <stdexcept>

#include <cstdint>//Necessaryforuint32_t
#include <limits>//Necessaryforstd::numeric_limits
#include <algorithm>//Necessaryforstd::clamp

SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device , VkSurfaceKHR surface) {
	SwapChainSupportDetails details;

	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);
	uint32_t formatCount;
	vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);
	if (formatCount != 0) {
		details.formats.resize(formatCount);
		vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, details.formats.data());
	}
	else throw std::runtime_error("failed to find swap chain pixel format , color space :( !");
	uint32_t presentModeCount;
	vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface,
		&presentModeCount, nullptr);
	if (presentModeCount != 0) {
		details.presentModes.resize(presentModeCount);
		vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface,
			&presentModeCount, details.presentModes.data());
	}
	else throw std::runtime_error("failed to find swap chain buffering modes :( !");
	return details;
}


VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats) {
	for (const auto& availableFormat : availableFormats) {
		if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB &&
			availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
			return availableFormat; // return the preferred format
		}
	}
	return availableFormats[0]; // if preferred format is not found, return the first one
}

VkPresentModeKHR chooseSwapPresentMode(const	std::vector<VkPresentModeKHR>& availablePresentModes) {
	for (const auto& availablePresentMode : availablePresentModes) {
		if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
			return availablePresentMode; // return mailbox mode for better performance
		}
	}
	return VK_PRESENT_MODE_FIFO_KHR; // if mailbox mode is not found, return FIFO mode :(
}

VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities , GLFWwindow* win) {
	if (capabilities.currentExtent.width != 0xFFFFFFFF) {
		return capabilities.currentExtent;
	}

	int width, height;
	glfwGetFramebufferSize(win, &width, &height);
	VkExtent2D actualExtent = {
		static_cast<uint32_t>(width),
		static_cast<uint32_t>(height)
	};

	actualExtent.width = std::clamp(actualExtent.width,
		capabilities.minImageExtent.width,
		capabilities.maxImageExtent.width);
	actualExtent.height = std::clamp(actualExtent.height,
		capabilities.minImageExtent.height,
		capabilities.maxImageExtent.height);

	return actualExtent;
}