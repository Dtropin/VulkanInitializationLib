//
// Created by Tropin Denis on 09.04.2018.
//
#pragma once

#include <iostream>
#include "VkInstanceProvider.h"

VkInstanceProvider::VkInstanceProvider(std::shared_ptr<VkInstanceCreateInfoProvider> sptr) :
        vkInstanceCreateInfoProvider(std::move(sptr)) {}

//VkInstance - primary object that required to build application. It stores all app states
std::unique_ptr<VkInstance> VkInstanceProvider::create(OutputWindowInterface *windowInterface,
                                                       VulkanInitializationRequest::VkInstanceData* vkInstanceData) const {
    auto *instance = new VkInstance;

    std::unique_ptr<VkInstanceCreateInfo> vkInstanceCreateInfo =
            vkInstanceCreateInfoProvider->createVkInstanceCreateInfo(windowInterface, vkInstanceData);

    if (vkCreateInstance(vkInstanceCreateInfo.get(), nullptr, instance) != VK_SUCCESS)
        throw std::runtime_error("failed to create instance!");

    return std::unique_ptr<VkInstance>(instance);
}