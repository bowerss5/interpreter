
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

#include "lexer.h"
struct TestCase {
    std::string expectedType;
    std::string expectedLiteral;
};
// std::string input = "=+(){},;";
// std::vector<TestCase> tests = {
//     {TokenType::ASSIGN, "="}, {TokenType::PLUS, "+"},
//     {TokenType::LPAREN, "("}, {TokenType::RPAREN, ")"},
//     {TokenType::LBRACE, "{"}, {TokenType::RBRACE, "}"},
//     {TokenType::COMMA, ","},  {TokenType::SEMICOLON, ";"},
//     {TokenType::EoF, ""},
// };
const std::string input = R"(let five = 5;
let ten = 10;
let add = fn(x, y) {
    x + y;
};
let result = add(five, ten);
)";

const std::vector<TestCase> tests = {
    {TokenType::LET, "let"},     {TokenType::IDENT, "five"},
    {TokenType::ASSIGN, "="},    {TokenType::INT, "5"},
    {TokenType::SEMICOLON, ";"}, {TokenType::LET, "let"},
    {TokenType::IDENT, "ten"},   {TokenType::ASSIGN, "="},
    {TokenType::INT, "10"},      {TokenType::SEMICOLON, ";"},
    {TokenType::LET, "let"},     {TokenType::IDENT, "add"},
    {TokenType::ASSIGN, "="},    {TokenType::FUNCTION, "fn"},
    {TokenType::LPAREN, "("},    {TokenType::IDENT, "x"},
    {TokenType::COMMA, ","},     {TokenType::IDENT, "y"},
    {TokenType::RPAREN, ")"},    {TokenType::LBRACE, "{"},
    {TokenType::IDENT, "x"},     {TokenType::PLUS, "+"},
    {TokenType::IDENT, "y"},     {TokenType::SEMICOLON, ";"},
    {TokenType::RBRACE, "}"},    {TokenType::SEMICOLON, ";"},
    {TokenType::LET, "let"},     {TokenType::IDENT, "result"},
    {TokenType::ASSIGN, "="},    {TokenType::IDENT, "add"},
    {TokenType::LPAREN, "("},    {TokenType::IDENT, "five"},
    {TokenType::COMMA, ","},     {TokenType::IDENT, "ten"},
    {TokenType::RPAREN, ")"},    {TokenType::SEMICOLON, ";"},
    {TokenType::EoF, ""},
};

int main(int argc, char* argv[]) {
    Lexer lexer(input);
    for (const auto& test : tests) {
        Token tok = lexer.nextToken();
        std::cout << tok.Literal << " : " << tok.Type << " | "
                  << test.expectedLiteral << " : " << test.expectedType
                  << std::endl;
        if (tok.Type != test.expectedType) {
            std::cerr << "Wrong token type" << std::endl;
        }
        if (tok.Literal != test.expectedLiteral) {
            std::cerr << "Wrong literal" << std::endl;
        }
    }

    return 0;
}
