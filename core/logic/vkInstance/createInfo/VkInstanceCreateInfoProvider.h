//
// Created by Tropin Denis on 09.04.2018.
//

#pragma once

#include <vulkan.h>
#include "../../../outputwindow/OutputWindowInterface.h"
#include "../../layersAndExtensions/VkInstanceLayersProvider.h"
#include "../../../initrequestmodel/VulkanInitalizationRequestModel.h"

class VkInstanceCreateInfoProvider {
    friend class VkInstanceProvider;

    friend class IocContainer;

public:
    VkInstanceCreateInfoProvider(const VkInstanceCreateInfoProvider &) = delete;

    VkInstanceCreateInfoProvider(VkInstanceCreateInfoProvider &) = delete;

    VkInstanceCreateInfoProvider &operator=(const VkInstanceCreateInfoProvider other) = delete;

private:
    explicit VkInstanceCreateInfoProvider(std::shared_ptr<VkInstanceLayersProvider>);

    std::shared_ptr<VkInstanceLayersProvider> instanceLayersProvider;

    std::unique_ptr<VkInstanceCreateInfo> createVkInstanceCreateInfo(OutputWindowInterface *windowInterface,
                                                                     VulkanInitializationRequest::VkInstanceData*);

    VkApplicationInfo *createApplicationInfoObject(VulkanInitializationRequest::VkInstanceData*);

    VkInstanceCreateInfo *createInstanceCreateInfoObject(
            VulkanInitializationRequest::VkInstanceData*);

    std::vector<const char *>* getExtensionsToEnable(OutputWindowInterface*, VulkanInitializationRequest::VkInstanceData*);

    void injectLayersToBeEnabled(VkInstanceCreateInfo *, VulkanInitializationRequest::VkInstanceData*);

    void VkInstanceCreateInfoProvider::injectExtensionsToBeEnabled(VkInstanceCreateInfo *,
                                                                   OutputWindowInterface *,
                                                                   VulkanInitializationRequest::VkInstanceData*);

#ifdef NDEBUG
    const bool enableValidationLayers = false;
#else
    const bool enableValidationLayers = true;
#endif
};
