//
// Created by Tropin Denis on 04.04.2018.
//
#pragma once

#include <atomic>
#include <vector>
#include "../outputwindow/OutputWindowInterface.h"
#include "../modules/VulkanInterface.h"
#include "ioc/IocContainer.h"


class VulkanInitializationEntryPoint {
public:
    static VulkanInitializationEntryPoint &getInstance();
    VulkanInterface *setupVulkanSystem(OutputWindowInterface *windowInterface);
private:
    IocContainer* iocContainer;

    VulkanInitializationEntryPoint();

    VulkanInitializationEntryPoint(VulkanInitializationEntryPoint &) = delete;
    VulkanInitializationEntryPoint(const VulkanInitializationEntryPoint &) = delete;
    VulkanInitializationEntryPoint &operator=(VulkanInitializationEntryPoint &) = delete;
};