#include "parser.h"

#include "ast.h"
#include "token.h"

// Helper methods to check token type
bool Parser::curTokenIs(tokenType t) { return curToken.Type == t; };
bool Parser::peekTokenIs(tokenType t) { return peekToken.Type == t; };

bool Parser::expectPeek(tokenType t) {
    if (peekTokenIs(t)) {
        nextToken();
        return true;
    }
    peekError(t);
    return false;
}

void Parser::peekError(tokenType t) {
    errors.push_back("Expected next token to be " + t + ", got " +
                     peekToken.Type + " instead.");
};
void Parser::curError(tokenType t) {
    errors.push_back("Expected next token to be " + t + ", got " +
                     curToken.Type + " instead.");
};
Parser::Parser(Lexer* l) {
    this->l = l;
    nextToken();
    nextToken();
    errors = std::vector<std::string>();
}

void Parser::nextToken() {
    curToken = peekToken;
    peekToken = l->nextToken();
}

Program* Parser::parseProgram() {
    Program* p = new Program();

    while (!curTokenIs(TokenType::EoF)) {
        Statement* s = parseStatement();
        if (s != nullptr) {
            p->statements.push_back(s);
        }
        nextToken();
    }
    return p;
}

// Wrapper to determine which statemnet processing method to use
Statement* Parser::parseStatement() {
    if (curTokenIs(TokenType::LET)) {
        return parseLetStatement();
    }
    if (curTokenIs(TokenType::RETURN)) {
        return parseReturnStatement();
    }
    return nullptr;
}

Statement* Parser::parseLetStatement() {
    LetStatement* s = new LetStatement(curToken);

    if (!expectPeek(TokenType::IDENT)) return nullptr;

    s->name = new Identifier(curToken);

    if (!expectPeek(TokenType::ASSIGN)) return nullptr;

    // Skip until semicolon
    // TODO add expression handling
    if (!curTokenIs(TokenType::SEMICOLON)) nextToken();
    return s;
}

Statement* Parser::parseReturnStatement() {
    ReturnStatement* s = new ReturnStatement(curToken);
    nextToken();

    // TODO add expression handling
    if (!curTokenIs(TokenType::SEMICOLON)) nextToken();
    return s;
}
