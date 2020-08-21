#include "recursiveParser.h"

#include <iostream>

auto comperror = [](std::string &filename, Token *loc, std::string warn) {
    std::cout << filename << ":l" << loc->line << ":" << loc->position
        << " " << warn << std::endl;
};

void RecursiveParser::nextToken() {
    current = &allTokens[nextPosition];
    nextPosition++;

    if(nextPosition > allTokens.size()) {
        std::cout << "reached end of file." << std::endl;
        current = nullptr;
    }
}

bool RecursiveParser::acceptTkn(const TokenType &t) {
    if(current == nullptr) return false;
    if(current->type == t) {
        nextToken();
        return true;
    }
    return false;
}
bool RecursiveParser::acceptCtx(const RuleContext &c) {
    if(current == nullptr) return false;
    return c.match(*this);
}

bool RecursiveParser::expectTkn(const TokenType &t) {
    if(acceptTkn(t)) return true;

    auto msg = "Unexpected token: got '" + tokenTypeToString(current->type)
        + "', expected '" + tokenTypeToString(t) + "'"; 
    comperror(filename, current, msg);
    return 0;
}
bool RecursiveParser::expectCtx(const RuleContext &c) {
    if(acceptCtx(c)) return true;
    std::cout << "expect: unexpected context at " << current->line 
        << " '" << c.getRuleName() << "'" << std::endl;

    auto msg = "Unexpected context: '" + c.getRuleName() + "'"; 
    comperror(filename, current, msg);
    return 0;
}

AST RecursiveParser::parse() {
    // load the first token
    nextToken();

    acceptCtx(ProgramContext());
};

// Handle contexts here as well

// Contexts
bool ProgramContext::match(RecursiveParser &p) const {
    while(p.acceptCtx(FunctionContext())){}
    std::cout << "parsed context: " << getRuleName() << std::endl;
    return true;
}

bool FunctionContext::match(RecursiveParser &p) const {
    if(p.expectTkn(t_new)) {
        p.expectTkn(t_identifier);
        p.expectTkn(t_lparen);
        p.acceptCtx(ArgsContext());
        p.expectTkn(t_rparen);
        p.expectCtx(CompoundContext());
        std::cout << "parsed context: " << getRuleName() << std::endl;
        return true;
    }
    return false;
}

bool ArgsContext::match(RecursiveParser &p) const {
    if(p.acceptTkn(t_identifier)) {
       while(p.acceptTkn(t_comma)) {
           p.expectTkn(t_identifier);
       }
       std::cout << "parsed context: " << getRuleName() << std::endl;
       return true;
    }
    return false;
}

bool CompoundContext::match(RecursiveParser &p) const {
    if(p.acceptTkn(t_lcurly)) {
        while(p.acceptCtx(StatementContext())) {}
        p.expectTkn(t_rcurly);
        std::cout << "parsed context: " << getRuleName() << std::endl;
        return true;
    } else if(p.acceptCtx(StatementContext())) {
        std::cout << "parsed context: " << getRuleName() << std::endl;
        return true;
    }
    return false;
}

bool StatementContext::match(RecursiveParser &p) const {
    if(p.acceptTkn(t_if)) {
        // If sats
        p.expectTkn(t_lparen);
        p.expectCtx(ExpressionContext());
        p.expectTkn(t_rparen);
        p.expectCtx(CompoundContext());
        std::cout << "parsed context: " << getRuleName() << std::endl;
        return true;
    } else if(p.acceptTkn(t_new)) {
        p.expectCtx(VarassignContext());
        p.expectTkn(t_scolon);
        std::cout << "parsed context: " << getRuleName() << std::endl;
        return true;
    }
    return false;
}

bool VarassignContext::match(RecursiveParser &p) const {
    if(p.acceptTkn(t_identifier)) {
        if(p.expectTkn(t_ass)) {
            p.expectCtx(ExpressionContext());
        }
        std::cout << "parsed context: " << getRuleName() << std::endl;
        return true;
    }
    return false;
}

bool ExpressionContext::match(RecursiveParser &p) const {
    if(p.acceptTkn(t_int_literal)) {            // int literal
        std::cout << "parsed context: " << getRuleName() << std::endl;
        return true;
    } else if(p.acceptTkn(t_str_literal)) {     // str literal
        std::cout << "parsed context: " << getRuleName() << std::endl;
        return true;
    }

    else if(p.acceptTkn(t_amp)) {               // ref
        p.expectCtx(ExpressionContext());
        std::cout << "parsed context: " << getRuleName() << std::endl;
        return true;
    } else if(p.acceptTkn(t_ast)) {             // de-ref
        p.expectCtx(ExpressionContext());
        std::cout << "parsed context: " << getRuleName() << std::endl;
        return true;
    } else if(p.acceptTkn(t_minus)) {           // invert
        p.expectCtx(ExpressionContext());
        std::cout << "parsed context: " << getRuleName() << std::endl;
        return true;
    } else if(p.acceptTkn(t_not)) {             //  logical invert
        p.expectCtx(ExpressionContext());
        std::cout << "parsed context: " << getRuleName() << std::endl;
        return true;
    } else if(p.acceptTkn(t_inc)) {             // increment
        p.expectCtx(ExpressionContext());
        std::cout << "parsed context: " << getRuleName() << std::endl;
        return true;
    } else if(p.acceptTkn(t_dec)) {             // decrement
        p.expectCtx(ExpressionContext());
        std::cout << "parsed context: " << getRuleName() << std::endl;
        return true;
    }

    else if(p.acceptTkn(t_identifier)) {      // identifier
        std::cout << "parsed context: " << getRuleName() << std::endl;
        return true;
    }

    else if(p.acceptCtx(ExpressionContext())) {
        if(p.acceptTkn(t_lbracket)) {           // array indexing
            p.expectCtx(ExpressionContext());
            p.expectTkn(t_rbracket);
            std::cout << "parsed context: " << getRuleName() << std::endl;
            return true;
        } else if(p.acceptTkn(t_lparen)) {      // func call
            p.acceptCtx(ExpargsContext());
            p.expectTkn(t_rparen);
            std::cout << "parsed context: " << getRuleName() << std::endl;
            return true;
        } else if(p.acceptTkn(t_ass)) {         // assignment
            p.expectCtx(ExpressionContext());
            std::cout << "parsed context: " << getRuleName() << std::endl;
            return true;
        }

        else if(p.acceptTkn(t_plus)) {          // addition
            p.expectCtx(ExpressionContext());
            std::cout << "parsed context: " << getRuleName() << std::endl;
            return true;
        } else if(p.acceptTkn(t_minus)) {       // subtraction
            p.expectCtx(ExpressionContext());
            std::cout << "parsed context: " << getRuleName() << std::endl;
            return true;
        } else if(p.acceptTkn(t_ast)) {        // multiplication
            p.expectCtx(ExpressionContext());
            std::cout << "parsed context: " << getRuleName() << std::endl;
            return true;
        }
    }

    return false;
}

bool ExpargsContext::match(RecursiveParser &p) const {
    if(p.acceptCtx(ExpressionContext())) {
        while(p.acceptTkn(t_comma)) {
            p.acceptCtx(ExpressionContext());
        }
        std::cout << "parsed context: " << getRuleName() << std::endl;
        return true;
    }
    return false;
}