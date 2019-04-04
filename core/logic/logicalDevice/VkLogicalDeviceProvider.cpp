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

std::shared_ptr<VkLogicalDeviceRepresentation>
VkLogicalDeviceProvider::create(VkPhysicalDeviceWrapper *const vkPhysicalDeviceWrapper,
                                std::vector<const char *> *const deviceExtensionsToEnable,
                                std::vector<std::function<bool(VkQueueFamilyProperties)>> queueFamilyPeekFunction) const {

    auto queueCreateInfo =
            vkLogicalDeviceQueueCreateInfoProvider->createDeviceQueueCreateInfo(
                    vkPhysicalDeviceWrapper->getQueueFamiliesProperties(),
                    std::move(queueFamilyPeekFunction));

    VkDeviceCreateInfo deviceCreateInfo =
            vkLogicalDeviceCreateInfoProvider->createDeviceCreateInfo(queueCreateInfo, *deviceExtensionsToEnable);

    VkDevice* vkDevice = createLogicalDevice(&deviceCreateInfo, vkPhysicalDeviceWrapper->getVkPhysicalDevice());

    return std::make_unique<VkLogicalDeviceRepresentation>(vkDevice);
}

VkDevice* VkLogicalDeviceProvider::createLogicalDevice(VkDeviceCreateInfo const * deviceCreateInfo,
                                             VkPhysicalDevice vkPhysicalDevice) const {
    auto vkDevice = new VkDevice;
	
	VkResult deviceCreationResult = vkCreateDevice(vkPhysicalDevice,
			deviceCreateInfo,
			nullptr,
			vkDevice);

    if (deviceCreationResult != VK_SUCCESS) {
        std::string errorMessageToThrow = formErrorMessageFromVkResult("Can't create logical device, vkResult is ",
                                                                       deviceCreationResult);
        throw std::runtime_error(errorMessageToThrow);
    }
	
    return vkDevice;
}


VkLogicalDeviceProvider::VkLogicalDeviceProvider(std::shared_ptr<VkLogicalDeviceCreateInfoProvider> provider1,
                                                 std::shared_ptr<VkLogicalDeviceQueueCreateInfoProvider> provider2)
        : vkLogicalDeviceCreateInfoProvider(std::move(provider1)),
          vkLogicalDeviceQueueCreateInfoProvider(std::move(provider2)) {}

