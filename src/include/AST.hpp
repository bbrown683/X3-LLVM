#ifndef AST_HPP
#define AST_HPP

#include <optional>

#define BOOST_SPIRIT_X3_DEBUG
#include <boost/algorithm/string/join.hpp>
#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>
#include <boost/spirit/home/x3/support/utility/error_reporting.hpp>
#include <boost/spirit/home/x3/support/utility/lambda_visitor.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/variant/apply_visitor.hpp>

using namespace boost::spirit;

// Holds the AST definitions.
namespace lang::ast {
    struct operation;
    struct variable;

    struct expressions_ : x3::variant<x3::forward_ast<variable>> {
        using base_type::base_type;
        using base_type::operator=;
    };

    struct literals_ : x3::variant<float, double, bool, int8_t, short, int, long, char, std::string> {
        using base_type::base_type;
        using base_type::operator=;
    };

    struct variable : x3::position_tagged {
        bool mutable_;
        std::string name;
        std::optional<std::string> type;
        literals_ literals;
    };

    struct parameter : x3::position_tagged {
        std::string name;
        std::string type;
    };

    struct function : x3::position_tagged {
        std::string name;
        std::vector<parameter> parameters;
        std::optional<std::string> returnType;
        std::vector<expressions_> expressions;
    };

    struct type : x3::position_tagged {
        std::string name;
        // TODO: members, functions, etc
    };

    typedef std::vector<std::string> module_;
    typedef std::vector<std::string> import_;

    struct declarations_ : x3::variant<x3::forward_ast<variable>,
    x3::forward_ast<function>,
    x3::forward_ast<type>> {
        using base_type::base_type;
        using base_type::operator=;
    };

    struct translationUnit : x3::position_tagged {
        module_ module;
        std::vector<import_> imports;
        std::vector<declarations_> declarations;
    };
}

BOOST_FUSION_ADAPT_STRUCT(lang::ast::variable,
    (bool, mutable_),
    (std::string, name),
    (std::optional<std::string>, type),
    (lang::ast::literals_, literals))
BOOST_FUSION_ADAPT_STRUCT(lang::ast::parameter,
    (std::string, name),
    (std::string, type))
BOOST_FUSION_ADAPT_STRUCT(lang::ast::function,
    (std::string, name),
    (std::vector<lang::ast::parameter>, parameters),
    (std::optional<std::string>, returnType),
    (std::vector<lang::ast::expressions_>, expressions))
BOOST_FUSION_ADAPT_STRUCT(lang::ast::type,
    (std::string, name))
BOOST_FUSION_ADAPT_STRUCT(lang::ast::translationUnit,
    (lang::ast::module_, module),
    (std::vector<lang::ast::import_>, imports),
    (std::vector<lang::ast::declarations_>, declarations))

#endif