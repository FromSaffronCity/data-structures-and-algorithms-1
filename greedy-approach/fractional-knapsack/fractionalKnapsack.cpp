#include<iostream>

using namespace std;


struct Item {
    int itemNumber;
    int value;
    int weight;
    double rate;  /* value/weight */
    int itemTaken;
};


/* Function Prototypes for Merge Sort */

void mergeSort(Item* array, int start, int end);
void merge(Item* array, int start, int mid, int end);


/* main function */

int main() {
    int amount, capacity;
    cin >> amount;

    if(amount < 1) {
        cout << "Invalid Input" << endl;
        return 0;
    }

    Item array[amount];

    for(int i=0; i<amount; i++) {
        cin >> array[i].weight >> array[i].value;

        array[i].itemNumber = i+1;
        array[i].rate = (double) array[i].value/array[i].weight;
        array[i].itemTaken = 0;
    }

    cin >> capacity;


    mergeSort(array, 0, amount-1);  /* Merge Sort - NOTICE */


    double totalValue = 0;

    for(int i=0; i<amount && capacity>0; i++) {
        if(array[i].weight <= capacity) {
            totalValue += array[i].value;
            capacity -= array[i].weight;

            array[i].itemTaken = array[i].weight;
        }
        else {
            totalValue += array[i].rate*capacity;
            array[i].itemTaken = capacity;

            capacity -= capacity;
        }
    }

    cout << "\n\n" << totalValue << endl;

    for(int i=0; i<amount; i++) {
        if(array[i].itemTaken > 0) {
            cout << array[i].itemNumber << " " << array[i].itemTaken << " ";
            cout << array[i].rate*array[i].itemTaken << endl;
        }
        else {
            break;
        }
    }

    return 0;
}


/* Function Definitions for Merge Sort */

void mergeSort(Item* array, int start, int end) {
    if(start < end) {
        int mid = (start+end)/2;

        mergeSort(array, start, mid);
        mergeSort(array, mid+1, end);

        merge(array, start, mid, end);
    }

    return ;
}


void merge(Item* array, int start, int mid, int end) {
    int amount1 = mid - start + 1;
    int amount2 = end - mid;

    Item* tempArray1 = new Item[amount1];
    Item* tempArray2 = new Item[amount2];

    for(int i=0; i<amount1; i++) {
        tempArray1[i] = array[start+i];
    }

    for(int i=0; i<amount2; i++) {
        tempArray2[i] = array[mid+1+i];
    }

    int index1, index2, indexMerged;
    index1 = index2 = 0;
    indexMerged = start;

    /* sorting in descending order of rate */
    while(index1<amount1 && index2<amount2) {
        if(tempArray1[index1].rate > tempArray2[index2].rate) {
            array[indexMerged++] = tempArray1[index1++];
        }
        else {
            array[indexMerged++] = tempArray2[index2++];
        }
    }

    while(index1 < amount1) {
        array[indexMerged++] = tempArray1[index1++];
    }

    while(index2 < amount2) {
        array[indexMerged++] = tempArray2[index2++];
    }

    delete[] tempArray1;
    delete[] tempArray2;

    return ;
}
