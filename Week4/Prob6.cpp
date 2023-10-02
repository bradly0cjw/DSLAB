//
// Created by LINBEI on 10/2/2023.
//

#include<iostream>
#include<cstdlib>

using namespace std;

class Node {
public:
    Node() {
        data = 0;
        next = NULL;
    }

    int data;
    struct Node *next;
};

class Set {
public:
    Set() {
        element=NULL;
    }

    bool addElement(int e) {
        // Check if the element already exists in the set
        Node *cur = element;
        while (cur != NULL) {
            if (cur->data == e) {
                return false; // Element already exists, return false
            }
            cur = cur->next;
        }

        // Create a new node for the element
        Node *newNode = new Node();
        newNode->data = e;

        // Insert the new node at the beginning of the list
        newNode->next = element;
        element = newNode;

        return true; // Element added successfully
    }

    Set *unions(Set *b) {
        Set *result = new Set();
        Node *cur = element;

        // Add all elements from set a to the result
        while (cur != NULL) {
            result->addElement(cur->data);
            cur = cur->next;
        }

        // Add elements from set b to the result (if they don't already exist)
        cur = b->element;
        while (cur != NULL) {
            result->addElement(cur->data);
            cur = cur->next;
        }

        return result;
    }

    Set *intersections(Set *b) {
        Set *result = new Set();
        Node *curA = element;

        while (curA != NULL) {
            Node *curB = b->element;
            bool found = false;

            while (curB != NULL) {
                if (curA->data == curB->data) {
                    found = true;
                    break;
                }
                curB = curB->next;
            }

            if (found) {
                result->addElement(curA->data);
            }

            curA = curA->next;
        }

        return result;
    }


    bool equivalent(Set *b) {
        // Check if both sets have the same elements
        Node *curA = element;
        Node *curB = b->element;

        while (curA != NULL && curB != NULL) {
            if (curA->data != curB->data) {
                return false; // Element in set a is not equal to element in set b
            }
            curA = curA->next;
            curB = curB->next;
        }

        // Check if both sets have the same number of elements
        return curA == NULL && curB == NULL;
    }

    void listAll() {
        Node *cur = element;
        while (cur != NULL) {
            cout << cur->data << " ";
            cur = cur->next;
        }
    }

private:
    Node *element;
};

int main() {
    Set *a = new Set();
    Set *b = new Set();
    Set *c;
    Node *cur;

    a->addElement(1);
    a->addElement(2);
    a->addElement(3);
    b->addElement(3);
    b->addElement(4);
    b->addElement(5);
    b->addElement(5);
    c = a->unions(b);
    c->listAll();
    cout<<endl;
    c = a->intersections(b);
    c->listAll();
    cout<<endl;
    if (a->equivalent(b) == 0)
        cout << "Not equivalent.\n";
    else
        cout << "Equivalent!\n";
}
