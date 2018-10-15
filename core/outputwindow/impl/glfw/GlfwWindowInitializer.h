//
// Created by Tropin Denis on 01.04.2018.
//

#include <sal.h>
#include "../../init/OutputWindowInitializer.h"

class GlfwWindowInitializer : public OutputWindowInitializer{
    public:
        GlfwWindowInitializer() {}
        __override OutputWindowInterface* createWindow();
};