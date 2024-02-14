#include <vector>
#include <any>
#include <functional>
#include <memory>
#include <exception>
#include <unordered_map>
#include <string>
#include <stdexcept>

class ASTNode {
public:
    virtual ~ASTNode() = default;
    virtual void execute(std::unordered_map<std::string, std::any>& context) = 0;
};

using ASTNodePtr = std::shared_ptr<ASTNode>;

class dSeqNode : public ASTNode {
    std::vector<ASTNodePtr> dStates;
public:
    void addState(ASTNodePtr state) {
        dStates.push_back(state);
    }

    void execute(std::unordered_map<std::string, std::any>& context) override {
        for (auto& state : dStates) {
            state->execute(context);
        }
    }
};

class VariableNode : public ASTNode {
    std::string name;
public:
    VariableNode(const std::string& name) : name(name) {}

    void execute(std::unordered_map<std::string, std::any>& context) override {
        if (context.find(name) == context.end()) {
            throw std::runtime_error("Variable " + name + " not defined.");
        }
        // Logik zur Verarbeitung der Variablen stehen.
    }
};

class AssignmentNode : public ASTNode {
    std::string name;
    std::any value;
public:
    AssignmentNode(const std::string& name, std::any value) : name(name), value(std::move(value)) {}

    void execute(std::unordered_map<std::string, std::any>& context) override {
        context[name] = value;
    }
};
