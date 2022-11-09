#include "lexer/lexer.h"
#include <iostream>

int main() {
    using namespace xorLang;

    Lexer lexer("fn main() -> int {\n    return 0;\n};");

    while (lexer.hasNext()) {
        auto token = lexer.next();
        std::cout << token.value << std::endl;
    }

    std::cout << "\nFinished lexxing\n";
    return 0;
}
