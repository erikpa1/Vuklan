#pragma once

#include <vulkan/vulkan.h>

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

    bool _IsDeviceSuitable(VkPhysicalDevice device);

    void _Surface();
    
};
