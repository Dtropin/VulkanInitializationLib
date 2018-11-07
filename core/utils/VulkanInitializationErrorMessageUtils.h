//
// Created by User on 07.11.2018.
//

#ifndef VULKANINITIALIZATIONLIB_VULKANINITIALIZATIONERRORMESSAGEUTILS_H
#define VULKANINITIALIZATIONLIB_VULKANINITIALIZATIONERRORMESSAGEUTILS_H

#include <string>
#include <vulkan_core.h>

std::string formErrorMessageFromVkResult(const char* baseMessage, VkResult vkResult) {
    std::string baseMessageStr = baseMessage;
    std::string vkResultStr = std::to_string(vkResult);
    std::string resultErrorMessage = baseMessageStr + vkResultStr;
    return resultErrorMessage;
}

#endif //VULKANINITIALIZATIONLIB_VULKANINITIALIZATIONERRORMESSAGEUTILS_H
