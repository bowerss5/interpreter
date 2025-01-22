#include <iostream>
#include <ostream>
#include <string>

#include "parser.h"

bool parserErrors(Parser *p) {
    std::vector<std::string> errors = p->getErrors();
    if (errors.empty()) {
        std::cout << "No Errors :)" << std::endl;
        return false;
    }
    for (auto &e : errors) {
        std::cout << e << std::endl;
    }
    return true;
}
int main(int argc, char *argv[]) {
    std::string input = R"(
let x = 5;
let y = 10;
let foobar = 838383;
return 3;
    )";
    Parser *p = new Parser(new Lexer(input));
    Program *pro = p->parseProgram();
    parserErrors(p);
    std::cout << pro->statements.size() << std::endl;
    std::cout << pro->statements[3]->tokenLiteral() << std::endl;
    std::cout << *pro;

    return 0;
}
