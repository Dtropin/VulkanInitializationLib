#pragma once

#include "../outputwindow/init/OutputWindowInitializer.h"
#include "../modules/VulkanInterface.h"
#include <atomic>

class GameApplicationRunner {

public:
    static GameApplicationRunner &getInstance();

    void mainLoop(VulkanInterface *vulkanInstanceHandler, OutputWindowInterface *w, VkSemaphore imageAvailableSemaphore,
                  VkSemaphore renderFinishedSemaphore);

    int runGame();

private:
    GameApplicationRunner();

    GameApplicationRunner(const GameApplicationRunner &) = delete;

    GameApplicationRunner &operator=(GameApplicationRunner &) = delete;

    std::atomic_flag isGameAlreadyRunned;

    OutputWindowInitializer *windowInitializer;
};

