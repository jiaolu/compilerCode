#ifndef AST_H
#define AST_H
#include <vector>
#include <memory>
#include <iostream>
#include <utility>

class Expression;
class Statement;
class ASTNode {
public:
    const char* nodeType; // Type of the AST node (e.g., "Prog", "FuncDecl", etc.)
    unsigned depth; // Depth of the node in the AST
    virtual ~ASTNode() = default;
    virtual void ChildrenPrint() const {
        for (const auto& child : children) {
            child->Print();
        }
    }
    virtual void Print() const {
        std::cout << std::string(depth * 2, ' ') << nodeType << "(" << std::endl;
        ChildrenPrint();
        std::cout << std::string(depth * 2, ' ') << " )" << std::endl;
    }
    ASTNode(const char* type, unsigned d) : nodeType(type), depth(d) {}
    virtual void addChild(std::unique_ptr<ASTNode> child) {
        children.push_back(std::move(child));
    }
    unsigned getDepth() const {
        return depth;
    }
    std::vector<std::unique_ptr<ASTNode>> children; // Vector to hold child nodes
};

class ProgNode : public ASTNode {
public:
    ProgNode (unsigned d) : ASTNode("Prog", d){ }
    void Print() const override {
        std::cout << std::endl << "---------------- AST --------------------" << std::endl;
        ASTNode::Print();
    }
};

class FuncNode : public ASTNode {
public:
    std::vector<std::unique_ptr<Statement>> statements; // Vector to hold child nodes
    FuncNode(unsigned d) : ASTNode("Func", d), funcName(nullptr) { }
    const char* funcName; // Name of the function
    void setFuncName(const char* name) {
        funcName = name;
    }
    virtual void Print() const override {
        std::cout << std::string(depth * 2, ' ') << nodeType << "(" << std::endl;
        std::cout  << std::string((depth + 1) * 2, ' ') << "name= " << funcName << std::endl;
        ChildrenPrint();
        std::cout << std::string(depth * 2, ' ') << " )" << std::endl;
    }

    void ChildrenPrint() const override;

    void addChild(std::unique_ptr<Statement> child){
        statements.push_back(std::move(child));
    }
};

class Statement: public ASTNode {
public:
    Statement(const char* typeName, unsigned depth) : ASTNode(typeName, depth) { }

};

class ReturnStm: public Statement {
public:
    std::unique_ptr<Expression> exp; // Vector to hold child nodes
    ReturnStm(unsigned depth) : Statement("Return", depth) { }
    void addChild(std::unique_ptr<Expression> child){
        exp = std::move(child);
    }
    void ChildrenPrint() const override;
};

class Expression: public ASTNode {
public:
    Expression(const char* type, unsigned d) : ASTNode(type, d){ }
};

class ConstantExp : public Expression {
public:
const char* value;
    ConstantExp(const char* val, unsigned d) : Expression("Constant", d), value(val) {}
    void Print() const override {
        std::cout << std::string(depth * 2, ' ') << nodeType << "(" << value << ")" << std::endl;
    }
};


#endif