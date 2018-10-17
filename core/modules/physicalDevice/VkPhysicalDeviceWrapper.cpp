//
// Created by User on 04.08.2018.
//

#include "VkPhysicalDeviceWrapper.h"

VkPhysicalDeviceWrapper::VkPhysicalDeviceWrapper(VkPhysicalDevice* vkp,
                                                               VkPhysicalDeviceMemoryProperties* memoryProperties,
                                                               std::vector<VkExtensionProperties>* supportedExtensions,
                                                               std::vector<VkQueueFamilyProperties>* queueFamilyProperties,
                                                               VkPhysicalDeviceFeatures* deviceFeatures) {
    this->vkPhysicalDevice = vkp;
    this->memoryProperties = memoryProperties;
    this->supportedExtensions = supportedExtensions;
    this->queueFamiliesProperties = queueFamilyProperties;
    this->deviceFeatures = deviceFeatures;
}

VkPhysicalDeviceWrapper::~VkPhysicalDeviceWrapper() {
    supportedExtensions->clear();
}

VkPhysicalDevice *VkPhysicalDeviceWrapper::getVkPhysicalDevice() const {
    return vkPhysicalDevice;
}

const VkPhysicalDeviceMemoryProperties* VkPhysicalDeviceWrapper::getMemoryProperties() const {
    return memoryProperties;
}

std::vector<VkQueueFamilyProperties> *VkPhysicalDeviceWrapper::getQueueFamiliesProperties() const {
    return queueFamiliesProperties;
}

std::vector<VkExtensionProperties> *VkPhysicalDeviceWrapper::getSupportedExtensions() const {
    return supportedExtensions;
}
