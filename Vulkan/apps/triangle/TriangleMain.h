#pragma once

#include <vulkan/vulkan.h>

class GLFWwindow;

class TriangleMain
{
private:
    VkInstance _vk;

public:
    void Start();

private:
    bool _InitVulkan();
    void _DeInitVulkan();
    void _InitPhysicalDevice();
    void _CreateSwapChain(VkPhysicalDevice & device);

    bool _IsDeviceSuitable(VkPhysicalDevice device);

    void _Surface();

    VkPresentModeKHR _GetPresentMode();


    VkExtent2D _ChooseSwapExtent(const VkSurfaceCapabilitiesKHR & capabilites);

    GLFWwindow * _window;
    
};
