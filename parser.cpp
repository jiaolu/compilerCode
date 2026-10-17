#include "token.h"
#include "parser.h"

extern const char* TokenTypeStrings[];

void expect(TokenType expected, unsigned& index, const std::vector<TokenType>& tokens) {
    if (index >= tokens.size() || tokens[index] != expected) {
        std::cerr << "Error: Expected token " << TokenTypeStrings[static_cast<unsigned>(expected)] << " at index " << index << std::endl;
        exit(1);
    }
    ++index; // Move to the next token
}

std::unique_ptr<Expression> parse_expression(unsigned depth, unsigned& index, const std::vector<TokenType>& tokens, const std::map<unsigned, std::string>& identifierMap) {
    // Placeholder for parsing an expression
    // For now, just return a nullptr to indicate that this is not implemented
    expect(TokenType::Constant, index, tokens); // Expecting a constant
    auto exprNode = std::make_unique<ConstantExp>(identifierMap.at(index - 1).c_str(), depth);
    return exprNode;
}

std::unique_ptr<Statement> parse_statement(unsigned depth, unsigned& index, const std::vector<TokenType>& tokens, const std::map<unsigned, std::string>& identifierMap) {
    // Placeholder for parsing a statement
    // For now, just return a nullptr to indicate that this is not implemented

    expect(TokenType::Return, index, tokens); // Expecting 'return' keyword
    auto exp = parse_expression(depth + 1, index, tokens, identifierMap); // Placeholder for parsing an expression
    expect(TokenType::SEMICOLON, index, tokens); // Expecting ';'
    auto funcNode = std::make_unique<ReturnStm>(depth);
    funcNode->addChild(std::move(exp));
    return funcNode;
}

std::unique_ptr<ASTNode> parse_function(unsigned depth,unsigned& index, const std::vector<TokenType>& tokens, const std::map<unsigned, std::string>& identifierMap) {
    auto funcNode = std::make_unique<FuncNode>(depth);
    expect(TokenType::Int, index, tokens); // Expecting 'int' keyword
    expect(TokenType::Identifier, index, tokens); // Expecting function name (identifier)
    funcNode->setFuncName(identifierMap.at(index - 1).c_str()); // Set the function name from the identifier map
    expect(TokenType::OpenParenthesis, index, tokens); // Expecting '('
    expect(TokenType::Void, index, tokens); // Expecting 'void' keyword
    expect(TokenType::CloseParenthesis, index, tokens); // Expecting ')'
    expect(TokenType::OpenBrace, index, tokens); // Expecting '{'
    auto statement = parse_statement(depth + 1, index, tokens, identifierMap); // Parse the function body (statements)
    funcNode->addChild(std::move(statement));
    expect(TokenType::CloseBrace, index, tokens); // Expecting '}'
    return funcNode;
}

std::unique_ptr<ASTNode> parse_program(const std::vector<TokenType>& tokens, const std::map<unsigned, std::string>& identifierMap) {
    // Placeholder for parsing logic
    // This function should implement the parsing of the token stream into an AST
    // For now, it just prints a message indicating that parsing is not implemented
    unsigned index = 0;
    auto progNode = std::make_unique<ProgNode>(0);

    while (index < tokens.size()) {
        std::unique_ptr<ASTNode> funcNode = parse_function(progNode->getDepth() + 1, index, tokens, identifierMap); // Placeholder for parsing a function declaration
        if (funcNode) {
            progNode->addChild(std::move(funcNode));
        } else {
            std::cerr << "Error: Unexpected token " << TokenTypeStrings[static_cast<unsigned>(tokens[index])] << " at index " << index << std::endl;
            exit(1);
        }
    }
    return progNode;
}






