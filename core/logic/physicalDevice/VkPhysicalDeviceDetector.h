//
// Created by Tropin Denis on 09.04.2018.
//

#include <vulkan.h>
#include <mutex>
#include <atomic>
#include "../../modules/physicalDevice/VkPhysicalDeviceWrapper.h"
#include "../../modules/vkinstance/VkInstanceWrapper.h"
#include "../../initrequestmodel/VulkanInitalizationRequestModel.h"
#include "propertiesExtractors/VkPhysicalDeviceExtensionsExtractor.h"
#include "propertiesExtractors/VkPhysicalDevicePropertiesExtractor.h"

class VkPhysicalDeviceDetector {
    friend class IocContainer;

public:
    std::shared_ptr<VkPhysicalDeviceWrapper> findSatisfyingDevices(VkInstance* const,
                                                   VkInstanceLayersWrapper* const,
                                                   VulkanInitializationRequest::PhysicalDeviceRequirements);
    ~VkPhysicalDeviceDetector() = default;
private:
    std::shared_ptr<VkPhysicalDeviceExtensionsExtractor> deviceExtensionsExtractor;
    std::shared_ptr<VkPhysicalDevicePropertiesExtractor> devicePropertiesExtractor;

    explicit VkPhysicalDeviceDetector(std::shared_ptr<VkPhysicalDeviceExtensionsExtractor>,
                             std::shared_ptr<VkPhysicalDevicePropertiesExtractor>);

    bool isExtensionVectorContainsExtensionWithSpecifiedName(std::vector<VkExtensionProperties> *in,
                                                             const char *extensionName);

    std::vector<VkPhysicalDevice> *detectAllDevicesOnHost(VkInstance *vkInstance);

    VkPhysicalDeviceWrapper *selectAppropriateDevice(std::vector<VkPhysicalDevice> * const,
                                                     VkInstanceLayersWrapper* const,
                                                     VulkanInitializationRequest::PhysicalDeviceRequirements);

    bool isAllSpecifiedExtensionsAreSupportedByDevice(const std::vector<const char *> &,
                                                      std::vector<VkExtensionProperties> *);

    bool hasDeviceRequiredQueues(std::vector<VkQueueFamilyProperties> *deviceQueues,
                                 std::vector<std::function<bool(
                                         VkQueueFamilyProperties)>> queueFamilyRequirementFunctions);
};
