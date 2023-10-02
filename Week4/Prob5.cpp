//
// Created by LINBEI on 10/2/2023.
//
#include <iostream>
#include <cstdlib>
#include <ctime>

#define SIZE 100

using namespace std;

class Node {
public:
    Node() {
        next = NULL;
        pre = NULL;
    }

    Node(int n) {
        data = n;
        next = NULL;
        pre = NULL;
    }

    int getData() { return data; }

    Node *getNext() { return next; }

    Node *getPre() { return pre; }

    void setData(int d) { data = d; }

    void setNext(Node *n) { next = n; }

    void setPre(Node *p) { pre = p; }

private:
    int data;
    Node *next, *pre;
};

class List {
public:
    List() { list = NULL; }

    List(int n) { generate(n); }

    void generate(int n) {
        int j;
        list = NULL;
        for (j = 0; j < n; j++)
            generate();
    }

    void generate() {
        Node *buf = new Node(rand());
        buf->setNext(list);
        if (list != NULL)
            list->setPre(buf);
        list = buf;
    }

    void bubbleSort() {
        bool swapped;
        Node *ptr;
        if (list == NULL)
            return;
        do {
            swapped = false;
            ptr = list;
            while (ptr->getNext() != NULL) {
                if (ptr->getData() > ptr->getNext()->getData()) {
                    int temp = ptr->getData();
                    ptr->setData(ptr->getNext()->getData());
                    ptr->getNext()->setData(temp);
                    swapped = true;
                }
                ptr = ptr->getNext();
            }
        } while (swapped);
    }

    void selectionSort() {
        Node *ptr, *min, *temp;
        if (list == NULL)
            return;
        ptr = list;
        while (ptr != NULL) {
            min = ptr;
            temp = ptr->getNext();
            while (temp != NULL) {
                if (min->getData() > temp->getData()) {
                    min = temp;
                }
                temp = temp->getNext();
            }
            int t = ptr->getData();
            ptr->setData(min->getData());
            min->setData(t);
            ptr = ptr->getNext();
        }
    }

    void insertionSort() {
        Node *sorted = NULL;

        Node *ptr = list;
        while (ptr != NULL) {
            Node *next = ptr->getNext();

            ptr->setPre(NULL);
            ptr->setNext(NULL);

            if (sorted == NULL || sorted->getData() >= ptr->getData()) {
                ptr->setNext(sorted);
                if (sorted != NULL) {
                    sorted->setPre(ptr);
                }
                sorted = ptr;
            } else {
                Node *current = sorted;
                while (current->getNext() != NULL && current->getNext()->getData() < ptr->getData()) {
                    current = current->getNext();
                }
                ptr->setNext(current->getNext());
                if (current->getNext() != NULL) {
                    current->getNext()->setPre(ptr);
                }
                current->setNext(ptr);
                ptr->setPre(current);
            }
            ptr = next;
        }
        list = sorted;
    }


    void print() {
        Node *cur = list;
        while (cur != NULL) {
            cout << cur->getData() << " ";
            cur = cur->getNext();
        }
        cout << endl;
    }

private:
    Node *list;
};

int main() {
    srand(time(NULL));
    List *l = new List(10);
    l->print();
    l->bubbleSort();
    l->print();

    l = new List(10);
    l->print();
    l->insertionSort();
    l->print();

    l = new List(10);
    l->print();
    l->selectionSort();
    l->print();
}

