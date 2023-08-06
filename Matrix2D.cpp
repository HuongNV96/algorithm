#include "Matrix2D.hpp"

ostream & operator << (ostream &out, const Node &node) {
    out << "{" << node.mRow << ", " <<  node.mColumn << "}";
    return out;
}

