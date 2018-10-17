//
// Created by Tropin Denis on 11.04.2018.
//
#pragma once

#include <vulkan.h>
#include <mutex>
#include <atomic>
#include "../../modules/logicalDevice/VkDeviceRepresentation.h"
#include "../../modules/physicalDevice/VkPhysicalDeviceWrapper.h"

class VkLogicalDeviceProvider {
    friend class IocContainer;

public:
    VkDeviceRepresentation *create(VkPhysicalDeviceWrapper *,
                                                std::vector<const char *>,
                                                std::vector<std::function<bool(VkQueueFamilyProperties)>>);

private:
    VkLogicalDeviceProvider() = default;

    VkDeviceRepresentation *cachedDevice;

    VkDeviceCreateInfo *
    createDeviceCreateInfo(std::vector<VkDeviceQueueCreateInfo *>, std::vector<const char *> &deviceExtensionsToEnable);

    std::vector<VkDeviceQueueCreateInfo *>
    createDeviceQueueCreateInfo(std::vector<VkQueueFamilyProperties> *queueFamiliesProperties,
                                std::vector<std::function<bool(VkQueueFamilyProperties)>> queueFamilyPeekFunction);

    VkDeviceRepresentation *createLogicalDevice(
            VkPhysicalDeviceWrapper *deviceRepresentation,
            std::vector<const char *> deviceExtensionsToEnable,
            std::vector<std::function<bool(
                    VkQueueFamilyProperties)>> queueFamilyPeekFunction);
};
