//
// Created by Tropin Denis on 25.04.2018.
//


#include <vulkan.h>
#include "../../modules/swapChain/SwapChainHandler.h"

class RenderPassInitializer {
    public:
        static VkRenderPass createRenderPass(SwapChainHandler swapChainHandler, VkDevice device);
};

