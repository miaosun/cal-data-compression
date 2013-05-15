//MinPriorityQueue.cpp

#include <cstdlib>
#include <iostream>
#include "MinPriorityQueue.h"

using namespace std;

template<class T> Q<T>::Q(int s) {
    array_size = s;
    heap_size = -1;
    A = new T*[s];
}

template<class T> Q<T>::~Q() {
    delete A;
}

template<class T> bool Q<T>::isEmpty() {
    return heap_size < 0;
}

template<class T> bool Q<T>::isFull() {
    return heap_size >= array_size - 1;
}

template<class T> T** Q<T>::getArray() {
    return A;
}

template<class T> int Q<T>::getArraySize() {
    return array_size;
}

template<class T> T* Q<T>::minimum() {
    return A[0];
}

template<class T> int Q<T>::left(int i) {
    return 2 * (i + 1) - 1;
}

template<class T> int Q<T>::right(int i) {
    return 2 * (i + 1);
}

template<class T> int Q<T>::parent(int i) {
    return max((i + 1) / 2 - 1, 0);
}

template<class T> T* Q<T>::extractMin() {
    if (isEmpty()) {
        cout << "Underflow...\n";
        T* t;
        return t;
    } else {
        T* min = A[0];
        A[0] = A[heap_size];
        heap_size--;
        minHeapify(0);
        return min;
    }
}

template<class T> void Q<T>::minHeapify(int i) {
    int l = left(i);
    int r = right(i);
    int smallest = i;
    if (l <= heap_size && ((*(A[l])) < (*(A[i])))) {
        smallest = l;
    }
    if (r <= heap_size && ((*(A[r])) < (*(A[smallest])))) {
        smallest = r;
    }
    if (smallest != i) {
        T* t = A[i];
        A[i] = A[smallest];
        A[smallest] = t;
        minHeapify(smallest);
    }
}

template<class T> bool Q<T>::insert(T* key) {
    if (isFull()) {
        cout << "Overflow...\n";
        return false;
    } else {
        heap_size++;
        decreaseKey(heap_size, key);
        return true;
    }
}

template<class T> void Q<T>::decreaseKey(int i, T* key) {
    A[i] = key;
    while ((i > 0) && ((*(A[parent(i)])) > (*(A[i])))) {
        T* t = A[i];
        A[i] = A[parent(i)];
        A[parent(i)] = t;
        i = parent(i);
    }
}