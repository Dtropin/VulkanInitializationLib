//
// Created by Tropin Denis on 31.03.2018.
//
#pragma once

#include <vulkan.h>
#include <glfw3.h>
#include <iostream>
#include "GlfwOutputWindow.h"

void GlfwOutputWindow::showWindow() {

}

GlfwOutputWindow::~GlfwOutputWindow() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

GlfwOutputWindow::GlfwOutputWindow(GLFWwindow * window) {
    this->window = window;
}

//TODO Сделать через шаблоны
GLFWwindow* GlfwOutputWindow::getWindow() {
	return window;
}

VulkanExtensionsInfo *GlfwOutputWindow::getExtensionsForVulkan() {
    unsigned int extensionCount = 0;
	//Функция glfw которая возвращает поддерживаемые extensions для вулкана
    const char** supportedExtensions = glfwGetRequiredInstanceExtensions(&extensionCount);

    VulkanExtensionsInfo* extensionsInfo = new VulkanExtensionsInfo;
    extensionsInfo->supportedExtensions = new std::vector<const char*>;

    for (unsigned int i = 0; i < extensionCount; i++)
        extensionsInfo->supportedExtensions->push_back(supportedExtensions[i]);

    return extensionsInfo;
}

VkSurfaceKHR *GlfwOutputWindow::getWindowSurface(VkInstance *instance) {
    VkSurfaceKHR * surfaceKHR = new VkSurfaceKHR;
    if (glfwCreateWindowSurface(*instance, window, nullptr, surfaceKHR) != VK_SUCCESS) {
        throw std::runtime_error("failed to create window surface!");
    }

    return surfaceKHR;
}
