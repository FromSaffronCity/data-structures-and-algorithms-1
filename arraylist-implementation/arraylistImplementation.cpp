/* Preprocessor Directives */

#include<iostream>
#include<string>
#include<cstdlib>
#include<conio.h> /* Only for getch() function */

using namespace std;


/* Macros */

#define LIST_INIT_SIZE 2
#define NULL_VALUE -99999
#define SUCCESS_VALUE 99999


/* ArrayList Class below */

class ArrayList {
    int* list;
    int listMaxSize,length;

public:

    ArrayList() { initializeList(); }

    int* getList() const { return this -> list; }
    int getLength() const { return this -> length; }
    int getListMaxSize() const { return this -> listMaxSize; }
    int getLastItem() const { return this -> list[(this -> length) - 1]; }

    void initializeList();  /* Basics */
    int searchItem(int);

    int expandList();  /* Insertion */
    int insertItem(int);
    int insertItemAt(int, int);

    int shrink();  /* deletion */
    int deleteItemAt(int);
    int deleteItem(int);
    int deleteLast();
    int deleteAllItems();
    int clear();
    int deleteAll();

    void printList(); /* Properties of ArrayList */

    ~ArrayList() { delete[] this -> list; }
};


/* Functions */

/* Basics */

void ArrayList::initializeList() {
	this -> listMaxSize = LIST_INIT_SIZE;
	this -> length = 0;
	this -> list = new int[listMaxSize];
}

int ArrayList::searchItem(int item) {
	for(int i=0; i<this -> length; i++) {
		if(this -> list[i] == item) {
            return i;
		}
	}

	return NULL_VALUE;
}


/* Insertions */

/* Added */
int ArrayList::expandList() {
    this -> listMaxSize *= 2;
    int* tempList = new int[this -> listMaxSize];

    for(int i=0; i<this -> length; i++) {
        tempList[i] = this -> list[i];
    }

    delete[] this -> list;
    this -> list = tempList;

    return SUCCESS_VALUE;
}

int ArrayList::insertItem(int newItem) {
    if(this -> list == NULL) {
        this -> list = new int[this -> listMaxSize];
    }

    if(this -> length == this -> listMaxSize) {
		expandList();
	}

	this -> list[length] = newItem; /* store new item */
	this -> length++;
	return SUCCESS_VALUE;
}

int ArrayList::insertItemAt(int position, int newItem) {
    if(position >= this -> length) {
        cout << "\n" << "Insertion failed" << endl;  /* IMPORTANT */
        return NULL_VALUE;
    }

    if(this -> length == this -> listMaxSize) {
		expandList();
	}

    this -> list[this -> length] = this -> list[position];  /* Shifting only one item */
    this -> list[position] = newItem;
    this -> length++;
    return SUCCESS_VALUE;
}


/* Deletion */

int ArrayList::shrink() {
    if(this -> listMaxSize == LIST_INIT_SIZE) {
        return NULL_VALUE;
    }

    this -> listMaxSize /= 2;
    int* tempList = new int[this -> listMaxSize];

    for(int i=0; i<this -> length; i++) {
        tempList[i] = this -> list[i];
    }

    delete[] this -> list;
    this -> list = tempList;

    return SUCCESS_VALUE;
}

int ArrayList::deleteItemAt(int position) {
    if(position >= this -> length) {
        cout << "\n" << "position not available" << endl;
        return NULL_VALUE;  /* NOTICE */
    }

	this -> list[position] = this -> list[this -> length-1];  /* NOTICE - Shifting the last item in the position */
	this -> length--;

	if(this -> length == this -> listMaxSize/2) {
        shrink();  /* Shrink feature */
	}

	return SUCCESS_VALUE ;
}

int ArrayList::deleteItem(int item) {
	int position;
	position = searchItem(item);

	if(position == NULL_VALUE) {
        cout << "\n" << "No such item found" << endl;
        return NULL_VALUE;
    }

	deleteItemAt(position);
	return SUCCESS_VALUE;
}

int ArrayList::deleteLast() {
    if(this -> length == 0) {
        cout << "\n" << "Deletion failed" << endl;
        return NULL_VALUE;
    }

    this -> length--;   /* IMPORTANT - concept of delete is just "length--" */

    if(this -> length == this -> listMaxSize/2) {
        shrink();  /* Shrink feature */
	}

    return SUCCESS_VALUE;
}

/* Added */
int ArrayList::deleteAllItems() {
    while(this -> length != 0) {
        this -> length--;

        if(this -> length == this -> listMaxSize/2) {
            shrink();  /* Shrink feature */
        }
    }

    return SUCCESS_VALUE;
}

