//
// Created by Tropin Denis on 14.04.2018.
//

#include "VkLogicalDeviceRepresentation.h"

VkDevice *VkLogicalDeviceRepresentation::getVkLogicalDevice() const {
    return vkLogicalDevice;
}


uint32_t VkLogicalDeviceRepresentation::getGraphicsQueueIdx() const {
    return graphicsQueueIdx;
}

uint32_t VkLogicalDeviceRepresentation::getPresentQueueIdx() const {
    return presentQueueIdx;
}

VkLogicalDeviceRepresentation::VkLogicalDeviceRepresentation(VkDevice* device) : vkLogicalDevice(device) {}

