//
// Created by Tropin Denis on 25.04.2018.
//
#pragma once

#include <vulkan.h>
#include "RenderPassInitializer.h"

VkRenderPass RenderPassInitializer::createRenderPass(SwapChainHandler swapChainHandler, VkDevice device) {
    //Информация о формате frame буфера и прочей мета-инфе

	//Attachment - RenderTarget. В данном случае только 1 буфер - Color buffer инициализируемый в SwapChain
	VkRenderPass renderPass;
    VkAttachmentDescription colorAttachment = {};
    colorAttachment.format = swapChainHandler.swapChainImageFormat;//Используемый формат, долженн совпадать с тем что в своп чейне
    colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;//Для сглаживания, у нас щас его нет,
    colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;//Что делать с с данными в attachment до рендера. CLEAR - присваивать константное значение
	//(Очистка)
    colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;//-||- после рендера. OP_STORE После рендера данные сохраняются и могут быть прочитаны
    colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;

	//FrameBuffer и Текстуры представлены Классом VkImage, но их макеты (layout) их можно менять 
    colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;//
    colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;// Говорит о том, что изображение будет презентовано в SwapChain
    
	//Вроде как у каждого RenderPass может быть subpass
	VkAttachmentReference colorAttachmentRef = {};
    colorAttachmentRef.attachment = 0;
    colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
    VkSubpassDescription subpass = {};
    subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpass.colorAttachmentCount = 1;
    subpass.pColorAttachments = &colorAttachmentRef;

    VkRenderPassCreateInfo renderPassInfo = {};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    renderPassInfo.attachmentCount = 1;
    renderPassInfo.pAttachments = &colorAttachment;
    renderPassInfo.subpassCount = 1;
    renderPassInfo.pSubpasses = &subpass;

    if (vkCreateRenderPass(device, &renderPassInfo, nullptr, &renderPass) != VK_SUCCESS) {
        throw std::runtime_error("failed to create render pass!");
    }

    return renderPass;
}


