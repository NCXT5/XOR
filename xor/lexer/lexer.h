#pragma once

#include <string>
#include <utility>
#include <optional>

namespace xorLang {
    enum class TokenType {
        // File
        NEWLINE, SPACE, TAB, EOI, COMMENT,

        // Symbols
        L_PAREN, R_PAREN, L_BRACE, R_BRACE, SEMICOLON, RETURN_ARROW,
        L_ANGLE, R_ANGLE, L_BRACKET, R_BRACKET, COMMA, DOT, COLON, DOLLAR,
        HASH, AT, AMPERSAND, PIPE, DOUBLE_PIPE, DOUBLE_AMPERSAND, EQUALS,
        DOUBLE_EQUALS, NOT_EQUALS, PLUS, MINUS, STAR, SLASH, PERCENT, CARET,
        STAR_EQUALS, SLASH_EQUALS, PERCENT_EQUALS, PLUS_EQUALS, MINUS_EQUALS,
        CARET_EQUALS, DOUBLE_PLUS, DOUBLE_MINUS, DOUBLE_LESS_THAN, NOT, TILDE,
        DOUBLE_GREATER_THAN, DOUBLE_GREATER_THAN_EQUALS, DOUBLE_LESS_THAN_EQUALS,
        DOUBLE_GREATER_THAN_GREATER_THAN, DOUBLE_LESS_THAN_LESS_THAN, QUESTION_MARK,
        LEFT_SHIFT, RIGHT_SHIFT,

        // Reserved keywords [UN = Unsafe]
        FN, RETURN, CLASS, IF, ELSE, WHILE, FOR, IN, BREAK, CONTINUE, IMPORT, AS,
        FROM, NULL_KW, SELF, SUPER, STATIC, CONST, MUT, ENUM, STRUCT,
        UNION, TYPE, PUBLIC, PRIVATE, PROTECTED, EXTENDS, IMPLEMENTS, INSTANCE_OF,
        UNSAFE, UN_DELETE, UN_CXX, UN_C, UN_ASM, UN_EXPOSE,

        // Reserved data types [UN = Unsafe]
        INT_8BIT, INT_16BIT, INT_32BIT, INT_64BIT, INT_128BIT,
        UINT_8BIT, UINT_16BIT, UINT_32BIT, UINT_64BIT, UINT_128BIT,
        FLOAT_32BIT, FLOAT_64BIT, BOOL, CHAR, VOID, UN_VOID

        // Literals
        IDENTIFIER, DECIMAL_NUMBER, NUMBER, STRING, CHAR_LIT, TRUE, FALSE, NULL_LIT
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

    public:
        explicit Lexer(std::string input): input(std::move(input)) {}

