#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/hash.hpp>

#include <vector>
#include <array>
#include <set>
#include <chrono>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <cstring>
#include <cstdlib>

//model struct
struct Model {
	int offset;
	int size;
};
//Object struct
struct Object {
	Model *model;
	glm::mat4 transformData;
	glm::vec3 scale;
	glm::vec3 position;
	glm::vec3 rotation;
	bool wireFrame = false;
	bool visible = true;
	bool relevant = true;
};

struct QuickDraw {
	Model *model;
	glm::mat4 transformData;
	glm::vec3 position;
	bool wireFrame = false;
};

struct UniformBufferObject {
	//glm::mat4 model;
	glm::mat4 view;
	glm::mat4 proj;
	glm::vec3 cameraPos;
};

struct Vertex {
	glm::vec3 pos;
	glm::vec4 color;
	glm::vec3 normal;
	glm::vec2 texCoord;

	static VkVertexInputBindingDescription getBindingDescription() {
		VkVertexInputBindingDescription bindingDescription = {};
		bindingDescription.binding = 0;
		bindingDescription.stride = sizeof(Vertex);
		bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

		return bindingDescription;
	}

	static std::array<VkVertexInputAttributeDescription, 4> getAttributeDescriptions() {
		std::array<VkVertexInputAttributeDescription, 4> attributeDescriptions = {};

		attributeDescriptions[0].binding = 0;
		attributeDescriptions[0].location = 0;
		attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[0].offset = offsetof(Vertex, pos);

		attributeDescriptions[1].binding = 0;
		attributeDescriptions[1].location = 1;
		attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[1].offset = offsetof(Vertex, color);

		attributeDescriptions[2].binding = 0;
		attributeDescriptions[2].location = 2;
		attributeDescriptions[2].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[2].offset = offsetof(Vertex, normal);

		attributeDescriptions[3].binding = 0;
		attributeDescriptions[3].location = 3;
		attributeDescriptions[3].format = VK_FORMAT_R32G32_SFLOAT;
		attributeDescriptions[3].offset = offsetof(Vertex, texCoord);

		return attributeDescriptions;
	}

	bool operator==(const Vertex& other) const {
		return pos == other.pos && color == other.color && texCoord == other.texCoord;
	}
};

namespace std {
	template<> struct hash<Vertex> {
		size_t operator()(Vertex const& vertex) const {
			return ((hash<glm::vec3>()(vertex.pos) ^ (hash<glm::vec3>()(vertex.color) << 1)) >> 1) ^ (hash<glm::vec2>()(vertex.texCoord) << 1);
		}
	};
}

struct SwapChainSupportDetails {
	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentModes;
};


struct QueueFamilyIndices {
	int graphicsFamily = -1;
	int presentFamily = -1;

	bool isComplete() {
		return graphicsFamily >= 0 && presentFamily >= 0;
	}
};


const std::string TEXTURE_PATH = "textures/menuTexture.png";

const std::vector<const char*> validationLayers = {
	"VK_LAYER_LUNARG_standard_validation"
};

