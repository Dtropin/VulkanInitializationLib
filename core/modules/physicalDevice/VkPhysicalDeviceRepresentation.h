//
// Created by User on 04.08.2018.
//
#pragma once
#include <vulkan.h>
#include <xstring>
#include <vector>
#include <map>

class VkPhysicalDeviceRepresentation {

    private:
        VkPhysicalDevice* vkPhysicalDevice;
        VkPhysicalDeviceMemoryProperties memoryProperties;
        std::map<std::string, std::vector<VkExtensionProperties>>* supportedExtensions;
        std::vector<VkQueueFamilyProperties>* queueFamiliesProperties;
        VkPhysicalDeviceFeatures* deviceFeatures;

    public:
		VkPhysicalDevice *getVkPhysicalDevice() const;

		const VkPhysicalDeviceMemoryProperties &getMemoryProperties() const;

		std::map<std::string, std::vector<VkExtensionProperties>> *getSupportedExtensions() const;

		std::vector<VkQueueFamilyProperties> *getQueueFamiliesProperties() const;

		VkPhysicalDeviceRepresentation &operator=(VkPhysicalDeviceRepresentation &) = delete;
			VkPhysicalDeviceRepresentation() = delete;
			~VkPhysicalDeviceRepresentation();
			VkPhysicalDeviceRepresentation(VkPhysicalDevice* vkp, VkPhysicalDeviceMemoryProperties memoryProperties,
										   std::map<std::string, std::vector<VkExtensionProperties>>* supportedExtensions,
										   std::vector<VkQueueFamilyProperties>* queueFamilyProperties,
										   VkPhysicalDeviceFeatures* deviceFeatures);
};