#pragma once

#include <vector>
#include <string>

struct AST {
    /// The parent of this node. If the return value is null, then this node
    /// is the root of the tree.
    //AST &parent;

    /// memory not managed here. This is just for the structure.
    //std::vector<AST &> children;

    /// Print out the whole tree.
    std::string toStringTree(bool pretty = false);
};
