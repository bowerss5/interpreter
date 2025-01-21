
#include <string>
using tokenType = std::string;
class Token {
   public:
    tokenType Type;
    std::string Literal;
    Token(const tokenType& type, const std::string& literal)
        : Type(type), Literal(literal) {}
};

namespace TokenType {
const std::string ILLEGAL = "ILLEGAL";
const std::string EoF = "EOF";
// Identifiers + literals
const std::string IDENT = "IDENT";
const std::string INT = "INT";
// Operators
const std::string ASSIGN = "=";
const std::string PLUS = "+";
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
}  // namespace TokenType
