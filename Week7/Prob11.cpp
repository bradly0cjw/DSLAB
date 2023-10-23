//
// Created by LINBEI on 10/23/2023.
//
#include<iostream>
#include<cstdlib>
#include<ctime>

#define SIZE 100
using namespace std;

class Queue {
public:
    Queue() {
        top = 0;
        bot = 0;
    }

    int enqueue(int element) {
        if ((top + 1) % SIZE == bot) {
            return -1;
        }
        data[top] = element;
        top = (top + 1) % SIZE;
        return 1;
    }

    int dequeue() {
        if (top == bot) {
            return NULL;
        }
        int temp = data[bot];
        bot = (bot + 1) % SIZE;
        return temp;
    }

private:
    int data[SIZE];
    int top, bot;
};

class Tree {
public:
    Tree() {
        int j;
        for (j = 0; j < 2000; j++)
            root[j] = -1;
    }

    void insert(int node) {
        int index = 0;
        while (index < 2000 && root[index] != -1) {
            if (root[index] < node)
                index = index * 2 + 2;
            else
                index = index * 2 + 1;
        }
        root[index] = node;
    }

    void inorder() {
        inorder(0);
        cout << "\n";
    }

    void preorder() {
        preorder(0);
        cout << "\n";
    }

    void postorder() {
        postorder(0);
        cout << "\n";
    }

    void levelorder() {
        levelorder(0);
        cout << "\n";
    }

    void inorder(int index) {
        if (index >= 2000 || root[index] == -1) return;
        inorder(index * 2 + 1);
        cout << root[index] << ' ';
        inorder(index * 2 + 2);
    }

    void preorder(int index) {
        if (index >= 2000 || root[index] == -1) return;
        cout << root[index] << ' ';
        preorder(index * 2 + 1);
        preorder(index * 2 + 2);
    }

    void postorder(int index) {
        if (index >= 2000 || root[index] == -1) return;
        postorder(index * 2 + 1);
        postorder(index * 2 + 2);
        cout << root[index] << ' ';
    }

    void levelorder(int index) {
        if (index >= 2000 || root[index] == -1) return;
        Queue *q = new Queue();
        q->enqueue(index);
        int init = 1;
        while (1) {
            int current = q->dequeue();
            if (current == NULL && init == 0) {
                break;
            }
            init = 0;
            cout << root[current] << ' ';
            if (current * 2 + 1 < 2000 && root[current * 2 + 1] != -1)
                q->enqueue(current * 2 + 1);

            if (current * 2 + 2 < 2000 && root[current * 2 + 2] != -1)
                q->enqueue(current * 2 + 2);
        }
    }

private:
    int root[2000];
};

int main() {
    Tree *tree = new Tree();
    int j, node;
    srand(time(NULL));
    for (j = 0; j < 10; j++) {
        node = rand();
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
