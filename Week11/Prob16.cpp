//
// Created by LINBEI on 11/20/2023.
//
#include <iostream>
#include <vector>

using namespace std;

template<typename ValueType>
class RedBlackTree {
public: // constructors, destructors
    RedBlackTree();

    RedBlackTree(const RedBlackTree &srcTree);

    ~RedBlackTree();

public: // methods
    void insert(const ValueType &val);

    void remove(const ValueType &val);

    void exists(const ValueType &val) const;

    size_t size() const;

    std::vector<ValueType> inOrder() const;

    std::vector<ValueType> levelOrder() const;
};

template<typename T>
void sortByBST(vector<T> &arr) {
    RedBlackTree<T> tree;
    for (auto data: arr)
        tree.insert(data);
    arr = tree.inorder();
}

int main() {
    return 0;
}
