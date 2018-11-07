#include <memory>

#include <memory>

//
// Created by User on 17.10.2018.
//

#include <iostream>
#include "IocContainer.h"

IocContainer &IocContainer::getInstance() {
    static IocContainer instance;
    return instance;
}

std::shared_ptr<VkInstanceProvider> IocContainer::getVkInstanceProvider() {
    return vkInstanceProvider;
}

std::shared_ptr<VkPhysicalDeviceDetector> IocContainer::getVkPhysicalDeviceDetector() {
    return vkPhysicalDeviceDetector;
}

std::shared_ptr<VkLogicalDeviceProvider> IocContainer::getVkLogicalDeviceProvider() {
    return vkLogicalDeviceProvider;
}

std::shared_ptr<VkInstanceLayersProvider> IocContainer::getVkInstanceLayersProvider() {
    return vkInstanceLayersProvider;
}

std::shared_ptr<VkPhysicalDeviceExtensionsExtractor> IocContainer::getDeviceExtensionsExtractor() {
    return deviceExtensionsExtractor;
}

IocContainer::IocContainer() {
    this->deviceExtensionsExtractor = std::make_shared<VkPhysicalDeviceExtensionsExtractor>();
    this->devicePropertiesExtractor = std::make_shared<VkPhysicalDevicePropertiesExtractor>();
    this->vkPhysicalDeviceDetector = std::shared_ptr<VkPhysicalDeviceDetector>(new VkPhysicalDeviceDetector(deviceExtensionsExtractor, devicePropertiesExtractor));
    this->vkInstanceLayersProvider = std::shared_ptr<VkInstanceLayersProvider>(new VkInstanceLayersProvider());
    this->instanceCreateInfoProvider = std::shared_ptr<VkInstanceCreateInfoProvider>(new VkInstanceCreateInfoProvider(vkInstanceLayersProvider));
    this->vkLogicalDeviceProvider = std::shared_ptr<VkLogicalDeviceProvider>(new VkLogicalDeviceProvider);
    this->vkInstanceProvider = std::make_shared<VkInstanceProvider>(instanceCreateInfoProvider);
}
