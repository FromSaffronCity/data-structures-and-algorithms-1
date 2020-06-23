#include<iostream>

#define MAX(X,Y) (X>Y)?X:Y

using namespace std;

struct Item {
    int value;
    int weight;
    bool isTaken;
};


void binaryKnapsack(Item*, int, int);


int main() {
    int number, capacity;

    cin >> number;

    if(number < 1) {
        cout << "Invalid Input" << endl;
        return 0;
    }

    Item* array = new Item[number];

    for(int i=0; i<number; i++) {
        cin >> array[i].value >> array[i].weight;
        array[i].isTaken = false;
    }

    cin >> capacity;

    binaryKnapsack(array, number, capacity);  // main part

    delete[] array;
    return 0;
}


void binaryKnapsack(Item* array, int number, int capacity) {
    int table[number+1][capacity+1];  // table holding total value of knapsack

    // tabulation process: O(n.w) time required
    for(int i=0; i<=number; i++) {
        for(int j=0; j<=capacity; j++) {
            if(i==0 || j==0) {
                table[i][j] = 0;
            }
            else {
                if(array[i-1].weight <= j) {
                    table[i][j] = MAX(table[i-1][j], array[i-1].value+table[i-1][j-array[i-1].weight]);  // NOTICE
                }
                else {
                    table[i][j] = table[i-1][j];
                }
            }
        }
    }

    // item taken finding: O(n) time required
    int i = number;
    int j = capacity;

    while(i > 0 && j > 0) {
        if(table[i][j] == table[i-1][j]) {
            i--;
        }
        else {
            array[i-1].isTaken = true;

            j -= array[i-1].weight;
            i--;
        }
    }

    // printing
    cout << "\nItem taken: ";

    for(int count=0; count<number; count++) {
        if(array[count].isTaken == true) {
            cout << count+1 << " ";
        }
    }

    cout << "\nTotal Value in Knapsack: " << table[number][capacity] << endl;

    return ;
}
