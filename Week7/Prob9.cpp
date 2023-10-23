//
// Created by LINBEI on 10/23/2023.
//
#include<iostream>
#include<cstdlib>
#include<ctime>

#define SIZE 100
using namespace std;

class Node {
public:
    int level, data;
    Node *left, *right;
};

class Queue {
public:
    Queue() {
        top = 0;
        bot = 0;
    }

    int enqueue(Node *element) {
        if ((top + 1) % SIZE == bot) {
            return -1;
        }
        data[top] = element;
        top = (top + 1) % SIZE;
        return 1;
    }

    Node *dequeue() {
        if (top == bot) {
            return NULL;
        }
        Node *temp = data[bot];
        bot = (bot + 1) % SIZE;
        return temp;
    }

private:
    Node *data[SIZE];
    int top, bot;
};

class Tree {
public:
    Tree() {
        root = NULL;
    }

    void insert(Node *n) {
        insert(&root, n);
    }

    void inorder() {
        inorder(root);
        cout << "\n";
    }

    void preorder() {
        preorder(root);
        cout << "\n";
    }

    void postorder() {
        postorder(root);
        cout << "\n";
    }

    void levelorder() {
        levelorder(root);
        cout << "\n";
    }

    void inorder(Node *node) {
        if (node != NULL) {
            inorder(node->left);
            cout << node->data << " ";
            inorder(node->right);
        }
    }

    void preorder(Node *node) {
        if (node != NULL) {
            cout << node->data << " ";
            preorder(node->left);
            preorder(node->right);
        }
    }

    void postorder(Node *node) {
        if (node != NULL) {
            postorder(node->left);
            postorder(node->right);
            cout << node->data << " ";
        }
    }

    void levelorder(Node *node) {
        if (node == NULL) {
            return;
        }
        Queue *queue = new Queue();
        queue->enqueue(node);
        while (1) {
            Node *temp = queue->dequeue();
            if (temp == NULL) {
                break;
            }
            cout << temp->data << " ";
            if (temp->left != NULL) {
                queue->enqueue(temp->left);
            }
            if (temp->right != NULL) {
                queue->enqueue(temp->right);
            }
        }
    }

private:
    Node *root;

    void insert(struct Node **r, struct Node *n) {
        if (*r == NULL)
            *r = n;
        else if (n->data > (*r)->data)
            insert(&((*r)->right), n);
        else
            insert(&((*r)->left), n);
    }
};

int main() {
    Tree *tree = new Tree();
    Node *node;
    int j;
    srand(time(NULL));
    for (j = 0; j < 10; j++) {
        node = new Node();
        node->data = rand();
        node->left = NULL;
        node->right = NULL;
        tree->insert(node);
    }
    tree->inorder();
    printf("\n");
    tree->preorder();
    printf("\n");
    tree->postorder();
    printf("\n");
    tree->levelorder();
    printf("\n");
}
