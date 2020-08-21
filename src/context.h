#pragma once

#include <string>

// Forward-declaration
class RecursiveParser;

class RuleContext {
protected:
    std::string ruleName;
public:
    virtual bool match(RecursiveParser &p) const = 0;

    std::string getRuleName() const { return ruleName; }

    RuleContext(std::string s) : ruleName(s) {};
};


// Language implementation

// Program
class ProgramContext : public RuleContext {
public:
    ProgramContext() : RuleContext("program") {};

    bool match(RecursiveParser &p) const override;
};

// Function definition
class FunctionContext : public RuleContext {
public:
    FunctionContext() : RuleContext("funcdef") {};

    bool match(RecursiveParser &p) const override;
};

// Function definition parameters
class ArgsContext : public RuleContext {
public:
    ArgsContext() : RuleContext("funcdef arguments") {};

    bool match(RecursiveParser &p) const override;
};

// Compound statement
class CompoundContext : public RuleContext {
public:
    CompoundContext() : RuleContext("compound statement") {};

    bool match(RecursiveParser &p) const override;
};

// Statement
class StatementContext : public RuleContext {
public:
    StatementContext() : RuleContext("statement") {};

    bool match(RecursiveParser &p) const override;
};

// Variable assignment
class VarassignContext : public RuleContext {
public:
    VarassignContext() : RuleContext("variable assignment") {};

    bool match(RecursiveParser &p) const override;
};

// Expression
class ExpressionContext : public RuleContext {
public:
    ExpressionContext() : RuleContext("expression") {};

    bool match(RecursiveParser &p) const override;
};

// Function call arguments
class ExpargsContext : public RuleContext {
public:
    ExpargsContext() : RuleContext("funccall arguments") {};

    bool match(RecursiveParser &p) const override;
};