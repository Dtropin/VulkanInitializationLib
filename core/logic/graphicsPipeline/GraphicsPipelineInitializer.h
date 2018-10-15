//
// Created by Tropin Denis on 24.04.2018.
//

#pragma once

#include <vulkan.h>
#include <vector>
#include "../../modules/swapChain/SwapChainHandler.h"
#include "../../modules/graphicsPipeline/GraphicsPipelineInterface.h"

class GraphicsPipelineInitializer {
public:
    static GraphicsPipelineInterface *createGraphicsPipeline(VkDevice, SwapChainHandler, VkRenderPass);

private:
    static VkShaderModule createShaderModule(const std::vector<char> &code, VkDevice);
};