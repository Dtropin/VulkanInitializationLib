//
// Created by Tropin Denis on 16.04.2018.
//
#pragma once
#include "VkSwapChainManager.h"
#include "../queueFamilies/QueueFamiliesController.h"
#include <algorithm>
#include <iostream>

VkSwapChainManager &VkSwapChainManager::getInstance() {
    static VkSwapChainManager swapchainController;
    return swapchainController;
}

SwapChainHandler* VkSwapChainManager::createSwapChain(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface,
        VkLogicalDeviceRepresentation* logicalDevice) {
    SwapChainSupportDetails swapChainSupport = querySwapChainSupport(physicalDevice, surface);
    VkSurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);
    VkPresentModeKHR presentMode = chooseSwapPresentMode(swapChainSupport.presentModes);
    VkExtent2D extent = chooseSwapExtent(swapChainSupport.capabilities);

    uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;

	//Устанавливаем глубину буферизации (т.е. длину очереди в swapChain - см. choosePresentationMode)
    if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount) {
        imageCount = swapChainSupport.capabilities.maxImageCount;
    }

    VkSwapchainCreateInfoKHR createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.surface = surface;
    createInfo.minImageCount = imageCount;
    createInfo.imageFormat = surfaceFormat.format;
    createInfo.imageColorSpace = surfaceFormat.colorSpace;
    createInfo.imageExtent = extent;
    createInfo.imageArrayLayers = 1;
    createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

    createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
    createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    createInfo.presentMode = presentMode;
    createInfo.clipped = VK_TRUE;
    createInfo.oldSwapchain = VK_NULL_HANDLE;

    VkSwapchainKHR swapChain;

    if (vkCreateSwapchainKHR(*logicalDevice->getVkLogicalDevice(), &createInfo, nullptr, &swapChain) != VK_SUCCESS) {
        throw std::runtime_error("failed to create swap chain!");
    }

	//Собственно сами image - интерпретация изображений в буфере (их соответственно столько, сколько размер буфера)
    std::vector<VkImage> swapChainImages;
    vkGetSwapchainImagesKHR(*logicalDevice->getVkLogicalDevice(), swapChain, &imageCount, nullptr);
    swapChainImages.resize(imageCount);
    vkGetSwapchainImagesKHR(*logicalDevice->getVkLogicalDevice(), swapChain, &imageCount, swapChainImages.data());

	//ImageView - дает доступ к image
    std::vector<VkImageView> swapChainImageViews;

    swapChainImageViews.resize(swapChainImages.size());
    for (size_t i = 0; i < swapChainImages.size(); i++) {
        VkImageViewCreateInfo createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        createInfo.image = swapChainImages[i];
        createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        createInfo.format = surfaceFormat.format;
        createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;//Мапит каналы, например можно все в R для монохромных текстур
        createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        createInfo.subresourceRange.baseMipLevel = 0;
        createInfo.subresourceRange.levelCount = 1;
        createInfo.subresourceRange.baseArrayLayer = 0;
        createInfo.subresourceRange.layerCount = 1;

        if (vkCreateImageView(*logicalDevice->getVkLogicalDevice(), &createInfo, nullptr, &swapChainImageViews[i]) != VK_SUCCESS) {
            throw std::runtime_error("failed to create image views!");
        }
    }

    return new SwapChainHandler(swapChain, surfaceFormat.format, extent, swapChainImages, swapChainImageViews);
}

SwapChainSupportDetails VkSwapChainManager::querySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR surface) {
    SwapChainSupportDetails details;
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);

    uint32_t formatCount;
	//Проверяем что устройство может работать с этим surface (по сути - image)
    vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);

    if (formatCount != 0) {
        details.formats.resize(formatCount);
        vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, details.formats.data());
    }

    uint32_t presentModeCount;
    vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, nullptr);

    if (presentModeCount != 0) {
        details.presentModes.resize(presentModeCount);
        vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, details.presentModes.data());
    }

    return details;
}

VkSurfaceFormatKHR VkSwapChainManager::chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats) {
	//Цветовое пространство
	//https://stackoverflow.com/questions/12524623/what-are-the-practical-differences-when-working-with-colors-in-a-linear-vs-a-no
	//Суть в кратце - обычное линейное цветовое пространство RGB представить можно в виде координат xyz;
	//Если я например значение красного удвою, то у него увеличится яркость. Вроде все ок. Но человеческий глаз почти не отличает более светлые тона
	//А темные наоборот сильнее отличает, поэтому получается что в полосе цветовой, в конце где белый, человек не заметит разницы
	//Для этого ввели пространство SRGB(И другие) - оно уже нелинейное, а представлено в виде кривой
	//Соответственно мониторы поддерживают формат srgb в котором цвета выглядят по другому нежели в RGB(т.е. этот контроль осуществляет монитор)
	//Например в обычном RGB значение компоненты 128 - это ровно половина яркости максимальной, но это же значение в srgb - имеет 22% от итоговой яркости
	//Вообщем вкратце - в sRGB попросту другая цветовая палитра получается и монитор эти цвета будет немного по другому выводить (т.е будет
	//больше оттенков темного, нежели при линейном rgb количество оттенков одинаково, но т.к. цветные не различаем в этом нет смысла)
	//Стандарт sRGB описывает, какой именно частоты должны быть основные цвета и какие именно оттенки достижимы при их смешивании
    if (availableFormats.size() == 1 && availableFormats[0].format == VK_FORMAT_UNDEFINED) {
        return {VK_FORMAT_B8G8R8A8_UNORM, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR};
    }

    for (const auto& availableFormat : availableFormats) {
        if (availableFormat.format == VK_FORMAT_B8G8R8A8_UNORM && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
            return availableFormat;
        }
    }

    return availableFormats[0];
}


VkPresentModeKHR VkSwapChainManager::chooseSwapPresentMode(const std::vector<VkPresentModeKHR> availablePresentModes) {
	//Настройка определяющая каким образом будет изображение попадать из чейна на экран
    VkPresentModeKHR bestMode = VK_PRESENT_MODE_FIFO_KHR;//Обычный вроде как дабл-буфер (хотя мб и не ограниченный)
	//The moment that the display is refreshed is known as “vertical blank”
    for (const auto& availablePresentMode : availablePresentModes) {
        if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {//Вот это вообще топчик
            return availablePresentMode;
        } else if (availablePresentMode == VK_PRESENT_MODE_IMMEDIATE_KHR) {
            bestMode = availablePresentMode;
        }
    }
    return bestMode;
}

VkExtent2D VkSwapChainManager::chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities) {
	//The swap extent is the resolution of the swap chain images and it’s almost always exactly equal to the resolution 
	//of the window that we’re drawing to
    if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
        return capabilities.currentExtent;
    } else {
        VkExtent2D actualExtent = {800, 600};
        actualExtent.width = std::max(capabilities.minImageExtent.width, std::min(capabilities.maxImageExtent.width, actualExtent.width));
        actualExtent.height = std::max(capabilities.minImageExtent.height, std::min(capabilities.maxImageExtent.height, actualExtent.height));
        return actualExtent;
    }
}