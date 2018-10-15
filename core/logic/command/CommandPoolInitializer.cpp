#include "CommandPoolInitializer.h"
#include "../queueFamilies/QueueFamiliesController.h"
#include <stdexcept>

VkCommandPool *CommandPoolInitializer::createCommandPool(VkLogicalDeviceRepresentation *deviceRepresentation) {
    VkCommandPoolCreateInfo cmdPoolCreateInfo = {
            VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
            NULL,
            VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT, // TODO этот флаг довольно важный
            deviceRepresentation->getGraphicsQueueIdx()
    };

    auto *pool = new VkCommandPool;

    //Command pool - contains command buffers which is used to record commands into queues
    vkCreateCommandPool(
            *deviceRepresentation->getVkLogicalDevice(),
            &cmdPoolCreateInfo,
            nullptr,
            pool
    );

    return pool;
}