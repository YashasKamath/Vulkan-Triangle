#pragma once

#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#define NOMINMAX
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#include <iostream>
#include <stdexcept> // For error handling
#include <cstdlib> // To include EXIT_SUCCESS and EXIT_FAILURE macros
#include <vector>
#include <cstring>
#include <optional>
#include <set>
#include <cstdint> // uint32_t
#include <limits> // std::numeric_limits
#include <algorithm> // std::clamp
#include <fstream>

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

const std::vector<const char*> validationLayers{
	"VK_LAYER_KHRONOS_validation"
};

const std::vector<const char*> deviceExtensions = {
	VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
	const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* debugMessenger);

void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger,
	const VkAllocationCallbacks* pAllocator);

struct QueueFamilyIndices {
	std::optional<uint32_t> graphicsFamily;
	std::optional<uint32_t> presentFamily; // device to window rendering should be compatible with the queue family chosen

	bool isComplete() {
		return graphicsFamily.has_value() && presentFamily.has_value();
	}
};

struct SwapChainSupportDetails {
	VkSurfaceCapabilitiesKHR capabilities; // min/max height and width of the images; min/max number of images in the swap chain
	std::vector<VkSurfaceFormatKHR> formats; // pixel format and color space
	std::vector<VkPresentModeKHR> presentModes;
};

class VulkanTriangle {
public:
	void run();
private:

	GLFWwindow* window;

	VkInstance instance;
	VkDebugUtilsMessengerEXT debugMessenger;
	VkSurfaceKHR surface;

	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	VkDevice device;

	VkQueue graphicsQueue;
	VkQueue presentQueue;

	VkSwapchainKHR swapChain;
	std::vector<VkImage> swapChainImages;
	VkFormat swapChainImageFormat; // rgb color format
	VkExtent2D swapChainExtent; // resolution of the images
	std::vector<VkImageView> swapChainImageViews;

	VkRenderPass renderPass;
	VkPipelineLayout pipelineLayout;
	VkPipeline graphicsPipeline;

	std::vector<VkFramebuffer> swapChainFramebuffers;

	VkCommandPool commandPool;
	VkCommandBuffer commandBuffer;

	VkSemaphore imageAvailableSemaphore; // sync between acquire and draw image calls
	VkSemaphore renderFinishedSemaphore; // sync between draw and present image calls.
	VkFence inFlightFence; // CPU waits until the previous frame rendering finishes.

	void initWindow();
	void initVulkan();
	void mainLoop();
	void cleanup();
	void createInstance();
	void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
	void setupDebugMessenger();
	void createSurface();
	void pickPhysicalDevice();
	void createLogicalDevice();
	void createSwapChain();
	void createImageViews();
	void createRenderPass();
	void createGraphicsPipeline();
	void createFramebuffers();
	void createCommandPool();
	void createCommandBuffer();
	void drawFrame();
	void createSyncObjects();
	void recordCommandBuffer(VkCommandBuffer commandBuffer,uint32_t imageIndex);
	VkShaderModule createShaderModule(const std::vector<char>& code);
	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
	SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
	bool isDeviceSuitable(VkPhysicalDevice device);
	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

	bool checkDeviceExtensionSupport(VkPhysicalDevice device);
	std::vector<const char*> getRequiredExtensions();
	bool checkExtensionSupport(uint32_t glfwExtensionCount, std::vector<const char*> glfwExtensions);
	bool checkValidationLayerSupport();

	static std::vector<char> readFile(const std::string& filename);
	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
		VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
		void* pUserData);

};


