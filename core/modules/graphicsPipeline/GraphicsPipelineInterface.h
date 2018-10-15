//
// Created by Tropin Denis on 25.04.2018.
//
#pragma once
#include <vulkan.h>

class GraphicsPipelineInterface {

    public:
        VkPipelineLayout pipelineLayout;
        VkPipeline pipeline;
        GraphicsPipelineInterface(VkPipeline, VkPipelineLayout);
        GraphicsPipelineInterface(){}

};
