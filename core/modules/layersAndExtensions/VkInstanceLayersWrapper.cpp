//
// Created by User on 29.07.2018.
//

#include <iostream>
#include "VkInstanceLayersWrapper.h"

bool VkInstanceLayersWrapper::containsLayer(std::string layerName) {
    return this->layerNameToLayerObjectMap->count(layerName);
}

VkInstanceLayersWrapper::VkInstanceLayersWrapper(std::vector<LayerAndItsExtensions>* const vector) {
    this->layerNameToLayerObjectMap = std::make_shared<std::map<std::string, LayerAndItsExtensions>>();

    for(int i = 0; i < vector->size(); i++) {
        LayerAndItsExtensions layerDescription = vector->at(i);
        std::string layerName(layerDescription.layerProperties.layerName);
        this->layerNameToLayerObjectMap->insert(std::pair<std::string, LayerAndItsExtensions>(layerName, layerDescription));
    }

    this->layersVector = std::shared_ptr<std::vector<LayerAndItsExtensions>>(vector);
}

std::shared_ptr<std::vector<LayerAndItsExtensions>> VkInstanceLayersWrapper::getInstanceLayers() {
    return layersVector;
}

