#ifndef PARSER_H
#define PARSER_H

#include "ast.h"
#include "lexer.h"
#include "token.h"

class Parser {
   public:
    Parser(Lexer* l);
    void nextToken();
    Program* parseProgram();
    Statement* parseStatement();
    Statement* parseLetStatement();
    Statement* parseReturnStatement();

    std::vector<std::string> getErrors() { return errors; }

    Token curToken;
    Token peekToken;

   private:
    void peekError(tokenType t);
    void curError(tokenType t);
    std::vector<std::string> errors;
    bool curTokenIs(tokenType t);
    bool peekTokenIs(tokenType t);
    bool expectPeek(tokenType t);
    Lexer* l;
};

#endif  // !PARSER_H
