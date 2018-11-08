#include <memory>

//
// Created by User on 07.11.2018.
//

#include "VkLogicalDeviceQueueCreateInfoProvider.h"
#include "../../queueFamilies/QueueFamiliesController.h"

std::vector<VkDeviceQueueCreateInfo> VkLogicalDeviceQueueCreateInfoProvider::createDeviceQueueCreateInfo(
        std::vector<VkQueueFamilyProperties> *queueFamiliesProperties,
        std::vector<std::function<bool(VkQueueFamilyProperties)>> queueFamilyPeekFunction) {

    auto deviceQueueCreateInfoVector = std::vector<VkDeviceQueueCreateInfo>();

    for (const auto &i : queueFamilyPeekFunction) {
        VkDeviceQueueCreateInfo queueCreateInfo = {};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        //Find queue family handle in form of index which is used to create appropriate queue
        queueCreateInfo.queueFamilyIndex = QueueFamiliesController::getInstance().findQueueFamilies(
                queueFamiliesProperties, i);
        queueCreateInfo.queueCount = 1;
        auto *priority = new float;
        *priority = 1.f;
        queueCreateInfo.pQueuePriorities = priority;
        deviceQueueCreateInfoVector.push_back(queueCreateInfo);
    }

    return deviceQueueCreateInfoVector;
}
