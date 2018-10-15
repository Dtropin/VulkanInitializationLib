//
// Created by Tropin Denis on 09.04.2018.
//
#pragma once

#include <iostream>
#include "VkInstanceManager.h"

//VkInstance - primary object that required to build application. It stores all app states
VkInstance *VkInstanceFactory::getOrCreate(OutputWindowInterface *windowInterface,
                                           ApplicationMetadata applicationMetadata) {
    std::unique_lock<std::mutex> lock(_mutex);

    if(!isInstanceAlreadyCreated.test_and_set()) {
        auto *instance = new VkInstance();

        VkInstanceCreateInfo *vkInstanceCreateInfo = VkInstanceCreateInfoFactory::getInstance()
                .createVkInstanceCreateInfo(windowInterface, std::move(applicationMetadata));

        if (vkCreateInstance(vkInstanceCreateInfo, nullptr, instance) != VK_SUCCESS)
            throw std::runtime_error("failed to create instance!");

        cachedInstance = instance;

        return cachedInstance;
    } else {
        return cachedInstance;
    }
}

VkInstanceFactory &VkInstanceFactory::getInstance() {
    static VkInstanceFactory initializer;
    return initializer;
}