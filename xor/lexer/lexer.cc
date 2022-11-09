#include "lexer.h"

namespace xorLang {
    Lexer::Lexer(const std::string &input): input(input) {}

    Token Lexer::next() {

    }

    bool Lexer::hasNext() {
        return input.length() != 0;
    }
}
