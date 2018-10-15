//
// Created by Tropin Denis on 04.04.2018.
//
#pragma once

#include <atomic>
#include <vector>
#include "../outputwindow/OutputWindowInterface.h"
#include "../modules/VulkanInterface.h"


class VulkanInitializationEntryPoint {
public:
    static VulkanInitializationEntryPoint &getInstance();

    VulkanInterface *initializeVulkanSystem(OutputWindowInterface *windowInterface);

    VulkanInitializationEntryPoint(const VulkanInitializationEntryPoint &) = delete;

private:

    VulkanInitializationEntryPoint();

    VulkanInitializationEntryPoint &operator=(VulkanInitializationEntryPoint &) = delete;

    VkInstance *initVkInstance(OutputWindowInterface *windowInterface);

    std::atomic_flag isSystemAlreadyInitialized;
};