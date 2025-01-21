#include "repl.h"

#include <ostream>
#include <string>

#include "lexer.h"

const std::string prompt = "$ ";

Repl::Repl(std::istream &in, std::ostream &out) {
    char *c;
    std::string s;
    out << prompt;

    std::getline(in, s);
    out << s;

    Lexer *l = new Lexer(s);
    Token t = l->nextToken();

    while (t.Type != TokenType::EoF) {
        out << "{Type: " + t.Type + " | Literal: " + t.Literal + " }"
            << std::endl;
        t = l->nextToken();
    }
}
int main(int argc, char *argv[]) {
    Repl *r = new Repl(std::cin, std::cout);

    return 0;
}
