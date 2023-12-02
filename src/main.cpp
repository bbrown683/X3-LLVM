#include <fstream>
#include "include/Parser.hpp"

int main() {
    const std::string example =
        R"(
        module example.test
        import stdlib.io
        import stdlib.test

        var width : Integer = 10
        var height = 7
        fn calculateArea(width : Integer, height : Integer) =


        var radius : Integer = 4
        fn calculateDiameter(radius : Integer) =

        )";

    lang::parse(example);
}