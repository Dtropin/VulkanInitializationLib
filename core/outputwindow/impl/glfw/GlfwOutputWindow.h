//
// Created by Tropin Denis on 31.03.2018.
#pragma once
#include <glfw3.h>
#include "../../OutputWindowInterface.h"

class GlfwOutputWindow : public OutputWindowInterface {
    public:
        GlfwOutputWindow(GLFWwindow*);
		__override GLFWwindow* getWindow();
        __override void showWindow();
        __override ~GlfwOutputWindow();
        __override VulkanExtensionsInfo* getExtensionsForVulkan();
        __override VkSurfaceKHR* getWindowSurface(VkInstance* instance);
    private:
        GLFWwindow* window;
};

