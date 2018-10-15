//
// Created by Tropin Denis on 01.04.2018.
//

#include <glfw3.h>
#include "GlfwWindowInitializer.h"
#include "GlfwOutputWindow.h"

/*
	Создаем окно куда выводить то что отрисовал вулкан, glfw поддерживает вулкан
*/
OutputWindowInterface *GlfwWindowInitializer::createWindow() {
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);//Говорим не создавать opengl context
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    GLFWwindow* window = glfwCreateWindow(800, 600, "Vulkan window", nullptr, nullptr);
    return new GlfwOutputWindow(window);
}
