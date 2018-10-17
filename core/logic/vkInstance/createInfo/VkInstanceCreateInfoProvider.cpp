#include <utility>

// Created by Tropin Denis on 09.04.2018.
//

#include <iostream>
#include <utility>
#include "VkInstanceCreateInfoProvider.h"
#include "../../../outputwindow/OutputWindowInterface.h"
#include "../../layersAndExtensions/VkInstanceLayersProvider.h"

std::unique_ptr<VkInstanceCreateInfo> VkInstanceCreateInfoProvider::createVkInstanceCreateInfo(OutputWindowInterface *windowInterface,
                                                                               VulkanInitializationRequest::VkInstanceData* vkInstanceInitializationData) {
    VkInstanceCreateInfo *createInfo = createInstanceCreateInfoObject(vkInstanceInitializationData);
    injectLayersToBeEnabled(createInfo, vkInstanceInitializationData);
    injectExtensionsToBeEnabled(createInfo, windowInterface, vkInstanceInitializationData);
    return std::unique_ptr<VkInstanceCreateInfo>(createInfo);
}

void VkInstanceCreateInfoProvider::injectLayersToBeEnabled(VkInstanceCreateInfo *toInject,
                                                           VulkanInitializationRequest::VkInstanceData* initializationData) {
    toInject->enabledLayerCount = initializationData->vkInstanceLayersToEnable.size();
    toInject->ppEnabledLayerNames = initializationData->vkInstanceLayersToEnable.data();
}

void VkInstanceCreateInfoProvider::injectExtensionsToBeEnabled(VkInstanceCreateInfo *toInject,
                                                               OutputWindowInterface *windowInterface,
                                                               VulkanInitializationRequest::VkInstanceData* vkInstanceInitializationData) {
    std::vector<const char *> *extensionsToEnable = getExtensionsToEnable(windowInterface,
                                                                          vkInstanceInitializationData);
    toInject->enabledExtensionCount = extensionsToEnable->size();
    toInject->ppEnabledExtensionNames = extensionsToEnable->data();
}

std::vector<const char *> *VkInstanceCreateInfoProvider::getExtensionsToEnable(OutputWindowInterface *windowInterface,
                                                                               VulkanInitializationRequest::VkInstanceData* initializationData) {
    std::vector<const char *> *extensionsFromWindowSystem = windowInterface->getExtensionsForVulkan()->supportedExtensions;
    std::vector<const char *> additionalExtensionsDefinedByUser = initializationData->vkInstanceExtensionsToEnable;

    auto *mergedExtensionsVector = new std::vector<const char *>;
    mergedExtensionsVector->insert(mergedExtensionsVector->end(), extensionsFromWindowSystem->begin(),
                                   extensionsFromWindowSystem->end());
    mergedExtensionsVector->insert(mergedExtensionsVector->end(), additionalExtensionsDefinedByUser.begin(),
                                   additionalExtensionsDefinedByUser.end());
    return mergedExtensionsVector;
}

VkInstanceCreateInfo *VkInstanceCreateInfoProvider::createInstanceCreateInfoObject(
        VulkanInitializationRequest::VkInstanceData* applicationMetadata) {
    auto *createInfo = new VkInstanceCreateInfo();
    createInfo->sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo->pApplicationInfo = createApplicationInfoObject(applicationMetadata);
    createInfo->pNext = nullptr;
    createInfo->flags = VkInstanceCreateFlags();
    return createInfo;
}

//Create information about application - version, name and so on
VkApplicationInfo *VkInstanceCreateInfoProvider::createApplicationInfoObject(
        VulkanInitializationRequest::VkInstanceData* applicationMetadata) {
    auto *appInfo = new VkApplicationInfo;
    appInfo->sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo->pApplicationName = applicationMetadata->appName;
    appInfo->pEngineName = applicationMetadata->engineName;
    appInfo->applicationVersion = VK_MAKE_VERSION(applicationMetadata->appVersion, 0, 0);
    appInfo->engineVersion = VK_MAKE_VERSION(applicationMetadata->engineVersion, 0, 0);
    appInfo->apiVersion = VK_API_VERSION_1_0;
    appInfo->pNext = nullptr;
    return appInfo;
}

VkInstanceCreateInfoProvider::VkInstanceCreateInfoProvider(std::shared_ptr<VkInstanceLayersProvider> layersProvider) :
        instanceLayersProvider(std::move(layersProvider)) {}
