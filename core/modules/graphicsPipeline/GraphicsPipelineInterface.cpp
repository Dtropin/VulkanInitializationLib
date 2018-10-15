//
// Created by Tropin Denis on 25.04.2018.
//

#include "GraphicsPipelineInterface.h"

GraphicsPipelineInterface::GraphicsPipelineInterface(VkPipeline pipeline, VkPipelineLayout pipelineLayout) {
    this->pipeline = pipeline;
    this->pipelineLayout = pipelineLayout;
}

