//
// Created by LINBEI on 10/30/2023.
//
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <ctime>

#define SIZE 100

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
class ListNode : public Node<T> {
public:
    ListNode() : Node<T>() {
        prev = NULL;
        next = NULL;
    }

    ListNode(T d) : Node<T>(d) {
        prev = NULL;
        next = NULL;
    }

    ListNode(ListNode *p, ListNode *n) : Node<T>() {
        prev = p;
        next = n;
    }

    ListNode(T d, ListNode *p, ListNode *n) : Node<T>(d) {
        prev = p;
        next = n;
    }

    ListNode *getNext() const {
        return next;
    }

    ListNode *getPrev() const {
        return prev;
    }

    void setNext(ListNode *n) {
        next = n;
    }

    void setPrev(ListNode *p) {
        prev = p;
    }

    ListNode &operator=(T d) {
        this->setData(d);
        return *this;
    }

private:
    ListNode *prev, *next;
};

template<class T>
class LinkList {
public:
    LinkList() {
        head = NULL;
        tail = NULL;
    }

    void addFromHead(T d) {
        ListNode<T> *node = new ListNode<T>(d);
        if (head != NULL) {
            head->setPrev(node);
        }
        node->setNext(head);
        head = node;
        if (tail == NULL)
            tail = node;
    }

    void addFromTail(T d) {
        ListNode<T> *node = new ListNode<T>(d);
        if (tail != NULL) {
            tail->setNext(node);
        }
        node->setPrev(tail);
        tail = node;
        if (head == NULL)
            head = node;
    }

    void addAfter(ListNode<T> *at, T d) {
        if (!exist(at))
            return;
        ListNode<T> *node = new ListNode<T>(d);
        if (at->getNext() != NULL)
            at->getNext()->setPrev(node);
        node->setNext(at->getNext());
        at->setNext(node);
        node->setPrev(at);
        if (node->getNext() == NULL)
            tail = node;
    }

    ListNode<T> *removeFromHead() {
        ListNode<T> *n = head;
        if (head != NULL) {
            head = head->getNext();
            if (head != NULL)
                head->setPrev(NULL);
            else
                tail = NULL;
            n->setNext(NULL);
        }
        return n;
    }

    ListNode<T> *removeFromTail() {
        ListNode<T> *n = tail;
        if (tail != NULL) {
            tail = tail->getPrev();
            if (tail != NULL)
                tail->setNext(NULL);
            else
                head = NULL;
            n->setPrev(NULL);
        }
        return n;
    }

    ListNode<T> *remove(ListNode<T> *n) {
        if (!exist(n))
            return NULL;
        if (n == head)
            return removeFromHead();
        if (n == tail)
            return removeFromTail();
        n->getPrev()->setNext(n->getNext());
        n->getNext()->setPrev(n->getPrev());
        n->setNext(NULL);
        n->setPrev(NULL);
        return n;
    }

    ListNode<T> *exist(T d) {
        ListNode<T> *j = head;
        while (j != NULL) {
            if (j->getData() == d)
                return j;
            j = j->getNext();
        }
        return NULL;
    }

    bool exist(ListNode<T> *n) {
        ListNode<T> *j = head;
        while (j != NULL) {
            if (j == n)
                return true;
            j = j->getNext();
        }
        return false;
    }

    ListNode<T> &operator[](int i) {
        ListNode<T> *j = head;
        int k;
        for (k = 0; k < i && j != NULL; k++)
            j = j->getNext();
        if (j == NULL)
            throw std::invalid_argument("index does not exist.");
        return *j;
    }

    void print() const {
        ListNode<T> *j;
        j = head;
        while (j != NULL) {
            std::cout << (*j) << " ";
            j = j->getNext();
        }
        std::cout << std::endl;
    }


    int size()
    {
        ListNode<T> *temp = head;
        int count = 0;
        if (head == NULL)
            return 0;
        while ((temp = temp->getNext()))
        {
            ++count;
        }
        return ++count;
    }

protected:
    ListNode<T> *head, *tail;
};

/*
	Please finish the TreeNode class, TreeNode class respresent a node in a general tree.
	A general tree is different from binary tree, every node in binary tree have at most two child node, but a node in general tree may have more than two child node.
*/

template<class T>
class TreeNode : public Node<T> {
public:
    TreeNode() : Node<T>() {
        child = new LinkList<TreeNode<T> *>();
    }

    TreeNode(T d) : Node<T>(d) {
        child = new LinkList<TreeNode<T> *>();
    }

