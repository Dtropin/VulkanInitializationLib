//
// Created by Tropin Denis on 09.04.2018.
//

#pragma once

#include <vulkan.h>
#include "../../../outputwindow/OutputWindowInterface.h"

struct ApplicationMetadata {
    const char* appName{};
    const char* engineName{};
    std::vector<const char*> vkInstanceExtensionsToEnable;
    std::vector<const char*> vkInstanceLayersToEnable;
    uint32_t majorAppVersion{};
    uint32_t majorEngineVersion{};

    ApplicationMetadata(ApplicationMetadata& m) {
        appName = m.appName;
        engineName = m.engineName;
        vkInstanceLayersToEnable = m.vkInstanceLayersToEnable;
        vkInstanceExtensionsToEnable = m.vkInstanceExtensionsToEnable;
        majorEngineVersion = m.majorEngineVersion;
        majorAppVersion = m.majorAppVersion;
    }

    ApplicationMetadata(ApplicationMetadata&& m) noexcept {
        appName = m.appName;
        engineName = m.engineName;
        vkInstanceLayersToEnable = std::move(m.vkInstanceLayersToEnable);
        vkInstanceExtensionsToEnable = std::move(m.vkInstanceExtensionsToEnable);
        majorEngineVersion = m.majorEngineVersion;
        majorAppVersion = m.majorAppVersion;
        m.appName = nullptr;
        m.engineName = nullptr;
    }

    ApplicationMetadata(const char* appName, const char* engineName, uint32_t majorApp, uint32_t majorEngine,
                        std::vector<const char *> vkInstanceExtensionsToEnable,
                        std::vector<const char *> vkInstanceLayersToEnable) {
        this->appName = appName;
        this->engineName = engineName;
        this->majorAppVersion = majorApp;
        this->majorEngineVersion = majorEngine;
        this->vkInstanceExtensionsToEnable = vkInstanceExtensionsToEnable;
        this->vkInstanceLayersToEnable = vkInstanceLayersToEnable;
    }
};

class VkInstanceCreateInfoFactory {
    friend class VkInstanceFactory;

    private:
        static VkInstanceCreateInfoFactory &getInstance();

        void validateInstanceLayersSupport(std::vector<const char*> vkInstanceLayersToEnable);

        VkApplicationInfo* createApplicationInfo(ApplicationMetadata applicationMetadata);

        VkInstanceCreateInfo* createVkInstanceCreateInfo(OutputWindowInterface *windowInterface,
                                                         ApplicationMetadata applicationMetadata);
        VkInstanceCreateInfoFactory();

        VkInstanceCreateInfo* createInstanceCreateInfo(ApplicationMetadata applicationMetadata);
        #ifdef NDEBUG
            const bool enableValidationLayers = false;
        #else
            const bool enableValidationLayers = true;
        #endif
};
