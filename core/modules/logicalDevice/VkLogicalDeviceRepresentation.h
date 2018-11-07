//
// Created by Tropin Denis on 14.04.2018.
//

#pragma once

#include <vulkan.h>

class VkLogicalDeviceRepresentation {
public:
    VkLogicalDeviceRepresentation(VkDevice *, int graphicsQueueIdx);

    VkDevice *getVkLogicalDevice() const;

    uint32_t getGraphicsQueueIdx() const;

    uint32_t getPresentQueueIdx() const;

private:
    // physical device data
    VkDevice *vkLogicalDevice;//interface to physical device
   uint32_t graphicsQueueIdx; //Idx of graphics queue
    uint32_t presentQueueIdx; //Idx of graphics queue
};