        std::optional<Token> next() {
            if (input.length() == 0)
                return Token{
                        TokenType::EOI,
                        "EOI",
                        line,
                        column,
                        index
                };

            if (input[0] == '\n') {
                line++;
                column = 0;

                input.erase(0, 1);
                index++;

                return Token{
                        .type = TokenType::NEWLINE,
                        .value = "\n",
                        .line = line,
                        .column = column,
                        .index = index
                };
            } else if (input[0] == ' ') {
                column++;

                input.erase(0, 1);
                index++;

                return Token{
                        .type = TokenType::SPACE,
                        .value = " ",
                        .line = line,
                        .column = column,
                        .index = index
                };
            } else if (input[0] == '\t') {
                column += 4;

                input.erase(0, 1);
                index++;

                return Token{
                        .type = TokenType::TAB,
                        .value = "\t",
                        .line = line,
                        .column = column,
                        .index = index
                };
            } else if (input[0] == '/') {
                if (input[1] == '/') {
                    input.erase(0, 2);
                    index += 2;

                    std::string comment = "//";

                    while (input[0] != '\n') {
                        comment += input[0];
                        input.erase(0, 1);
                        index++;
                    }

                    return Token{
                            .type = TokenType::COMMENT,
                            .value = comment,
                            .line = line,
                            .column = column,
                            .index = index
                    };
                } else if (input[1] == '*') {
                    input.erase(0, 2);
                    index += 2;

                    std::string comment = "/*";

                    while (input[0] != '*' && input[1] != '/') {
                        comment += input[0];
                        input.erase(0, 1);
                        index++;
                    }

                    comment += "*/";

                    input.erase(0, 2);
                    index += 2;

                    return Token{
                            .type = TokenType::COMMENT,
                            .value = comment,
                            .line = line,
                            .column = column,
                            .index = index
                    };
                }
            } else if (input[0] == '(') {
                column++;

                input.erase(0, 1);
                index++;

                return Token{
                        .type = TokenType::L_PAREN,
                        .value = "(",
                        .line = line,
                        .column = column,
                        .index = index
                };
            } else if (input[0] == ')') {
                column++;

                input.erase(0, 1);
                index++;

                return Token{
                        .type = TokenType::R_PAREN,
                        .value = ")",
                        .line = line,
                        .column = column,
                        .index = index
                };
            } else if (input[0] == '{') {
                column++;

                input.erase(0, 1);
                index++;

                return Token{
                        .type = TokenType::L_BRACE,
                        .value = "{",
                        .line = line,
                        .column = column,
                        .index = index
                };
            } else if (input[0] == '}') {
                column++;

                input.erase(0, 1);
                index++;

                return Token{
                        .type = TokenType::R_BRACE,
                        .value = "}",
                        .line = line,
                        .column = column,
                        .index = index
                };
            } else if (input[0] == ';') {
                column++;

                input.erase(0, 1);
                index++;

                return Token{
                        .type = TokenType::SEMICOLON,
                        .value = ";",
                        .line = line,
                        .column = column,
                        .index = index
                };
            } else if (input[0] == '-') {
                if (input[1] == '>') {
                    column += 2;

                    input.erase(0, 2);
                    index += 2;

                    return Token{
                            .type = TokenType::RETURN_ARROW,
                            .value = "->",
                            .line = line,
                            .column = column,
                            .index = index
                    };
                } else {
                    column++;

                    input.erase(0, 1);
                    index++;

                    return Token{
                            .type = TokenType::MINUS,
                            .value = "-",
                            .line = line,
                            .column = column,
                            .index = index
                    };
                }
            } else if (input[0] == '<') {
                if (input[1] == '<') {
                    column += 2;

                    input.erase(0, 2);
                    index += 2;

                    return Token{
                            .type = TokenType::LEFT_SHIFT,
                            .value = "<<",
                            .line = line,
                            .column = column,
                            .index = index
                    };
                } else {
                    column++;

                    input.erase(0, 1);
                    index++;

                    return Token{
                            .type = TokenType::L_ANGLE,
                            .value = "<",
                            .line = line,
                            .column = column,
                            .index = index
                    };
                }
            } else if (input[0] == '>') {
                if (input[1] == '>') {
                    column += 2;

                    input.erase(0, 2);
                    index += 2;

                    return Token{
                            .type = TokenType::RIGHT_SHIFT,
                            .value = ">>",
                            .line = line,
                            .column = column,
                            .index = index
                    };
                } else {
                    column++;

                    input.erase(0, 1);
                    index++;

                    return Token{
                            .type = TokenType::R_ANGLE,
                            .value = ">",
                            .line = line,
                            .column = column,
                            .index = index
                    };
                }
            } else if (input[0] == '=') {
                if (input[1] == '=') {
                    column += 2;

                    input.erase(0, 2);
                    index += 2;

                    return Token{
                            .type = TokenType::EQUALS,
                            .value = "==",
                            .line = line,
                            .column = column,
                            .index = index
                    };
                } else {
                    column++;

                    input.erase(0, 1);
                    index++;

                    return Token{
                            .type = TokenType::EQUALS,
                            .value = "=",
                            .line = line,
                            .column = column,
                            .index = index
                    };
                }
            } else if (input[0] == '!') {
                if (input[1] == '=') {
                    column += 2;

                    input.erase(0, 2);
                    index += 2;

                    return Token{
                            .type = TokenType::NOT_EQUALS,
                            .value = "!=",
                            .line = line,
                            .column = column,
                            .index = index
                    };
                } else {
                    column++;

                    input.erase(0, 1);
                    index++;

                    return Token{
                            .type = TokenType::NOT,
                            .value = "!",
                            .line = line,
                            .column = column,
                            .index = index
                    };
                }
            } else if (input[0] == '+') {
                column++;

                input.erase(0, 1);
                index++;

                return Token{
                        .type = TokenType::PLUS,
                        .value = "+",
                        .line = line,
                        .column = column,
                        .index = index
                };
            } else if (input[0] == '*') {
                column++;

                input.erase(0, 1);
                index++;

                return Token{
                        .type = TokenType::STAR,
                        .value = "*",
                        .line = line,
                        .column = column,
                        .index = index
                };
            } else if (input[0] == '/') {
                column++;

                input.erase(0, 1);
                index++;

                return Token{
                        .type = TokenType::SLASH,
                        .value = "/",
                        .line = line,
                        .column = column,
                        .index = index
                };
            } else if (input[0] == '%') {
                column++;

                input.erase(0, 1);
                index++;

                return Token{
                        .type = TokenType::PERCENT,
                        .value = "%",
                        .line = line,
                        .column = column,
                        .index = index
                };
            } else if (input[0] == ',') {
                column++;

                input.erase(0, 1);
                index++;

                return Token{
                        .type = TokenType::COMMA,
                        .value = ",",
                        .line = line,
                        .column = column,
                        .index = index
                };
            } else if (input[0] == '.') {
                column++;

                input.erase(0, 1);
                index++;

                return Token{
                        .type = TokenType::DOT,
                        .value = ".",
                        .line = line,
                        .column = column,
                        .index = index
                };
            } else if (input[0] == ':') {
                column++;

                input.erase(0, 1);
                index++;

                return Token{
                        .type = TokenType::COLON,
                        .value = ":",
                        .line = line,
                        .column = column,
                        .index = index
                };
            } else if (input[0] == '&') {
                if (input[1] == '&') {
                    column += 2;

                    input.erase(0, 2);
                    index += 2;

                    return Token{
                            .type = TokenType::DOUBLE_AMPERSAND,
                            .value = "&&",
                            .line = line,
                            .column = column,
                            .index = index
                    };
                } else {
                    column++;

                    input.erase(0, 1);
                    index++;

                    return Token{
                            .type = TokenType::AMPERSAND,
                            .value = "&",
                            .line = line,
                            .column = column,
                            .index = index
                    };
                }
            } else if (input[0] == '|') {
                if (input[1] == '|') {
                    column += 2;

                    input.erase(0, 2);
                    index += 2;

                    return Token{
                            .type = TokenType::DOUBLE_PIPE,
                            .value = "||",
                            .line = line,
                            .column = column,
                            .index = index
                    };
                } else {
                    column++;

                    input.erase(0, 1);
                    index++;

                    return Token{
                            .type = TokenType::PIPE,
                            .value = "|",
                            .line = line,
                            .column = column,
                            .index = index
                    };
                }
            } else if (input[0] == '^') {
                column++;

                input.erase(0, 1);
                index++;

                return Token{
                        .type = TokenType::CARET,
                        .value = "^",
                        .line = line,
                        .column = column,
                        .index = index
                };
            } else if (input[0] == '~') {
                column++;

                input.erase(0, 1);
                index++;

                return Token{
                        .type = TokenType::TILDE,
                        .value = "~",
                        .line = line,
                        .column = column,
                        .index = index
                };
            } else if (input[0] == '?') {
                column++;

                input.erase(0, 1);
                index++;

                return Token{
                        .type = TokenType::QUESTION_MARK,
                        .value = "?",
                        .line = line,
                        .column = column,
                        .index = index
                };
            } else if (input[0] == ';') {
                column++;

                input.erase(0, 1);
                index++;

                return Token{
                        .type = TokenType::SEMICOLON,
                        .value = ";",
                        .line = line,
                        .column = column,
                        .index = index
                };
            } else if (input[0] == '(') {
                column++;

                input.erase(0, 1);
                index++;

                return Token{
                        .type = TokenType::L_PAREN,
                        .value = "(",
                        .line = line,
                        .column = column,
                        .index = index
                };
            } else if (input[0] == ')') {
                column++;

                input.erase(0, 1);
                index++;
            }

            //TODO: Unknown tokenS
        }

        bool hasNext() {
            return input.length() != 0;
        }
    };
}
