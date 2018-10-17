//
// Created by Tropin Denis on 14.04.2018.
//

#include "VkDeviceRepresentation.h"

VkDevice *VkDeviceRepresentation::getVkLogicalDevice() const {
    return vkLogicalDevice;
}

VkDeviceRepresentation::VkDeviceRepresentation(VkDevice *dev, int graphicsQueueIdx) {
    this->vkLogicalDevice = dev;
    this->graphicsQueueIdx = graphicsQueueIdx;
}

uint32_t VkDeviceRepresentation::getGraphicsQueueIdx() const {
    return graphicsQueueIdx;
}

uint32_t VkDeviceRepresentation::getPresentQueueIdx() const {
    return presentQueueIdx;
}

