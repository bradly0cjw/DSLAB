//
// Created by LINBEI on 10/23/2023.
//
#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std;

class Tree {
public:
    Tree() {
        int j, k;
        for (j = 0; j < 20; j++)
            for (k = 0; k < 4; k++)
                root[j][k] = -1;
    }

    int insert(int node) {
        int f = 0, index = 0;
        while (root[index][0] != -1)
            index++;
        if (index >= 20)
            return -1;
        if (index == 0) {
            root[0][0] = 1;
            root[0][1] = node;
            return 1;
        } else {
            root[index][0] = 1;
            root[index][1] = node;
            while (1) {
                if (root[f][1] < node) {
                    if (root[f][3] == -1) {
                        root[f][3] = index;
                        return 1;
                    } else {
                        f = root[f][3];
                    }
                } else {
                    if (root[f][2] == -1) {
                        root[f][2] = index;
                        return 1;
                    } else {
                        f = root[f][2];
                    }
                }
            }
        }
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

    void inorder(int node) {
        if (node >= 20 || node == -1 || root[node][0] == -1)
            return;

        inorder(root[node][2]);
        cout << root[node][1] << " ";
        inorder(root[node][3]);
    }

    void preorder(int node) {
        if (node >= 20 || node == -1 || root[node][0] == -1)
            return;

        cout << root[node][1] << " ";
        preorder(root[node][2]);
        preorder(root[node][3]);
    }

    void postorder(int node) {
        if (node >= 20 || node == -1 || root[node][0] == -1)
            return;

        postorder(root[node][2]);
        postorder(root[node][3]);
        cout << root[node][1] << " ";
    }

    void levelorder(int node) {
        for (int i = 0; i < 20 && root[i][0] != -1; i++)
            cout << root[i][1] << " ";
    }

private:
    int root[20][4];
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
