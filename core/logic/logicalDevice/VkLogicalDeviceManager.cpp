//
// Created by Tropin Denis on 11.04.2018.
//

#include <stdexcept>
#include <iostream>
#include <utility>
#include <set>
#include "VkLogicalDeviceManager.h"
#include "../queueFamilies/QueueFamiliesController.h"

VkLogicalDeviceManager &VkLogicalDeviceManager::getInstance() {
    static VkLogicalDeviceManager initializer;
    return initializer;
}

VkLogicalDeviceRepresentation *VkLogicalDeviceManager::getOrCreate(VkPhysicalDeviceRepresentation *deviceRepresentation,
                                                                   std::vector<const char *> deviceExtensionsToEnable,
                                                                   std::vector<std::function<bool(
                                                                           VkQueueFamilyProperties)>> queueFamilyPeekFunction) {
    //Info about what queues need to create for this device
    std::vector<VkDeviceQueueCreateInfo *> queueCreateInfos = createDeviceQueueCreateInfo(
            deviceRepresentation->getQueueFamiliesProperties(),
            std::move(queueFamilyPeekFunction));
    //Info about device going to create
    VkDeviceCreateInfo *deviceCreateInfo = createDeviceCreateInfo(queueCreateInfos, deviceExtensionsToEnable);

    auto *device = new VkDevice;
	
	VkResult res = vkCreateDevice(*deviceRepresentation->getVkPhysicalDevice(),
		deviceCreateInfo, nullptr, device);
    
	if (res != VK_SUCCESS)
        throw std::runtime_error("failed to create logical device!");

    auto *logicalDevice = new VkLogicalDeviceRepresentation(device, queueCreateInfos.data()[0]->queueFamilyIndex);
    this->cachedDevice = logicalDevice;
    return cachedDevice;
}


VkDeviceCreateInfo *
VkLogicalDeviceManager::createDeviceCreateInfo(std::vector<VkDeviceQueueCreateInfo *> queueCreateInfos,
                                               std::vector<const char *> &deviceExtensionsToEnable) {
    auto *createInfo = new VkDeviceCreateInfo();
    createInfo->sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo->pQueueCreateInfos = *queueCreateInfos.data();
    createInfo->queueCreateInfoCount = queueCreateInfos.size();
    //createInfo.pEnabledFeatures = &deviceFeaturs;//TODO С этим стоит быть аккуратнее
    createInfo->enabledExtensionCount = deviceExtensionsToEnable.size();
    createInfo->ppEnabledExtensionNames = deviceExtensionsToEnable.data();
    createInfo->ppEnabledLayerNames = nullptr;
    createInfo->enabledLayerCount = 0;
    return createInfo;
}

std::vector<VkDeviceQueueCreateInfo *>
VkLogicalDeviceManager::createDeviceQueueCreateInfo(std::vector<VkQueueFamilyProperties> *queueFamiliesProperties,
                                                    std::vector<std::function<bool(
                                                            VkQueueFamilyProperties)>> queueFamilyPeekFunction) {
    std::vector<VkDeviceQueueCreateInfo *> vector;

    for (const auto &i : queueFamilyPeekFunction) {
        auto *queueCreateInfo = new VkDeviceQueueCreateInfo();
        queueCreateInfo->sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        //Find queue family handle in form of index which is used to create appropriate queue
        queueCreateInfo->queueFamilyIndex = QueueFamiliesController::getInstance().findQueueFamilies(
                queueFamiliesProperties, i);
        queueCreateInfo->queueCount = 1;
        auto *priority = new float;
        *priority = 1.f;
        queueCreateInfo->pQueuePriorities = priority;
        vector.push_back(queueCreateInfo);
    }

    return vector;
}

