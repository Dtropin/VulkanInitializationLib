//
// Created by Tropin Denis on 04.04.2018.
//
#pragma once

#include <stdexcept>
#include <glfw3.h>
#include <iostream>
#include <vector>
#include "VulkanInitializationEntryPoint.h"
#include "../modules/physicalDevice/VkPhysicalDeviceWrapper.h"
#include "logicalDevice/VkLogicalDeviceProvider.h"
#include "command/CommandPoolInitializer.h"
#include "swapChain/VkSwapChainManager.h"
#include "renderPass/RenderPassInitializer.h"
#include "graphicsPipeline/GraphicsPipelineInitializer.h"
#include "swapChain/FrameBuffersManager.h"
#include "../modules/commands/CommandBufferManager.h"
#include "vkInstance/VkInstanceProvider.h"

VulkanInitializationEntryPoint &VulkanInitializationEntryPoint::getInstance() {
    static VulkanInitializationEntryPoint initializer;
    return initializer;
}

VulkanInitializationEntryPoint::VulkanInitializationEntryPoint()
        : iocContainer(&IocContainer::getInstance()) {}

VulkanInitializationRequest debugRequest() {
    VulkanInitializationRequest request;

    VulkanInitializationRequest::PhysicalDeviceRequirements pdr;

    request.vkInstanceData.vkInstanceLayersToEnable = {
            "VK_LAYER_LUNARG_api_dump"
    };
	request.vkInstanceData.appName = "123";
	request.vkInstanceData.appVersion = 1;
	request.vkInstanceData.engineName = "lalka";
	request.vkInstanceData.engineVersion = 1;

    request.physicalDeviceRequirements.requiredDeviceExtensions = {
            //VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };

    request.physicalDeviceRequirements.queueFamilyRequirementFunctions.emplace_back([](VkQueueFamilyProperties prop) {
        return prop.queueFlags & VK_QUEUE_GRAPHICS_BIT;
    });

    return request;
}

VulkanInterface *VulkanInitializationEntryPoint::setupVulkanSystem(OutputWindowInterface *windowInterface) {
    //into args
    auto request = debugRequest();

    //TODO Валидатор для instance layers, поддерживаются ли они системой

    std::shared_ptr<VkInstanceLayersProvider> vkInstanceLayersProvider = iocContainer->getVkInstanceLayersProvider();
    std::shared_ptr<VkInstanceLayersWrapper> vkInstanceLayers = vkInstanceLayersProvider->getInstanceLayersAndExtensions();

    std::shared_ptr<VkInstanceProvider> vkInstanceProvider = iocContainer->getVkInstanceProvider();
    std::shared_ptr<VkInstance> vkInstance = vkInstanceProvider->create(windowInterface, &request.vkInstanceData);

    std::shared_ptr<VkPhysicalDeviceDetector> vkPhysicalDeviceProvider = iocContainer->getVkPhysicalDeviceDetector();
    std::shared_ptr<VkPhysicalDeviceWrapper> appropriatePhysicalDevice = vkPhysicalDeviceProvider->findSatisfyingDevices(
            vkInstance.get(), vkInstanceLayers.get(), request.physicalDeviceRequirements);

    std::shared_ptr<VkLogicalDeviceProvider> vkLogicalDeviceProvider = iocContainer->getVkLogicalDeviceProvider();

    std::shared_ptr<VkLogicalDeviceRepresentation> vkLogicalDevice = vkLogicalDeviceProvider->create(
            appropriatePhysicalDevice.get(),
            &request.physicalDeviceRequirements.requiredDeviceExtensions,
            request.physicalDeviceRequirements.queueFamilyRequirementFunctions);

    //TODO Определится что же все таки делать со смарт пойнтерами, особенно unique
    /**

    VkCommandPool *commandPool = CommandPoolInitializer::
    createCommandPool(logicalDevice);

    VkSurfaceKHR *vkSurface = windowInterface->getWindowSurface(vkInstance);

    SwapChainHandler *swapchain = VkSwapChainManager::getInstance().createSwapChain(
            *pickedPhysicalDevice->getVkPhysicalDevice(),
            *vkSurface, logicalDevice);

    VkRenderPass renderPass = RenderPassInitializer::createRenderPass(*swapchain, *logicalDevice->getVkLogicalDevice());
    GraphicsPipelineInterface *pipelineLayout = GraphicsPipelineInitializer::createGraphicsPipeline(
            *logicalDevice->getVkLogicalDevice(), *swapchain, renderPass);
    std::vector<VkFramebuffer> *frameBuffers = FrameBuffersManager::createFrameBuffers(swapchain,
                                                                                       *logicalDevice->getVkLogicalDevice(),
                                                                                       renderPass);

    std::vector<VkCommandBuffer> *commandBuffers = CommandBufferManager::createCommandBuffers(frameBuffers,
                                                                                              *commandPool,
                                                                                              *logicalDevice->getVkLogicalDevice(),
                                                                                              renderPass, swapchain,
                                                                                              pipelineLayout);

    return new VulkanInterface(vkInstance, logicalDevice, vkSurface, swapchain, pipelineLayout, renderPass,
                               frameBuffers, *commandPool, commandBuffers);**/


    vkDestroyDevice(*vkLogicalDevice->getVkLogicalDevice(), nullptr);
    vkDestroyInstance(*vkInstance, nullptr);

    return nullptr;
}