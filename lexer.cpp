#include "lexer.h"

#include <iostream>

// --------------------
// -- Helper Methods --
// --------------------

// Wrapper methods to create token objects
Token createToken(tokenType type, std::string ch) { return Token(type, ch); }

Token createToken(tokenType type, char ch) {
    return createToken(type, std::string(1, ch));
}

bool isLetter(char ch) {
    return (std::isalpha(ch) || ch == '_');  // Letters and underscore
}
// -----------------
// -- Lexer Class --
// -----------------

// Method that reads the next character in the lexer and updates position
void Lexer::readChar() {
    if (readPosition >= input.size()) {
        currentChar = '\0';
    } else {
        currentChar = input[readPosition];
    }
    position = readPosition;
    readPosition++;
}

// Method that reads the next character in the lexer WITHOUT updating position
char Lexer::peekChar() {
    if (readPosition >= input.size()) {
        return '\0';
    }
    return input[readPosition];
}

// Constructor for lexer
Lexer::Lexer(std::string input)
    : input(input), position(0), readPosition(0), currentChar('\0') {}

// Method to read next token in the Lexer
Token Lexer::nextToken() {
    readChar();
    switch (currentChar) {
        case '=':
            return createToken(TokenType::ASSIGN, currentChar);
        case ';':
            return createToken(TokenType::SEMICOLON, currentChar);
        case '(':
            return createToken(TokenType::LPAREN, currentChar);
        case ')':
            return createToken(TokenType::RPAREN, currentChar);
        case '+':
            return createToken(TokenType::PLUS, currentChar);
        case '{':
            return createToken(TokenType::LBRACE, currentChar);
        case '}':
            return createToken(TokenType::RBRACE, currentChar);
        case ',':
            return createToken(TokenType::COMMA, currentChar);
        case '\0':
            return createToken(TokenType::EoF, "");
    }
    if (isLetter(currentChar)) {
        std::string literal = readIdent();
        return createToken(TokenType::ILLEGAL, literal);
    }
    return createToken(TokenType::ILLEGAL, currentChar);
}

std::string Lexer::readIdent() {
    size_t pos = position;
    while (isLetter(currentChar)) {
        readChar();
    }
    return input.substr(pos, position - pos);
}
