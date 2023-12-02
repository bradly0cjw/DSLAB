#include <iostream>
#include <vector>
#include <fstream>

#define SIZE 100
using namespace std;

template<typename ValueType>
class RedBlackTree {
protected:
    enum State {
        Red, Black
    };

    struct RedBlackNode {
        ValueType data;
        State state;
        RedBlackNode *left, *right, *parent;

        size_t height() const;

        size_t size() const;
    };

public: // constructors, destructors
    RedBlackTree() {
        root = nullptr;
    };

    RedBlackTree(const RedBlackTree &srcTree) {
        root = srcTree.root;
    };

    ~RedBlackTree() {
        delete root;
    };

public: // methods
    void insert(const ValueType &val) {
        RedBlackNode *newNode = new RedBlackNode{val, Red, nullptr, nullptr, nullptr};
        if (root == nullptr) {
            root = newNode;
            root->state = Black;
            root->left = nullptr;
            root->right = nullptr;
            return;
        }
        RedBlackNode *current = root;
        while (current != nullptr) {
            newNode->parent = current;
            if (val < current->data) {
                if (current->left == nullptr) {
                    current->left = newNode;
                    break;
                } else {
                    current = current->left;
                }
            } else {
                if (current->right == nullptr) {
                    current->right = newNode;
                    break;
                } else {
                    current = current->right;
                }
            }
        }
        while (newNode != root && newNode->parent->state == Red) {
            RedBlackNode *parent = newNode->parent;
            RedBlackNode *grandparent = parent->parent;
            if (grandparent->left == parent) {
                RedBlackNode *uncle = grandparent->right;
                if (uncle != nullptr && uncle->state == Red) {
                    parent->state = Black;
                    uncle->state = Black;
                    grandparent->state = Red;
                    newNode = grandparent;
                } else {
                    if (parent->right == newNode) {
                        newNode = parent;
                        rotateLeft(newNode);
                    }
                    parent->state = Black;
                    grandparent->state = Red;
                    rotateRight(grandparent);
                }
            } else {
                RedBlackNode *uncle = grandparent->left;
                if (uncle != nullptr && uncle->state == Red) {
                    parent->state = Black;
                    uncle->state = Black;
                    grandparent->state = Red;
                    newNode = grandparent;
                } else {
                    if (parent->left == newNode) {
                        newNode = parent;
                        rotateRight(newNode);
                    }
                    parent->state = Black;
                    grandparent->state = Red;
                    rotateLeft(grandparent);
                }
            }
        }
        root->state = Black;
    };

    void rotateLeft(RedBlackNode *node) {
        RedBlackNode *right = node->right;
        node->right = right->left;
        if (right->left != nullptr) {
            right->left->parent = node;
        }
        right->parent = node->parent;
        if (node->parent == nullptr) {
            root = right;
        } else if (node == node->parent->left) {
            node->parent->left = right;
        } else {
            node->parent->right = right;
        }
        right->left = node;
        node->parent = right;
    };

    void rotateRight(RedBlackNode *node) {
        RedBlackNode *left = node->left;
        node->left = left->right;
        if (left->right != nullptr) {
            left->right->parent = node;
        }
        left->parent = node->parent;
        if (node->parent == nullptr) {
            root = left;
        } else if (node == node->parent->right) {
            node->parent->right = left;
        } else {
            node->parent->left = left;
        }
        left->right = node;
        node->parent = left;
    };

    void remove(const ValueType &val) {
        RedBlackNode *nodeToDelete = root;
        while (nodeToDelete != nullptr) {
            if (val == nodeToDelete->data) {
                break;
            } else if (val < nodeToDelete->data) {
                nodeToDelete = nodeToDelete->left;
            } else {
                nodeToDelete = nodeToDelete->right;
            }
        }
        if (nodeToDelete == nullptr) {
            return;
        }
        RedBlackNode *nodeToReplace = nullptr;
        RedBlackNode *child = nullptr;
        State originalColor = nodeToDelete->state;
        if (nodeToDelete->left == nullptr) {
            child = nodeToDelete->right;
            transplant(nodeToDelete, nodeToDelete->right);
        } else if (nodeToDelete->right == nullptr) {
            child = nodeToDelete->left;
            transplant(nodeToDelete, nodeToDelete->left);
        } else {
            nodeToReplace = maximum(nodeToDelete->left);
            originalColor = nodeToReplace->state;
            child = nodeToReplace->left;
            if (nodeToReplace->parent == nodeToDelete) {
                if (child != nullptr) child->parent = nodeToReplace;
            } else {
                transplant(nodeToReplace, nodeToReplace->left);
                nodeToReplace->left = nodeToDelete->left;
                nodeToReplace->left->parent = nodeToReplace;
            }
            transplant(nodeToDelete, nodeToReplace);
            nodeToReplace->right = nodeToDelete->right;
            nodeToReplace->right->parent = nodeToReplace;
            nodeToReplace->state = nodeToDelete->state;
        }
        if (originalColor == Black) {
            removeFixup(child);
        }
        delete nodeToDelete;
    };

    RedBlackNode *maximum(RedBlackNode *node) {
        while (node->right != nullptr) {
            node = node->right;
        }
        return node;
    }

