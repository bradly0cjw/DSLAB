//
// Created by LINBEI on 11/27/2023.
//
//PREPEND BEGIN
/*some text*/
//PREPEND END

//TEMPLATE BEGIN
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <ctime>

using namespace std;

template<class T>
class Node {
public:
    Node() {
        data = new T;
    }

    Node(T d) {
        data = new T;
        (*data) = d;
    }

    Node &operator=(T d) {
        (*data) = d;
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &out, Node n) {
        out << *(n.data);
        return out;
    }

    friend std::ostream &operator<<(std::ostream &out, Node *n) {
        out << *(n->data);
        return out;
    }

    void setData(T d) {
        *data = d;
    }

    T &getData() const {
        return *data;
    }

protected:
    T *data;
};

template<class T>
class BinaryTreeNode : public Node<T> {
public:
    BinaryTreeNode() : Node<T>() {
        left = NULL;
        right = NULL;
        height = 1;
    }

    BinaryTreeNode(T d) : Node<T>(d) {
        left = NULL;
        right = NULL;
        height = 1;
    }

    BinaryTreeNode(BinaryTreeNode<T> *l, BinaryTreeNode<T> *r) : Node<T>() {
        left = l;
        right = r;
        height = 1;
    }

    BinaryTreeNode(T d, BinaryTreeNode<T> *l, BinaryTreeNode<T> *r) : Node<T>(d) {
        left = l;
        right = r;
    }

    void setLeft(BinaryTreeNode<T> *l) {
        left = l;
    }

    void setRight(BinaryTreeNode<T> *r) {
        right = r;
    }

    BinaryTreeNode<T> *&getLeft() {
        return left;
    }

    BinaryTreeNode<T> *&getRight() {
        return right;
    }

    bool operator>(BinaryTreeNode<T> n) {
        if (*(this->data) > *(n.data))
            return true;
        return false;
    }

    bool operator==(BinaryTreeNode<T> n) {
        if (*(this->data) == *(n.data))
            return true;
        return false;
    }

    int height;
private:
    BinaryTreeNode<T> *left, *right;
};

template<class T>
class AVLTree {
private:
    BinaryTreeNode<T> *root;

    void inorder(BinaryTreeNode<T> *cur, int n) {
        if (cur == NULL)
            return;
        inorder(cur->getRight(), n + 1);
        int j;
        for (j = 0; j < n; j++)
            cout << "  ";
        cout << cur << endl;
        inorder(cur->getLeft(), n + 1);
    }


public:
    AVLTree() {
        root = NULL;
    };

    void insert(T d) {
        root = insert(root, d);
    };

    BinaryTreeNode<T> *insert(BinaryTreeNode<T> *node, T d) {
        if (node == NULL)
            return (new BinaryTreeNode<T>(d));
        if (d < node->getData())
            node->setLeft(insert(node->getLeft(), d));
        else if (d > node->getData())
            node->setRight(insert(node->getRight(), d));
        else
            return node;
        node->height = 1 + max(height(node->getLeft()), height(node->getRight()));
        int balance = getBalance(node);
        if (balance > 1 && d < node->getLeft()->getData())
            return rightRotate(node);
        if (balance < -1 && d > node->getRight()->getData())
            return leftRotate(node);
        if (balance > 1 && d > node->getLeft()->getData()) {
            node->setLeft(leftRotate(node->getLeft()));
            return rightRotate(node);
        }
        if (balance < -1 && d < node->getRight()->getData()) {
            node->setRight(rightRotate(node->getRight()));
            return leftRotate(node);
        }
        return node;
    }

    int height(BinaryTreeNode<T> *N) {
        if (N == NULL)
            return 0;
        return N->height;
    }

    int getBalance(BinaryTreeNode<T> *N) {
        if (N == NULL)
            return 0;
        return height(N->getLeft()) - height(N->getRight());
    }

    BinaryTreeNode<T> *rightRotate(BinaryTreeNode<T> *y) {
        BinaryTreeNode<T> *x = y->getLeft();
        BinaryTreeNode<T> *T2 = x->getRight();
        x->setRight(y);
        y->setLeft(T2);
        y->height = max(height(y->getLeft()), height(y->getRight())) + 1;
        x->height = max(height(x->getLeft()), height(x->getRight())) + 1;
        return x;
    }

    BinaryTreeNode<T> *leftRotate(BinaryTreeNode<T> *x) {
        BinaryTreeNode<T> *y = x->getRight();
        BinaryTreeNode<T> *T2 = y->getLeft();
        y->setLeft(x);
        x->setRight(T2);
        x->height = max(height(x->getLeft()), height(x->getRight())) + 1;
        y->height = max(height(y->getLeft()), height(y->getRight())) + 1;
        return y;
    }

    void inorder() {
        inorder(root, 0);
    }
};

int main() {
    AVLTree<int> *tree = new AVLTree<int>();
    srand(0);
    int j, k, i;
    for (j = 0; j < 20; j++) {
        tree->insert(k = rand() % 100);
        cout << "Insert: " << k << endl;
        tree->inorder();
    }
}
