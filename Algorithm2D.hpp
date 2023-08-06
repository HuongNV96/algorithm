#pragma once

#include "Matrix2D.hpp"

/*****************************Example******************************************************/
/* Matrix
1 -1 1 1
-1 1 1 1
-1 1 1 1
1 1 -1 1

Explain : 
* -1 will can not move, other is ok
* path is line between 2 nodes follow vertical or horizontal direction
* we need find shortest path form src to des
*/

template <typename T> std::vector<Node> findBestPathFromSrcToDesWithBfs(Matrix2D<T> & matrix, Node src, Node des) {
    if (matrix.rowCount() == 0 || matrix.columnCount() == 0) {
        return std::vector<Node>();
    }

    if ((matrix.value(src) == static_cast<T>(-1)) || (matrix.value(des) == static_cast<T>(-1))) {
        return std::vector<Node>();
    }

    std::vector<Node> visited;

    {
        auto currentPath = src.path();
        currentPath.push_back(src);
        src.updatePath(currentPath);
    }

    std::queue<Node> stack;
    stack.push(src);

    size_t minPath = -1;
    std::vector<Node> bestPath;

    const std::vector<std::vector<long>> nextNodes = {{-1L, 0L}, {1L, 0L}, {0L, -1L}, {0L ,1L}};

    while (!stack.empty()) {
        Node node = stack.front();        
        stack.pop();

        visited.push_back(node);
        auto row = node.row();
        auto col = node.column();
        if (node == des) {
            auto path = node.path();
            if (minPath == -1 || minPath > path.size()) {
                bestPath = path;
                minPath = path.size();
            }
        }

        for (auto & nextNode : nextNodes) {
            if ((row + nextNode[0] >= 0) && (col + nextNode[1] >= 0) && ((row + nextNode[0] < matrix.rowCount()) && (col + nextNode[1] < matrix.columnCount()))) {
                if (matrix.value(Node(row + nextNode[0], col + nextNode[1])) != -1) {
                    if (std::find(visited.begin(), visited.end(), Node(row + nextNode[0], col + nextNode[1])) == visited.end()) {
                        Node next(row + nextNode[0], col + nextNode[1]);
                        auto currentPath = node.path();
                        currentPath.push_back(next);
                        next.updatePath(currentPath);

                        stack.push(next);    
                        visited.push_back(node);    
                    }
                }
            }
        }
    }

    return bestPath;
}

template <typename T> void findBestPathFromSrcToDesWithDfsRecurse(Matrix2D<T> & matrix, Node src, Node des, std::vector<Node> & visited, std::vector<Node> &bestPath, size_t & minPath) {
    auto row = src.row();
    auto col = src.column();
    if (src == des) {
        auto path = src.path();
        if (minPath == -1 || minPath > path.size()) {
            bestPath = path;
            minPath = path.size();
        }
    }

    const std::vector<std::vector<long>> nextNodes = {{-1L, 0L}, {1L, 0L}, {0L, -1L}, {0L ,1L}};

    for (auto & nextNode : nextNodes) {
        if ((row + nextNode[0] >= 0) && (col + nextNode[1] >= 0) && ((row + nextNode[0] < matrix.rowCount()) && (col + nextNode[1] < matrix.columnCount()))) {
            if (matrix.value(Node(row + nextNode[0], col + nextNode[1])) != -1) {
                if (std::find(visited.begin(), visited.end(), Node(row + nextNode[0], col + nextNode[1])) == visited.end()) {
                    Node next(row + nextNode[0], col + nextNode[1]);
                    auto currentPath = src.path();
                    currentPath.push_back(next);
                    next.updatePath(currentPath);

                    visited.push_back(src);    
                    findBestPathFromSrcToDesWithDfsRecurse(matrix, next, des, visited, bestPath, minPath);
                }
            }
        }
    }
}

template <typename T> std::vector<Node> findBestPathFromSrcToDesWithDfs(Matrix2D<T> & matrix, Node src, Node des) {
    if (matrix.rowCount() == 0 || matrix.columnCount() == 0) {
        return std::vector<Node>();
    }

    if ((matrix.value(src) == static_cast<T>(-1)) || (matrix.value(des) == static_cast<T>(-1))) {
        return std::vector<Node>();
    }

    auto currentPath = src.path();
    currentPath.push_back(src);
    src.updatePath(currentPath);

    size_t minPath = -1;
    std::vector<Node> bestPath;
    std::vector<Node> visited;

    findBestPathFromSrcToDesWithDfsRecurse(matrix, src, des, visited, bestPath, minPath);
    return bestPath;
}
