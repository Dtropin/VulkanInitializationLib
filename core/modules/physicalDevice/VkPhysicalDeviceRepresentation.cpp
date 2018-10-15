//
// Created by User on 04.08.2018.
//

#include "VkPhysicalDeviceRepresentation.h"

VkPhysicalDeviceRepresentation::VkPhysicalDeviceRepresentation(VkPhysicalDevice* vkp,
                                                               VkPhysicalDeviceMemoryProperties memoryProperties,
                                                               std::map<std::string, std::vector<VkExtensionProperties>>* supportedExtensions,
                                                               std::vector<VkQueueFamilyProperties>* queueFamilyProperties,
                                                               VkPhysicalDeviceFeatures* deviceFeatures) {
    this->vkPhysicalDevice = vkp;
    this->memoryProperties = memoryProperties;
    this->supportedExtensions = supportedExtensions;
    this->queueFamiliesProperties = queueFamilyProperties;
    this->deviceFeatures = deviceFeatures;
}

VkPhysicalDeviceRepresentation::~VkPhysicalDeviceRepresentation() {
    supportedExtensions->clear();
}

VkPhysicalDevice *VkPhysicalDeviceRepresentation::getVkPhysicalDevice() const {
    return vkPhysicalDevice;
}

const VkPhysicalDeviceMemoryProperties &VkPhysicalDeviceRepresentation::getMemoryProperties() const {
    return memoryProperties;
}

std::map<std::string, std::vector<VkExtensionProperties>> *
VkPhysicalDeviceRepresentation::getSupportedExtensions() const {
    return supportedExtensions;
}

std::vector<VkQueueFamilyProperties> *VkPhysicalDeviceRepresentation::getQueueFamiliesProperties() const {
    return queueFamiliesProperties;
}
