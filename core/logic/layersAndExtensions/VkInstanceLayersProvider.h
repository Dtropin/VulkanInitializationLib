//
// Created by User on 29.07.2018.
//

#pragma once

#include <vulkan.h>
#include <atomic>
#include <mutex>
#include "../../modules/layersAndExtensions/VkInstanceLayersWrapper.h"

class VkInstanceLayersProvider {
    friend class IocContainer;

public:
    std::shared_ptr<VkInstanceLayersWrapper> getInstanceLayersAndExtensions();

private:
    explicit VkInstanceLayersProvider();

    VkResult getVkInstanceExtensionsProperties(LayerAndItsExtensions *);

    uint32_t getInstanceLayersCount();

    std::vector<VkLayerProperties>* getInstanceLayerProperties(uint32_t instanceLayersCount);

    std::vector<LayerAndItsExtensions>* VkInstanceLayersProvider::getExtensionsForSpecifiedLayers(
            std::vector<VkLayerProperties> *);
};
