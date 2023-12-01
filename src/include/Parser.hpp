#ifndef PARSER_HPP
#define PARSER_HPP

#include <iostream>
#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/support/utility/error_reporting.hpp>

#include "AST.hpp"
#include "Rules.hpp"

typedef std::string::const_iterator iterator;

namespace lang {
    bool parse(std::string input) {
        using Iterator = std::string::const_iterator;

        Iterator begin = input.begin();
        Iterator const end = input.end();

        ast::translationUnit translationUnit;
        auto result = phrase_parse(begin, end, rules::translationUnit, x3::ascii::space, translationUnit);
        if(result && begin == end) {
            std::cout << "Parsing Complete" << std::endl;
            constexpr ast::Printer printer;
            printer(translationUnit);
        } else {
            std::cout << "Parsing Failed" << std::endl;
        }
        return result;
    }
}
#endif //PARSER_HPP
