//
// Created by Tropin Denis on 27.04.2018.
//

#include "FrameBuffersManager.h"
#include <iostream>

std::vector<VkFramebuffer> *FrameBuffersManager::createFrameBuffers(SwapChainHandler* swapChainHandler, VkDevice device, VkRenderPass renderPass) {
	std::vector<VkFramebuffer> * swapChainFramebuffers = new std::vector<VkFramebuffer>();
    swapChainFramebuffers->resize(swapChainHandler->swapChainImageViews.size());

    for (size_t i = 0; i < swapChainHandler->swapChainImageViews.size(); i++) {
        VkImageView attachments[] = {
                swapChainHandler->swapChainImageViews[i]
        };
        VkFramebufferCreateInfo framebufferInfo = {};
        framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebufferInfo.renderPass = renderPass;
        framebufferInfo.attachmentCount = 1;
        framebufferInfo.pAttachments = attachments;
        framebufferInfo.width = swapChainHandler->swapChainExtent.width;
        framebufferInfo.height = swapChainHandler->swapChainExtent.height;
        framebufferInfo.layers = 1;
		VkFramebuffer buffer = swapChainFramebuffers->at(i);
        if (vkCreateFramebuffer(device, &framebufferInfo, nullptr, &(buffer)) != VK_SUCCESS) {
            throw std::runtime_error("failed to create framebuffer!");
        }
		swapChainFramebuffers->at(i) = buffer;
    }

    return swapChainFramebuffers;
}
