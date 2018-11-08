//
// Created by User on 07.11.2018.
//

#ifndef VULKANINITIALIZATIONLIB_VKLOGICALDEVICEQUEUECREATEINFOPROVIDER_H
#define VULKANINITIALIZATIONLIB_VKLOGICALDEVICEQUEUECREATEINFOPROVIDER_H

#include <vector>
#include <functional>
#include <vulkan_core.h>

class VkLogicalDeviceQueueCreateInfoProvider {
public:
    std::vector<VkDeviceQueueCreateInfo> createDeviceQueueCreateInfo(
            std::vector<VkQueueFamilyProperties> *queueFamiliesProperties,
            std::vector<std::function<bool(VkQueueFamilyProperties)>> queueFamilyPeekFunction);
};


#endif //VULKANINITIALIZATIONLIB_VKLOGICALDEVICEQUEUECREATEINFOPROVIDER_H
