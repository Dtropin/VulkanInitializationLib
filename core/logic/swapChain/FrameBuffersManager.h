//
// Created by Tropin Denis on 27.04.2018.
//


#include <vulkan.h>
#include <vector>
#include "../../modules/swapChain/SwapChainHandler.h"


class FrameBuffersManager {
public:
    static std::vector<VkFramebuffer>* createFrameBuffers(SwapChainHandler*, VkDevice device, VkRenderPass renderPass);
};