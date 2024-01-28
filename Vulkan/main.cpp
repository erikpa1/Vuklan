#define VK_USE_PLATFORM_WIN32_KHR
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_INCLUDE_VULKAN

#include "apps/triangle/TriangleMain.h"

#include <GLFW/glfw3.h>


const int WIDTH = 800;
const int HEIGHT = 600;


#include <iostream>
#include <stdexcept>
#include <vector>

class VulkanApp
{
public:
    void run()
    {
        initWindow();
        mainLoop();
        cleanup();
    }

private:
    GLFWwindow* window;
    VkInstance instance;

    void initWindow()
    {
        // Initialize GLFW
        if (!glfwInit())
        {
            throw std::runtime_error("Failed to initialize GLFW!");
        }

        // Configure GLFW
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // Tell GLFW not to create an OpenGL context
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        // Create the window
        window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan GLFW Example", nullptr, nullptr);
        if (!window)
        {
            throw std::runtime_error("Failed to create GLFW window!");
        }
    }


    void mainLoop()
    {
        while (!glfwWindowShouldClose(window))
        {
            glfwPollEvents();
        }
    }

    void cleanup()
    {
        vkDestroyInstance(instance, nullptr);
        glfwDestroyWindow(window);
        glfwTerminate();
    }
};


bool run_demo()
{
    VulkanApp app;


    try
    {
        app.run();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}


int run_triangle()
{
    TriangleMain app;
    app.Start();
    return EXIT_SUCCESS;
}

int main()
{
    return run_triangle();
    // return run_demo();
}
