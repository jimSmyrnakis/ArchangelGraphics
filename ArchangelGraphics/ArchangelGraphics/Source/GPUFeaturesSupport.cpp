
#include "GPUFeaturesSupport.hpp"
#include <vector>
bool QueueFamilyIndices::isComplete() {
	return graphicsFamily.has_value() && presentFamily.has_value();

}
int ratePhysicalDevice(VkPhysicalDevice device) {
	// This function rates the physical device based on its properties and features.
	// It will return a score that indicates how suitable the device is for our application.
	VkPhysicalDeviceProperties deviceProperties;
	vkGetPhysicalDeviceProperties(device, &deviceProperties);
	VkPhysicalDeviceFeatures deviceFeatures;
	vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

	int score = 0;
	if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
		score += 1000; // discrete GPUs are preferred
	}
	score += deviceProperties.limits.maxImageDimension2D; // higher resolution is better
	if (!deviceFeatures.geometryShader || !deviceFeatures.tessellationShader ) {
		score = 0; // geometry shaders are required for our application
	}
	return score;
}

QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device , VkSurfaceKHR surface) {
	QueueFamilyIndices indices;
	// check if the device supports graphics operations
	uint32_t queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
	// take the number of queue families that the device supports
	std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());
	
	// take all available queue families and store them in a vector
	for (uint32_t i = 0; i < queueFamilyCount; i++) {
		if (queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
			indices.graphicsFamily = i;
			
		}
		VkBool32 presentSupport = false;
		vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface,
			&presentSupport);
		if (presentSupport) {
			indices.presentFamily = i;
		}

		if (indices.isComplete()) {
			break; // if we found the graphics family, we can stop searching
		}
	}

	return indices;
}



