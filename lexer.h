#ifndef LEXER_H
#define LEXER_H
#include <string>

#include "token.h"

class Lexer {
   public:
    Lexer(std::string input);
    Token nextToken();

   private:
    std::string input;
    size_t position, readPosition;
    char currentChar;
    std::string readIdent();
    std::string readNumber();
    void skipWhitespace();
    void readChar();
    char peekChar();
};
#endif
