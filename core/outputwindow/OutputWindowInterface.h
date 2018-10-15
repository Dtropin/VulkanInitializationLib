//
// Created by Tropin Denis on 31.03.2018.
//
#pragma once

#include <vector>
#include <vulkan.h>
#include <glfw3.h>

struct VulkanExtensionsInfo {
    std::vector<const char*>* supportedExtensions;
};

class OutputWindowInterface {
    public:
        virtual void showWindow() = 0;
		virtual GLFWwindow * getWindow() = 0;//TODO сделать через шаблоны
        virtual VulkanExtensionsInfo* getExtensionsForVulkan() = 0;
        virtual VkSurfaceKHR* getWindowSurface(VkInstance* instance) = 0;
        virtual ~OutputWindowInterface() {};
};
