//
// Created by Tropin Denis on 01.04.2018.
//
#pragma once

#include <glfw3.h>
#include <stdexcept>
#include <iostream>
#include "VulkanInterface.h"

VkInstance* VulkanInterface::getVulkanInstance() {
    return vulkanInstance;
}

VulkanInterface::VulkanInterface(
        VkInstance* vulkanInstance,
        VkDeviceRepresentation* logicalDevice, VkSurfaceKHR* vkSurfaceKHR, SwapChainHandler* swapChainHandler, GraphicsPipelineInterface* graphicsPipeline,
        VkRenderPass vkRenderPass, std::vector<VkFramebuffer>* swapChainFramebuffers, VkCommandPool commandPool, std::vector<VkCommandBuffer>* commandBuffers) {
    this->vulkanInstance = vulkanInstance;

    this->logicalDevice = logicalDevice;
    this->surfaceKHR = vkSurfaceKHR;
    this->swapChainHandler = swapChainHandler;
    this->graphicsPipeline = graphicsPipeline;
    this->vkRenderPass = vkRenderPass;
    this->swapChainFramebuffers = swapChainFramebuffers;
	this->commandPool = commandPool;
	this->commandBuffers = commandBuffers;
}

VulkanInterface::~VulkanInterface() {
	vkDestroyCommandPool(*logicalDevice->getVkLogicalDevice(), commandPool, nullptr);

    for (size_t i = 0; i < swapChainFramebuffers->size(); i++) {
        vkDestroyFramebuffer(*logicalDevice->getVkLogicalDevice(), swapChainFramebuffers->at(i), nullptr);
    }

    for (size_t i = 0; i < swapChainHandler->swapChainImageViews.size(); i++) {
        vkDestroyImageView(*logicalDevice->getVkLogicalDevice(), swapChainHandler->swapChainImageViews[i], nullptr);
    }

    vkDestroyRenderPass(*logicalDevice->getVkLogicalDevice(), vkRenderPass, nullptr);

    vkDestroyPipeline(*logicalDevice->getVkLogicalDevice(), graphicsPipeline->pipeline, nullptr);
    vkDestroyPipelineLayout(*logicalDevice->getVkLogicalDevice(), graphicsPipeline->pipelineLayout, nullptr);
    vkDestroySwapchainKHR(*logicalDevice->getVkLogicalDevice(), swapChainHandler->swapChain, nullptr);


    if (logicalDevice != nullptr) {
        vkDestroyDevice(*logicalDevice->getVkLogicalDevice(), nullptr);
        delete logicalDevice;
    }

    if(surfaceKHR != nullptr) {
        vkDestroySurfaceKHR(*vulkanInstance, *surfaceKHR, nullptr);
        delete surfaceKHR;
    }

    if (vulkanInstance != nullptr) {
        vkDestroyInstance(*vulkanInstance, nullptr);
        delete vulkanInstance;
    }
}
