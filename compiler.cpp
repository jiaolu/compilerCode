#include <fstream>
#include <sstream>
#include <iostream>
#include <regex>
#include <cstdlib>
#include "token.h"
#include "lex.h"
#include "parser.h"
#include "codegen.h"
using namespace std;

extern const char *TokenTypeStrings[];

int main(int argc, char *argv[])
{
    if (argc == 2)
    {
        const std::string inputFilename = argv[1];
        std::ifstream inputFile(inputFilename);
        auto fileExtension = inputFilename.rfind('.', inputFilename.length() - 1);
        auto fileNameWithoutExtension = inputFilename.substr(0, fileExtension);
        std::string outputFilename = fileNameWithoutExtension + ".s";
        //
        std::stringstream buffer;
        buffer << inputFile.rdbuf();
        std::string content = buffer.str();
        std::vector<TokenType> tokens;
        std::map<unsigned, std::string> identifierMap;
        unsigned result = lex(content, tokens, identifierMap);
        if (result != 0)
        {
            return result;
        }
        // lex_print(tokens, identifierMap);
        std::unique_ptr<ASTNode> astRoot = parse_program(tokens, identifierMap);
        ASTNode *astRootPtr = astRoot.get();
        auto asmProgram = convertProg(astRootPtr);

        ofstream outputFile(outputFilename, ios::out | ios::trunc);
        codegen(asmProgram.get(), outputFile);

        outputFile.close();

        const std::string exeFilename = fileNameWithoutExtension;
        const std::string gccCommand = "gcc " + outputFilename + " -o " + exeFilename;
        const int gccResult = std::system(gccCommand.c_str());
        if (gccResult != 0)
        {
            std::cerr << "Error: gcc failed to assemble/compile " << outputFilename << std::endl;
            return 1;
        }
    }
    else if(argc == 3)
    {
        const std::string command = argv[1];
        const std::string inputFilename = argv[2];

        std::ifstream inputFile(inputFilename);
        if (!inputFile.is_open())
        {
            std::cerr << "Error opening file: " << inputFilename << std::endl;
            return 1;
        }

        std::stringstream buffer;
        buffer << inputFile.rdbuf();
        std::string content = buffer.str();
        std::vector<TokenType> tokens;
        std::map<unsigned, std::string> identifierMap;
        if (command == std::string("--lex"))
        {
            unsigned result = lex(content, tokens, identifierMap);
            if (result != 0)
            {
                return result;
            }
            lex_print(tokens, identifierMap);
        }
        else if (command == std::string("--parse"))
        {
            unsigned result = lex(content, tokens, identifierMap);
            if (result != 0)
            {
                return result;
            }
            lex_print(tokens, identifierMap);
            std::unique_ptr<ASTNode> astRoot = parse_program(tokens, identifierMap);
            if (astRoot)
            {
                astRoot->Print();
            }
            else
            {
                std::cerr << "Error: Failed to parse the program." << std::endl;
                return 1;
            }
        }
        else if (command == std::string("--codegen"))
        {
            unsigned result = lex(content, tokens, identifierMap);
            if (result != 0)
            {
                return result;
            }
            // lex_print(tokens, identifierMap);
            std::unique_ptr<ASTNode> astRoot = parse_program(tokens, identifierMap);
            ASTNode *astRootPtr = astRoot.get();
            auto asmProgram = convertProg(astRootPtr);
            codegen(asmProgram.get(), std::cout);
        }

        inputFile.close();
        return 0;
    }
}