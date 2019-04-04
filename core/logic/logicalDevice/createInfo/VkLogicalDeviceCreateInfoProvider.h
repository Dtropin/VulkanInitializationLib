//
// Created by User on 07.11.2018.
//

#ifndef VULKANINITIALIZATIONLIB_VKLOGICALDEVICECREATEINFOPROVIDER_H
#define VULKANINITIALIZATIONLIB_VKLOGICALDEVICECREATEINFOPROVIDER_H


#include <vulkan_core.h>
#include <functional>

class VkLogicalDeviceCreateInfoProvider {
public:
    VkDeviceCreateInfo createDeviceCreateInfo(std::vector<VkDeviceQueueCreateInfo>*,
                           std::vector<const char *> &deviceExtensionsToEnable);
};


#endif //VULKANINITIALIZATIONLIB_VKLOGICALDEVICECREATEINFOPROVIDER_H
