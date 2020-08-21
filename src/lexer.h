#pragma once

#include <string>
#include <vector>

#include "token.h"

class Lexer {
public:
    std::vector<Token> tokenize(const std::string &data);
};