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

class HelloTriangleApplication {
public:
	void run();

	std::vector<const char*> getRequiredExtensions() const;

private:

	void initWindow();

	void initVulkan();

	void createInstance();

	void mainLoop();

	void cleanup();

	bool checkValidationLayerSupport(void);

	void setupDebugMessenger(void);

	void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

private:
	GLFWwindow* m_Window;
	const uint32_t m_Width = 800;
	const uint32_t m_Height = 600;
	VkInstance m_Instance;

	std::vector<const char*> m_ValidationLayers = {
		"VK_LAYER_KHRONOS_validation"
	};

#ifndef NDEBUG
	bool m_EnableValidationLayers = true;
#else
	bool m_EnableValidationLayers = false;
#endif

	VkDebugUtilsMessengerEXT m_debugMessenger;
};