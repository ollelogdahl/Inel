#include "process.h"

#include "lexer.h"
#include "recursiveParser.h"

#include <iostream>
#include <fstream>

void processFile(std::string filename, bool verbose) {
    // read file
    std::ifstream ifs(filename);
    std::string content(
        (std::istreambuf_iterator<char>(ifs)),
        (std::istreambuf_iterator<char>())
    );

    std::cout << "\e[33m" << filename << "\e[0m" << std::endl;
    if(verbose) {
        std::cout << "\e[2m" << content << "\e[0m" << std::endl;
        std::cout << "\e[33mend\e[0m" << std::endl;
    }

    // convert file into tokens
    auto lexer = Lexer();
    auto tokens = lexer.tokenize(content);

    std::cout << std::to_string(tokens.size()) 
        << " tokens created." << std::endl;

    // Print lexer tokens
    if(verbose) {
        std::cout << "\e[33mlex\e[0;2m" << std::endl;
        for(auto &token : tokens) 
            std::cout << token.toString() << std::endl;
        std::cout << "\e[0m";
        std::cout << "\e[33mend\e[0m" << std::endl;
    }

    // parse token vector
    auto parser = RecursiveParser(filename, tokens);
    auto ast = parser.parse();
}