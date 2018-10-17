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

	//������������� ������� ����������� (�.�. ����� ������� � swapChain - ��. choosePresentationMode)
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

	//���������� ���� image - ������������� ����������� � ������ (�� �������������� �������, ������� ������ ������)
    std::vector<VkImage> swapChainImages;
    vkGetSwapchainImagesKHR(*logicalDevice->getVkLogicalDevice(), swapChain, &imageCount, nullptr);
    swapChainImages.resize(imageCount);
    vkGetSwapchainImagesKHR(*logicalDevice->getVkLogicalDevice(), swapChain, &imageCount, swapChainImages.data());

	//ImageView - ���� ������ � image
    std::vector<VkImageView> swapChainImageViews;

    swapChainImageViews.resize(swapChainImages.size());
    for (size_t i = 0; i < swapChainImages.size(); i++) {
        VkImageViewCreateInfo createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        createInfo.image = swapChainImages[i];
        createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        createInfo.format = surfaceFormat.format;
        createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;//����� ������, �������� ����� ��� � R ��� ����������� �������
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
	//��������� ��� ���������� ����� �������� � ���� surface (�� ���� - image)
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
	//�������� ������������
	//https://stackoverflow.com/questions/12524623/what-are-the-practical-differences-when-working-with-colors-in-a-linear-vs-a-no
	//���� � ������ - ������� �������� �������� ������������ RGB ����������� ����� � ���� ��������� xyz;
	//���� � �������� �������� �������� �����, �� � ���� ���������� �������. ����� ��� ��. �� ������������ ���� ����� �� �������� ����� ������� ����
	//� ������ �������� ������� ��������, ������� ���������� ��� � ������ ��������, � ����� ��� �����, ������� �� ������� �������
	//��� ����� ����� ������������ SRGB(� ������) - ��� ��� ����������, � ������������ � ���� ������
	//�������������� �������� ������������ ������ srgb � ������� ����� �������� �� ������� ������ � RGB(�.�. ���� �������� ������������ �������)
	//�������� � ������� RGB �������� ���������� 128 - ��� ����� �������� ������� ������������, �� ��� �� �������� � srgb - ����� 22% �� �������� �������
	//������� ������� - � sRGB �������� ������ �������� ������� ���������� � ������� ��� ����� ����� ������� �� ������� �������� (�.� �����
	//������ �������� �������, ������ ��� �������� rgb ���������� �������� ���������, �� �.�. ������� �� ��������� � ���� ��� ������)
	//�������� sRGB ���������, ����� ������ ������� ������ ���� �������� ����� � ����� ������ ������� ��������� ��� �� ����������
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
	//��������� ������������ ����� ������� ����� ����������� �������� �� ����� �� �����
    VkPresentModeKHR bestMode = VK_PRESENT_MODE_FIFO_KHR;//������� ����� ��� ����-����� (���� �� � �� ������������)
	//The moment that the display is refreshed is known as �vertical blank�
    for (const auto& availablePresentMode : availablePresentModes) {
        if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {//��� ��� ������ ������
            return availablePresentMode;
        } else if (availablePresentMode == VK_PRESENT_MODE_IMMEDIATE_KHR) {
            bestMode = availablePresentMode;
        }
    }
    return bestMode;
}

VkExtent2D VkSwapChainManager::chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities) {
	//The swap extent is the resolution of the swap chain images and it�s almost always exactly equal to the resolution 
	//of the window that we�re drawing to
    if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
        return capabilities.currentExtent;
    } else {
        VkExtent2D actualExtent = {800, 600};
        actualExtent.width = std::max(capabilities.minImageExtent.width, std::min(capabilities.maxImageExtent.width, actualExtent.width));
        actualExtent.height = std::max(capabilities.minImageExtent.height, std::min(capabilities.maxImageExtent.height, actualExtent.height));
        return actualExtent;
    }
}