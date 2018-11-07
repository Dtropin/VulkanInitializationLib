//
// Created by User on 26.10.2018.
//

#include "VkPhysicalDeviceExtensionsExtractor.h"

std::vector<VkExtensionProperties> *
VkPhysicalDeviceExtensionsExtractor::getAllSupportedExtensionsForDevice(VkPhysicalDevice device,
                                                                        VkInstanceLayersWrapper *const instanceLayersWrapper) const {
    auto *deviceExtensions = new std::vector<VkExtensionProperties>();

    auto availableInstanceLayers = instanceLayersWrapper->getInstanceLayers();

    for (auto availableInstanceLayer : *availableInstanceLayers) {
        char const *layerName = availableInstanceLayer.layerProperties.layerName;
        std::string layerNameStr = std::string(layerName);

        //get supported extensions for device and corresponding instance layer
        std::vector<VkExtensionProperties> extensionsOfDevice = getExtensionsForLayerAndGpu(device,
                                                                                            layerName);
        deviceExtensions->insert(deviceExtensions->end(), extensionsOfDevice.begin(), extensionsOfDevice.end());
    }

    return deviceExtensions;
}

std::vector<VkExtensionProperties>
VkPhysicalDeviceExtensionsExtractor::getExtensionsForLayerAndGpu(VkPhysicalDevice gpu,
                                                                 char const *instanceLayerName) const {
    uint32_t extensionsCount;
    //Get supported extensions count for device and corresponding layer
    vkEnumerateDeviceExtensionProperties(gpu, instanceLayerName, &extensionsCount, nullptr);

    auto extensionProperties = std::vector<VkExtensionProperties>();
    extensionProperties.resize(extensionsCount);
    vkEnumerateDeviceExtensionProperties(gpu, instanceLayerName, &extensionsCount, extensionProperties.data());
    return extensionProperties;
}
