
#include "HelloTriangleApplication.h"
#include "ExtraVulkanLoaders.hpp"

  
	void HelloTriangleApplication::run() {
		initWindow();
		initVulkan();
		mainLoop();
		cleanup();
	}

	void HelloTriangleApplication::initWindow() {
		if (!glfwInit()) {
			throw std::runtime_error("Failed to initialize GLFW");
		}
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		m_Window = glfwCreateWindow(m_Width, m_Height, "Vulkan", nullptr, nullptr);

	}
	
	void HelloTriangleApplication::mainLoop() {
		while (!glfwWindowShouldClose(m_Window)) {
			glfwPollEvents();

		}
	}












	void HelloTriangleApplication::initVulkan() {
		
		createInstance();
		setupDebugMessenger();
		createSurface();
		pickPhysicalDevice();
		createLogicalDevice();
		
	}
































































	
	void HelloTriangleApplication::createInstance() {
		VkApplicationInfo appInfo{};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = "vulkan app";
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName = "No Engine";
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_0;
		// όλα έχουν σκοπό να προσδιορίσουν την εφαρμογή μας, ώστε να μπορεί να αναγνωριστεί από το Vulkan.
		// Το pApplicationName είναι το όνομα της εφαρμογής μας, το applicationVersion είναι η έκδοση της εφαρμογής,
		// το pEngineName είναι το όνομα της μηχανής γραφικών (αν χρησιμοποιούμε κάποια), το engineVersion είναι η έκδοση της μηχανής γραφικών,
		// και το apiVersion είναι η έκδοση του Vulkan API που χρησιμοποιούμε και καθορίζει ποιό API θα πρέπει ο driver  τουλάχιστον να υποστηρίζει.
		
		// ελέγχει όλα τα validation layers που έχουμε ζητήσει αν είναι διαθέσιμα στο σύστημα μας 
		if (m_EnableValidationLayers && !checkValidationLayerSupport()) 
			throw std::runtime_error("validation layers requested ,but not available!");
		else 
			std::cout << "validation layers are supported" << std::endl;
		
		// δημιουργεί το instance του Vulkan, το οποίο είναι το πρώτο βήμα για να ξεκινήσει η χρήση του Vulkan API.
		VkInstanceCreateInfo insInfo{};
		// Πρώτα απο όλα, δηλώνουμε όλα τα validation layers που θέλουμε να χρησιμοποιήσουμε.
		// Ενώ το Vulkan API δεν παρέχει validation layers από μόνο του, καθώς και χρησιμοποιούμε
		// την επέκταση VK_EXT_debug_utils για να δημιουργήσουμε ένα debug messenger που θα μας επιτρέπει να λαμβάνουμε μηνύματα από το Vulkan API
		// ακομά και απο την δημιουργία του instance.
		VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
		if (m_EnableValidationLayers) {
			insInfo.enabledLayerCount =	static_cast<uint32_t>(m_ValidationLayers.size());
			insInfo.ppEnabledLayerNames = m_ValidationLayers.data();
			populateDebugMessengerCreateInfo(debugCreateInfo);
			insInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*) &debugCreateInfo;
			// for debugging the instance creation we use the pNext extension special
		}
		else {
			insInfo.enabledLayerCount = 0;
			insInfo.ppEnabledLayerNames = nullptr;
		}
		insInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		insInfo.pApplicationInfo = &appInfo;
		auto extensions = getRequiredExtensions();
		insInfo.enabledExtensionCount =
			static_cast<uint32_t>(extensions.size());
		insInfo.ppEnabledExtensionNames = extensions.data();

#ifndef NDEBUG 
		std::cout << "Total validation layers that have set : " << insInfo.enabledLayerCount << std::endl;
		for (int i = 0; i < insInfo.enabledLayerCount; i++) {
			std::cout << "Validation layer " << i << ": " << insInfo.ppEnabledLayerNames[i] << std::endl;
			
		}

		std::cout << "Total extensions that have set : " << insInfo.enabledExtensionCount << std::endl;
		for (int i = 0; i < insInfo.enabledExtensionCount; i++) {
			std::cout << "Extension " << i << ": " << insInfo.ppEnabledExtensionNames[i] << std::endl;
		}
