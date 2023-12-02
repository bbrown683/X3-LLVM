#ifndef RULES_HPP
#define RULES_HPP

#include <iostream>
#include <boost/spirit/home/x3.hpp>

#include "AST.hpp"

using namespace boost::spirit;

// Holds the rule definitions.
namespace lang::rules {
    constexpr x3::rule<struct translationUnit, ast::translationUnit> translationUnit = "translationUnit";
    constexpr x3::rule<struct module, ast::module_> module = "module";
    constexpr x3::rule<struct import, ast::import_> import = "import";
    constexpr x3::rule<struct variable, ast::variable> variable = "variable";
    constexpr x3::rule<struct function, ast::function> function = "function";
    constexpr x3::rule<struct parameter, ast::parameter> parameter = "parameter";
    constexpr x3::rule<struct type, ast::type> type = "type";
    constexpr x3::rule<struct expression, ast::expressions> expression = "expression";
    constexpr x3::rule<struct if_else> ifElse = "ifElse";

    auto constexpr identifier = x3::rule<struct identifier, std::string>{"identifier"} = x3::lexeme[x3::alpha >> *x3::alnum];
    auto constexpr values = x3::rule<struct values, ast::values>{"values"} = x3::long_;

    auto inline translationUnit_def = module >> *import >> *(variable | function | type);
    auto inline module_def = "module" >> identifier % ".";
    auto inline import_def = "import" >> identifier % ".";
    auto inline variable_def = "var" >> identifier >> -(":" >> identifier) >> "=" >> values;
    auto inline function_def = "fn" >> identifier >> ("(" >> parameter % ',' >> ")") >> "=" >> *expression;
    auto inline parameter_def = identifier >> ":" >> identifier;
    auto inline type_def = "type" >> identifier;
    auto inline expression_def = variable | ifElse;
    auto inline ifElse_def = "if";
    BOOST_SPIRIT_DEFINE(translationUnit, module, import, variable, function, parameter, type, expression, ifElse);
}



#endif //RULES_HPP
