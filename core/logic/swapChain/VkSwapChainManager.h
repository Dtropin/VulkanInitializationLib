//
// Created by Tropin Denis on 16.04.2018.
//

#include <vulkan.h>
#include <vector>
#include "../../modules/swapChain/SwapChainHandler.h"
#include "../../modules/logicalDevice/VkDeviceRepresentation.h"

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    VkSwapchainCreateInfoKHR createInfo;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

//The swap chain is essentially a queue of images
//that are waiting to be presented to the screen
/*
How exactly the queue
works and the conditions for presenting an image from the queue depend on
how the swap chain is set up, but the general purpose of the swap chain is to
synchronize the presentation of images with the refresh rate of the screen
*/
class VkSwapChainManager {
    public:
        static VkSwapChainManager &getInstance();
        SwapChainHandler* createSwapChain(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, VkDeviceRepresentation* logicalDevice);
        SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR surface);
    private:
        VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);
        VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> availablePresentModes);
        VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities);
};