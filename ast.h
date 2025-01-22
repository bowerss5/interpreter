// ast.h
#ifndef AST_H
#define AST_H

#include <ostream>
#include <string>
#include <vector>

#include "token.h"

class Node {
   public:
    virtual ~Node() = default;
    virtual std::string tokenLiteral() const = 0;
    friend std::ostream& operator<<(std::ostream& os, const Node& n);
};

class Statement : public virtual Node {
   public:
    virtual ~Statement() = default;
    virtual void statementNode() = 0;
};

class Expression : public virtual Node {
   public:
    virtual ~Expression() = default;
    virtual void expressionNode() = 0;
};

class Program : public Node {
   public:
    std::vector<Statement*> statements;
    Program() : statements(std::vector<Statement*>()) {};

    std::string tokenLiteral() const override {
        if (!statements.empty()) {
            return statements[0]->tokenLiteral();
        }
        return "";
    }
    ~Program() {
        for (auto s : statements) {
            delete s;
        }
    }
    friend std::ostream& operator<<(std::ostream& os, const Program& p) {
        for (auto& s : p.statements) {
            os << *s;
        }
        return os;
    };
};

class Identifier : public Expression {
   public:
    void expressionNode() override {};
    std::string tokenLiteral() const override { return token.Literal; };
    Identifier(Token t) : token(t), value(t.Literal) {};
    friend std::ostream& operator<<(std::ostream& os, const Identifier& id) {
        os << id.value;
        return os;
    }

   private:
    Token token;
    std::string value;
};

class LetStatement : public Statement {
   public:
    void statementNode() override {};
    std::string tokenLiteral() const override { return token.Literal; };
    LetStatement(Token t) : token(t), name(0), value(0) {};
    Token token;
    Identifier* name;
    Expression* value;

    friend std::ostream& operator<<(std::ostream& os, const LetStatement& ls) {
        os << ls.tokenLiteral() << " " << ls.name << " = ";
        if (ls.value != nullptr) {
            os << *ls.value;
        }
        os << std::endl;
        return os;
    }

   private:
};

class ReturnStatement : public Statement {
   public:
    void statementNode() override {};
    std::string tokenLiteral() const override { return token.Literal; };
    ReturnStatement(Token t) : token(t), value(0) {};
    Token token;
    Expression* value;
    friend std::ostream& operator<<(std::ostream& os,
                                    const ReturnStatement& rs) {
        os << rs.tokenLiteral() << " ";
        if (rs.value != nullptr) {
            os << *rs.value;
        }
        os << std::endl;
        return os;
    }
};

class ExpressionStatement : public Statement {
   public:
    void statementNode() override {};
    std::string tokenLiteral() const override { return token.Literal; };
    ExpressionStatement(Token t) : token(t), value(0) {};
    Token token;
    Expression* value;

    friend std::ostream& operator<<(std::ostream& os,
                                    const ExpressionStatement& es) {
        if (es.value != nullptr) {
            os << *es.value << std::endl;
        }
        return os;
    }
};

#endif
