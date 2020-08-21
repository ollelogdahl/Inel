#include "lexer.h"

#include <iostream>
#include <fstream>
#include <map>

#include <regex>

const std::vector<std::pair<std::string, TokenType>> tokenRules {
        // Keywords
        {R"(if)",                       t_if},
        {R"(while)",                    t_while},
        {R"(return)",                   t_return},
        {R"(new)",                      t_new},
        // Literals and identifiers
        {R"(-?[0-9]+)",                 t_int_literal},
        {R"(".*")",                     t_str_literal},
        {R"([a-zA-Z_][a-zA-Z0-9_]*)",    t_identifier},
        
        // Parenthesis
        {R"(\()", t_lparen},
        {R"(\))", t_rparen},
        {R"(\[)", t_lbracket},
        {R"(])", t_rbracket},
        {R"(\{)", t_lcurly},
        {R"(})", t_rcurly},
        
        {R"(,)", t_comma},
        {R"(;)", t_scolon},
        
        // Modifiers
        {R"(\+=)",     t_peq},
        {R"(-=)",     t_meq},
        {R"(\+\+)",    t_inc},
        {R"(--)",    t_dec},

        // Logical operators
        {R"(!)",      t_not},
        {R"(&&)",    t_and},
        {R"(\|\|)",    t_or},
        {R"(==)",      t_eq},
        {R"(!=)",     t_neq},
        
        // Operators and assignment
        {R"(=)",        t_ass},
        {R"(\+)",       t_plus},
        {R"(-)",        t_minus},
        {R"(\*)",       t_ast},
        {R"(&)",        t_amp}
};

std::vector<Token> Lexer::tokenize(const std::string &text) {

    // Merge all expressions into one
    std::string expression;
    for(auto const &rule : tokenRules)
        expression += "(" + rule.first + ")|";
    // remove the last | character
    expression.pop_back();

    // token vector
    std::vector<Token> tokens;

    // create regex engine
    std::regex regex(expression, std::regex::extended);

    auto wordsBegin = std::sregex_iterator(text.begin(), text.end(), regex);
    auto wordsEnd = std::sregex_iterator();

    for(auto it= wordsBegin; it != wordsEnd; ++it) {
        unsigned index = 0;

        for(; index < it->size(); ++index) {
            if(!it->str(index + 1).empty())
                break;
        }

        Token token = Token(tokenRules[index].second, it->str(), rand()%100, 0);
        //std::cout << token.toString() << std::endl;
        tokens.push_back(token);
    }
    return tokens;
}