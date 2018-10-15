//
// Created by Tropin Denis on 09.04.2018.
//
#pragma once

#include <vulkan.h>
#include <mutex>
#include <atomic>
#include "../../outputwindow/OutputWindowInterface.h"
#include "createInfo/VkInstanceCreateInfoFactory.h"

class VkInstanceFactory {

    public:
        VkInstanceFactory(const VkInstanceFactory &) = delete;

        VkInstanceFactory &operator=(VkInstanceFactory &) = delete;

        static VkInstanceFactory &getInstance();

        VkInstance* getOrCreate(OutputWindowInterface *windowInterface,
                            ApplicationMetadata applicationMetadata);

    private:
        std::mutex _mutex;
        std::atomic_flag isInstanceAlreadyCreated;
        VkInstance* cachedInstance;
        VkInstanceFactory() = default;
        ~VkInstanceFactory() = default;
};

