#include "token.h"

std::string tokenTypeToString(TokenType t) {
    std::string ts;
    switch(t) {
        case t_identifier: ts = "identifier"; break;
        case t_int_literal: ts = "int literal"; break;
        case t_str_literal: ts = "str literal"; break;
        case t_if: ts = "if"; break;
        case t_while: ts = "while"; break;
        case t_return: ts = "return"; break;
        case t_new: ts = "new"; break;
        case t_lparen: ts = "("; break;
        case t_rparen: ts = ")"; break;
        case t_lbracket: ts = "["; break;
        case t_rbracket: ts = "]"; break;
        case t_lcurly: ts = "{"; break;
        case t_rcurly: ts = "}"; break;
        case t_comma: ts = ","; break;
        case t_scolon: ts = ";"; break;
        case t_plus: ts = "+"; break;
        case t_minus: ts = "-"; break;
        case t_amp: ts = "&"; break;
        case t_ast: ts = "*"; break;
        case t_ass: ts = "="; break;
        case t_peq: ts = "+="; break;
        case t_meq: ts = "-="; break;
        case t_inc: ts = "++"; break;
        case t_dec: ts = "--"; break;
        case t_not: ts = "!"; break;
        case t_and: ts = "&&"; break;
        case t_or: ts = "||"; break;
        case t_eq: ts = "=="; break;
        case t_neq: ts = "!="; break;
    }
    return ts;
};

std::string Token::toString() const {
    std::string ts = tokenTypeToString(type);

    return "line " + std::to_string(line) + ", " + std::to_string(position) + " | " + ts + ": " + value;
}