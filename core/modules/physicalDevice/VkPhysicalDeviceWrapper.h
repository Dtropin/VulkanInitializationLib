//
// Created by User on 04.08.2018.
//
#pragma once

#include <vulkan.h>
#include <xstring>
#include <vector>
#include <map>

class VkPhysicalDeviceWrapper {

private:
    VkPhysicalDevice vkPhysicalDevice;
    VkPhysicalDeviceMemoryProperties *memoryProperties;
    std::vector<VkExtensionProperties> *supportedExtensions;
    std::vector<VkQueueFamilyProperties> *queueFamiliesProperties;
    VkPhysicalDeviceFeatures *deviceFeatures;

public:
    VkPhysicalDevice getVkPhysicalDevice() const;

    const VkPhysicalDeviceMemoryProperties* getMemoryProperties() const;

    std::vector<VkExtensionProperties> *getSupportedExtensions() const;

    std::vector<VkQueueFamilyProperties> *getQueueFamiliesProperties() const;

    VkPhysicalDeviceWrapper &operator=(VkPhysicalDeviceWrapper &) = delete;

    VkPhysicalDeviceWrapper() = delete;

    ~VkPhysicalDeviceWrapper();

    VkPhysicalDeviceWrapper(VkPhysicalDevice vkp, VkPhysicalDeviceMemoryProperties *memoryProperties,
                            std::vector<VkExtensionProperties> *supportedExtensions,
                            std::vector<VkQueueFamilyProperties> *queueFamilyProperties,
                            VkPhysicalDeviceFeatures *deviceFeatures);
};