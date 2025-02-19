#include "include/Parser.hpp"

#include <fstream>

int main() {

    std::ifstream ifstream("test.lang");
    std::stringstream stringstream;
    ifstream >> stringstream.rdbuf();

    std::string content = stringstream.str();
    lang::parse(content);
    return 0;
}