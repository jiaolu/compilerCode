#ifndef PARSER_H
#define PARSER_H
#include "ast.h"
std::unique_ptr<ASTNode> parse_program(const std::vector<TokenType>& tokens, const std::map<unsigned, std::string>& identifierMap);
#endif