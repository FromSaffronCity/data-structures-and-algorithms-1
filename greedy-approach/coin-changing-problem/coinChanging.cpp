#include<iostream>

using namespace std;


struct Note {
    double denomination;
    int taken;
};


/* MergeSort prototypes */

void mergeSort(Note* array, int start, int end);
void merge(Note* array, int start, int mid, int end);


/* main function */

int main() {
    int number;
    double amount;

    cin >> number;

    if(number < 1) {
        cout << "Invalid Input" << endl;
        return 0;
    }

    Note array[number];  /* available notes */

    for(int i=0; i<number; i++) {
        cin >> array[i].denomination;

        array[i].taken = 0;
    }

    cin >> amount;

    mergeSort(array, 0, number-1);  /* Merge Sort */

    int total = 0;

    for(int i=0; i<number && amount>0; i++) {
        array[i].taken = (int) amount/array[i].denomination;
        amount -= array[i].taken*array[i].denomination;

        total += array[i].taken;
    }

    cout << "\n\n" << total << endl;

    for(int i=0; i<number; i++) {
        if(array[i].taken != 0) {
            cout << array[i].denomination << " " << array[i].taken << endl;
        }
    }

    return 0;
}


/* MergeSort definitions */

void mergeSort(Note* array, int start, int end) {
    if(start < end) {
        int mid = (start+end)/2;

        mergeSort(array, start, mid);
        mergeSort(array, mid+1, end);

        merge(array, start, mid, end);
    }

    return ;
}


void merge(Note* array, int start, int mid, int end) {
    int amount1 = mid - start + 1;
    int amount2 = end - mid;

    Note* tempArray1 = new Note[amount1];
    Note* tempArray2 = new Note[amount2];

    for(int i=0; i<amount1; i++) {
        tempArray1[i] = array[start+i];
    }

    for(int i=0; i<amount2; i++) {
        tempArray2[i] = array[mid+1+i];
    }

    int index1, index2, indexMerged;
    index1 = index2 = 0;
    indexMerged = start;

    /* sorting in descending order of denomination of notes */
    while(index1<amount1 && index2<amount2) {
        if(tempArray1[index1].denomination > tempArray2[index2].denomination) {
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
