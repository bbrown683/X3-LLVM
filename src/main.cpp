#include <fstream>
#include "include/Parser.hpp"

int main() {
    const std::string example =
        R"(
        module example.test
        import stdlib.io
        import stdlib.test

        var variableTest
        type typeTest
        fn functionTest
        )";

    lang::parse(example);
}