//
// Created by Tropin Denis on 20.04.2018.
//

#pragma once
#include <vulkan.h>
#include <vector>

class SwapChainHandler {
    public:
        SwapChainHandler(VkSwapchainKHR, VkFormat, VkExtent2D, std::vector<VkImage> swapChainImages, std::vector<VkImageView> swapChainImageViews);
        std::vector<VkImage> swapChainImages;
        std::vector<VkImageView> swapChainImageViews;
        VkFormat swapChainImageFormat;
        VkExtent2D swapChainExtent;
        VkSwapchainKHR swapChain;
};
