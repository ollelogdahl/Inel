#pragma once

#include <vector>

#include "token.h"
#include "context.h"
#include "ast.h"

class RecursiveParser {
private:
    // Pointer to the current token
    Token *current;
    int nextPosition = 0;

    std::string filename;
    std::vector<Token> allTokens;
public:    
    // Reads next token in the vector, and assigning current to it.
    void nextToken();

    // Tries to pair the given tokentype, and consumes if successful
    bool acceptTkn(const TokenType &t);
    // Same as accept, but throws a parser error if not successful
    bool expectTkn(const TokenType &t);

    // Tries to pair the given context, and consumes all tokens in context if sucessful
    bool acceptCtx(const RuleContext &c);
    // Same as accept, but throws a parser error if not successful
    bool expectCtx(const RuleContext &c);

    RecursiveParser(const std::string &f, const std::vector<Token> &tokens) 
        : filename(f), allTokens(tokens) {};

    AST parse();
};