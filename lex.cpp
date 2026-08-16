#include "token.h"
#include <vector>
#include <iostream>

std::regex  regexPatterns[] = {
    std::regex(R"(int\b)"),
    std::regex(R"(void\b)"),
    std::regex(R"(return\b)"),
    std::regex(R"(\()"),
    std::regex(R"(\))"),
    std::regex(R"(\{)"),
    std::regex(R"(\})"),
    std::regex(R"(;)"),
    std::regex(R"(\d+\b)"),
    std::regex(R"([a-zA-Z_]\w*\b)")
};

const char* TokenTypeStrings[] = {
    "int keyword",
    "void keyword",
    "return keyword",
    "Open Parenthesis",
    "Close Parenthesis",
    "Open Brace",
    "Close Brace",
    "Semicolon",
    "Constant",
    "Identifier",
};

static_assert(sizeof(TokenTypeStrings) / sizeof(TokenTypeStrings[0]) == static_cast<size_t>(TokenType::COUNT), "TokenTypeStrings array size does not match TokenType enum count.");

unsigned lex(const std::string& input, std::vector<TokenType>& tokens, std::map<unsigned, std::string>& identifierMap) {
    auto itr = input.begin();
    while(itr != input.end()) {
        if (*itr == ' ' || *itr == '\t' || *itr == '\n' || *itr == '\r') {
            ++itr;
            continue;
        }
        if (*itr == '/' && (itr + 1) != input.end() && *(itr + 1) == '/') {
            // Skip single-line comments
            while (itr != input.end() && *itr != '\n') {
                ++itr;
            }
            continue;
        }
        if (*itr == '/' && (itr + 1) != input.end() && *(itr + 1) == '*') {
            // Skip multi-line comments
            itr += 2; // Skip the '/*'
            while (itr != input.end() && !(*itr == '*' && (itr + 1) != input.end() && *(itr + 1) == '/')) {
                ++itr;
            }
            if (itr != input.end()) {
                itr += 2; // Skip the '*/'
            }
            continue;
        }
        unsigned i = 0;
        for (; i < static_cast<unsigned>(TokenType::COUNT); ++i) {
            std::smatch match;
            std::string remaining(itr, input.end());
            if (std::regex_search(remaining, match, regexPatterns[i]) && match.position() == 0) {
                if (static_cast<TokenType>(i) == TokenType::Identifier
                    || static_cast<TokenType>(i) == TokenType::Constant) {
                    unsigned idIndex = tokens.size();
                    identifierMap[idIndex] = match.str();
                }
                tokens.push_back(static_cast<TokenType>(i));
                itr += match.length();
                break;
            }
        }
        if (i == static_cast<unsigned>(TokenType::COUNT)) {
           std::cerr << "Unrecognized token starting at: " << std::string(itr, input.end()) << std::endl;
           return 1;
        }
    }
    return 0;
}

void lex_print(const std::vector<TokenType>& tokens, const std::map<unsigned, std::string>& identifierMap) {
    std::cout << "-------------- lex Tokens ---------------" << std::endl;
    for (unsigned i = 0; i < tokens.size(); ++i) {
        TokenType token = tokens[i];
        std::cout << TokenTypeStrings[static_cast<unsigned>(token)];
        if (token == TokenType::Identifier || token == TokenType::Constant) {
            std::cout << " (" << identifierMap.at(i) << ")";
        }
        std::cout << std::endl;
    }
}
