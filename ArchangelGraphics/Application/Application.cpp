#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

 #include <iostream>
int main() {
	 glfwInit();
	
		 glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	 GLFWwindow * window = glfwCreateWindow(800, 600, "Vulkanwindow",
		nullptr, nullptr);
	
		 uint32_textensionCount = 0;
	 vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount,
		nullptr);
	
		 std::cout << extensionCount << "extensionssupported\n";
	
		 glm::mat4matrix;
	 glm::vec4vec;
	 autotest = matrix * vec;
	
		 while (!glfwWindowShouldClose(window)) {
		 glfwPollEvents();
		
	}
	
		 glfwDestroyWindow(window);
	
		 glfwTerminate();
	
		 return0;
	
}