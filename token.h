#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <unordered_map>
using tokenType = std::string;

namespace TokenType {
const std::string ILLEGAL = "ILLEGAL";
const std::string EoF = "EOF";
// Identifiers + literals
const std::string IDENT = "IDENT";
const std::string INT = "INT";
// Operators
const std::string ASSIGN = "=";
const std::string PLUS = "+";
const std::string MINUS = "-";
const std::string BANG = "!";
const std::string ASTERISK = "*";
const std::string SLASH = "/";

const std::string LT = "<";
const std::string GT = ">";
const std::string EQ = "==";
const std::string NOTEQ = "!=";
// Delimiters
const std::string COMMA = ",";
const std::string SEMICOLON = ";";
const std::string LPAREN = "(";
const std::string RPAREN = ")";
const std::string LBRACE = "{";
const std::string RBRACE = "}";
// Keywords
const std::string FUNCTION = "FUNCTION";
const std::string LET = "LET";
const std::string TRUE = "TRUE";
const std::string FALSE = "FALSE";
const std::string IF = "IF";
const std::string ELSE = "ELSE";
const std::string RETURN = "RETURN";
// Operators
}  // namespace TokenType

class Token {
   public:
    tokenType Type;
    std::string Literal;
    Token(const tokenType& type, const std::string& literal)
        : Type(type), Literal(literal) {};
    Token() : Type(TokenType::ILLEGAL), Literal("ILLEGAL") {};
};

//
const std::unordered_map<std::string, std::string> keywords = {
    {"fn", TokenType::FUNCTION},   {"let", TokenType::LET},
    {"true", TokenType::TRUE},     {"false", TokenType::FALSE},
    {"if", TokenType::IF},         {"else", TokenType::ELSE},
    {"return", TokenType::RETURN},
};

#endif
