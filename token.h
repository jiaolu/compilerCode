#ifndef TOKEN_H
#define TOKEN_H
#include <regex>

enum TokenType : unsigned {
    Int = 0,
    Void ,
    Return ,
    OpenParenthesis,
    CloseParenthesis,
    OpenBrace,
    CloseBrace,
    SEMICOLON,
    Constant ,
    Identifier,
    COUNT
};

#endif