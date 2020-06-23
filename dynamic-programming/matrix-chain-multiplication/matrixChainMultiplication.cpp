#include<iostream>

using namespace std;


/* Function Prototype for finding the minimum multiplications needed for given chain of matrices */

int findMin(int*, int);




/* main function */

int main() {
    int number;  // number of matrices in chain
    cin >> number;

    if(number < 1) {
        cout << "Invalid Input" << endl;
        return 0;
    }

    int* array = new int[++number];  // array containing the dimensions of matrices

    for(int i=0; i<number; i++) {
        cin >> array[i];
    }

    cout << "\nMinimum Multiplication: " << findMin(array, number) << endl;

    delete[] array;
    return 0;
}




/* Function Definition */

int findMin(int* array, int number) {
    // tabulation to memoize minimum multiplications
    int table[number][number];

    // assigning zero to each element in table in O(n^2) time
    for(int i=0; i<number; i++) {
        for(int j=0; j<number; j++) {
            table[i][j] = 0;
        }
    }

    // NOTICE - creating the table in O(n^3) time
    for(int length=2; length<number; length++) {
        // length = length of given matrix chain

        for(int row=1; row<(number - length + 1); row++) {
            int column = row + length - 1;
            table[row][column] = 999999;  // randomly chosen large value

            for(int i=row; i<column; i++) {
                int operation = table[row][i] + table[i+1][column] + array[row-1]*array[i]*array[column];

                table[row][column] = (table[row][column] < operation) ? table[row][column] : operation;
            }
        }
    }

    return table[1][number-1];  // returning the minimum multiplication needed for multiplying matrix 1 to n (= number-1)
}
