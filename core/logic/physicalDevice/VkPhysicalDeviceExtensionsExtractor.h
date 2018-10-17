//
// Created by User on 26.10.2018.
//

#include <vulkan_core.h>
#include <vector>
#include "../../modules/layersAndExtensions/VkInstanceLayersWrapper.h"

class VkPhysicalDeviceExtensionsExtractor {
public:
    std::vector<VkExtensionProperties> *getAllSupportedExtensionsForDevice(
            VkPhysicalDevice,
            VkInstanceLayersWrapper* const) const;
private:
    std::vector<VkExtensionProperties> getExtensionsForLayerAndGpu(VkPhysicalDevice gpu, char const *instanceLayerName) const;
};