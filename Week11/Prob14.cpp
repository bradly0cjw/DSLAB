//
// Created by LINBEI on 11/20/2023.
//
#include <iostream>
#include <stack>
#include <sstream>

using namespace std;

class ExpressionTree {
private:
    struct Node {
        string value;
        Node *left;
        Node *right;
    };
    Node *root;

public:
    //constructure an Expression Tree using a string. The string representing an in-order expression contains operator =, -, *, /, parentheses, and number in floationg point.
    ExpressionTree(string exp) {
        stack<Node *> st;
        stringstream ss(exp);
        string token;
        while (ss >> token) {
            Node *node = new Node{token, nullptr, nullptr};
            if (token == "+" || token == "-" || token == "*" || token == "/") {
                node->right = st.top();
                st.pop();
                node->left = st.top();
                st.pop();
            }
            st.push(node);
        }
        root = st.top();
        st.pop();
    }

    //Display the Expression Tree in in-order traverse.
    void inorder(Node *node) {
        if (node == nullptr) return;
        inorder(node->left);
        cout << node->value << ' ';
        inorder(node->right);
    }

    //Display the Expression Tree in post-order traverse.
    void postorder(Node *node) {
        if (node == nullptr) return;
        postorder(node->left);
        postorder(node->right);
        cout << node->value << ' ';
    }

    //Display the Expression Tree in pre-order traverse.
    void preorder(Node *node) {
        if (node == nullptr) return;
        cout << node->value << ' ';
        preorder(node->left);
        preorder(node->right);
    }

    //Evaluate the expression and return the result.
    double evaluate(Node *node) {
        if (node->left == nullptr && node->right == nullptr)
            return stod(node->value);
        else {
            double left = evaluate(node->left);
            double right = evaluate(node->right);
            if (node->value == "+") return left + right;
            if (node->value == "-") return left - right;
            if (node->value == "*") return left * right;
            if (node->value == "/") return left / right;
        }
        return 0;
    }

    void inorder() { inorder(root); }

    void postorder() { postorder(root); }

    void preorder() { preorder(root); }

    double evaluate() { return evaluate(root); }
};


