#pragma once

#include <string>
#include <utility>
#include <optional>

namespace xorLang {
    enum class TokenType {
        // File
        NEWLINE, SPACE, TAB, EOI, COMMENT,

        // Symbols [D_ = Double, T_ = Triple]
        D_L_PAREN, L_PAREN, D_R_PAREN, R_PAREN, D_L_BRACE, L_BRACE, D_R_BRACE,
        R_BRACE, SEMICOLON, RETURN_ARROW, D_L_ANGLE, L_ANGLE, D_R_ANGLE, R_ANGLE,
        D_L_BRACKET, L_BRACKET, D_R_BRACKET, R_BRACKET, COMMA, T_DOT, DOT, D_COLON,
        COLON, HASH, AT,

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
                }
            }

            //TODO: Unknown tokenS
        }

        bool hasNext() {
            return input.length() != 0;
        }
    };
}
