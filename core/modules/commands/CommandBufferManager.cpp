#include "CommandBufferManager.h"

std::vector<VkCommandBuffer>* CommandBufferManager::createCommandBuffers(std::vector<VkFramebuffer>* swapChainFramebuffers,
	VkCommandPool commandPool, VkDevice device, VkRenderPass renderPass, SwapChainHandler* swapChainHandler, GraphicsPipelineInterface* graphicsPipeline) {
	std::vector<VkCommandBuffer>* commandBuffer = new std::vector<VkCommandBuffer>();
	commandBuffer->resize(swapChainFramebuffers->size());
	VkCommandBufferAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = commandPool;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;

	allocInfo.commandBufferCount = (uint32_t)commandBuffer->size();

	if (vkAllocateCommandBuffers(device, &allocInfo, commandBuffer->data()) != VK_SUCCESS) {
		throw std::runtime_error("failed to allocate command buffers!");
	}

	for (size_t i = 0; i < commandBuffer->size(); i++) {
		VkCommandBufferBeginInfo beginInfo = {};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		beginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
		beginInfo.pInheritanceInfo = nullptr; // Optional
		vkBeginCommandBuffer(commandBuffer->at(i), &beginInfo);

		VkRenderPassBeginInfo renderPassInfo = {};
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		renderPassInfo.renderPass = renderPass;
		renderPassInfo.framebuffer = swapChainFramebuffers->at(i);
		renderPassInfo.renderArea.offset = { 0, 0 };
		renderPassInfo.renderArea.extent = swapChainHandler->swapChainExtent;
		VkClearValue clearColor = { 0.0f, 0.0f, 0.0f, 1.0f };
		renderPassInfo.clearValueCount = 1;
		renderPassInfo.pClearValues = &clearColor;
		vkCmdBeginRenderPass(commandBuffer->at(i), &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
		vkCmdBindPipeline(commandBuffer->at(i), VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline->pipeline);
		vkCmdDraw(commandBuffer->at(i), 3, 1, 0, 0);
		vkCmdEndRenderPass(commandBuffer->at(i));
		if (vkEndCommandBuffer(commandBuffer->at(i)) != VK_SUCCESS) {
			throw std::runtime_error("failed to record command buffer!");
		}
	}

	return commandBuffer;
}