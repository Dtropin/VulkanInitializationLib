cmake_minimum_required(VERSION 3.10)

project(VulkanInitializationLib)

set(CMAKE_CXX_STANDARD 17)

set(VULKAN_INCLUDE_DIR C:/VulkanSDK/1.1.70.1/Include/vulkan)
set(GLWF_INCLUDE_DIR C:/VulkanSDK/1.1.70.1/GLFW)
set(GLM_INCLUDE_DIR C:/VulkanSDK/1.1.70.1/Third-Party/Include/glm)

include_directories(${VULKAN_INCLUDE_DIR} ${GLWF_INCLUDE_DIR} ${GLM_INCLUDE_DIR})

file(GLOB SOURCES
        *.h
        *.cpp
        core/entryPoint/*.h
        core/entryPoint/*.cpp
        core/graphicsSystem/vulkan/initialization/*.h
        core/graphicsSystem/vulkan/initialization/*.cpp
        core/graphicsSystem/vulkan/*.h
        core/graphicsSystem/vulkan/*.cpp
        core/logic/*.h
        core/logic/*.cpp
        core/logic/command/*.h
        core/logic/command/*.cpp
        core/logic/graphicsPipeline/*.cpp
        core/logic/graphicsPipeline/*.h
        core/logic/logicalDevice/*.cpp
        core/logic/logicalDevice/*.h
        core/logic/queueFamilies/*.cpp
        core/logic/physicalDevice/*.cpp
        core/logic/physicalDevice/*.h
        core/logic/queueFamilies/*.h
        core/logic/renderPass/*.cpp
        core/logic/renderPass/*.h
        core/logic/swapChain/*.cpp
        core/logic/swapChain/*.h
        core/logic/vkInstance/*.cpp
        core/logic/vkInstance/*.h
        core/logic/vkInstance/createInfo/*.cpp
        core/logic/vkInstance/createInfo/*.h
        core/modules/commands/*.cpp
        core/modules/commands/*.h
        core/modules/graphicsPipeline/*.cpp
        core/modules/graphicsPipeline/*.h
        core/modules/swapChain/*.cpp
        core/modules/swapChain/*.h
        core/modules/*.cpp
        core/modules/*.h
        core/modules/logicalDevice/*.cpp
        core/modules/logicalDevice/*.h
        core/modules/physicalDevice/*.cpp
        core/modules/physicalDevice/*.h
        core/shaders/*.cpp
        core/shaders/*.h
        core/outputwindow/impl/glfw/*.h
        core/outputwindow/impl/glfw/*.cpp
        core/outputwindow/init/*.h
        core/outputwindow/init/*.cpp
        core/outputwindow/*.h
        core/outputwindow/*.cpp
        core/modules/layersAndExtensions/VkInstanceLayersWrapper.cpp
        core/modules/layersAndExtensions/VkInstanceLayersWrapper.h
        core/logic/layersAndExtensions/VkInstanceLayersProvider.cpp
        core/logic/layersAndExtensions/VkInstanceLayersProvider.h
        )

set(SOURCE_FILES
        ${VULKAN_INCLUDE_DIR}
        ${GLWF_INCLUDE_DIR}
        ${GLM_INCLUDE_DIR}
        ${SOURCES} core/modules/physicalDevice/VkPhysicalDeviceWrapper.cpp core/modules/physicalDevice/VkPhysicalDeviceWrapper.h core/modules/layersAndExtensions/LayersPrintUtil.h core/logic/ioc/IocContainer.cpp core/logic/ioc/IocContainer.h core/initrequestmodel/VulkanInitalizationRequestModel.h core/modules/vkinstance/VkInstanceWrapper.cpp core/modules/vkinstance/VkInstanceWrapper.h core/logic/physicalDevice/propertiesExtractors/VkPhysicalDeviceExtensionsExtractor.cpp core/logic/physicalDevice/propertiesExtractors/VkPhysicalDeviceExtensionsExtractor.h core/logic/physicalDevice/propertiesExtractors/VkPhysicalDevicePropertiesExtractor.cpp core/logic/physicalDevice/propertiesExtractors/VkPhysicalDevicePropertiesExtractor.h core/utils/VulkanInitializationErrorMessageUtils.h core/logic/logicalDevice/createInfo/VkLogicalDeviceCreateInfoProvider.cpp core/logic/logicalDevice/createInfo/VkLogicalDeviceCreateInfoProvider.h)

add_executable(VulkanInitializationLib ${SOURCE_FILES})

set(VULKAN_LIB_DIR C:/VulkanSDK/1.1.70.1/Lib32)
set(GLWF_LIB_DIR C:/VulkanSDK/1.1.70.1/GLFW/lib)

link_directories(${VULKAN_LIB_DIR} ${GLWF_LIB_DIR})
target_link_libraries(VulkanInitializationLib ${GLWF_LIB_DIR}/glfw3.lib ${VULKAN_LIB_DIR}/vulkan-1.lib)