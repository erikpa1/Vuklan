#include "TriangleMain.h"

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <GLFW/glfw3.h>

#define VK_USE_PLATFORM_WIN64_KHR
#include <vulkan/vulkan.h>

#include <GLFW/glfw3native.h>

void TriangleMain::Start()
{
    const uint32_t WIDTH = 800;
    const uint32_t HEIGH = 600;

    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);


    if (_InitVulkan())
    {
        _InitPhysicalDevice();

        auto window = glfwCreateWindow(WIDTH, HEIGH, "VulkanTriangle", nullptr, nullptr);

        _Surface();

        while (glfwWindowShouldClose(window) == false)
        {
            glfwPollEvents();
        }

        _DeInitVulkan();
        glfwDestroyWindow(window);
        glfwTerminate();
    }
}

bool TriangleMain::_InitVulkan()
{
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Triangle";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.apiVersion = VK_API_VERSION_1_0;

    uint32_t glfwExtensionCount = 0;

    const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    std::vector<const char*> requiredExtensions;

    std::cout << "Supported GLFW extensions \n";
    for (uint32_t i = 0; i < glfwExtensionCount; i++)
    {
        requiredExtensions.emplace_back(glfwExtensions[i]);
        std::cout << glfwExtensions[i] << std::endl;
    }

    requiredExtensions.emplace_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    createInfo.enabledExtensionCount = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;
    createInfo.enabledLayerCount = 0;
    createInfo.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
    createInfo.enabledExtensionCount = (uint32_t)requiredExtensions.size();
    createInfo.ppEnabledExtensionNames = requiredExtensions.data();

    VkResult result = vkCreateInstance(&createInfo, nullptr, &_vk);


    if (result != VK_SUCCESS)
    {
        std::cout << "Failed to create VK instance /n";
        return false;
    }

    uint32_t vkExtensionsCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &vkExtensionsCount, nullptr);

    std::vector<VkExtensionProperties> vkExtensions(vkExtensionsCount);

    vkEnumerateInstanceExtensionProperties(nullptr, &vkExtensionsCount, nullptr);

    std::cout << "VK extensions" << std::endl;
    for (const auto& extension : vkExtensions)
    {
        std::cout << '\t' << extension.extensionName << std::endl;
    }


    return true;
}

void TriangleMain::_DeInitVulkan()
{
    vkDestroyInstance(_vk, nullptr);
}

void TriangleMain::_InitPhysicalDevice()
{
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(_vk, &deviceCount, nullptr);

    if (deviceCount == 0)
    {
        std::cout << "No physical devices to render" << std::endl;
    }

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(_vk, &deviceCount, devices.data());


    for (const auto& device : devices)
    {
        if (_IsDeviceSuitable(device))
        {
            physicalDevice = device;
        }
    }

    if (physicalDevice == VK_NULL_HANDLE)
    {
        std::cout << "Failed to find sutiable GPU!" << std::endl;
    }
}

bool TriangleMain::_IsDeviceSuitable(VkPhysicalDevice device)
{
    VkPhysicalDeviceProperties deviceProperties;
    VkPhysicalDeviceFeatures deviceFeatures;

    vkGetPhysicalDeviceProperties(device, &deviceProperties);
    vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

    std::cout << "[GPU INFO] " << std::endl;
    std::cout << "[GPU NAME] " << deviceProperties.deviceName << std::endl;
    std::cout << "[GPU API VERSION] " << deviceProperties.apiVersion << std::endl;
    std::cout << "[GPU DEVICE TYPE] " << deviceProperties.deviceType << std::endl;
    std::cout << "[GPU VENDOR ID] " << deviceProperties.vendorID << std::endl;
    std::cout << "[GPU MAX IMAGE DIMENSION 2D] " << deviceProperties.limits.maxImageDimension2D << std::endl;


    return deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU && deviceFeatures.geometryShader;
}

void TriangleMain::_Surface()
{
    VkSurfaceKHR surface;

}
