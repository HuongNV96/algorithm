#pragma once

#include <iostream>
#include <stdint.h>
#include <stdbool.h>
#include <vector>
#include <limits>
#include <queue>
#include <memory>
#include <algorithm>
#include <deque>

using namespace std;

class Node {
private :
    size_t mRow;
    size_t mColumn;
    std::vector<Node> mPath;
public :
    explicit Node(size_t row, size_t column) {
        mRow =  row;
        mColumn = column;
    }

    inline constexpr size_t row() const {
        return mRow;
    }

    inline constexpr size_t column() const {
        return mColumn;
    }

    inline std::vector<Node> path() const {
        return mPath;
    }

    inline void updatePath(std::vector<Node> & path) {
        mPath = path;
    }


    bool operator==(const Node &node) {
        return ((mRow == node.row()) && (mColumn == node.column()));
    }

    friend ostream & operator << (ostream &out, const Node &node);
};

ostream & operator << (ostream &out, const Node &node);

template <typename T> class Matrix2D {
public :
    inline constexpr size_t rowCount() const {
        return mData.size();
    }

    inline constexpr size_t columnCount() const {
        if (mData.size() <= 0) {
            return 0;
        } 
        return mData[0].size();
    }

    inline constexpr T value(const Node node) const {
        if (!validNode(node)) {
            std::cout << "Node is invalid : " << node;
            return std::numeric_limits<T>::quiet_NaN();
        }
        return mData[node.row()][node.column()];
    }

    inline constexpr T value(const size_t row, const size_t column) const {
        return value(Node(row, column));
    }

    inline bool update(const size_t row, const size_t column) const {
        return update(Node(row, column));
    }

    inline bool update(Node node, T value) const {
        if (!validNode(node)) {
            std::cout << "Node is invalid : " << node;
            return false;
        }

        mData.a[node.row()][node.column()] = value;
        return true;
    }

    inline std::string name() const {
        return mName;
    }

    explicit Matrix2D(std::string name, size_t rowCount, size_t columnCount) : 
        mName(name),
        mRowCount(rowCount),
        mColumnCount(columnCount) {

        for (size_t r = 0; r < rowCount; r++) {
            mData.push_back(std::vector<T> (columnCount, static_cast<T>(0)));
        } 
    }

    explicit Matrix2D(std::string name, const std::vector<std::vector<T>> data) : 
        mName(name) {

        if (!(data.size() && data[0].size())) {
            std::cout << "size data is valid" << std::endl;
            return;
        }
        auto col = data[0].size();
        for (auto & row : data) {
            if (row.size() != col) {
                std::cout << "size data is valid" << std::endl;
                return;
            }
        }

        mData = data;
    }

private :
    std::string mName;
    size_t mRowCount, mColumnCount;
    std::vector<std::vector<T>> mData;
    constexpr bool validNode(const Node & node) const {
        return (node.row() >= 0 && node.column() >= 0 && node.row() < rowCount() && node.column() < columnCount());
    }
};

template <typename T> ostream & operator << (ostream &out, const Matrix2D<T> &matrix) {
    out << matrix.name() << " : " << std::endl;
    for (size_t r = 0; r < matrix.rowCount(); r++) {
        for (size_t c = 0; c < matrix.columnCount(); c++) {
            out << matrix.value(Node(r, c)) << " ";
        }
        out << std::endl;
    }
    out << std::endl;
    return out;
}
