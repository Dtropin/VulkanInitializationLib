//
// Created by Tropin Denis on 09.04.2018.
//

#include <vulkan.h>
#include <mutex>
#include <atomic>
#include "../../modules/physicalDevice/VkPhysicalDeviceRepresentation.h"

class VkPhysicalDeviceManager {
    public:
        static VkPhysicalDeviceManager &getInstance();
        std::vector<VkPhysicalDeviceRepresentation>* getOrCreate(VkInstance *vkInstance);
        VkPhysicalDeviceManager(const VkPhysicalDeviceManager&) = delete;
        VkPhysicalDeviceManager&operator=(VkPhysicalDeviceManager&) = delete;
    private:
        VkPhysicalDeviceManager();
        ~VkPhysicalDeviceManager();

        std::vector<VkExtensionProperties> getExtensionsForLayerAndGpu(VkPhysicalDevice, char const* instanceLayerName);
        std::vector<VkQueueFamilyProperties>* getDeviceQueueFamilies(VkPhysicalDevice* physicalDevice);
        std::vector<VkPhysicalDeviceRepresentation>* cachedDevices;
        std::mutex _mutex;
        std::atomic_flag isManagerAlreadyCreated;
};
