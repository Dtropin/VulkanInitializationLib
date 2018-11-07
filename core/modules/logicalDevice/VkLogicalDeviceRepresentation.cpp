//
// Created by Tropin Denis on 14.04.2018.
//

#include "VkLogicalDeviceRepresentation.h"

VkDevice *VkLogicalDeviceRepresentation::getVkLogicalDevice() const {
    return vkLogicalDevice;
}

VkLogicalDeviceRepresentation::VkLogicalDeviceRepresentation(VkDevice *dev, int graphicsQueueIdx) {
    this->vkLogicalDevice = dev;
    this->graphicsQueueIdx = graphicsQueueIdx;
}

uint32_t VkLogicalDeviceRepresentation::getGraphicsQueueIdx() const {
    return graphicsQueueIdx;
}

uint32_t VkLogicalDeviceRepresentation::getPresentQueueIdx() const {
    return presentQueueIdx;
}

