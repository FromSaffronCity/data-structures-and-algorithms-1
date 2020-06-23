#include<iostream>

using namespace std;


/* MergeSort: Function Prototypes */

void mergeSort(int* array, int start, int end);
void merge(int* array, int start, int mid, int end);


/* main function */

int main() {
    int number;
    cin >> number;

    int* array = new int[number];

    for(int i=0; i<number; i++) {
        cin >> array[i];
    }

    mergeSort(array, 0, number-1);  /* Merge Sort */

    cout << endl;

    for(int i=0; i<number; i++) {
        cout << array[i] << " ";
    }

    cout << endl;

    return 0;
}


/* MergeSort: Function Definitions */

void mergeSort(int* array, int start, int end) {
    if(start < end) {
        int mid = (start+end)/2;

        mergeSort(array, start, mid);
        mergeSort(array, mid+1, end);

        merge(array, start, mid, end);
    }

    return ;
}

void merge(int* array, int start, int mid, int end) {
    int amount1 = mid - start + 1;
    int amount2 = end - mid;

    int* tempArray1 = new int[amount1];
    int* tempArray2 = new int[amount2];

    for(int i=0; i<amount1; i++) {
        tempArray1[i] = array[start+i];
    }

    for(int i=0; i<amount2; i++) {
        tempArray2[i] = array[mid+1+i];
    }

    int index1, index2, indexMerged;
    index1 = index2 = 0;
    indexMerged = start;

    /* sorting in ascending order of integer value */
    while(index1<amount1 && index2<amount2) {
        if(tempArray1[index1] < tempArray2[index2]) {
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
