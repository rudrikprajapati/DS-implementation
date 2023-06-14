#include <iostream>
#include <vector>

using namespace std;

class MinHeap {
private:
    vector<int> heap;

    void heapifyUp(int index);
    void heapifyDown(int index);

public:
    MinHeap() = default; // Default constructor

    void insert(int value);
    int pop();
    int getMin() const;
    bool empty() const;
};

void MinHeap::heapifyUp(int index) {
    if (index == 0)
        return;

    int parentIndex = (index - 1) / 2;
    if (heap[parentIndex] > heap[index]) {
        swap(heap[parentIndex], heap[index]);
        heapifyUp(parentIndex);
    }
}

void MinHeap::heapifyDown(int index) {
    int leftChildIndex = 2 * index + 1;
    int rightChildIndex = 2 * index + 2;
    int smallestIndex = index;

    if (leftChildIndex < heap.size() && heap[leftChildIndex] < heap[smallestIndex])
        smallestIndex = leftChildIndex;

    if (rightChildIndex < heap.size() && heap[rightChildIndex] < heap[smallestIndex])
        smallestIndex = rightChildIndex;

    if (smallestIndex != index) {
        swap(heap[index], heap[smallestIndex]);
        heapifyDown(smallestIndex);
    }
}

void MinHeap::insert(int value) {
    heap.push_back(value);
    heapifyUp(heap.size() - 1);
}

int MinHeap::pop() {
    if (heap.empty())
        throw runtime_error("Heap is empty");

    int minElement = heap[0];
    swap(heap[0], heap[heap.size() - 1]);
    heap.pop_back();
    heapifyDown(0);

    return minElement;
}

int MinHeap::getMin() const {
    if (heap.empty())
        throw runtime_error("Heap is empty");

    return heap[0];
}

bool MinHeap::empty() const {
    return heap.empty();
}

int main() {
    MinHeap pq;

    pq.insert(30);
    pq.insert(20);
    pq.insert(10);
    pq.insert(15);

    cout << "Min Element: " << pq.getMin() << endl;

    int minElement = pq.pop();

    cout << "Extracted Min Element: " << minElement << endl;
    cout << "Min Element after extraction: " << pq.getMin() << endl;

    return 0;
}