#pragma once

#include <string>

namespace xorLang {
    enum class TokenType {
        // File
        NEWLINE, SPACE, TAB, EOI, COMMENT,

        // Symbols
        L_PAREN, R_PAREN, L_BRACE, R_BRACE, SEMICOLON, RETURN_ARROW,

        // Reserved keywords
        FN, RETURN,

        // Literals
        IDENTIFIER, DECIMAL, NUMBER
    };

    struct Token {
        TokenType type;
        std::string value;

        size_t line;
        size_t column;
        size_t index;
    };

    class Lexer {
        std::string input;
        size_t line = 0;
        size_t column = 0;
        size_t index = 0;

        // File
        bool isNewLine();
        bool isSpace();
        bool isTab();
        bool isEOI();
        bool isComment();

        // Symbols
        bool isLParen();
        bool isRParen();
        bool isLBrace();
        bool isRBrace();
        bool isSemicolon();
        bool isReturnArrow();

        // Reserved keywords
        bool isFn();
        bool isReturn();

        // Literals
        bool isIdentifier();
        bool isDecimal();
        bool isNumber();

    public:
        explicit Lexer(const std::string &input);

        Token next();

        bool hasNext();
    };
}
