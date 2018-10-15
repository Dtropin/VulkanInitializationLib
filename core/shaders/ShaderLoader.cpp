//
// Created by Tropin Denis on 24.04.2018.
//

#include "ShaderLoader.h"

//Вершинный шейдер обрабатывает каждую вершину и выдает для нее после всеъ преобразований
//clip coordinate is a four dimensional vector from the vertex shader that is
//subsequently turned into a normalized device coordinate by dividing the whole
//vector by its last component
std::vector<char> ShaderLoader::readFile(const std::string &filename) {
    std::ifstream file(filename, std::ios::ate | std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("failed to open file!");
    }

    size_t fileSize = (size_t) file.tellg();
    std::vector<char> buffer(fileSize);
    file.seekg(0);
    file.read(buffer.data(), fileSize);
    file.close();
    return buffer;
}
