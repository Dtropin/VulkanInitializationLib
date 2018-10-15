//
// Created by Tropin Denis on 24.04.2018.
//

#include <xstring>
#include <vector>
#include <fstream>

class ShaderLoader {
    public:
        static std::vector<char> readFile(const std::string& filename);
};