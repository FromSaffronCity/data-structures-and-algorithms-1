#include<iostream>

using namespace std;


/* Node Class */

class Node {
    int keyValue;
    int index;

public:
    Node();
    Node(int);
    ~Node();

    void setValue(int);
    void setIndex(int);

    int getValue() const;
    int getIndex() const;

    int getParent() const;
    int getLeft() const;
    int getRight() const;
};


Node::Node() {
    keyValue = 0;
    index = -1;
}

Node::Node(int keyValue) {
    this->keyValue = keyValue;
    this->index = -1;
}

Node::~Node() {
    keyValue = 0;
    index = -1;
}

void Node::setValue(int keyValue) {
    this->keyValue = keyValue;
}

void Node::setIndex(int index) {
    this->index = index;
}

int Node::getValue() const {
    return keyValue;
}

int Node::getIndex() const {
    return index;
}

int Node::getParent() const {
    return (index-1)/2;
}

int Node::getLeft() const {
    return 2*index+1;
}

int Node::getRight() const {
    return 2*index+2;
}




/* MaxHeap Class */

class MaxHeap {
    int size;
    int capacity;
    Node* array;

    /* private member functions */
    void expand();  // additional
    void destroyHeap();

    void createHeap();  // create operation
    void heapify();

    void siftUp(int);  // internal operations
    void siftDown(int);

public:
    MaxHeap();
    ~MaxHeap();

    int getSize() const;  // inspection operations
    bool isEmpty() const;

    Node findMax() const;  // basic operations
    void insert(Node);
    void deleteMax();
    Node extractMax();
    void replace(Node);  // NOTICE

    void deleteNode(int);  // internal operations
    void increaseKey(int, int);
    void decreaseKey(int, int);

    MaxHeap& mergeHeap(MaxHeap&);  // creation operation - NOTICE
    MaxHeap& meldHeap(MaxHeap&);

    void printHeap();  // additional operation
};


/* Definition of private member functions */

void MaxHeap::expand() {
    capacity = capacity*2;

    Node* tempArray = new Node[capacity];

    for(int i=0; i<size; i++) {
        tempArray[i] = array[i];
    }

    delete[] array;
    array = tempArray;

    return ;
}

void MaxHeap::destroyHeap() {
    delete[] array;

    size = 0;
    capacity = 2;
    array = NULL;

    return ;
}

void MaxHeap::createHeap() {
    array = new Node[capacity];
}

void MaxHeap::heapify() {
    for(int i=(size/2 - 1); i>=0; i--) {
        siftDown(i);
    }

    return ;
}

void MaxHeap::siftUp(int index) {
    if(array[index].getIndex() == 0) {
        return ;  // the node is root here
    }

    int parentIdx = array[index].getParent();

    if(array[parentIdx].getValue() < array[index].getValue()) {
        /* swapping parent and child */
        Node temp = array[index];
        array[index] = array[parentIdx];
        array[parentIdx] = temp;

        array[parentIdx].setIndex(parentIdx);  // NOTICE
        array[index].setIndex(index);

        siftUp(parentIdx);  // NOTICE
    }

    return ;
}

void MaxHeap::siftDown(int index) {
    int parentIdx = index;
    int leftIdx = array[index].getLeft();
    int rightIdx = array[index].getRight();

    if(leftIdx<size && array[leftIdx].getValue()>array[parentIdx].getValue()) {
        parentIdx = leftIdx;
    }

    if(rightIdx<size && array[rightIdx].getValue()>array[parentIdx].getValue()) {
        parentIdx = rightIdx;
    }

    if(parentIdx != index) {
        /* swapping parent and child */
        Node temp = array[index];
        array[index] = array[parentIdx];
        array[parentIdx] = temp;

        array[index].setIndex(index);
        array[parentIdx].setIndex(parentIdx);

        siftDown(parentIdx);  // NOTICE
    }

    return ;
}


/* Definition of public member functions */

MaxHeap::MaxHeap() {
    size = 0;
    capacity = 2;

    createHeap();
}

MaxHeap::~MaxHeap() {
    delete[] array;

    size = 0;
    capacity = 0;
    array = NULL;
}

int MaxHeap::getSize() const {
    return size;
}

bool MaxHeap::isEmpty() const {
    return (size == 0);
}

Node MaxHeap::findMax() const {
    if(size != 0) {
        return array[0];
    }
    else {
        return Node();  // returning an invalid Node
    }
}

void MaxHeap::insert(Node node) {
    if(array == NULL) {
        return ;  // invalid operation
    }

    if(size == capacity) {
        expand();
    }

    array[size] = node;
    array[size].setIndex(size);

    siftUp(size);  // NOTICE

    size++;
    return ;
}

void MaxHeap::deleteMax() {
    if(size == 0) {
        return ;  // empty heap
    }

    array[0] = array[size-1];
    array[0].setIndex(0);

    size--;
    siftDown(0);  // NOTICE

    return ;
}

