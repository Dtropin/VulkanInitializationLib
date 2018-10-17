//
// Created by User on 17.10.2018.
//
#pragma once
#include <vector>
#include <functional>
#include <vulkan.h>
//TODO почитать про инклуды, как правильно организовать

struct VulkanInitializationRequest {

    struct VkInstanceData {
        std::vector<const char *> vkInstanceLayersToEnable;
        std::vector<const char *> vkInstanceExtensionsToEnable;
        const char *appName;
        const char *engineName;
        uint32_t appVersion;
        uint32_t engineVersion;
    };

    VkInstanceData vkInstanceData;

    struct PhysicalDeviceRequirements {
        std::vector<const char *> requiredDeviceExtensions;
        std::vector<std::function<bool(VkQueueFamilyProperties)>> queueFamilyRequirementFunctions;
    };

    PhysicalDeviceRequirements physicalDeviceRequirements;

};