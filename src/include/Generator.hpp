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

using namespace boost::spirit;
using namespace llvm;

// LLVM code generation
namespace lang::codegen {
    class Generator {
        std::unique_ptr<LLVMContext> context;
        std::unique_ptr<IRBuilder<>> builder;
        std::unique_ptr<Module> module;
    public:
        Generator() {
            context = std::make_unique<LLVMContext>();
            builder = std::make_unique<IRBuilder<>>(*context);
            module = std::make_unique<Module>("module", *context);
        }
    };
}



#endif //GENERATOR_HPP
