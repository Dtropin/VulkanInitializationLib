//
// Created by Tropin Denis on 09.04.2018.
//

#include <iostream>
#include "VkInstanceCreateInfoFactory.h"
#include "../../../outputwindow/OutputWindowInterface.h"
#include "../../layersAndExtensions/LayersAndExtensionsManagerFactory.h"

VkInstanceCreateInfoFactory &VkInstanceCreateInfoFactory::getInstance() {
    static VkInstanceCreateInfoFactory initializer;
    return initializer;
}

//Create information about application - version, name and so on
VkApplicationInfo *VkInstanceCreateInfoFactory::createApplicationInfo(ApplicationMetadata applicationMetadata) {
    auto *appInfo = new VkApplicationInfo;
    appInfo->sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo->pApplicationName = applicationMetadata.appName;
    appInfo->pEngineName = applicationMetadata.engineName;
    appInfo->applicationVersion = VK_MAKE_VERSION(applicationMetadata.majorAppVersion, 0, 0);
    appInfo->engineVersion = VK_MAKE_VERSION(applicationMetadata.majorEngineVersion, 0, 0);
    appInfo->apiVersion = VK_API_VERSION_1_0;
    appInfo->pNext = nullptr;
    return appInfo;
}

VkInstanceCreateInfo *VkInstanceCreateInfoFactory::createVkInstanceCreateInfo(OutputWindowInterface *windowInterface,
                                                                              ApplicationMetadata applicationMetadata) {
    validateInstanceLayersSupport(applicationMetadata.vkInstanceLayersToEnable);

    auto* createInfo = createInstanceCreateInfo(applicationMetadata);

    const auto ** layerNames = new const char*[createInfo->enabledLayerCount];

    int j = 0;

    for (auto it = applicationMetadata.vkInstanceLayersToEnable.begin(); it != applicationMetadata.vkInstanceLayersToEnable.end(); ++it) {
        layerNames[j++] = *it;
    }

    createInfo->ppEnabledLayerNames = layerNames;

    std::vector<const char*>* extensionsFromWindowSystem = windowInterface->getExtensionsForVulkan()->supportedExtensions;
    std::vector<const char*> additionalExtensionsDefinedByUser = applicationMetadata.vkInstanceExtensionsToEnable;

    auto * mergedExtensionsVector = new std::vector<const char*>;
    mergedExtensionsVector->insert(mergedExtensionsVector->end(), extensionsFromWindowSystem->begin(), extensionsFromWindowSystem->end());
    mergedExtensionsVector->insert(mergedExtensionsVector->end(), additionalExtensionsDefinedByUser.begin(), additionalExtensionsDefinedByUser.end());

    createInfo->enabledExtensionCount = static_cast<uint32_t>(mergedExtensionsVector->size());
    createInfo->ppEnabledExtensionNames = mergedExtensionsVector->data();
    return createInfo;
}

void VkInstanceCreateInfoFactory::validateInstanceLayersSupport(std::vector<const char *> vkInstanceLayersToEnable) {
    LayersAndExtensionsManager* layersAndExtensionsManager =
            LayersAndExtensionsManagerFactory::getInstance().getOrCreate();

    for(auto const& i: vkInstanceLayersToEnable) {
        if(!layersAndExtensionsManager->containsLayer(std::string(i))) {
            throw std::runtime_error("instance layer not supported");
        }
    }
}

VkInstanceCreateInfo *VkInstanceCreateInfoFactory::createInstanceCreateInfo(ApplicationMetadata applicationMetadata) {
    auto * createInfo = new VkInstanceCreateInfo();

    createInfo->sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo->pApplicationInfo = createApplicationInfo(applicationMetadata);
    createInfo->pNext = nullptr;
    createInfo->flags = VkInstanceCreateFlags();
    createInfo->enabledLayerCount = applicationMetadata.vkInstanceLayersToEnable.size();
    return createInfo;
}

VkInstanceCreateInfoFactory::VkInstanceCreateInfoFactory() = default;
