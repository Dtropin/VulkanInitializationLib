//
// Created by User on 26.10.2018.
//

#include <vector>
#include <vulkan_core.h>

class VkPhysicalDevicePropertiesExtractor {
public:
    std::vector<VkQueueFamilyProperties>* getDeviceQueueFamilies(VkPhysicalDevice *physicalDevice) const;
    VkPhysicalDeviceFeatures* getDeviceFeatures(VkPhysicalDevice device) const;
    VkPhysicalDeviceMemoryProperties* getMemoryProperties(VkPhysicalDevice device) const;
};