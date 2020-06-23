#include<stdio.h>

#define NULL_VALUE -99999
#define SUCCESS_VALUE 99999


/* ******************* LinkedList ********************** */

class ListNode {

public:
    int item;
    ListNode* next;
};


class LinkedList {

    ListNode* head;
    int length;  /*NOTICE*/

public:

    LinkedList() {
        head = NULL; // initially set to NULL
        length = 0;
    }

    int getLength() const {
        return length;
    }

    int insertItem(int item) {
        // insert at the beginning

        ListNode* newNode = new ListNode();  /*NOTICE - using .cpp here*/
        newNode->item = item;
        newNode->next = head; // point to previous first node
        head = newNode; // set list to point to newnode as this is now the first node

        length++;
        return SUCCESS_VALUE ;
    }

    int deleteItem(int item) {
        ListNode* temp;
        ListNode* previous;  /*NOTICE*/

        temp = head; // start at the beginning

        while(temp != NULL) {
            if (temp->item == item) {
                break;
            }

            previous = temp;
            temp = temp->next; // move to next node
        }

        if (temp == NULL){
            return NULL_VALUE;  // item not found to delete or list is empty
        }

        if (temp == head) {
            head = head->next;  // delete the first node
        }
        else {
            previous->next = temp->next;
        }

        delete[] temp;  /*IMPORTANT*/
        length--;
        return SUCCESS_VALUE;
    }


    ListNode* searchItem(int item) const {
        ListNode* temp = head; // start at the beginning

        while(temp != NULL) {
            if (temp->item == item) {
                return temp;
            }

            temp = temp->next; // move to next node
        }

        return NULL; // Not found
    }

    void printList() const {
        ListNode* temp = head; // start at the beginning

        while(temp != NULL) {
            printf("%d->", temp->item);
            temp = temp->next;
        }

        printf("\n");
        printf("Length: %d\n",length);
    }

    /*------------write code for the functions below-----------*/

    int insertLast(int item) {
        ListNode* temp;
        ListNode* newNode = new ListNode();

        newNode -> item = item;
        temp = head;

        if(temp == NULL) {
            // list is empty

            insertItem(item);
            return SUCCESS_VALUE;
        }

        while(temp->next != NULL) {
            temp = temp->next;
        }

        temp->next = newNode;
        newNode->next = NULL;

        length++;
        return SUCCESS_VALUE;
    }

    int insertAfter(int oldItem, int newItem) {
        ListNode* temp = searchItem(oldItem);

        if(temp == NULL) {
            printf("\nInsertion failed\n");
            return NULL_VALUE;
        }

        // insert newItem only after first occurence of oldItem

        ListNode* newNode = new ListNode();

        newNode->item = newItem;
        newNode->next = temp->next;
        temp->next = newNode;

        length++;
        return SUCCESS_VALUE;
    }

    ListNode* getItemAt(int position) const {
        if(position > length || position < 1) {
            ListNode* failNode = new ListNode();  /*NOTICE*/

            failNode->item = NULL_VALUE;
            failNode->next = NULL;

            return failNode;
        }

        ListNode* temp = head;

        for(int i=1; i<position; i++) {
            temp = temp->next;
        }

        return temp;
    }

    int deleteFirst() {
        return deleteItem(getItemAt(1) -> item);  /*NOTICE - IMPORTANT*/
    }


    ~LinkedList() {
        while(deleteFirst() != NULL_VALUE) {
            /*NOTHING here*/
        }
    }

};

/* ************************************************** */


class Stack {
    LinkedList ll;

public:

    Stack() {
        /*Nothing here*/
    }

    void push(int item) {
        ll.insertItem(item);
    }

    int pop() {
        ListNode* node = ll.getItemAt(1);

        ll.deleteFirst();
        return node->item;
    }

    /*ADDEDs*/
    void printStack() const {
        ll.printList();
    }

    ~Stack() {
        /*Nothing here*/
    }
};


int main(void) {
    Stack stackObj;
    int choice, item;

    while(1) {
        printf("1. Push\n2. Pop\n3. Print stack\n4. exit\n");

        printf("\nEnter choice: ");
        scanf("%d",&choice);

        if(choice == 1) {
            printf("\nEnter item: ");
            scanf("%d", &item);

            stackObj.push(item);
        }
        else if(choice == 2){
            item = stackObj.pop();

            if(item == NULL_VALUE) {
                printf("\nPop failed\n");
            }
            else {
                printf("\nPopped item: %d\n", item);
            }
        }
        else if(choice == 3) {
            stackObj.printStack();
        }
        else if(choice == 4) {
            break;
        }
        else {
            printf("\nInvalid choice\n");
        }

        printf("\n---------------------------------------------\n\n");
    }

    return 0;
}
