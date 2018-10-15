//
// Created by User on 29.07.2018.
//

#pragma once
#include <cstdint>
#include <vulkan.h>
#include <vector>
#include <map>

//Layers - extends functionality on vulkan api calls like proxy(e.g. validation)
//Extensions - provide additional functionality (eg wsi - integrating with window system). Each layer may has own extensions
struct LayerAndExtensionProperties {
    VkLayerProperties layerProperties;
    std::vector<VkExtensionProperties> extensionsProperties;
};

class LayersAndExtensionsManager {
    friend class LayersAndExtensionsManagerFactory;

    public:
        bool containsLayer(std::string);
        std::vector<LayerAndExtensionProperties> getAllInstanceLayers();

    private:

        ~LayersAndExtensionsManager() = default;

        explicit LayersAndExtensionsManager(std::vector<LayerAndExtensionProperties>);

        std::map<std::string, LayerAndExtensionProperties> instanceLayersAndExtensionsProperties;
};
