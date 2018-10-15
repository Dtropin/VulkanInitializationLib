//
// Created by User on 29.07.2018.
//

#pragma once
#include <vulkan.h>
#include <atomic>
#include <mutex>
#include "../../modules/layersAndExtensions/LayersAndExtensionsManager.h"

class LayersAndExtensionsManagerFactory {
    public:
        LayersAndExtensionsManager* getOrCreate();
        static LayersAndExtensionsManagerFactory &getInstance();
        LayersAndExtensionsManagerFactory(const LayersAndExtensionsManagerFactory&) = delete;
        LayersAndExtensionsManagerFactory &operator=(LayersAndExtensionsManagerFactory&) = delete;
    private:
        LayersAndExtensionsManagerFactory() = default;
        ~LayersAndExtensionsManagerFactory() = default;
        std::mutex _mutex;
        std::atomic_flag isManagerAlreadyCreated;
        LayersAndExtensionsManager* instance;
        VkResult getVkInstanceExtensionsProperties(LayerAndExtensionProperties *);
};