#endif 

		VkResult result = vkCreateInstance(&insInfo, nullptr, &m_Instance);
		if (result != VK_SUCCESS) {
			throw std::runtime_error("Failed to create Vulkan instance");
		}




	}

	bool HelloTriangleApplication::checkValidationLayerSupport(void) {

		//retreive all layer properties of this 
		uint32_t layerCount;
		vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

		std::vector<VkLayerProperties>availableLayers(layerCount);

		vkEnumerateInstanceLayerProperties(&layerCount,
			availableLayers.data());

		for (const char* layerName : m_ValidationLayers) {
			bool layerFound = false;
			for (const auto& layerProperties : availableLayers) {
				if (strcmp(layerName, layerProperties.layerName) == 0) {
					layerFound = true;
					break;
				}
			}

			if (!layerFound)	return false;
		}



		
		return true;
	}


	std::vector<const char*> HelloTriangleApplication::getRequiredExtensions() const {
		uint32_t glfwExtensionCount = 0;
		const char * *glfwExtensions;
		glfwExtensions =
			glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
		std::vector<const char*> extensions(glfwExtensions,glfwExtensions + glfwExtensionCount);

		if (m_EnableValidationLayers) 
			extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
		
		// here any other extensions can be added that are required by the application

		return extensions;
	}

	//debug callback function for 
	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
	VkDebugUtilsMessageSeverityFlagBitsEXT			messageSeverity,
	VkDebugUtilsMessageTypeFlagsEXT					messageType,
	const VkDebugUtilsMessengerCallbackDataEXT*		pCallbackData,
	void* pUserData) {
		if (messageSeverity <
			VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) 
			return VK_FALSE; // ignore messages that are not warnings or errors


		std::cerr << "validationlayer:" << pCallbackData->pMessage <<
			std::endl;
		return VK_FALSE;

	}


	void  HelloTriangleApplication::populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT&
		createInfo) {
		createInfo = {};
		createInfo.sType =
			VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
		createInfo.messageSeverity =
			VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
		createInfo.messageType =
			VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
		createInfo.pfnUserCallback = debugCallback;
	}


	void HelloTriangleApplication::setupDebugMessenger(void) {
		if (!m_EnableValidationLayers) return;

		VkDebugUtilsMessengerCreateInfoEXT createInfo;
		populateDebugMessengerCreateInfo(createInfo);
		createInfo.pUserData = nullptr; // Optional user data pointer

		if (CreateDebugUtilsMessengerEXT(m_Instance, &createInfo, nullptr,&m_debugMessenger) != VK_SUCCESS) {
				throw std::runtime_error("failed to set up debug messenger!");
		}

	}























#include "GPUFeaturesSupport.hpp"

	void HelloTriangleApplication::pickPhysicalDevice(void) {
		// This function is used to select a physical device (GPU) that supports Vulkan.
		// It will enumerate all available physical devices and check if they support
		uint32_t deviceCount = 0;
		vkEnumeratePhysicalDevices(m_Instance, &deviceCount, nullptr); 
		// μας επιστρέφει των αριθμο διαθέσιμων φυσικών συσκευών (GPU) που υποστηρίζουν Vulkan.
		if (deviceCount == 0) 
			throw std::runtime_error("failed to find GPUs with Vulkan support :? !");
		
		std::vector<VkPhysicalDevice> devices(deviceCount);
		vkEnumeratePhysicalDevices(m_Instance, &deviceCount, devices.data());
		// τώρα πέρνουμε τις διαθέσημες κάρτες γραφικών συνολικά σε ένα vector.
		
		VkPhysicalDeviceProperties deviceProperties;
		int maxScore = 0;
		// ελεγχος αν περιέχει ιδιότητες που θέλουμε και πόσο απυτιχιμένα
		for (auto device : devices) {
			vkGetPhysicalDeviceProperties(device, &deviceProperties);
			if (isDeviceSuitable(device)) {
				// αν η συσκευή είναι κατάλληλη για την εφαρμογή μας, τότε την επιλέγουμε.

				std::cout << "Found suitable GPU: " << deviceProperties.deviceName << std::endl;
				int score = ratePhysicalDevice(device);
				m_RatedDevices[score] = device;
				if (maxScore < score) {
					maxScore = score;
					m_PhysicalDevice = device;
				}

			}
			else continue;
			
		}

	}

	bool HelloTriangleApplication::isDeviceSuitable(VkPhysicalDevice device) {
		// This function checks if the given physical device is suitable for our application.
		// It will check if the device supports the required features and properties.
		VkPhysicalDeviceProperties deviceProperties;
		vkGetPhysicalDeviceProperties(device, &deviceProperties);

		VkPhysicalDeviceFeatures deviceFeatures;
		vkGetPhysicalDeviceFeatures(device, &deviceFeatures);
		QueueFamilyIndices indices = findQueueFamilies(device , m_Surface);
		return  deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU &&
				deviceFeatures.geometryShader 
			&&	deviceFeatures.tessellationShader 
			
			&& indices.isComplete();
		// Tessellation and geometry shaders are required for our application.
	}

