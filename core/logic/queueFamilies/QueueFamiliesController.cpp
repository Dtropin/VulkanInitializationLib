//
// Created by Tropin Denis on 11.04.2018.
//


#include <stdexcept>
#include <vector>
#include <functional>
#include "QueueFamiliesController.h"

/*
anything from drawing to uploading textures, requires commands to be submitted
to a queue
*/
QueueFamiliesController &QueueFamiliesController::getInstance() {
    static QueueFamiliesController instance;
    return instance;
}

QueueFamiliesController::QueueFamiliesController() = default;

uint32_t QueueFamiliesController::findQueueFamilies(std::vector<VkQueueFamilyProperties>* queueFamiliesProperties,
                                                    std::function<bool(VkQueueFamilyProperties)>peekFunction) {
    VkQueueFamilyProperties* data = queueFamiliesProperties->data();

    for(uint32_t i = 0; i < queueFamiliesProperties->size(); i++) {
        if(peekFunction(data[i]))
            return i;
    }

    throw std::runtime_error("cant find appropriate queue family");
}


