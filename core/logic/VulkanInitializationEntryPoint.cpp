//
// Created by Tropin Denis on 04.04.2018.
//
#pragma once

#include <stdexcept>
#include <glfw3.h>
#include <iostream>
#include <vector>
#include "VulkanInitializationEntryPoint.h"
#include "../modules/physicalDevice/VkPhysicalDeviceRepresentation.h"
#include "physicalDevice/VkPhysicalDeviceManager.h"
#include "logicalDevice/VkLogicalDeviceManager.h"
#include "command/CommandPoolInitializer.h"
#include "swapChain/VkSwapChainManager.h"
#include "renderPass/RenderPassInitializer.h"
#include "graphicsPipeline/GraphicsPipelineInitializer.h"
#include "swapChain/FrameBuffersManager.h"
#include "../modules/commands/CommandBufferManager.h"
#include "vkInstance/VkInstanceManager.h"

VulkanInitializationEntryPoint &VulkanInitializationEntryPoint::getInstance() {
    static VulkanInitializationEntryPoint initializer;
    return initializer;
}

VulkanInitializationEntryPoint::VulkanInitializationEntryPoint() = default;

//TODO WRAP THIS PROJECT TO LIBRARY


VulkanInterface* VulkanInitializationEntryPoint::initializeVulkanSystem(OutputWindowInterface *windowInterface) {
    if(!isSystemAlreadyInitialized.test_and_set()) {
        VkInstance* vkInstance = initVkInstance(windowInterface);

        std::vector<VkPhysicalDeviceRepresentation>* vkPhysicalDevices = VkPhysicalDeviceManager::getInstance().getOrCreate(vkInstance);
        
		std::vector<const char *> deviceExtensionsToEnable = {
                VK_KHR_SWAPCHAIN_EXTENSION_NAME
		};

		std::vector<std::function<bool(VkQueueFamilyProperties)>>queueFamilyPeekFunction;

        queueFamilyPeekFunction.emplace_back([](VkQueueFamilyProperties prop) {
            return prop.queueFlags & VK_QUEUE_GRAPHICS_BIT;
        });

        VkPhysicalDeviceRepresentation* pickedPhysicalDevice = &vkPhysicalDevices[0][0];

        VkLogicalDeviceRepresentation* logicalDevice = VkLogicalDeviceManager::getInstance()
                .getOrCreate(pickedPhysicalDevice, deviceExtensionsToEnable, queueFamilyPeekFunction);

        VkCommandPool* commandPool = CommandPoolInitializer::
                createCommandPool(logicalDevice);

		VkSurfaceKHR * vkSurface = windowInterface->getWindowSurface(vkInstance);

		SwapChainHandler* swapchain = VkSwapChainManager::getInstance().createSwapChain(
		        *pickedPhysicalDevice->getVkPhysicalDevice(),
		        *vkSurface, logicalDevice);

        VkRenderPass renderPass = RenderPassInitializer::createRenderPass(*swapchain, *logicalDevice->getVkLogicalDevice());
        GraphicsPipelineInterface* pipelineLayout = GraphicsPipelineInitializer::createGraphicsPipeline(*logicalDevice->getVkLogicalDevice(), *swapchain, renderPass);
		std::vector<VkFramebuffer> * frameBuffers = FrameBuffersManager::createFrameBuffers(swapchain, *logicalDevice->getVkLogicalDevice(), renderPass);

		std::vector<VkCommandBuffer>* commandBuffers = CommandBufferManager::createCommandBuffers(frameBuffers, *commandPool, *logicalDevice->getVkLogicalDevice(), renderPass, swapchain, pipelineLayout);

		return new VulkanInterface(vkInstance, logicalDevice, vkSurface, swapchain, pipelineLayout, renderPass, frameBuffers, *commandPool, commandBuffers);
    } else {
        throw std::runtime_error("vulkan instance already created");
    }
}

VkInstance *VulkanInitializationEntryPoint::initVkInstance(OutputWindowInterface *windowInterface) {
    std::vector<const char*> vkInstanceLayersToEnable;
   // vkInstanceLayersToEnable.push_back("VK_LAYER_LUNARG_api_dump");
    std::vector<const char*> vkInstanceExtensionsToEnable;

    ApplicationMetadata applicationMetadata("VulkanLib", "No engine", 1, 1, vkInstanceExtensionsToEnable, vkInstanceLayersToEnable);

    return VkInstanceFactory::getInstance().getOrCreate(windowInterface, std::move(applicationMetadata));
}