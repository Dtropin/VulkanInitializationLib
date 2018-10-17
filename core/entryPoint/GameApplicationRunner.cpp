#include <stdexcept>
#include <iostream>
#include "GameApplicationRunner.h"
#include "glfw3.h"
#include "../outputwindow/impl/glfw/GlfwWindowInitializer.h"
#include "../logic/VulkanInitializationEntryPoint.h"

int GameApplicationRunner::runGame() {
    if(!isGameAlreadyRunned.test_and_set()) {
		VkSemaphore imageAvailableSemaphore;
		VkSemaphore renderFinishedSemaphore;
		
        OutputWindowInterface* window = windowInitializer->createWindow();
		
        VulkanInterface* vulkanInstanceHandler = VulkanInitializationEntryPoint::getInstance()
                .setupVulkanSystem(window);

/**
		VkSemaphoreCreateInfo semaphoreInfo = {};
		semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
		
		if (vkCreateSemaphore(*vulkanInstanceHandler->logicalDevice->getVkLogicalDevice(), &semaphoreInfo, nullptr, &imageAvailableSemaphore) != VK_SUCCESS ||
			vkCreateSemaphore(*vulkanInstanceHandler->logicalDevice->getVkLogicalDevice(), &semaphoreInfo, nullptr, &renderFinishedSemaphore) != VK_SUCCESS) {
			throw std::runtime_error("failed to create semaphores!");
		}
		
		//this->mainLoop(vulkanInstanceHandler, window, imageAvailableSemaphore, renderFinishedSemaphore);
		vkDestroySemaphore(*vulkanInstanceHandler->logicalDevice->getVkLogicalDevice(), renderFinishedSemaphore, nullptr);
		vkDestroySemaphore(*vulkanInstanceHandler->logicalDevice->getVkLogicalDevice(), imageAvailableSemaphore, nullptr);
**/
        delete window;
        if(vulkanInstanceHandler != nullptr)
        delete vulkanInstanceHandler;
        return 0;
    } else {
        throw std::runtime_error("Game already started");
    }
}

GameApplicationRunner &GameApplicationRunner::getInstance() {
    static GameApplicationRunner runner;
    return runner;
}

GameApplicationRunner::GameApplicationRunner() {
    windowInitializer = new GlfwWindowInitializer();

}


void GameApplicationRunner::mainLoop(VulkanInterface* vulkanInstanceHandler, OutputWindowInterface* window
, VkSemaphore imageAvailableSemaphore, VkSemaphore renderFinishedSemaphore) {
	int count = 0;
	while (!glfwWindowShouldClose(window->getWindow())) {
		glfwPollEvents();
		if (count++ == 0) {
			uint32_t imageIndex;
			vkAcquireNextImageKHR(*vulkanInstanceHandler->logicalDevice->getVkLogicalDevice(),
				vulkanInstanceHandler->swapChainHandler->swapChain, std::numeric_limits<uint64_t>::max(), imageAvailableSemaphore,
				VK_NULL_HANDLE, &imageIndex);
			VkSubmitInfo submitInfo = {};
			submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
			VkSemaphore waitSemaphores[] = { imageAvailableSemaphore };
			VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
			submitInfo.waitSemaphoreCount = 1;
			submitInfo.pWaitSemaphores = waitSemaphores;
			submitInfo.pWaitDstStageMask = waitStages;
			submitInfo.commandBufferCount = 1;
			submitInfo.pCommandBuffers = &vulkanInstanceHandler->commandBuffers->at(imageIndex);
			VkSemaphore signalSemaphores[] = { renderFinishedSemaphore };
			submitInfo.signalSemaphoreCount = 1;
			submitInfo.pSignalSemaphores = signalSemaphores;

			VkSubpassDependency dependency = {};
			dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
			dependency.dstSubpass = 0;
			dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
			dependency.srcAccessMask = 0;
			dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
			dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
			VkPresentInfoKHR presentInfo = {};
			presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
			presentInfo.waitSemaphoreCount = 1;
			presentInfo.pWaitSemaphores = signalSemaphores;
			VkSwapchainKHR swapChains[] = { vulkanInstanceHandler->swapChainHandler->swapChain };
			presentInfo.swapchainCount = 1;
			presentInfo.pSwapchains = swapChains;
			presentInfo.pImageIndices = &imageIndex;
			presentInfo.pResults = nullptr; // Optional
		}
	}
	
}



