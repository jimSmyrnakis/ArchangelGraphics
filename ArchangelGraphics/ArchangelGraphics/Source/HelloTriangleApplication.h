#pragma once

#define GLFW_INCLUDE_VULKAN
#define GLFW_STATIC
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <iostream>
#include <vulkan/vulkan.h>
#include <cstdlib>
#include <stdexcept>
#include <vector>
#include <cstring>
#include <map>

#include <set>
class HelloTriangleApplication {
public:
	void run();

	std::vector<const char*> getRequiredExtensions() const;

private:

	void initWindow();

	// ========== vulkan =============
	void initVulkan();
	// intance
	void createInstance();
	//debug
	bool checkValidationLayerSupport(void);
	void setupDebugMessenger(void);
	void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
	// device
	void pickPhysicalDevice(void);
	bool isDeviceSuitable(VkPhysicalDevice device);
	void createLogicalDevice();
	bool checkDeviceExtensionSupport(VkPhysicalDevice device);
	void createSurface();
	void createSwapChain();
	void createImageViews();

	void mainLoop();

	void cleanup();

	

	

	
private:
	GLFWwindow* m_Window;
	const uint32_t m_Width = 800;
	const uint32_t m_Height = 600;
	VkInstance m_Instance;

	std::vector<const char*> m_ValidationLayers = {
		"VK_LAYER_KHRONOS_validation"
	};

	const std::vector<const char*> m_PhysicalDeviceExtensions = {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};

#ifndef NDEBUG
	bool m_EnableValidationLayers = true;
#else
	bool m_EnableValidationLayers = false;
#endif

	VkDebugUtilsMessengerEXT m_debugMessenger;

	VkPhysicalDevice m_PhysicalDevice = VK_NULL_HANDLE;
	std::map<int, VkPhysicalDevice> m_RatedDevices;
	VkDevice m_LogicalDevice;
	VkQueue m_GraphicsQueue;
	VkQueue m_PresentQueue;
	VkSurfaceKHR m_Surface;
	VkSwapchainKHR m_SwapChain;
	std::vector<VkImage> m_SwapChainImages;
	VkFormat m_SwapChainImageFormat;
	VkExtent2D m_SwapChainExtent;
	std::vector<VkImageView> m_SwapChainImageViews;
};