#ifndef RULES_HPP
#define RULES_HPP

#include <boost/spirit/home/x3/numeric/int.hpp>
#include <boost/spirit/home/x3.hpp>

#include "AST.hpp"

using namespace boost::spirit;

// Holds the rule definitions.
namespace lang::rules {
    // Rules that will be skipped during parsing.
    constexpr x3::rule<struct skipper> skipper = "skipper";
    constexpr x3::rule<struct comment> comment = "comment";

    auto inline skipper_def = x3::space | comment;
    auto inline comment_def = x3::string("#") >> x3::lexeme[*(x3::char_ - x3::eol)];

    BOOST_SPIRIT_DEFINE(skipper, comment);

    // Rules that will not be skipped during parsing.
    constexpr x3::rule<struct translationUnit, ast::translationUnit> translationUnit = "translationUnit";
    constexpr x3::rule<struct module, ast::module_> module = "module";
    constexpr x3::rule<struct import, ast::import_> import = "import";
    constexpr x3::rule<struct variable, ast::variable> variable = "variable";
    constexpr x3::rule<struct function, ast::function> function = "function";
    constexpr x3::rule<struct parameter, ast::parameter> parameter = "parameter";
    constexpr x3::rule<struct type, ast::type> type = "type";
    constexpr x3::rule<struct expression, ast::expressions_> expression = "expression";
    constexpr x3::rule<struct branch> branch = "branch";
    constexpr x3::rule<struct loop> loop = "loop";
    constexpr x3::rule<struct match> match = "match";

    auto constexpr identifier = x3::rule<struct identifier, std::string>{"identifier"} = x3::lexeme[x3::alpha >> *x3::alnum];
    auto constexpr literals = x3::rule<struct literals, ast::literals_>{"values"} =
        x3::float_ | x3::double_ | x3::bool_ | x3::int8 | x3::int16 | x3::int32 | x3::int64 |
        x3::lit("'") >> x3::char_ >> x3::lit("'") | x3::lit('"') >> x3::lexeme[*(x3::char_ - x3::lit('"'))] >> x3::lit('"');

    auto inline translationUnit_def = module >> *import >> *(variable | function | type);
    auto inline module_def = "module" >> identifier % ".";
    auto inline import_def = "import" >> identifier % ".";
    auto inline variable_def = x3::matches["mut"] >> "var" >> identifier >> -(":" >> identifier) >> "=" >> literals;
    auto inline function_def = "fn" >> identifier >> ("(" >> parameter % ',' >> ")") >> -(":" >> identifier) >> "=" >> *expression;
    auto inline parameter_def = identifier >> ":" >> identifier;
    auto inline type_def = "type" >> identifier;
    auto inline expression_def = variable | branch;
    auto inline branch_def = x3::string("if") | x3::string("else if") | x3::string("else");
    auto inline loop_def = x3::string("while") | x3::string("for");

    auto inline match_def = "match";

    BOOST_SPIRIT_DEFINE(translationUnit, module, import, variable, function, parameter, type, expression, branch, loop, match);
}



#endif //RULES_HPP
