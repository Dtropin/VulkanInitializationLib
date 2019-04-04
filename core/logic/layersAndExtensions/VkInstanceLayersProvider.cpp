#include <memory>

//
// Created by User on 29.07.2018.
//

#include <iostream>
#include "VkInstanceLayersProvider.h"
#include "../../modules/layersAndExtensions/LayersPrintUtil.h"

std::shared_ptr<VkInstanceLayersWrapper> VkInstanceLayersProvider::getInstanceLayersAndExtensions() {
    uint32_t instanceLayersCount = getInstanceLayersCount();

    std::vector<VkLayerProperties>* instanceLayersProperties = getInstanceLayerProperties(instanceLayersCount);

    std::vector<LayerAndItsExtensions>* layersAndItsExtensions = getExtensionsForSpecifiedLayers(instanceLayersProperties);

    return std::make_shared<VkInstanceLayersWrapper>(layersAndItsExtensions);
}

uint32_t VkInstanceLayersProvider::getInstanceLayersCount() {
    uint32_t instanceLayersCount;

    //retrieve INSTANCE layers COUNT
    if (vkEnumerateInstanceLayerProperties(&instanceLayersCount, nullptr) != VK_SUCCESS) {
        throw std::runtime_error("can't get instance layers properties count");
    }

    return instanceLayersCount;
}

std::vector<LayerAndItsExtensions>* VkInstanceLayersProvider::getExtensionsForSpecifiedLayers(
        std::vector<VkLayerProperties> *instanceLayersProperties) {

    auto* layersAndExtensions = new std::vector<LayerAndItsExtensions>();

    for (auto layerProperty : *instanceLayersProperties) {
        LayerAndItsExtensions layerAndExtensionProperties;

        layerAndExtensionProperties.layerProperties = layerProperty;

        // Get Instance level extensions for corresponding layer properties
        if (getVkInstanceExtensionsProperties(&layerAndExtensionProperties) != VK_SUCCESS) {
            std::cerr << "cannot get extensions for layer " << layerProperty.layerName << "\n";
            continue;
        } else {
            // Print extension name for each instance layer
            LayersPrintUtil::printLayerAndExtensionPretty(layerProperty.layerName,
                                                          layerAndExtensionProperties.extensionsProperties);
            layersAndExtensions->push_back(layerAndExtensionProperties);
        }
    }

    return layersAndExtensions;
}

std::vector<VkLayerProperties> *VkInstanceLayersProvider::getInstanceLayerProperties(uint32_t instanceLayersCount) {
    auto layersProperties = new std::vector<VkLayerProperties>(instanceLayersCount);

    //retrieve INSTANCE layers
    if (vkEnumerateInstanceLayerProperties(&instanceLayersCount, layersProperties->data()) != VK_SUCCESS) {
        throw std::runtime_error("can't get instance layers properties");
    }

    return layersProperties;
}

VkResult VkInstanceLayersProvider::getVkInstanceExtensionsProperties(LayerAndItsExtensions *arg) {
    uint32_t extensionCount;

    char *layerName = arg->layerProperties.layerName;

    VkResult result = vkEnumerateInstanceExtensionProperties(layerName, &extensionCount, nullptr);

    if (result != VK_SUCCESS || extensionCount == 0) {
        return result;
    }

    arg->extensionsProperties.resize(extensionCount);

    return vkEnumerateInstanceExtensionProperties(layerName, &extensionCount, arg->extensionsProperties.data());
}

VkInstanceLayersProvider::VkInstanceLayersProvider() = default;
