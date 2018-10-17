//
// Created by Tropin Denis on 01.04.2018.
//
#pragma once
#include <atomic>
#include <vulkan.h> //Заголовки вулкана со структурами, функциями(интерфейсы, реализация - в библиотеке (либ))
#include "logicalDevice/VkDeviceRepresentation.h"
#include "swapChain/SwapChainHandler.h"
#include "graphicsPipeline/GraphicsPipelineInterface.h"

class VulkanInterface {
    public:
        VulkanInterface(
                VkInstance *vulkanInstance,
                VkDeviceRepresentation* logicalDevice, VkSurfaceKHR* vkSurfaceKHR, SwapChainHandler* swapChainHandler,
                GraphicsPipelineInterface* graphicsPipeline, VkRenderPass, std::vector<VkFramebuffer>* swapChainFramebuffers,
				VkCommandPool commandPool, std::vector<VkCommandBuffer>* commandBuffers);

        VkInstance* getVulkanInstance();

        ~VulkanInterface();
 
        VkSurfaceKHR* surfaceKHR;
        VkInstance* vulkanInstance;//Connection between my app and vulkan
        SwapChainHandler* swapChainHandler;
        VkDeviceRepresentation* logicalDevice; //interface to physical device. There is possibility to create few logical to one physical
        GraphicsPipelineInterface* graphicsPipeline;
        VkRenderPass vkRenderPass;
        std::vector<VkFramebuffer>* swapChainFramebuffers;
		VkCommandPool commandPool;
		std::vector<VkCommandBuffer>* commandBuffers;
};