#ifndef GENERATOR_HPP
#define GENERATOR_HPP

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
    private: 
        Type* getTypeFromName(const std::string name) {
            if(name == "Integer") {
                return Type::getInt64Ty(*context);
            } else if (name == "String") {
                return Type::getInt8PtrTy(*context);
            } else if (name == "Boolean") {
                return Type::getInt1Ty(*context);
            } else if (name == "Float") {
                return Type::getFloatTy(*context);
            } else if (name == "Double") {
                return Type::getDoubleTy(*context);
            } else if (name == "Character") {
                return Type::getInt8Ty(*context);
            } else {
                return Type::getVoidTy(*context);
            }
        }

    public:
        Generator() {
            context = std::make_unique<LLVMContext>();
            builder = std::make_unique<IRBuilder<>>(*context);
            module = std::make_unique<Module>("module", *context);
        }

        void operator()(const variable& variable) {
            std::cout << "Variable: Name - " << variable.name
            << ", Type - " << variable.type.value_or("Inferred")
            << ", Value - " << variable.values.get() << std::endl;
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

        void operator()(const translationUnit& translationUnit) {
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



#endif //GENERATOR_HPP