const std::vector<const char*> deviceExtensions = {
	VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

class Graphics {
public:

	bool shouldClose = false;

	void init();

	void run();

	void cleanup();

	void changeCameraPos(float x, float y, float z);

	void setCameraAngle(glm::vec3 cameraAngle);

	void setCameraPos(glm::vec3 cameraPos);

	glm::vec3 getProperCameraVelocity(glm::vec3 cameraVel);

	GLFWwindow* getWindowPointer();

	void drawString(std::string string, float x, float y);

	void drawCharacter(char character, float x, float y);

	void quickDraw(glm::vec3 position, int modelIndex, bool wireFrame = false);

	int addObject(glm::vec3 position, glm::vec3 scale, int modelIndex, bool wireFrame = false);

	int addObject(glm::vec3 position, glm::vec3 scale, int modelIndex, glm::vec3 rotation, bool wireFrame = false);

	void moveObject(int objectIndex, glm::vec3 position);

	void rotateObject(int objectIndex, glm::vec3 rotation);

	void removeObject(int objectIndex);

	void scaleObject(int objectIndex, glm::vec3 scale);

	void recalculateObjectMatrix(int objectIndex);

	void calculateQuickDrawMatrix(int quickDrawIndex);

	Object* getObjectAtIndex(int i);

	glm::vec3 getCameraPos();

	void setFreeLook(bool value);

	void setObjectsWireFrame(bool value);

	void setObjectVisible(int objectIndex, bool visible);

private:

	std::vector<Model> models;

	std::vector<Object> objects;

	std::vector<QuickDraw> quickDraws;

	const int MAX_OBJECTS = 9900;

	const int MAX_QUICKDRAWS = 100;

	int sizeOfAllModels = 0;

	const int TextureWidth = 4000;

	const int TextureHeight = 2000;

	const int WIDTH = 1920;
	const int HEIGHT = 1080;
	const int MAX_FRAMES_IN_FLIGHT = 2;

	bool freeLook = false;

	glm::vec3 cameraAngle;

	glm::vec3 cameraPosition;

	float FOV = 90;

	glm::vec3 direction;

	glm::vec3 right;

	glm::vec3 up;

	float cameraVelocity = 0.5;

	GLFWwindow* window;

	VkInstance instance;
	VkDebugReportCallbackEXT callback;
	VkSurfaceKHR surface;

	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	VkDevice device;

	VkQueue graphicsQueue;
	VkQueue presentQueue;

	VkSwapchainKHR swapChain;
	std::vector<VkImage> swapChainImages;
	VkFormat swapChainImageFormat;
	VkExtent2D swapChainExtent;
	std::vector<VkImageView> swapChainImageViews;
	std::vector<VkFramebuffer> swapChainFramebuffers;

	VkRenderPass renderPass;
	VkDescriptorSetLayout descriptorSetLayout;

	VkPipelineLayout pipelineLayout;
	VkPipeline triangleGraphicsPipeline;
	VkPipeline lineGraphicsPipeline;

	VkCommandPool commandPool;

	VkImage depthImage;
	VkDeviceMemory depthImageMemory;
	VkImageView depthImageView;

	uint32_t mipLevels;
	VkImage textureImage;
	VkDeviceMemory textureImageMemory;
	VkImageView textureImageView;
	VkSampler textureSampler;

	VkSampleCountFlagBits msaaSamples = VK_SAMPLE_COUNT_1_BIT;
	VkImage colorImage;
	VkDeviceMemory colorImageMemory;
	VkImageView colorImageView;

	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
	VkBuffer vertexBuffer;
	VkDeviceMemory vertexBufferMemory;
	VkBuffer indexBuffer;
	VkDeviceMemory indexBufferMemory;

	VkBuffer storageBuffer;
	VkDeviceMemory storageBufferMemory;

	std::vector<VkBuffer> uniformBuffers;
	std::vector<VkDeviceMemory> uniformBuffersMemory;

	VkDescriptorPool descriptorPool;
	std::vector<VkDescriptorSet> descriptorSets;

	std::vector<VkCommandBuffer> commandBuffers;

	std::vector<VkSemaphore> imageAvailableSemaphores;
	std::vector<VkSemaphore> renderFinishedSemaphores;
	std::vector<VkFence> inFlightFences;
	size_t currentFrame = 0;

	bool framebufferResized = false;

	void loadModel(const char * path, glm::vec4 colour, glm::vec3 scale);

	void loadModels();

	void loadFlatImageModel(float width, float height, glm::vec2 imageMin, glm::vec2 imageMax);

	void loadFlatImageModels();

	void loadObjects();

	void setUpCamera();

	VkResult CreateDebugReportCallbackEXT(VkInstance instance, const VkDebugReportCallbackCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugReportCallbackEXT* pCallback) {
		auto func = (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugReportCallbackEXT");
		if (func != nullptr) {
			return func(instance, pCreateInfo, pAllocator, pCallback);
		}
		else {
			return VK_ERROR_EXTENSION_NOT_PRESENT;
		}
	}

	void DestroyDebugReportCallbackEXT(VkInstance instance, VkDebugReportCallbackEXT callback, const VkAllocationCallbacks* pAllocator) {
		auto func = (PFN_vkDestroyDebugReportCallbackEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugReportCallbackEXT");
		if (func != nullptr) {
			func(instance, callback, pAllocator);
		}
	}

	void initWindow();

	static void framebufferResizeCallback(GLFWwindow* window, int width, int height);

	void initVulkan();

	//void mainLoop();

	void cleanupSwapChain();

	void recreateSwapChain();

	void createInstance();

	void setupDebugCallback();

	void createSurface();

	void pickPhysicalDevice();

	void createLogicalDevice();

	void createSwapChain();

	void createImageViews();

	void createRenderPass();

	void createDescriptorSetLayout();

	void createTriangleGraphicsPipeline();

	void createLineGraphicsPipeline();

	void createFramebuffers();

	void createCommandPool();

	void createDepthResources();

	VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);

	VkFormat findDepthFormat();

	bool hasStencilComponent(VkFormat format);

	void createTextureImage();

	void generateMipmaps(VkImage image, VkFormat imageFormat, int32_t texWidth, int32_t texHeight, uint32_t mipLevels);

	VkSampleCountFlagBits getMaxUsableSampleCount();

	void createColorResources();

	void createTextureImageView();

	void createTextureSampler();

	VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, uint32_t mipLevels);

	void createImage(uint32_t width, uint32_t height, uint32_t mipLevels, VkSampleCountFlagBits numSamples, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);

	void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout, uint32_t mipLevels);

	void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);

	int loadOBJFile(std::string path, glm::vec4 colour, glm::vec3 scale);

	void createVertexBuffer();

	void createIndexBuffer();

	void clearStorageBuffer();

	void createStorageBuffer();

	void updateStorageBuffer();

	void createUniformBuffers();

	void createDescriptorPool();

	void createDescriptorSets();

	void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);

	VkCommandBuffer beginSingleTimeCommands();

	void endSingleTimeCommands(VkCommandBuffer commandBuffer);

	void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

	uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

	void createCommandBuffers();

	void createSyncObjects();

	void updateUniformBuffer(uint32_t currentImage);

	void drawFrame();

	VkShaderModule createShaderModule(const std::vector<char>& code);

	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);

	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> availablePresentModes);

	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

	SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);

	bool isDeviceSuitable(VkPhysicalDevice device);

	bool checkDeviceExtensionSupport(VkPhysicalDevice device);

	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

	std::vector<const char*> getRequiredExtensions();

	bool checkValidationLayerSupport();

	static std::vector<char> readFile(const std::string& filename);

	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objType, uint64_t obj, size_t location, int32_t code, const char* layerPrefix, const char* msg, void* userData);
};