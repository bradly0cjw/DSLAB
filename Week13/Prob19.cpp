//
// Created by LINBEI on 12/4/2023.
//
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <ctime>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

template<class T>
class Node
{
public:
	Node()
	{
		data = new T;
	}
	Node(T d)
	{
		data = new T;
		(*data) = d;
	}
	Node &operator=(T d)
	{
		(*data) = d;
		return *this;
	}
	friend std::ostream &operator<<(std::ostream &out, Node n)
	{
		out<<(*(n.data));
		return out;
	}
	friend std::ostream &operator<<(std::ostream &out, Node *n)
	{
		out<<(*(n->data));
		return out;
	}
	void setData(T d)
	{
		*data = d;
	}
	T &getData() const
	{
		return *data;
	}
protected:
	T *data;
};

template<class T>
class ListNode : public Node<T>
{
public:
	ListNode() : Node<T>()
	{
		prev = NULL;
		next = NULL;
	}
	ListNode(T d) : Node<T>(d)
	{
		prev = NULL;
		next = NULL;
	}
	ListNode(ListNode *p, ListNode *n) : Node<T>()
	{
		prev = p;
		next = n;
	}
	ListNode(T d, ListNode *p, ListNode *n) : Node<T>(d)
	{
		prev = p;
		next = n;
	}
	ListNode *getNext() const
	{
		return next;
	}
	ListNode *getPrev() const
	{
		return prev;
	}
	void setNext(ListNode *n)
	{
		next = n;
	}
	void setPrev(ListNode *p)
	{
		prev = p;
	}
	ListNode &operator=(T d)
	{
		this->setData(d);
		return *this;
	}
private:
	ListNode *prev, *next;
};

template<class T>
class LinkList
{
public:
	LinkList()
	{
		head = NULL;
		tail = NULL;
	}
	void addFromHead(T d)
	{
		ListNode<T> *node = new ListNode<T>(d);
		if(head != NULL)
		{
			head->setPrev(node);
		}
		node->setNext(head);
		head = node;
		if(tail == NULL)
			tail = node;
	}
	void addFromTail(T d)
	{
		ListNode<T> *node = new ListNode<T>(d);
		if(tail != NULL)
		{
			tail->setNext(node);
		}
		node->setPrev(tail);
		tail = node;
		if(head == NULL)
			head = node;
	}
	void addAfter(ListNode<T> *at, T d)
	{
		if(!exist(at))
			return;
		ListNode<T> *node = new ListNode<T>(d);
		if(at->getNext() != NULL)
			at->getNext()->setPrev(node);
		node->setNext(at->getNext());
		at->setNext(node);
		node->setPrev(at);
		if(node->getNext() == NULL)
			tail = node;
	}
	ListNode<T> *removeFromHead()
	{
		ListNode<T> *n = head;
		if(head != NULL)
		{
			head = head->getNext();
			if(head != NULL)
				head->setPrev(NULL);
			else
				tail = NULL;
			n->setNext(NULL);
		}
		return n;
	}
	ListNode<T> *removeFromTail()
	{
		ListNode<T> *n = tail;
		if(tail != NULL)
		{
			tail = tail->getPrev();
			if(tail != NULL)
				tail->setNext(NULL);
			else
				head = NULL;
			n->setPrev(NULL);
		}
		return n;
	}
	ListNode<T> *remove(ListNode<T> *n)
	{
		if(!exist(n))
			return NULL;
		if(n == head)
			return removeFromHead();
		if(n == tail)
			return removeFromTail();
		n->getPrev()->setNext(n->getNext());
		n->getNext()->setPrev(n->getPrev());
		n->setNext(NULL);
		n->setPrev(NULL);
		return n;
	}
	ListNode<T> *exist(T d)
	{
		ListNode<T> *j = head;
		while(j != NULL)
		{
			if(j->getData() == d)
				return j;
			j = j->getNext();
		}
		return NULL;
	}
	bool exist(ListNode<T> *n)
	{
		ListNode<T> *j = head;
		while(j != NULL)
		{
			if(j == n)
				return true;
			j = j->getNext();
		}
		return false;
	}
	ListNode<T> &operator[](int i)
	{
		ListNode<T> *j = head;
		int k;
		for(k = 0;k < i && j != NULL;k ++)
			j = j->getNext();
		if(j == NULL)
			throw std::invalid_argument("index does not exist.");
		return *j;
	}
	void print() const
	{
		ListNode<T> *j;
		j = head;
		while(j != NULL)
		{
			std::cout<<(*j)<<" ";
			j = j->getNext();
		}
		std::cout<<std::endl;
	}
protected:
	ListNode<T> *head, *tail;
};

template<class T>
class GraphNode : public Node<T>
{
public:
	GraphNode() :Node<T>()
	{
		list = new LinkList<T>();
	}
	GraphNode(T d) :Node<T>(d)
	{
		list = new LinkList<GraphNode<T> *>();
	}
	void addLink(GraphNode<T> *node)
	{
		list->addFromTail(node);
	}
	bool exist(GraphNode<T> *node)
	{
		if(list->exist(node))
			return true;
		return false;
	}
	void remove(GraphNode<T> *node)
	{
	}
	ListNode<GraphNode<T> *> *operator[](int n)
	{
	    try
	    {
            return &(*list)[n];
	    }
		catch(std::invalid_argument e)
		{
			return NULL;
		}
	}
private:
	LinkList<GraphNode<T> *> *list;
};