    void removeFixup(RedBlackNode *node) {
        while (node != root && node->state == Black) {
            if (node == node->parent->left) {
                RedBlackNode *sibling = node->parent->right;
                if (sibling->state == Red) {
                    sibling->state = Black;
                    node->parent->state = Red;
                    rotateLeft(node->parent);
                    sibling = node->parent->right;
                }
                if (sibling->left->state == Black && sibling->right->state == Black) {
                    sibling->state = Red;
                    node = node->parent;
                } else {
                    if (sibling->right->state == Black) {
                        sibling->left->state = Black;
                        sibling->state = Red;
                        rotateRight(sibling);
                        sibling = node->parent->right;
                    }
                    sibling->state = node->parent->state;
                    node->parent->state = Black;
                    sibling->right->state = Black;
                    rotateLeft(node->parent);
                    node = root;
                }
            } else {
                RedBlackNode *sibling = node->parent->left;
                if (sibling->state == Red) {
                    sibling->state = Black;
                    node->parent->state = Red;
                    rotateRight(node->parent);
                    sibling = node->parent->left;
                }
                if (sibling->right->state == Black && sibling->left->state == Black) {
                    sibling->state = Red;
                    node = node->parent;
                } else {
                    if (sibling->left->state == Black) {
                        sibling->right->state = Black;
                        sibling->state = Red;
                        rotateLeft(sibling);
                        sibling = node->parent->left;
                    }
                    sibling->state = node->parent->state;
                    node->parent->state = Black;
                    sibling->left->state = Black;
                    rotateRight(node->parent);
                    node = root;
                }
            }
        }
        node->state = Black;
    }

    void transplant(RedBlackNode *u, RedBlackNode *v) {
        if (u->parent == nullptr) {
            root = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        if (v != nullptr) {
            v->parent = u->parent;
        }
    };

    bool exists(const ValueType &val) const {
        RedBlackNode *current = root;
        while (current != nullptr) {
            if (val == current->data) {
                return true;
            } else if (val < current->data) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        return false;
    };

    size_t height() const {
        return height_helper(root);
    };

    size_t height_helper(RedBlackNode *node) const {
        if (node == nullptr)
            return 0;
        else {
            return 1 + max(height_helper(node->left), height_helper(node->right));
        }
    };

    size_t size() const {
        return size_helper(root);
    };

    size_t size_helper(RedBlackNode *node) const {
        if (node == nullptr)
            return 0;
        else {
            return 1 + size_helper(node->left) + size_helper(node->right);
        }
    };

    std::vector<ValueType> inOrder() const {
        vector<ValueType> result;
        inOrder_helper(root, result);
        return result;
    };

    void inOrder_helper(RedBlackNode *node, vector<ValueType> &result) const {
        if (node == nullptr)
            return;
        inOrder_helper(node->left, result);
        result.push_back(node->data);
        inOrder_helper(node->right, result);
    };

    std::vector<ValueType> levelOrder() const {
        vector<ValueType> result;
        levelOrder_helper(root, result);
        return result;
    };

    void levelOrder_helper(RedBlackNode *node, vector<ValueType> &result) const {
        if (node == nullptr)
            return;
        RedBlackTree::Queue<RedBlackNode *> q;
        q.enqueue(node);
        while (q.size() != 0) {
            RedBlackNode *temp = q.dequeue();
            result.push_back(temp->data);
            if (temp->left != nullptr)
                q.enqueue(temp->left);
            if (temp->right != nullptr)
                q.enqueue(temp->right);
        }
    };

    template<class T>
    class Queue {
    public:
        Queue() {
            top = 0;
            bot = 0;
            for (int i = 0; i < SIZE; i++)
                data[i] = NULL;
        }

        ~Queue() {
            for (int i = bot; i != top; i = (i + 1) % SIZE) {
                delete data[i];
            }
        }

        int enqueue(T element) {
            if ((top + 1) % SIZE == bot) {
                return -1; // Queue is full
            }
            data[top] = new T(element);
            top = (top + 1) % SIZE;
            return 1;
        }

        T dequeue() {
            if (top == bot) {
                return T(); // Queue is empty, return default constructed T
            }
            T *temp = data[bot];
            bot = (bot + 1) % SIZE;
            T ret = *temp;
            delete temp;
            return ret;
        }

        int size() {
            return (top - bot + SIZE) % SIZE;
        }

    private:
        T *data[SIZE];
        int top, bot;
    };

    void findroot() {
        cout << root->data << endl;
    }

protected:
    RedBlackNode *root;
};

template<typename T>
void sortByBST(vector<T> &arr) {
    RedBlackTree<T> tree;
    for (auto data: arr)
        tree.insert(data);
    arr = tree.inOrder();
}

int main() {
    RedBlackTree<string> tree;
    string operation;
    string data;
    ifstream in(R"(C:\Users\LINBEI\Documents\GitHub\NDHU\DSLAB\Week11\Prob16-1.in)");
//    int n;
//    cin >> n;
//    in >> n;
//    for (int i = 0; i < n; i++) {
//        cin >> operation >> data;
//        in >> operation >> data;
//    while (cin >> operation >> data) {
    while (in >> operation >> data) {
        if (operation == "insert") {
            tree.insert(data);
        } else if (operation == "delete") {
            tree.remove(data);
        }
    }

//     Print the in-order traversal of the tree
    vector<string> inOrder = tree.inOrder();
    cout << "In-order: ";
    for (const auto &i: inOrder) {
        cout << i << " ";
    }
    cout << "\n";
//     Print the level-order traversal of the tree
    vector<string> levelOrder = tree.levelOrder();
    cout << "Level-order: ";
    for (const auto &i: levelOrder) {
        cout << i << " ";
    }
    cout << "\n";

    return 0;
}