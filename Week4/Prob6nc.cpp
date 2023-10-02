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
        Node *cur = element;
        while (cur != NULL) {
            if (cur->data == e) {
                return false;
            }
            cur = cur->next;
        }
        Node *newNode = new Node();
        newNode->data = e;
        newNode->next = element;
        element = newNode;
        return true;
    }

    Set *unions(Set *b) {
        Set *result = new Set();
        Node *cur = element;
        while (cur != NULL) {
            result->addElement(cur->data);
            cur = cur->next;
        }
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

        Node *curA = element;
        Node *curB = b->element;
        bool find;
        while(curB != NULL){
            curA=element;
            find=false;
            while (curA != NULL) {
                if (curA->data == curB->data) {
                    find= true;
                    break;
                }
                curA = curA->next;
            }
            if(!find){
                return false;
            }
            curB =curB->next;
        }
        find=false;
        curA=element;
        while(curA != NULL){
            curB=b->element;
            find=false;
            while (curB != NULL) {
                if (curB->data == curA->data) {
                    find= true;
                    break;
                }
                curB = curB->next;
            }
            if(!find){
                return false;
            }
            curA =curA->next;
        }
        return true;
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
