//
// Created by Tropin Denis on 11.04.2018.
//
#pragma once
#include <vulkan.h>
#include <mutex>
#include <atomic>
#include "../../modules/logicalDevice/VkLogicalDeviceRepresentation.h"
#include "../../modules/physicalDevice/VkPhysicalDeviceRepresentation.h"

class VkLogicalDeviceManager {
    public:
        static VkLogicalDeviceManager &getInstance();
        VkLogicalDeviceRepresentation* getOrCreate(VkPhysicalDeviceRepresentation* deviceRepresentation, std::vector<const char *>,
                                                   std::vector<std::function<bool(VkQueueFamilyProperties)>>);
    private:
        VkLogicalDeviceManager() = default;
        VkLogicalDeviceRepresentation* cachedDevice;
        VkDeviceCreateInfo* createDeviceCreateInfo(std::vector<VkDeviceQueueCreateInfo*>, std::vector<const char *>& deviceExtensionsToEnable);
        std::vector<VkDeviceQueueCreateInfo*> createDeviceQueueCreateInfo(std::vector<VkQueueFamilyProperties>* queueFamiliesProperties,
                                                             std::vector<std::function<bool(VkQueueFamilyProperties)>>queueFamilyPeekFunction);
};
