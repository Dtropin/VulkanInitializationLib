//
// Created by Tropin Denis on 09.04.2018.
//
#pragma once

#include <vulkan.h>
#include <mutex>
#include <atomic>
#include "../../outputwindow/OutputWindowInterface.h"
#include "createInfo/VkInstanceCreateInfoProvider.h"
#include "../../initrequestmodel/VulkanInitalizationRequestModel.h"
#include "../layersAndExtensions/VkInstanceLayersProvider.h"
#include "../../modules/vkinstance/VkInstanceWrapper.h"

class VkInstanceProvider {
    friend class IocContainer;

public:
    explicit VkInstanceProvider(std::shared_ptr<VkInstanceCreateInfoProvider>);

    std::shared_ptr<VkInstance> create(OutputWindowInterface *windowInterface,
                                       VulkanInitializationRequest::VkInstanceData* vkInstanceData) const;

private:
    std::shared_ptr<VkInstanceCreateInfoProvider> vkInstanceCreateInfoProvider;
};

