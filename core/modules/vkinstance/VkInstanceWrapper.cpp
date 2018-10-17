#include <utility>

//
// Created by User on 20.10.2018.
//

#include "VkInstanceWrapper.h"

VkInstance* VkInstanceWrapper::get() {
    return vkInstance;
}

VkInstanceWrapper::VkInstanceWrapper(VkInstance* vkInstance) {
    this->vkInstance = vkInstance;
}
