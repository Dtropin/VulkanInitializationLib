#include <iostream>
#include <memory>
#include "core/entryPoint/GameApplicationRunner.h"

int main() {
   return GameApplicationRunner::getInstance().runGame();
}