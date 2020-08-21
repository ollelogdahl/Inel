#pragma once

#include <string>

enum TokenType {
    t_identifier,
    t_int_literal,
    t_str_literal,
    t_if,
    t_while,
    t_return,
    t_new,
    t_lparen,
    t_rparen,
    t_lbracket,
    t_rbracket,
    t_lcurly,
    t_rcurly,
    t_comma,
    t_scolon,
    t_plus,
    t_minus,
    t_amp,
    t_ast,
    t_ass,
    t_peq,
    t_meq,
    t_inc,
    t_dec,
    t_not,
    t_and,
    t_or,
    t_eq,
    t_neq
};

std::string tokenTypeToString(TokenType t);

struct Token {
    TokenType type;
    std::string value;
    unsigned line;
    unsigned position;

    Token(TokenType t, std::string v, unsigned l, unsigned c)
        : type(t), value(v), line(l), position(c) {}

    std::string toString() const;
};