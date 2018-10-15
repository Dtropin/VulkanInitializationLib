//
// Created by Tropin Denis on 09.04.2018.
//

#include <stdexcept>
#include <vector>
#include <set>
#include <iostream>
#include "VkPhysicalDeviceManager.h"
#include "../swapChain/VkSwapChainManager.h"
#include "../layersAndExtensions/LayersAndExtensionsManagerFactory.h"
#include "../queueFamilies/QueueFamiliesController.h"

VkPhysicalDeviceManager &VkPhysicalDeviceManager::getInstance() {
    static VkPhysicalDeviceManager initializer;
    return initializer;
}

std::vector<VkPhysicalDeviceRepresentation>* VkPhysicalDeviceManager::getOrCreate(VkInstance *vkInstance) {
    std::unique_lock<std::mutex> lock(_mutex);
    if(!isManagerAlreadyCreated.test_and_set()) {
        uint32_t deviceCount = 0;

        //Get devices count
        vkEnumeratePhysicalDevices(*vkInstance, &deviceCount, nullptr);

        if (deviceCount == 0) {
            throw std::runtime_error("failed to find GPUs with Vulkan support!");
        } else {
            auto *devices = new std::vector<VkPhysicalDevice>();
            devices->resize(deviceCount);
            //Get devices
            vkEnumeratePhysicalDevices(*vkInstance, &deviceCount, devices->data());

            VkPhysicalDevice* devicesArray = devices->data();

            auto * representationArray = new std::vector<VkPhysicalDeviceRepresentation>();

            LayersAndExtensionsManager* lem = LayersAndExtensionsManagerFactory::getInstance().getOrCreate();

            std::vector<LayerAndExtensionProperties> instanceLayers = lem->getAllInstanceLayers();

            for(uint32_t i = 0; i < deviceCount; i++) {
                auto * layerMap = new std::map<std::string, std::vector<VkExtensionProperties>>();

                for (auto it = instanceLayers.begin(); it != instanceLayers.end(); ++it) {
                    char const * layerName = it->layerProperties.layerName;
                    std::string layerNameStr = std::string(layerName);

                    //get supported extensions for device and corresponding instance layer
                    std::vector<VkExtensionProperties> extensionsOfDevice = getExtensionsForLayerAndGpu(devicesArray[i], layerName);

                    layerMap->insert(make_pair(layerNameStr, extensionsOfDevice));
                }

                VkPhysicalDeviceMemoryProperties memoryProperties;
                vkGetPhysicalDeviceMemoryProperties(devicesArray[i], &memoryProperties);

                auto * features = new VkPhysicalDeviceFeatures();
                vkGetPhysicalDeviceFeatures(devicesArray[i], features);

                representationArray->push_back(VkPhysicalDeviceRepresentation(&devicesArray[i],
                                                                              memoryProperties, layerMap, getDeviceQueueFamilies(&devicesArray[i]),
                                                                              features));
            }

            this->cachedDevices = representationArray;

            return cachedDevices;
        }
    } else {
        return cachedDevices;
    }
}

//get info about supported queue families(types) by device
std::vector<VkQueueFamilyProperties> *VkPhysicalDeviceManager::getDeviceQueueFamilies(VkPhysicalDevice* physicalDevice) {
    uint32_t count;
    auto * properties = new std::vector<VkQueueFamilyProperties>();
    vkGetPhysicalDeviceQueueFamilyProperties(*physicalDevice, &count, NULL);
    properties->resize(count);
    vkGetPhysicalDeviceQueueFamilyProperties(*physicalDevice, &count, properties->data());
    return properties;
}


std::vector<VkExtensionProperties> VkPhysicalDeviceManager::getExtensionsForLayerAndGpu(VkPhysicalDevice gpu, char const *instanceLayerName) {
    uint32_t extensionsCount;
    //Get supported extensions count for device and corresponding layer
    vkEnumerateDeviceExtensionProperties(gpu, instanceLayerName, &extensionsCount, nullptr);

    auto extensionProperties = std::vector<VkExtensionProperties>();
    extensionProperties.resize(extensionsCount);
    vkEnumerateDeviceExtensionProperties(gpu, instanceLayerName, &extensionsCount, extensionProperties.data());
    return extensionProperties;
}

VkPhysicalDeviceManager::~VkPhysicalDeviceManager() {
    delete cachedDevices;
}


VkPhysicalDeviceManager::VkPhysicalDeviceManager() = default;
