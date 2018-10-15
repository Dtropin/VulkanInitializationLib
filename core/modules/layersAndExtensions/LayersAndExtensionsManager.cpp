//
// Created by User on 29.07.2018.
//

#include <iostream>
#include "LayersAndExtensionsManager.h"

LayersAndExtensionsManager::LayersAndExtensionsManager(std::vector<LayerAndExtensionProperties> props) {
    for(LayerAndExtensionProperties const& i: props) {
        this->instanceLayersAndExtensionsProperties[i.layerProperties.layerName] = i;
    }
}

bool LayersAndExtensionsManager::containsLayer(std::string layerName) {
    return this->instanceLayersAndExtensionsProperties.count(layerName) == 1;
}

std::vector<LayerAndExtensionProperties> LayersAndExtensionsManager::getAllInstanceLayers() {
    std::vector<LayerAndExtensionProperties> vector;

    for(auto it = instanceLayersAndExtensionsProperties.begin(); it != instanceLayersAndExtensionsProperties.end(); ++it) {
        vector.push_back(it->second);
    }

    return vector;
}


