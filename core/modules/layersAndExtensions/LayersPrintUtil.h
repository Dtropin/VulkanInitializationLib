//
// Created by User on 04.08.2018.
//

#pragma once
#include <iostream>
#include <vector>
#include <vulkan.h>

class LayersPrintUtil {
public:
    static void printLayerAndExtensionPretty(char const * layerName, std::vector<VkExtensionProperties>& exts) {
        std::cout << "\n\t|\n\t|---[Layer Name]--> " << layerName << "\n";
        for (auto extensionProp : exts) {
            std::cout << "\t\t|\n\t\t|---" << "[Layer Extension]--> " << extensionProp.extensionName << "\n";
        }
    }
};