Node MaxHeap::extractMax() {
    if(size == 0) {
        return Node();  // empty heap, so returning invalid node
    }

    Node maxNode = findMax();
    deleteMax();

    return maxNode;
}

void MaxHeap::replace(Node node) {
    if(size == 0) {
        return ;  // empty heap
    }

    array[0] = array[size-1];
    array[0].setIndex(0);
    array[size-1] = node;
    array[size-1].setIndex(size-1);

    heapify();  // NOTICE

    return;
}

void MaxHeap::deleteNode(int index) {
    if(index >= size) {
        return ;  // invalid operation
    }

    array[index] = array[size-1];
    array[index].setIndex(index);

    size--;
    siftDown(index);

    return ;
}

void MaxHeap::increaseKey(int index, int keyValue) {
    if(index >= size) {
        return ;  // invalid operation
    }

    if(array[index].getValue() >= keyValue) {
        return ;  // invalid operation
    }

    array[index].setValue(keyValue);
    siftUp(index);  // NOTICE

    return ;
}

void MaxHeap::decreaseKey(int index, int keyValue) {
    if(index >= size) {
        return ; // invalid operation
    }

    if(array[index].getValue() <= keyValue) {
        return ;  // invalid operation
    }

    array[index].setValue(keyValue);
    siftDown(index);  // NOTICE

    return ;
}

MaxHeap& MaxHeap::mergeHeap(MaxHeap& heap) {
    MaxHeap* newHeap = new MaxHeap;

    for(int i=0; i<(this->size); i++) {
        newHeap->insert(this->array[i]);
    }

    for(int i=0; i<(heap.size); i++) {
        newHeap->insert(heap.array[i]);  // NOTICE
    }

    return *newHeap;
}

MaxHeap& MaxHeap::meldHeap(MaxHeap& heap) {
    MaxHeap* newHeap = new MaxHeap;

    for(int i=0; i<(this->size); i++) {
        newHeap->insert(this->array[i]);
    }

    for(int i=0; i<(heap.size); i++) {
        newHeap->insert(heap.array[i]);  // NOTICE
    }

    this->destroyHeap();  // NOTICE
    heap.destroyHeap();

    return *newHeap;
}

void MaxHeap::printHeap() {
    cout << "\nKeys:";

    for(int i=0; i<size; i++) {
        cout << " " << array[i].getValue();
    }

    cout << endl;

    return ;
}




/* Main Function */

int main() {
    MaxHeap heap1, heap2;

    /* Basic Operation */

    heap1.insert(Node(2));
    heap1.insert(Node(1));
    heap1.insert(Node(5));
    heap1.insert(Node(9));
    heap1.insert(Node(7));

    heap1.printHeap();

    heap2.insert(Node(3));
    heap2.insert(Node(6));
    heap2.insert(Node(2));
    heap2.insert(Node(4));
    heap2.insert(Node(10));
    heap2.insert(Node(8));

    heap2.printHeap();

    cout << "\nroot of heap1 = " << heap1.findMax().getValue() << endl;
    heap1.deleteMax();
    cout << "\nroot of heap1 after deletion = " << heap1.findMax().getValue() << endl;

    cout << "\nextracted root of heap2 = " << heap2.extractMax().getValue() << endl;
    cout << "\nroot of heap2 after extraction = " << heap2.findMax().getValue() << endl;

    heap1.printHeap();

    heap2.replace(Node(13));
    heap2.printHeap();  // heap2 after replacement

    cout << "----------------------------------------" << endl;


    /* Inspection Operation */

    cout << "\nSize of heap1 = " << heap1.getSize() << endl;
    cout << "Size of heap2 = " << heap2.getSize() << endl;
    cout << "\nIs heap1 empty ? - " << heap1.isEmpty() << endl;
    cout << "Is heap2 empty ? - " << heap2.isEmpty() << endl;

    cout << "----------------------------------------" << endl;


    /* Internal Operation */

    heap1.printHeap();

    heap2.deleteNode(2);
    heap2.printHeap();  // heap2 after deletion

    heap1.increaseKey(1, 3);
    heap2.decreaseKey(1, 7);

    heap1.printHeap();  // after failed attempts
    heap2.printHeap();

    heap1.increaseKey(1, 8);
    heap2.decreaseKey(1, 5);

    heap1.printHeap();  // after successful attempts
    heap2.printHeap();

    cout << "----------------------------------------" << endl;


    /* Creation Operation */

    MaxHeap newHeap1 = heap1.mergeHeap(heap2);
    newHeap1.printHeap();

    MaxHeap newHeap2 = heap1.meldHeap(heap2);
    newHeap2.printHeap();

    heap1.printHeap();
    heap2.printHeap();


    return 0;
}
