//
// Created by User on 31.03.2018.
//
#pragma once
#include "../OutputWindowInterface.h"

class OutputWindowInitializer {
    public:
        virtual OutputWindowInterface* createWindow() = 0;
        OutputWindowInitializer() {}
    private:
        OutputWindowInitializer(const OutputWindowInitializer &) = delete;
        OutputWindowInitializer &operator=(OutputWindowInitializer &) = delete;
};

