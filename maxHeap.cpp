#include <iostream>
#include <vector>
// priority queue

using namespace std;

class MaxHeap
{
private:
    vector<int> heap;

    void heapifyUp(int index);
    void heapifyDown(int index);

public:
    MaxHeap() = default; // Default constructor

    void insert(int value);
    int pop();
    int getMax() const;
    bool empty() const;
};

void MaxHeap::heapifyUp(int index)
{
    if (index == 0)
        return;

    int parentIndex = (index - 1) / 2;
    if (heap[parentIndex] < heap[index])
    {
        swap(heap[parentIndex], heap[index]);
        heapifyUp(parentIndex);
    }
}

void MaxHeap::heapifyDown(int index)
{
    int leftChildIndex = 2 * index + 1;
    int rightChildIndex = 2 * index + 2;
    int largestIndex = index;

    if (leftChildIndex < heap.size() && heap[leftChildIndex] > heap[largestIndex])
        largestIndex = leftChildIndex;

    if (rightChildIndex < heap.size() && heap[rightChildIndex] > heap[largestIndex])
        largestIndex = rightChildIndex;

    if (largestIndex != index)
    {
        swap(heap[index], heap[largestIndex]);
        heapifyDown(largestIndex);
    }
}

void MaxHeap::insert(int value)
{
    heap.push_back(value);
    heapifyUp(heap.size() - 1);
}

int MaxHeap::pop()
{
    if (heap.empty())
        throw runtime_error("Heap is empty");

    int maxElement = heap[0];
    swap(heap[0], heap[heap.size() - 1]);
    heap.pop_back();
    heapifyDown(0);

    return maxElement;
}

int MaxHeap::getMax() const
{
    if (heap.empty())
        throw runtime_error("Heap is empty");

    return heap[0];
}

bool MaxHeap::empty() const
{
    return heap.empty();
}

int main()
{
    MaxHeap pq;

    pq.insert(10);
    pq.insert(20);
    pq.insert(15);
    pq.insert(30);

    cout << "Max Element: " << pq.getMax() << endl;

    int maxElement = pq.pop();

    cout << "Extracted Max Element: " << maxElement << endl;
    cout << "Max Element after extraction: " << pq.getMax() << endl;

    return 0;
}