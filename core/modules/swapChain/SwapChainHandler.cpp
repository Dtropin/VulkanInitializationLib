//
// Created by Tropin Denis on 20.04.2018.
//

#include "SwapChainHandler.h"

SwapChainHandler::SwapChainHandler(VkSwapchainKHR vkSwapchainKHR, VkFormat swapChainImageFormat,
                                   VkExtent2D swapChainExtent,std::vector<VkImage> swapChainImages, std::vector<VkImageView> swapChainImageViews) {
    this->swapChain = vkSwapchainKHR;
    this->swapChainImageFormat = swapChainImageFormat;
    this->swapChainExtent = swapChainExtent;
    this->swapChainImages = swapChainImages;
    this->swapChainImageViews = swapChainImageViews;

}
