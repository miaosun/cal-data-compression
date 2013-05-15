//Minimum Priority Queue Implemented Using Min-Heap in C++
//MinPriorityQueue.h

#ifndef MINPRIORITYQUEUE_H
#define MINPRIORITYQUEUE_H

template<class T> class Q {
    int array_size, heap_size;
    T** A; // pointer for the array    

public:
    Q(int s);
    ~Q();
    bool isEmpty();
    bool isFull();
    T** getArray();
    int getArraySize();
    T* minimum();
    T* extractMin();
    bool insert(T*);

private:
    int left(int i);
    int right(int i);
    int parent(int i);
    void decreaseKey(int, T*);
    void minHeapify(int);
};

#endif /* MINPRIORITYQUEUE_H */