//
// Created by User on 26.10.2018.
//

#include "VkPhysicalDevicePropertiesExtractor.h"


//get info about supported queue families(types) by device
std::vector<VkQueueFamilyProperties> *
VkPhysicalDevicePropertiesExtractor::getDeviceQueueFamilies(VkPhysicalDevice *physicalDevice) const {
    uint32_t count;
    auto *properties = new std::vector<VkQueueFamilyProperties>();
    vkGetPhysicalDeviceQueueFamilyProperties(*physicalDevice, &count, NULL);
    properties->resize(count);
    vkGetPhysicalDeviceQueueFamilyProperties(*physicalDevice, &count, properties->data());
    return properties;
}

VkPhysicalDeviceFeatures *VkPhysicalDevicePropertiesExtractor::getDeviceFeatures(VkPhysicalDevice device) const {
    auto *features = new VkPhysicalDeviceFeatures();
    vkGetPhysicalDeviceFeatures(device, features);
    return features;
}

VkPhysicalDeviceMemoryProperties *VkPhysicalDevicePropertiesExtractor::getMemoryProperties(VkPhysicalDevice device) const {
    auto * memoryProperties = new VkPhysicalDeviceMemoryProperties();
    vkGetPhysicalDeviceMemoryProperties(device, memoryProperties);
    return memoryProperties;
}