template<class T>
class Graph
{
public:
	Graph()
	{
		vertex = new LinkList<GraphNode<T> *>();
		count = 0;
	}
	GraphNode<T> *addVertex(T d)
	{
		GraphNode<T> *node = new GraphNode<T>(d);
		vertex->addFromTail(node);
		count ++;
		return node;
	}
	void addLink(GraphNode<T> *node1, GraphNode<T> *node2)
	{
		node1->addLink(node2);
		node2->addLink(node1);
	}
	bool isLinked(GraphNode<T> *node1, GraphNode<T> *node2)
	{
		return node1->exist(node2);
	}
	GraphNode<T> *operator[](int n)
	{
		try
		{
			return (*vertex)[n].getData();
		}
		catch(std::invalid_argument e)
		{
			return NULL;
		}
	}

    void adjMatrix() {
        int **matrix = new int *[count];
        for (int i = 0; i < count; i++) {
            matrix[i] = new int[count];
            for (int j = 0; j < count; j++) {
                matrix[i][j] = 0;
            }
        }

        ListNode<GraphNode<T> *> *v = vertex->exist((*vertex)[0].getData());
        int i = 0;
        while (v != NULL) {
            ListNode<GraphNode<T> *> *e = (*(v->getData()))[0];
            while (e != NULL) {
                int j = 0;
                while (j < count && (*vertex)[j].getData() != e->getData()) {
                    j++;
                }
                if (j < count) {
                    matrix[i][j] = 1;
                }
                e = e->getNext();
            }
            v = v->getNext();
            i++;
        }

        for (int i = 0; i < count; i++) {
            for (int j = 0; j < count; j++) {
                cout << matrix[i][j];
            }
            cout << endl;
        }
    }

//Prob19.exe<week13/19.in>week13/19.out
    void adjList() {
        ListNode<GraphNode<T> *> *v = vertex->exist((*vertex)[0].getData());
        while (v != NULL) {
//            if(v->getData()->getData() - 1 == 45) {
//                cout<<"alert";
//            }
            vector<int> adjNodes;
            ListNode<GraphNode<T> *> *e = (*(v->getData()))[0];
            while (e != NULL) {
                if (find(adjNodes.begin(), adjNodes.end(), e->getData()->getData() - 1) == adjNodes.end()) {
                    adjNodes.push_back(e->getData()->getData() - 1);
                }
                e = e->getNext();
            }
            cout << v->getData()->getData() - 1 << ":";
            if (!adjNodes.empty()) {
                sort(adjNodes.begin(), adjNodes.end());
                for (int i = 0; i < adjNodes.size(); i++) {
                    cout << adjNodes[i] << " ";
                }

            }
            cout<<endl;
            v = v->getNext();
        }
    }

    void BFS(GraphNode<T> *node) {
        LinkList<GraphNode<T> *> *l = new LinkList<GraphNode<T> *>();
        l->addFromTail(node);
        ListNode<GraphNode<T> *> *cur = l->exist(node);
        while (cur != NULL) {
            std::cout << cur << " ";
            ListNode<GraphNode<T> *> *e = (*(cur->getData()))[0];
            while (e != NULL) {
                if (l->exist(e->getData()) == NULL)
                    l->addFromTail(e->getData());
                e = e->getNext();
            }
            cur = cur->getNext();
        }
    }

    void DFS(GraphNode<T> *node) {
        LinkList<GraphNode<T> *> *l = new LinkList<GraphNode<T> *>();
        l->addFromTail(node);
        ListNode<GraphNode<T> *> *cur = l->exist(node);
        while (cur != NULL) {
            std::cout << cur << " ";
            ListNode<GraphNode<T> *> *e = (*(cur->getData()))[0];
            while (e != NULL) {
                if (l->exist(e->getData()) == NULL)
                    l->addAfter(cur, e->getData());
                e = e->getNext();
            }
            cur = cur->getNext();
        }
    }

private:
    LinkList<GraphNode<T> *> *vertex;
    int count;
};

int main() {
    Graph<int> *g = new Graph<int>();
    LinkList<GraphNode<int> *> *node = new LinkList<GraphNode<int> *>();
    int j, k, s, a, b, n;
    scanf("%d", &s);
//    s = 3;
    srand(s);
    n = rand() % 50;
//    n = 50;
    for (j = 0; j < n; j++)
        node->addFromTail(g->addVertex(j + 1));
    k = rand() % 100;
    for (j = 0; j < k; j++) {
        a = rand() % n;
        b = rand() % n;
        g->addLink(((*node)[a]).getData(), ((*node)[b]).getData());
    }
    g->adjMatrix();
    g->adjList();
    return 0;
}
