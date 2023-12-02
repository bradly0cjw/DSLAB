//
// Created by LINBEI on 11/27/2023.
//
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

class TrieNode;

class ChildNode {
public:
    char key;
    TrieNode *node;

    ChildNode(char key, TrieNode *node) : key(key), node(node) {}
};

class TrieNode {
public:
    vector<ChildNode *> children;
    bool isEndOfWord;
//    int childCount;
    TrieNode *parent;

    TrieNode() {
        isEndOfWord = false;
        parent = nullptr;
//        isEndOfWord = false;
//        for (int i = 0; i < 26; i++)
//            children[i] = nullptr;
//        childCount = 0;
//        parent = nullptr;
    }
};

class Trie {
private:
    TrieNode *root;

public:
    /*
    construct a Trie.
    */
    Trie() {
        root = new TrieNode();
    };

    /*
	search trie for key, return true if exist, false if not.
	*/
    bool search(string key) {
        TrieNode *node = root;
        for (char c: key) {
            bool found = false;
            for (ChildNode *child: node->children) {
                if (child->key == c) {
                    node = child->node;
                    found = true;
                    break;
                }
            }
            if (!found) return false;
        }
        return node->isEndOfWord;
    };

    /*
	insert value into trie.
	*/
    void insert(string value) {
        TrieNode *node = root;
        for (char c: value) {
            bool found = false;
            for (ChildNode *child: node->children) {
                if (child->key == c) {
                    node = child->node;
                    found = true;
                    break;
                }
            }
            if (!found) {
                ChildNode *newChild = new ChildNode(c, new TrieNode());
                newChild->node->parent = node;
                node->children.push_back(newChild);
                node = newChild->node;
            }
        }
        node->isEndOfWord = true;
    };

    /*
	display trie in pre-order, each element in a line, display space befoer element base on the level of 	the element. level 1 for 2 space, level 2 for 4 space, level 3 for 6 space and so on, root is level 	0.
	*/
    void preorder_helper(TrieNode *node, int level, bool isendl = false, int isOnlyChild = 0) {
        if (node == nullptr)
            return;

        for (ChildNode *child: node->children) {
            if (child != nullptr && child->node != nullptr) {
                if (isendl) {
                    for (int j = 0; j < level - isOnlyChild; j++)
                        cout << "  ";
                    isendl = false;
                    isOnlyChild = 0;
                } else {
                    isOnlyChild = 1;
                }
                char c = child->key;
                cout << child->key;
                if (child->node->isEndOfWord || child->node->children.size() > 1) {
                    cout << endl;
                    isendl = true;
                }
                preorder_helper(child->node, level + 1, isendl, isOnlyChild);
            }
        }
    }

    void preorder() {
        cout << "[]" << endl;
        preorder_helper(root, 1, true);
    }
};

int main() {
    Trie *trie = new Trie();
    string command, key, value;
//    ifstream in(R"(C:\Users\LINBEI\Documents\GitHub\NDHU\DSLAB\Week12\Prob17-1.in)");
//    ofstream out(R"(C:\Users\LINBEI\Documents\GitHub\NDHU\DSLAB\Week12\Prob17-1.out)");
    while (1) {
        cin >> command;
        if (command == "insert") {
            cin >> value;
            trie->insert(value);
        } else if (command == "search") {
            cin >> key;
            if (trie->search(key))
                cout << "exist" << endl;
            else
                cout << "not exist" << endl;
        } else if (command == "print") {
            trie->preorder();
        } else if (command == "exit") {
            break;
        }
        if (cin.eof())
            break;
    }
    return 0;
}
