//
// Created by User on 20.10.2018.
//

#pragma once

#include <vulkan.h>
#include <vector>
#include "../layersAndExtensions/VkInstanceLayersWrapper.h"

class VkInstanceWrapper {

public:
    VkInstance* get();

    explicit VkInstanceWrapper(VkInstance*);
private:
    VkInstance* vkInstance;
};
