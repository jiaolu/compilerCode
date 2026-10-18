#ifndef LEX_H
#define LEX_H
#include "token.h"
unsigned lex(const std::string &input, std::vector<TokenType> &tokens,
             std::map<unsigned, std::string> &identifierMap);
void lex_print(const std::vector<TokenType> &tokens,
               const std::map<unsigned, std::string> &identifierMap);
#endif
