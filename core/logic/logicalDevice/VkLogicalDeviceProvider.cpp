//
// Created by Tropin Denis on 11.04.2018.
//

#include <stdexcept>
#include <iostream>
#include <utility>
#include <string>
#include <set>
#include "VkLogicalDeviceProvider.h"
#include "../../utils/VulkanInitializationErrorMessageUtils.h"
#include "../queueFamilies/QueueFamiliesController.h"

VkDeviceCreateInfo *
VkLogicalDeviceProvider::createDeviceCreateInfo(std::vector<VkDeviceQueueCreateInfo *> queueCreateInfos,
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
VkLogicalDeviceProvider::createDeviceQueueCreateInfo(std::vector<VkQueueFamilyProperties> *queueFamiliesProperties,
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

std::unique_ptr<VkLogicalDeviceRepresentation>
VkLogicalDeviceProvider::create(VkPhysicalDeviceWrapper *const vkPhysicalDeviceWrapper,
                                std::vector<const char *>,
                                std::vector<std::function<bool(VkQueueFamilyProperties)>>) {

    auto vkDevice = new VkDevice;

    VkResult deviceCreationResult = vkCreateDevice(*vkPhysicalDeviceWrapper->getVkPhysicalDevice(),
                                                   nullptr,
                                                   nullptr,
                                                   vkDevice);

    if (deviceCreationResult != VK_SUCCESS) {
        std::string errorMessageToThrow = formErrorMessageFromVkResult("Can't create logical device, vkResult is ",
                                                                       deviceCreationResult);
        throw std::runtime_error(errorMessageToThrow);
    }

    return std::unique_ptr<VkLogicalDeviceRepresentation>(new VkLogicalDeviceRepresentation());
}

