#pragma once
#include <vector>
#include <vulkan.h>
#include "../swapChain/SwapChainHandler.h"
#include "../graphicsPipeline/GraphicsPipelineInterface.h"
class CommandBufferManager {

public:
	static std::vector<VkCommandBuffer>* createCommandBuffers(std::vector<VkFramebuffer>* swapChainFramebuffers, VkCommandPool, VkDevice device, 
		VkRenderPass renderPass, SwapChainHandler* swapChainHandler, GraphicsPipelineInterface* graphicsPipeline);
};
