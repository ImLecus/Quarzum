#pragma once
#include "astnode.hpp"

class Identifier : public ASTNode {
public:
    std::string name;
    Identifier(std::string name) : name(name) {}
    void print() override{
        std::cout << "Identifier: " << name << '\n';
    }
};

class Type : public ASTNode {
public:
    std::string type;
    Type(std::string type) : type(type) {}
    void print() override{
        std::cout << "Type: " << type << '\n';
    }
};


class FunctionCall : public ASTNode {
public:
    ASTNode* identifier;
    std::vector<ASTNode*> args;
    FunctionCall(ASTNode* identifier, std::vector<ASTNode*> args): identifier(identifier), args(args) {}
    void print() override{
        std::cout << "FunctionCall:\n";
        identifier->print();
        for(auto& arg: args){
            arg->print();
        }
    }
};

class Argument : public ASTNode {
public:
    ASTNode* type;
    ASTNode* identifier;
    Argument(ASTNode* type, ASTNode* identifier): type(type), identifier(identifier) {}
    void print() override{
        std::cout << "Argument:\n";
        type->print();
        identifier->print();
    }
};