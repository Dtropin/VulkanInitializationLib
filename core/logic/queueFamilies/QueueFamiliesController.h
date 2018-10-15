//
// Created by Tropin Denis on 11.04.2018.
//
#pragma once

#include <vulkan.h>
#include <vector>
#include <functional>
/*
anything from drawing to uploading textures, requires commands to be submitted
to a queue
*/

class QueueFamiliesController {
    public:
        static QueueFamiliesController &getInstance();
        uint32_t findQueueFamilies(std::vector<VkQueueFamilyProperties>* queueFamiliesProperties,
                std::function<bool(VkQueueFamilyProperties)>peekFunction);
    private:
        QueueFamiliesController();
};
