#include<stdio.h>

#define NULL_VALUE -99999
#define SUCCESS_VALUE 99999


/* ************ LinkedListWithTail ************** */

class ListNode {

public:
    int item;
    ListNode* next;
};


class LinkedListWithTail {

    ListNode* head;
    ListNode* tail;  /*EXTRA*/
    int length;

public:

    LinkedListWithTail() {
        head = tail = NULL;  // initially set to NULL
        length = 0;
    }

    int getLength() const {
        return length;
    }

    int insertItem(int item) {
        // insert at the beginning

        ListNode* newNode = new ListNode();
        newNode->item = item;
        newNode->next = head; // point to previous first node

        /*Handling tail below*/
        if(head == NULL) {
            head = tail = newNode;  /*IMPORTANT - only for the first item of the list*/
        }
        else {
            head = newNode; //set list to point to newnode as this is now the first node
        }

        length++;
        return SUCCESS_VALUE;
    }

    int deleteItem(int item) {
        ListNode* temp;
        ListNode* previous=NULL;

        temp = head; // start at the beginning

        while(temp != NULL) {
            if (temp->item == item) {
                break;
            }

            previous = temp;
            temp = temp->next; // move to next node
        }

        if(temp == NULL) {
            return NULL_VALUE; // item not found to delete or empty list
        }

        if(temp == head) {
            head = head->next; // delete the first node
        }
        else {
            previous->next = temp->next;
        }

        /*Handling tail below*/
        if(temp == tail) {
            tail = previous;
        }

        delete[] temp;
        length--;
        return SUCCESS_VALUE ;
    }

    ListNode* searchItem(int item) const {
        ListNode* temp = head; // start at the beginning

        while(temp != NULL) {
            if(temp->item == item) {
                return temp;
            }

            temp = temp->next; // move to next node
        }

        return NULL; // Not found
    }

    void printList() const {
        ListNode* temp = head;

        while(temp != NULL) {
            printf("%d->", temp->item);
            temp = temp->next;
        }

        printf("\n");
        printf("Length: %d\n",getLength());
    }

    //------------write code for the functions below-----------
    int insertLast(int item) {
        ListNode* newNode = new ListNode();
        newNode->item = item;
        newNode->next = NULL;

        if(tail == NULL) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }

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

    int deleteLast() {
        return deleteItem(getItemAt(length) -> item);  /*NOTICE - IMPORTANT*/

        /*Can't use tail pointer directly as we need a pointer pointing to previous node as well*/
    }

    // Added
    ~LinkedListWithTail() {
        while(deleteLast() != NULL_VALUE) {
            /*NOTHING here*/
        }
    }
};

/* ********************************************* */


class Queue {
    LinkedListWithTail ll;

public:
    Queue() {
        /* NOTHING here */
    }

    void enqueue(int item) {
        ll.insertLast(item);
    }

    int dequeue() {
        ListNode* node = ll.getItemAt(1);

        ll.deleteItem(node -> item);
        return node->item;
    }

    /* ADDEDs */
    void printQueue() const {
        ll.printList();
    }

    ~Queue() {
        /* NOTHING here */
    }
};


int main(void) {
    Queue queueObj;
    int choice, item;

    while(1) {
        printf("1. Enqueue\n2. Dequeue\n3. Print queue\n4. exit\n");

        printf("\nEnter choice: ");
        scanf("%d",&choice);

        if(choice == 1) {
            printf("\nEnter item: ");
            scanf("%d", &item);

            queueObj.enqueue(item);
        }
        else if(choice == 2){
            item = queueObj.dequeue();

            if(item == NULL_VALUE) {
                printf("\nDequeue failed\n");
            }
            else {
                printf("\nDequeued item: %d\n", item);
            }
        }
        else if(choice == 3) {
            queueObj.printQueue();
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
