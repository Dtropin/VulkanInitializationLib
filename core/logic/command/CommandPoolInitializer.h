#pragma once
#include <vulkan.h>
#include "../../modules/logicalDevice/VkLogicalDeviceRepresentation.h"

class CommandPoolInitializer {
public:
	static VkCommandPool* createCommandPool(VkLogicalDeviceRepresentation* deviceRepresentation);
};