#include "lexer.h"

#include <cctype>
#include <iostream>
#include <string>

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

// Check if token is a reserved keyword, if not return IDENT
std::string lookupIdent(const std::string& ident) {
    auto it = keywords.find(ident);
    if (it != keywords.end()) {
        return it->second;
    }
    return TokenType::IDENT;
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
    : input(input), position(0), readPosition(0), currentChar(' ') {}

// Method to skip over whitespaces/tabs/returns
void Lexer::skipWhitespace() {
    while (currentChar == ' ' || currentChar == '\n' || currentChar == '\t' ||
           currentChar == '\r') {
        readChar();
    }
}

// Method to read next token in the Lexer
Token Lexer::nextToken() {
    skipWhitespace();
    Token t = createToken(TokenType::ILLEGAL, currentChar);
    switch (currentChar) {
        case '=':
            if (peekChar() == '=') {
                t = createToken(TokenType::EQ, "==");
                readChar();
            } else {
                t.Type = TokenType::ASSIGN;
            }
            break;
        case '!':
            if (peekChar() == '=') {
                t = createToken(TokenType::NOTEQ, "!=");
                readChar();
            } else {
                t.Type = TokenType::BANG;
            }
            break;
        case ';':
            t.Type = TokenType::SEMICOLON;
            break;
        case '(':
            t.Type = TokenType::LPAREN;
            break;
        case ')':
            t.Type = TokenType::RPAREN;
            break;
        case '+':
            t.Type = TokenType::PLUS;
            break;
        case '-':
            t.Type = TokenType::MINUS;
            break;
        case '/':
            t.Type = TokenType::SLASH;
            break;
        case '*':
            t.Type = TokenType::ASTERISK;
            break;
        case '<':
            t.Type = TokenType::LT;
            break;
        case '>':
            t.Type = TokenType::GT;
            break;
        case '{':
            t.Type = TokenType::LBRACE;
            break;
        case '}':
            t.Type = TokenType::RBRACE;
            break;
        case ',':
            t.Type = TokenType::COMMA;
            break;
        case '\0':
            t.Type = TokenType::EoF;
            t.Literal = "";
            break;
        default:
            if (isLetter(currentChar)) {
                std::string literal = readIdent();
                return createToken(lookupIdent(literal), literal);
            }
            if (std::isdigit(currentChar)) {
                return createToken(TokenType::INT, readNumber());
            }
    }

    readChar();

    return t;
}

std::string Lexer::readIdent() {
    size_t pos = position;
    while (isLetter(currentChar)) {
        readChar();
    }
    return input.substr(pos, position - pos);
}

std::string Lexer::readNumber() {
    size_t pos = position;
    while (std::isdigit(currentChar)) {
        readChar();
    }
    return input.substr(pos, position - pos);
}
