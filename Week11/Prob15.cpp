//
// Created by LINBEI on 11/20/2023.
//
#include <iostream>
#include <vector>

using namespace std;

template<class T>
class MaxHeap {
private:
    vector<T> heap;

    void heapify_up(int i) {
        while (i != 0 && heap[parent(i)] < heap[i]) {
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }

    void heapify_down(int i) {
        int left = left_child(i);
        int right = right_child(i);
        int largest = i;

        if (left < count() && heap[left] > heap[i])
            largest = left;

        if (right < count() && heap[right] > heap[largest])
            largest = right;

        if (largest != i) {
            swap(heap[i], heap[largest]);
            heapify_down(largest);
        }
    }

    int parent(int i) { return (i - 1) / 2; }

    int left_child(int i) { return 2 * i + 1; }

    int right_child(int i) { return 2 * i + 2; }

public:
    //Constructing a empty heap.
    MaxHeap() {}

    //To add an element to the heap.
    void insert(T key) {
        heap.push_back(key);
        int index = count() - 1;
        heapify_up(index);
    }

    //To remove the root element in the heap and return it.
    T extract() {
        if (count() == 0)
            throw out_of_range("Heap is empty");

        T root = heap.front();
        heap[0] = heap.back();
        heap.pop_back();

        heapify_down(0);

        return root;
    }

    //Return the number of element int the heap.
    int count() {
        return heap.size();
    }
};