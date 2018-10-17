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
    std::unique_ptr<VkInstanceLayersWrapper> vkInstanceLayers = vkInstanceLayersProvider->getInstanceLayersAndExtensions();

    std::shared_ptr<VkInstanceProvider> vkInstanceProvider = iocContainer->getVkInstanceProvider();
    std::unique_ptr<VkInstance> vkInstance = vkInstanceProvider->create(windowInterface, &request.vkInstanceData);

    std::shared_ptr<VkPhysicalDeviceDetector> vkPhysicalDeviceProvider = iocContainer->getVkPhysicalDeviceDetector();
    std::unique_ptr<VkPhysicalDeviceWrapper> appropriatePhysicalDevice = vkPhysicalDeviceProvider->findSatisfyingDevices(
            vkInstance.get(), vkInstanceLayers.get(), request.physicalDeviceRequirements);

    //const VkLogicalDeviceProvider* vkLogicalDeviceProvider = iocContainer->getVkLogicalDeviceProvider();
    //vkLogicalDeviceProvider->create();

    /**

    VkDeviceRepresentation *logicalDevice = VkDeviceProvider
            .getOrCreate(availiablePhysicalDevices, deviceExtensionsToEnable, queueFamilyPeekFunction);

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
    return nullptr;
}