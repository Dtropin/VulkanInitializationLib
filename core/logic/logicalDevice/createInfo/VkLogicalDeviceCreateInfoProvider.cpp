//
// Created by User on 07.11.2018.
//

#include "VkLogicalDeviceCreateInfoProvider.h"
#include "../../queueFamilies/QueueFamiliesController.h"

VkDeviceCreateInfo VkLogicalDeviceCreateInfoProvider::createDeviceCreateInfo(std::vector<VkDeviceQueueCreateInfo>* queueCreateInfos,
                                                                              std::vector<const char *> &deviceExtensionsToEnable) {

    VkDeviceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.pQueueCreateInfos = queueCreateInfos->data();
    createInfo.queueCreateInfoCount = queueCreateInfos->size();
    createInfo.enabledExtensionCount = deviceExtensionsToEnable.size();
    createInfo.ppEnabledExtensionNames = deviceExtensionsToEnable.data();
    createInfo.ppEnabledLayerNames = nullptr;
    createInfo.pEnabledFeatures = nullptr;
    createInfo.enabledLayerCount = 0;
    return createInfo;
}
