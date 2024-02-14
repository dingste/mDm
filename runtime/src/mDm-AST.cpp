#include "mDm-AST.h"
#include <unordered_map>
#include <iostream>

class RuntimeEnvironment {
    std::unordered_map<std::string, ASTNodePtr> dSeqDefinitions;
    std::unordered_map<std::string, std::any> globalContext;

public:
    void registerdSeq(const std::string& name, ASTNodePtr node) {
        dSeqDefinitions[name] = std::move(node);
    }

    void executedSeq(const std::string& name) {
        if (dSeqDefinitions.find(name) == dSeqDefinitions.end()) {
            throw std::runtime_error("dSeq " + name + " not defined.");
        }
        std::cout << "execute "<< name <<  std::endl;

        dSeqDefinitions[name]->execute(globalContext);
    }

    // Logik zur dynamischen Reorganisation des ASTs stehen.
};
