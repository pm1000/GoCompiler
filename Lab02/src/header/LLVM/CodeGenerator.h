//
// Created by philipp on 20.06.21.
//

#ifndef LAB02_CODEGENERATOR_H
#define LAB02_CODEGENERATOR_H

#include "llvm/ADT/STLExtras.h"
#include "llvm/ADT/iterator_range.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/JITSymbol.h"
#include "llvm/ExecutionEngine/Orc/CompileUtils.h"
#include "llvm/ExecutionEngine/Orc/IRCompileLayer.h"
#include "llvm/ExecutionEngine/Orc/LambdaResolver.h"
#include "llvm/ExecutionEngine/Orc/RTDyldObjectLinkingLayer.h"
#include "llvm/ExecutionEngine/RTDyldMemoryManager.h"
#include "llvm/ExecutionEngine/SectionMemoryManager.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/IR/Mangler.h"
#include "llvm/Support/DynamicLibrary.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {
    namespace orc {

        using ObjLayerT = LegacyRTDyldObjectLinkingLayer;
        using CompileLayerT = LegacyIRCompileLayer<ObjLayerT, SimpleCompiler>;

        class CodeGenerator {
        private:
            std::string mangle(const std::string &Name);
            JITSymbol findMangledSymbol(const std::string &Name);
            ExecutionSession ES;
            std::shared_ptr<SymbolResolver> Resolver;
            std::unique_ptr<TargetMachine> TM;
            const DataLayout DL;
            ObjLayerT ObjectLayer;
            CompileLayerT  CompileLayer;
            std::vector<VModuleKey> ModuleKeys;


        public:

            CodeGenerator();

            TargetMachine& getTargetMachine();
            VModuleKey addModule(std::unique_ptr<Module> M);
            void removeModule(VModuleKey K);
            JITSymbol findSymbol(const std::string Name);
        };

    }
}


#endif //LAB02_CODEGENERATOR_H