int ArrayList::clear() {
    if(this -> length == 0) {
        cout << "\n" << "clear failed" << endl;
        return NULL_VALUE;
    }

    this -> deleteAllItems();  /* delete all items */
    delete[] this -> list;  /* memory deallocation */
    this -> list = NULL;  /* Not a dangling pointer, a NULL pointer */

    return SUCCESS_VALUE;
}

int ArrayList::deleteAll() {
    if(this -> length == 0) {
        cout << "\n" << "deleteAll failed" << endl;
        return NULL_VALUE;
    }

    deleteAllItems();  /* delete all items */
    return SUCCESS_VALUE;
}


/* Property of List */

void ArrayList::printList() {
    for(int i=0; i<this -> length; i++) {
        cout << this -> list[i] << " ";
    }

    cout << "\n\n" << "Current size: " << this -> listMaxSize << "\n" << "Current length: " << this -> length << endl;
}




/* main functions */

int main() {
    // for testing tasks 1-6

    int choice, item, position;
    ArrayList objAl;

    while(1) {
        system("cls");  /* for clearing console */

        /* Menu */
        cout << "1. Get current length" << "\n" << "2. Print list and other properties" << endl;
        cout << "3. Insert new item" << "\n" << "4. Insert new item at" << endl;
        cout << "5. Delete item at" << "\n" << "6. Delete item" << "\n" << "7. Delete last item" << endl;
        cout << "8. Clear list" << "\n" << "9. Delete all items" << "\n" << "10. exit" << endl;

        cout << "\n" << "Enter your choice: ";
        cin >> choice;

        if(choice == 1) {
            cout << "\nCurrent length(number of items): " << objAl.getLength() << endl;
        }
        else if(choice == 2) {
            cout << endl;
            objAl.printList();
        }
        else if(choice == 3) {
            cout << "\n" << "Enter new item: ";
            cin >> item;

            objAl.insertItem(item);
        }
        else if(choice == 4) {
            cout << "\n" << "Enter positon: ";
            cin >> position;
            cout << "\n" << "Enter new item: ";
            cin >> item;

            objAl.insertItemAt(position, item);
        }
        else if(choice == 5) {
            cout << "\n" << "Enter positon: ";
            cin >> position;

            objAl.deleteItemAt(position);
        }
        else if(choice == 6) {
            cout << "\n" << "Enter item to be deleted: ";
            cin >> item;

            objAl.deleteItem(item);
        }
        else if(choice == 7) {
            objAl.deleteLast();
        }
        else if(choice == 8) {
            objAl.clear();
        }
        else if(choice == 9) {
            objAl.deleteAll();
        }
        else if(choice == 10) {
            break;
        }
        else {
            cout << "\n" << "Invalid choice entered" << endl;
        }

        /* For a buffer */
        cout << "\n" << "Press Enter to continue";
        getch();  /* NOTICE !!! */
    }

    return 0;
}


int main(void) {
    // for task 7: postfix arithmetic expression evaluation
    ArrayList objAl;

    int operandOne, operandTwo;
    string input;

    cout << "Enter input: ";
    cin >> input;

    /* Step 3 */
    for(int i=0; i<input.length(); i++) {
        if(input[i] >= 48 && input[i] <= 57) {
            objAl.insertItem(input[i] - 48);
        }
        else {
            if(objAl.getLength() == 0 || objAl.getLength() == 1) {
                cout << "Invalid Input" << endl;
                return 0;
            }
            else {
                operandTwo = objAl.getLastItem();
                objAl.deleteLast();
                operandOne = objAl.getLastItem();
                objAl.deleteLast();

                if(input[i] == '+') {
                    objAl.insertItem(operandOne + operandTwo);
                }
                else if(input[i] == '-') {
                    objAl.insertItem(operandOne - operandTwo);
                }
                else if(input[i] == '*') {
                    objAl.insertItem(operandOne * operandTwo);
                }
                else {
                    if(operandTwo == 0) {
                        cout << "Invalid Input" << endl;
                        return 0;
                    }

                    objAl.insertItem(operandOne / operandTwo);
                }
            }
        }
    }

    /* Step 4 */
    if(objAl.getLength() == 1) {
        cout << "Output = " << objAl.getLastItem() << endl;
        objAl.deleteLast();
    }
    else {
        cout << "Invalid Input" << endl;
        objAl.deleteAll();
    }

    return 0;
}
