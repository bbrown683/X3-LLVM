#ifndef GENERATOR_HPP
#define GENERATOR_HPP

#include "boost/variant.hpp"
#include "boost/variant/get.hpp"

#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"

#include "AST.hpp"

using namespace llvm;
using namespace lang::ast;

// LLVM code generation
namespace lang::codegen {
    class Generator {
        std::unique_ptr<LLVMContext> context;
        std::unique_ptr<IRBuilder<>> builder;
        std::unique_ptr<Module> module;
        std::vector<std::unique_ptr<GlobalVariable>> globalVariables;

        std::string getTypeFromValue(const literals_& value) {
            switch (value.var.which()) {
                case 0: return "f32";
                case 1: return "f64";
                case 2: return "bool";
                case 3: return "i8";
                case 4: return "i16";
                case 5: return "i32";
                case 6: return "i64";
                case 7: return "char";
                case 8: return "str";
            }
            return "any";
        }

        Type* getTypeFromName(const std::string& name) {
            if (name == "bool") {
                return Type::getInt1Ty(*context);
            }
            if (name == "i8") {
                return Type::getInt8Ty(*context);
            }
            if(name == "i16") {
                return Type::getInt16Ty(*context);
            }
            if(name == "i32") {
                return Type::getInt32Ty(*context);
            }
            if (name == "i64") {
                return Type::getInt64Ty(*context);
            }
            if (name == "f32") {
                return Type::getFloatTy(*context);
            }
            if (name == "f64") {
                return Type::getDoubleTy(*context);
            }
            if (name == "char") {
                return Type::getInt8Ty(*context);
            }
            if (name == "str") {
                return Type::getInt8PtrTy(*context);
            }
            return Type::getVoidTy(*context);
        }
    public:
        Generator(const translationUnit& translationUnit) {
            context = std::make_unique<LLVMContext>();
            builder = std::make_unique<IRBuilder<>>(*context);
            std::string modulePath = boost::algorithm::join(translationUnit.module, ".");
            std::cout << "Module: " << modulePath << std::endl;
            module = std::make_unique<Module>(modulePath, *context);

            for(const auto& import : translationUnit.imports) {
                std::cout << "Import: " << boost::algorithm::join(import, ".") << std::endl;
            }

            for(const auto& declaration : translationUnit.declarations) {
                boost::apply_visitor(*this, declaration);
            }
        }

        std::string GetIR() {
            std::string moduleString;
            raw_string_ostream rawStringOstream(moduleString);
            module->print(rawStringOstream, nullptr);
            return moduleString;
        }

        void operator()(const variable& variable) {
            auto value = variable.literals;
            auto type = variable.type.value_or(getTypeFromValue(value));
            std::cout << "Variable: Name - " << variable.name
            << ", Type - " << type
            << ", Value - " << value.get()
            << ", Mutable - " << variable.mutable_ << std::endl;
            globalVariables.push_back(std::make_unique<GlobalVariable>(*module, getTypeFromName(type), !variable.mutable_, GlobalValue::ExternalLinkage, nullptr, Twine(variable.name)));
        }

        void operator()(const type& type) {
            std::cout << "Type: "  << type.name << std::endl;
        }

        void operator()(const function& function) {
            std::cout << "Function: " << function.name << std::endl;

            std::vector<Type*> paramTypes;
            for(auto& parameter : function.parameters) {
                std::cout << "\tParameter: Name - " << parameter.name
                << ", Type - " << parameter.type << std::endl;
                paramTypes.push_back(getTypeFromName(parameter.type));
            }

            std::cout << "\tReturn Type: " << function.returnType.value_or("Inferred") << std::endl;
            FunctionType* functionType = FunctionType::get(getTypeFromName(function.returnType.value_or("Inferred")), paramTypes, false);

            Function* llvmFunction = Function::Create(functionType, Function::ExternalLinkage, function.name, *module);

            BasicBlock* basicBlock = BasicBlock::Create(*context, "entry", llvmFunction);
            builder->SetInsertPoint(basicBlock);
            for(auto& expression : function.expressions) {
                std::cout << "\t";
                boost::apply_visitor(*this, expression);
            }
            
            // Add a return statement at the end of the function.
            // For simplicity, let's assume it always returns 0.
            builder->CreateRet(ConstantInt::get(*context, APInt(64, 0)));
            
            verifyFunction(*llvmFunction);
        }
    };
}



#endif //GENERATOR_HPP
