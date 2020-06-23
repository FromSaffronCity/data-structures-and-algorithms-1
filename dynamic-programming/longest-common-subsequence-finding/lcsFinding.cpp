#include<iostream>
#include<string>

using namespace std;


/* "MyVector" Data Container class */

class MyVector {
    int size;
    int capacity;
    char* array;

    void expand();

public:
    MyVector();
    ~MyVector();

    void push(char);
    char pop();
    int getSize() const;
};

MyVector::MyVector() {
    size = 0;
    capacity = 2;
    array = new char[capacity];
}

MyVector::~MyVector() {
    delete[] array;
    array = NULL;
}

void MyVector::expand() {
    capacity *= 2;
    char* tempArray = new char[capacity];

    for(int i=0; i<size; i++) {
        tempArray[i] = array[i];
    }

    delete[] array;
    array = tempArray;
    return ;
}

void MyVector::push(char character) {
    if(size == capacity) {
        expand();
    }

    array[size++] = character;
    return ;
}

char MyVector::pop() {
    if(size < 1) {
        return '\0';
    }

    return array[--size];
}

int MyVector::getSize() const {
    return size;
}




/* Function Prototype for finding LCS of given two strings */

void findLCS(string, string);




/* main function */

int main() {
    string string1, string2;  // objects of string class

    getline(cin, string1);
    getline(cin, string2);

    findLCS(string1, string2);

    return 0;
}




/* function definition for finding LCS of given two strings */

void findLCS(string string1, string string2) {
    // for tabulation to memoize LCS
    int row = string1.length() + 1;
    int column = string2.length() + 1;

    int table[row][column];

    // creating the table - done in O(mn) time
    for(int i=0; i<row; i++) {
        for(int j=0; j<column; j++) {
            if(i==0 || j==0) {
                table[i][j] = 0;
            }
            else if(string1[i-1] == string2[j-1]) {
                table[i][j] = 1 + table[i-1][j-1];
            }
            else {
                table[i][j] = (table[i][j-1] > table[i-1][j])? table[i][j-1]: table[i-1][j];
            }
        }
    }

    // here, table[row-1][column-1] contains the length of LCS

    // NOTICE: printing LCS - done in O(m+n) time
    MyVector vector;

    row--;
    column--;

    while(row>0 && column>0) {
        // starting from the bottom right corner of table
        if(string1[row-1] == string2[column-1]) {
            vector.push(string1[row-1]);

            row--;
            column--;
        }
        else {
            (table[row-1][column] > table[row][column-1]) ? row-- : column--;
        }
    }

    // output
    int length = vector.getSize();

    cout << "\nObtained LCS: ";

    while(vector.getSize() > 0) {
        cout << vector.pop();
    }

    cout << "\nLength of LCS: " << length << endl;

    return ;
}
