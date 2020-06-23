#include<iostream>

using namespace std;


struct Customer {
    int serviceTime;
    int serial;
};


/* MergeSort prototypes */

void mergeSort(Customer* array, int start, int end);
void merge(Customer* array, int start, int mid, int end);


/* main function */

int main() {
    int number;
    cin >> number;

    Customer array[number];

    for(int i=0; i<number; i++) {
        cin >> array[i].serviceTime;

        array[i].serial = i+1;
    }

    mergeSort(array, 0, number-1);  /* merge sorting */

    cout << "\n" << endl;

    for(int i=0; i<number; i++) {
        cout << array[i].serial << " ";
    }

    cout << endl;

    return 0;
}


/* MergeSort Definitions */

void mergeSort(Customer* array, int start, int end) {
    if(start < end) {
        int mid = (start+end)/2;

        mergeSort(array, start, mid);
        mergeSort(array, mid+1, end);

        merge(array, start, mid, end);
    }

    return ;
}


void merge(Customer* array, int start, int mid, int end) {
    int amount1 = mid - start + 1;
    int amount2 = end - mid;

    Customer* tempArray1 = new Customer[amount1];
    Customer* tempArray2 = new Customer[amount2];

    for(int i=0; i<amount1; i++) {
        tempArray1[i] = array[start+i];
    }

    for(int i=0; i<amount2; i++) {
        tempArray2[i] = array[mid+1+i];
    }

    int index1, index2, indexMerged;
    index1 = index2 = 0;
    indexMerged = start;

    /* sorting in ascending order of serviceTime */
    while(index1<amount1 && index2<amount2) {
        if(tempArray1[index1].serviceTime <= tempArray2[index2].serviceTime) {
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


