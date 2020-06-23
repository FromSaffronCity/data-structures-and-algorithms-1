#include<iostream>

using namespace std;

int main() {
    int number;
    cin >> number;

    if(number < 1) {
        cout << "Invalid Input" << endl;
        return 0;
    }

    int* array = new int[number];

    for(int i=0; i<number; i++) {
        cin >> array[i];
    }

    /* Applying Kadane's Algorithm to find maximum subset (contiguous) array sum */

    int sum, max;
    sum = max = 0;

    for(int i=0; i<number; i++) {
        sum += array[i];

        if(sum < 0) {
            sum = 0;
        }

        if(max < sum) {
            max = sum;
        }
    }

    cout << "\n" << max << endl;

    /*
     *  if all the elements of the array are negative
     *  then the max will be zero
     *  that is, the subset will be empty
     */

    delete[] array;
    return 0;
}