#include <set>

	void HelloTriangleApplication::createLogicalDevice() {
		// This function creates a logical device that allows us to interact with the physical device.
		// It will create a queue for graphics operations and a command pool for command buffers.
		QueueFamilyIndices indices = findQueueFamilies(m_PhysicalDevice , m_Surface);
		std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
		std::set<uint32_t> uniqueQueueFamilies =
		{ indices.graphicsFamily.value(), indices.presentFamily.value() };
		float queuePriority = 1.0f;
		for (uint32_t queueFamily : uniqueQueueFamilies)
		{
			VkDeviceQueueCreateInfo queueCreateInfo{};
			queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queueCreateInfo.queueFamilyIndex = queueFamily;
			queueCreateInfo.queueCount = 1;
			queueCreateInfo.pQueuePriorities = &queuePriority;
			queueCreateInfos.push_back(queueCreateInfo);
		}
		
		VkPhysicalDeviceFeatures deviceFeatures{};
		deviceFeatures.geometryShader = VK_TRUE; // enable geometry shaders
		deviceFeatures.tessellationShader = VK_TRUE; // enable tessellation shaders
		VkDeviceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		createInfo.pQueueCreateInfos = queueCreateInfos.data();
		createInfo.queueCreateInfoCount = queueCreateInfos.size();
		createInfo.pEnabledFeatures = &deviceFeatures;

		createInfo.enabledExtensionCount = 0; // these is where logical device extensions can be added
		if (m_EnableValidationLayers) {
			createInfo.enabledLayerCount =
			static_cast<uint32_t>(m_ValidationLayers.size());
			createInfo.ppEnabledLayerNames = m_ValidationLayers.data();
		}
		else {
			createInfo.enabledLayerCount = 0;
		}

		if (vkCreateDevice(m_PhysicalDevice, &createInfo, nullptr, &m_LogicalDevice) !=
			VK_SUCCESS) {
			throw std::runtime_error("failed to create logical device!");
		}

		vkGetDeviceQueue(m_LogicalDevice, indices.graphicsFamily.value(), 0, &m_GraphicsQueue);
		vkGetDeviceQueue(m_LogicalDevice, indices.presentFamily.value(), 0, &m_PresentQueue);
	}

	void HelloTriangleApplication::createSurface() {
		if (glfwCreateWindowSurface(m_Instance, m_Window, nullptr, &m_Surface) != VK_SUCCESS) {
			throw std::runtime_error("failed to create window surface!");
		}
	}





















	





	void HelloTriangleApplication::cleanup() {
		vkDestroyDevice(m_LogicalDevice, nullptr);
		vkDestroySurfaceKHR(m_Instance, m_Surface, nullptr);
		if (m_EnableValidationLayers) {
			DestroyDebugUtilsMessengerEXT(m_Instance, m_debugMessenger, nullptr);
		}
		vkDestroyInstance(m_Instance, nullptr);
		
		glfwDestroyWindow(m_Window);
		glfwTerminate();
		
	}