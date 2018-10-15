//
// Created by User on 29.07.2018.
//

#include <iostream>
#include "LayersAndExtensionsManagerFactory.h"
#include "../../modules/layersAndExtensions/LayersPrintUtil.h"

LayersAndExtensionsManagerFactory &LayersAndExtensionsManagerFactory::getInstance() {
    static LayersAndExtensionsManagerFactory initializer;
    return initializer;
}

VkResult LayersAndExtensionsManagerFactory::getVkInstanceExtensionsProperties(LayerAndExtensionProperties *arg) {
    uint32_t extensionCount;

    char* layerName = arg->layerProperties.layerName;

    VkResult result = vkEnumerateInstanceExtensionProperties(layerName, &extensionCount, nullptr);

    if(result != VK_SUCCESS || extensionCount == 0) {
        return result;
    }

    arg->extensionsProperties.resize(extensionCount);

    return vkEnumerateInstanceExtensionProperties(layerName, &extensionCount, arg->extensionsProperties.data());
}

LayersAndExtensionsManager* LayersAndExtensionsManagerFactory::getOrCreate() {
    std::unique_lock<std::mutex> lock(_mutex);
    if(!isManagerAlreadyCreated.test_and_set()) {
        uint32_t instanceLayersCount;

        //retrieve INSTANCE layers COUNT
        if (vkEnumerateInstanceLayerProperties(&instanceLayersCount, nullptr) != VK_SUCCESS) {
            throw std::runtime_error("can't get instance layers properties count");
        }

        std::vector<VkLayerProperties> instanceLayersProperties;

        instanceLayersProperties.resize(instanceLayersCount);

        //retrieve INSTANCE layers
        if (vkEnumerateInstanceLayerProperties(&instanceLayersCount, instanceLayersProperties.data()) != VK_SUCCESS) {
            throw std::runtime_error("can't get instance layers properties");
        }

        std::vector<LayerAndExtensionProperties> instanceLayersAndExtensionsProperties;

        for (auto instanceLayerProp : instanceLayersProperties) {
            LayerAndExtensionProperties layerAndExtensionProperties;
            layerAndExtensionProperties.layerProperties = instanceLayerProp;

            // Get Instance level extensions for corresponding layer properties
            if (getVkInstanceExtensionsProperties(&layerAndExtensionProperties) != VK_SUCCESS) {
                std::cout << "cannot get extensions for layer " << instanceLayerProp.layerName << "\n";
                continue;
            } else {
                // Print extension name for each instance layer
                LayersPrintUtil::printLayerAndExtensionPretty(instanceLayerProp.layerName,
                                                              layerAndExtensionProperties.extensionsProperties);
                instanceLayersAndExtensionsProperties.push_back(layerAndExtensionProperties);
            }
        }

        this->instance = new LayersAndExtensionsManager(instanceLayersAndExtensionsProperties);
        return this->instance;
    } else {
        return instance;
    }
}