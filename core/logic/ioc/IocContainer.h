//
// Created by User on 17.10.2018.
//

#include "../vkInstance/VkInstanceProvider.h"
#include "../physicalDevice/VkPhysicalDeviceDetector.h"
#include "../logicalDevice/VkLogicalDeviceProvider.h"

class IocContainer {
public:
    IocContainer(const IocContainer &) = delete;

    IocContainer(IocContainer &) = delete;

    IocContainer &operator=(const IocContainer other) = delete;

    static IocContainer &getInstance();

    std::shared_ptr<VkInstanceProvider> getVkInstanceProvider();

    std::shared_ptr<VkInstanceLayersProvider> getVkInstanceLayersProvider();

    std::shared_ptr<VkPhysicalDeviceDetector> getVkPhysicalDeviceDetector();

    std::shared_ptr<VkPhysicalDeviceExtensionsExtractor> getDeviceExtensionsExtractor();

    std::shared_ptr<VkLogicalDeviceProvider> getVkLogicalDeviceProvider();

private:
    IocContainer();

    std::shared_ptr<VkLogicalDeviceCreateInfoProvider> vkLogicalDeviceCreateInfoProvider;

    std::shared_ptr<VkLogicalDeviceQueueCreateInfoProvider> vkLogicalDeviceQueueCreateInfoProvider;

    std::shared_ptr<VkLogicalDeviceProvider> vkLogicalDeviceProvider;

    std::shared_ptr<VkPhysicalDeviceExtensionsExtractor> deviceExtensionsExtractor;

    std::shared_ptr<VkPhysicalDevicePropertiesExtractor> devicePropertiesExtractor;

    std::shared_ptr<VkPhysicalDeviceDetector> vkPhysicalDeviceDetector;

    std::shared_ptr<VkInstanceLayersProvider> vkInstanceLayersProvider;

    std::shared_ptr<VkInstanceCreateInfoProvider> instanceCreateInfoProvider;

    std::shared_ptr<VkInstanceProvider> vkInstanceProvider;
};