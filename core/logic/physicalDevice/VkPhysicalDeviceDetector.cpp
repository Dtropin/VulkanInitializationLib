//
// Created by Tropin Denis on 09.04.2018.
//

#include <stdexcept>
#include <vector>
#include <set>
#include <iostream>
#include "VkPhysicalDeviceDetector.h"
#include "../swapChain/VkSwapChainManager.h"
#include "../layersAndExtensions/VkInstanceLayersProvider.h"
#include "../queueFamilies/QueueFamiliesController.h"

using namespace std;

std::shared_ptr<VkPhysicalDeviceWrapper> VkPhysicalDeviceDetector::findSatisfyingDevices(
        VkInstance * const vkInstance,
        VkInstanceLayersWrapper* const instanceLayers,
        VulkanInitializationRequest::PhysicalDeviceRequirements deviceRequirements) {

    vector<VkPhysicalDevice> *allHostDevices = detectAllDevicesOnHost(vkInstance);

    return std::unique_ptr<VkPhysicalDeviceWrapper>(selectAppropriateDevice(allHostDevices, instanceLayers, move(deviceRequirements)));
}

vector<VkPhysicalDevice> *VkPhysicalDeviceDetector::detectAllDevicesOnHost(VkInstance *vkInstance) {
    uint32_t deviceCount = 0;

    //Get devices count
    vkEnumeratePhysicalDevices(*vkInstance, &deviceCount, nullptr);

    if (deviceCount == 0) {
        throw runtime_error("failed to find GPUs with Vulkan support!");
    }

    auto devices = new vector<VkPhysicalDevice>(deviceCount);

    //Get devices
    vkEnumeratePhysicalDevices(*vkInstance, &deviceCount, devices->data());

    return devices;
}

VkPhysicalDeviceWrapper *VkPhysicalDeviceDetector::selectAppropriateDevice(
        vector<VkPhysicalDevice>* const availableDevices,
        VkInstanceLayersWrapper* const availableInstanceLayers,
        VulkanInitializationRequest::PhysicalDeviceRequirements deviceRequirements) {

    for (int i = 0; i < availableDevices->size(); i++) {
        VkPhysicalDevice candidate = availableDevices->at(i);

        vector<VkExtensionProperties> *supportedExtensions =
                deviceExtensionsExtractor->getAllSupportedExtensionsForDevice(candidate, availableInstanceLayers);

        if (!isAllSpecifiedExtensionsAreSupportedByDevice(deviceRequirements.requiredDeviceExtensions,
                                                          supportedExtensions)) {
            delete supportedExtensions;
            continue;
        }

        vector<VkQueueFamilyProperties> *supportedDeviceQueues =
                devicePropertiesExtractor->getDeviceQueueFamilies(&candidate);

        if (hasDeviceRequiredQueues(supportedDeviceQueues, deviceRequirements.queueFamilyRequirementFunctions)) {
            return new VkPhysicalDeviceWrapper(candidate,
                                               devicePropertiesExtractor->getMemoryProperties(candidate),
                                               supportedExtensions,
                                               supportedDeviceQueues,
                                               devicePropertiesExtractor->getDeviceFeatures(candidate));
        }
    }

    throw runtime_error("no appropriate GPUs was found!");
}

bool VkPhysicalDeviceDetector::hasDeviceRequiredQueues(vector<VkQueueFamilyProperties> *deviceQueues,
                                                       vector<function<bool(
                                                               VkQueueFamilyProperties)>> queueFamilyRequirementFunctions) {
    for (int i = 0; i < deviceQueues->size(); i++) {
        VkQueueFamilyProperties queue = deviceQueues->at(i);

        bool isSatisfy = true;

        for (int j = 0; j < queueFamilyRequirementFunctions.size(); j++) {
            function<bool(VkQueueFamilyProperties)> queuePickFunction = queueFamilyRequirementFunctions.at(j);
            if (!queuePickFunction(queue)) {
                isSatisfy = false;
                break;
            }
        }

        if (isSatisfy)
            return true;
    }

    return false;
}

bool VkPhysicalDeviceDetector::isAllSpecifiedExtensionsAreSupportedByDevice(
        const vector<const char *> &extNamesToSupport,
        vector<VkExtensionProperties> *supportedExtensionsByDevice) {
    for (int i = 0; i < extNamesToSupport.size(); i++) {
        if (!isExtensionVectorContainsExtensionWithSpecifiedName(supportedExtensionsByDevice, extNamesToSupport.at(i)))
            return false;
    }

    return true;
}

bool VkPhysicalDeviceDetector::isExtensionVectorContainsExtensionWithSpecifiedName(
        vector<VkExtensionProperties> *in,
        const char *extensionName) {
    for (int i = 0; i < in->size(); i++) {
        VkExtensionProperties extensionProperty = in->at(i);
        if (extensionProperty.extensionName == extensionName)
            return true;
    }
    return false;
}

VkPhysicalDeviceDetector::VkPhysicalDeviceDetector(std::shared_ptr<VkPhysicalDeviceExtensionsExtractor> arg1,
                                                   std::shared_ptr<VkPhysicalDevicePropertiesExtractor> arg2)
        : devicePropertiesExtractor(std::move(arg2)),
          deviceExtensionsExtractor(std::move(arg1)) {}
