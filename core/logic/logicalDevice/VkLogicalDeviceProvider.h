//
// Created by Tropin Denis on 11.04.2018.
//
#pragma once

#include <vulkan.h>
#include <mutex>
#include <atomic>
#include "../../modules/logicalDevice/VkLogicalDeviceRepresentation.h"
#include "../../modules/physicalDevice/VkPhysicalDeviceWrapper.h"
#include "createInfo/VkLogicalDeviceCreateInfoProvider.h"
#include "createInfo/VkLogicalDeviceQueueCreateInfoProvider.h"

class VkLogicalDeviceProvider {
    friend class IocContainer;

public:
    std::shared_ptr<VkLogicalDeviceRepresentation> create(VkPhysicalDeviceWrapper *,
                                                          std::vector<const char *> *,
                                                          std::vector<std::function<bool(VkQueueFamilyProperties)>>) const;

private:
    explicit VkLogicalDeviceProvider(std::shared_ptr<VkLogicalDeviceCreateInfoProvider>,
                                     std::shared_ptr<VkLogicalDeviceQueueCreateInfoProvider>);

    VkDevice* createLogicalDevice(VkDeviceCreateInfo const * deviceCreateInfo,
                                                  VkPhysicalDevice vkPhysicalDevice) const;

    std::shared_ptr<VkLogicalDeviceCreateInfoProvider> vkLogicalDeviceCreateInfoProvider;
    std::shared_ptr<VkLogicalDeviceQueueCreateInfoProvider> vkLogicalDeviceQueueCreateInfoProvider;
};
