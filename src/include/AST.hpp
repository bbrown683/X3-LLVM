#ifndef AST_HPP
#define AST_HPP

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
    struct variable;

    struct expressions : x3::variant<x3::forward_ast<variable>> {
        using base_type::base_type;
        using base_type::operator=;
    };

    struct values : x3::variant<long, char, std::string> {
        using base_type::base_type;
        using base_type::operator=;
    };

    struct variable : x3::position_tagged {
        std::string name;
        std::optional<std::string> type;
        values values;
    };

    struct parameter : x3::position_tagged {
        std::string name;
        std::string type;
    };

    struct function : x3::position_tagged {
        std::string name;
        std::vector<parameter> parameters;
        std::vector<expressions> expressions;
    };

    struct type : x3::position_tagged {
        std::string name;
        // TODO: members, functions, etc
    };

    typedef std::vector<std::string> module_;
    typedef std::vector<std::string> import_;

    struct declarations : x3::variant<x3::forward_ast<variable>,
    x3::forward_ast<function>,
    x3::forward_ast<type>> {
        using base_type::base_type;
        using base_type::operator=;
    };

    struct translationUnit : x3::position_tagged {
        module_ module;
        std::vector<import_> imports;
        std::vector<declarations> declarations;
    };

    struct Printer {
        void operator()(const variable& variable) const {
            std::cout << "Variable: Name - " << variable.name
            << ", Type - " << variable.type.value_or("Inferred")
            << ", Value - " << variable.values.get() << std::endl;
        }

        void operator()(const type& type) const {
            std::cout << "Type: "  << type.name << std::endl;
        }

        void operator()(const function& function) const {
            std::cout << "Function: " << function.name << std::endl;

            for(auto& parameter : function.parameters) {
                std::cout << "\tParameter: Name - " << parameter.name
                << ", Type - " << parameter.type << std::endl;
            }

            for(auto& expression : function.expressions) {
                std::cout << "\t";
                boost::apply_visitor(*this, expression);
            }
        }

        void operator()(const translationUnit& translationUnit) const {
            std::cout << "Module: " << boost::algorithm::join(translationUnit.module, ".") << std::endl;

            for(const auto& import : translationUnit.imports) {
                std::cout << "Import: " << boost::algorithm::join(import, ".") << std::endl;
            }

            for(const auto& declaration : translationUnit.declarations) {
                boost::apply_visitor(*this, declaration);
            }
        }
    };
}

BOOST_FUSION_ADAPT_STRUCT(lang::ast::variable,
    (std::string, name),
    (std::optional<std::string>, type),
    (lang::ast::values, values))
BOOST_FUSION_ADAPT_STRUCT(lang::ast::parameter,
    (std::string, name),
    (std::string, type))
BOOST_FUSION_ADAPT_STRUCT(lang::ast::function,
    (std::string, name),
    (std::vector<lang::ast::parameter>, parameters),
    (std::vector<lang::ast::expressions>, expressions))
BOOST_FUSION_ADAPT_STRUCT(lang::ast::type,
    (std::string, name))
BOOST_FUSION_ADAPT_STRUCT(lang::ast::translationUnit,
    (lang::ast::module_, module),
    (std::vector<lang::ast::import_>, imports),
    (std::vector<lang::ast::declarations>, declarations))

#endif