    /*
        Add a child to this node.
    */
    void addChild(TreeNode *n) {
        child->addFromTail(n);
    }

    /*
        Add a child to this node.
    */
    void addChild(T d) {
        TreeNode<T> *n = new TreeNode<T>(d);
        child->addFromTail(n);
    }

    /*
        Return the nth child of the node.
    */
    TreeNode<T> *operator[](int n) {
        if (n >= child->size()) {
            return NULL;
        } else {
            return (*child)[n].getData();
        }
//      return ((*child)[n]).getData();//(*child)[n] = ListNode<TreeNode<T> *>

    }


private:
    LinkList<TreeNode<T> *> *child;
};

/*
	Please finish the Tree class. Tree class respresent a general tree, that means node on this tree may have more than two child node.

*/
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
        for (int i = 0; i < SIZE; i++)
            delete data[i];
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

private:
    T *data[SIZE];
    int top, bot;
};

template<class T>
class Tree {
public:
    Tree() {
        root = NULL;
    }

    /*
        return the nth node on this tree with level order.
    */
    TreeNode<T> *operator[](int n) {
        Queue<TreeNode<T> *> *queue = new Queue<TreeNode<T> *>();
        queue->enqueue(root);
        TreeNode<T> *node = NULL;
        int nodeCount = 0;
        while ((node = queue->dequeue()) != NULL) {
            if (nodeCount == n) {
                free(queue);
                return node;
            }
            nodeCount++;
            int i = 0;
            TreeNode<T> *child = NULL;
            while ((child = (*node)[i]) != NULL) {
                queue->enqueue(child);
                i++;
            }
        }
        free(queue);
        return NULL;
    }

    /*
        return the number of nodes on this tree.
    */
    int count() {
        return countNodes(root);
    }

    int countNodes(TreeNode<T> *node) {
        int count = 0;
        Queue<TreeNode<T> *> *queue = new Queue<TreeNode<T> *>();
        queue->enqueue(node);
        TreeNode<T> *CurrentNode = NULL;
        if (node == NULL) {
            free(queue);
            return 0;
        }
        while ((CurrentNode = queue->dequeue()) != NULL) {
            count++;
            int i = 0;
            TreeNode<T> *child = NULL;
            while (CurrentNode != NULL && (child = (*CurrentNode)[i]) != NULL) {
                queue->enqueue(child);
                i++;
            }
        }
        free(queue);
        return count;
    }

    /*
        print all the node on this tree with level order.
    */
    void levelOrder() {
        levelOrder(root);
        std::cout << std::endl;
    }

    void levelOrder(TreeNode<T> *node) {
        if (node == NULL) {
            return;
        }
        Queue<TreeNode<T> *> *queue = new Queue<TreeNode<T> *>();
        queue->enqueue(node);
        TreeNode<T> *currentNode = NULL;
        while ((currentNode = queue->dequeue()) != NULL) {
            std::cout << currentNode->getData() << " ";
            int i = 0;
            TreeNode<T> *child = NULL;
            while ((child = (*currentNode)[i]) != NULL) {
                queue->enqueue(child);
                i++;
            }
        }
    }


    /*
        print all the node on this tree with preorder.
    */
    void preorder() {
        preorder(root);
        std::cout << std::endl;
    }

    void preorder(TreeNode<T> *root) {
        if (root == NULL)
            return;
        std::cout << root->getData() << " ";
        int i = 0;
        TreeNode<T> *child = NULL;
        while ((child = (*root)[i]) != NULL) {
            preorder(child);
            i++;
        }
    }

    /*
        print all the node on this tree with postorder.
    */
    void postorder() {
        postorder(root);
        std::cout << std::endl;
    }

    void postorder(TreeNode<T> *root) {
        if (root == NULL)
            return;
        int i = 0;
        TreeNode<T> *child = NULL;
        while ((child = (*root)[i]) != NULL) {
            postorder(child);
            i++;
        }
        std::cout << root->getData() << " ";
    }

    /*
        set the root of this tree.
    */
    void setRoot(T d) {
        root = new TreeNode<T>(d);
    }

private:
    TreeNode<T> *root;
};


int main() {
    Tree<int> *tree = new Tree<int>();
//    srand(unsigned(time(NULL)));
    srand(0);
    int j, k, i;
    for (j = 0; j < 20; j++) {
        if (tree->count() == 0) {

            tree->setRoot(rand() % 100);
        } else {
            k = rand() % tree->count();
            (*tree)[k]->addChild(rand() % 100);
        }
    }
    tree->levelOrder();
    tree->preorder();
    tree->postorder();
}
