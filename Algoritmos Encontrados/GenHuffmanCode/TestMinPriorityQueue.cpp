//TestMinPriorityQueue.cpp

#include "MinPriorityQueue.cpp"

using namespace std;

void testMinPQ() {
    Q<int> *q = new Q<int>(10);
    int x[] = {10, 5, 8, 15, 4, 20, 28, 33, 11, 3};
    for (int i = 0; i < 10; i++) {
        q->insert(&x[i]);
    }
    for (int i = 0; i < 10; i++) {
        cout << (*q->extractMin()) << ", ";
    }
}

int main(int argc, char** argv) {
    testMinPQ();
    return 0;
}

/*
Output

3, 4, 5, 8, 10, 11, 15, 20, 28, 33,
*/