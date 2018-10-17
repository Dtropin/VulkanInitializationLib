#pragma once
#include <vulkan.h>
#include "../../modules/logicalDevice/VkDeviceRepresentation.h"

class CommandPoolInitializer {
public:
	static VkCommandPool* createCommandPool(VkDeviceRepresentation* deviceRepresentation);
};