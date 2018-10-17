//
// Created by User on 29.07.2018.
//

#pragma once

#include <cstdint>
#include <vulkan.h>
#include <vector>
#include <map>
#include <memory>

//Layers - extends functionality on vulkan api calls like proxy(e.g. validation)
//Layers only for instance level!!!!!! Extensions - for both instance and device
//Extensions - provide additional functionality (eg wsi - integrating with window system). Each layer may has own extensions
struct LayerAndItsExtensions {
    VkLayerProperties layerProperties;
    std::vector<VkExtensionProperties> extensionsProperties;
};

class VkInstanceLayersWrapper {
public:
    bool containsLayer(std::string);
    std::shared_ptr<std::vector<LayerAndItsExtensions>> getInstanceLayers();
    explicit VkInstanceLayersWrapper(std::vector<LayerAndItsExtensions>* const vector);
private:
    std::shared_ptr<std::map<std::string, LayerAndItsExtensions>> layerNameToLayerObjectMap;
    std::shared_ptr<std::vector<LayerAndItsExtensions>> layersVector;
};
