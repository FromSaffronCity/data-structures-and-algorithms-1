#include<stdio.h>

#define NULL_VALUE -99999
#define SUCCESS_VALUE 99999


class ListNode {

public:
    int item;
    ListNode* next;
    ListNode* previous;
};


class LinkedListDoubly {

    ListNode* head;
    ListNode* tail;
    int length;

public:

    LinkedListDoubly() {
        head = tail = NULL;  // initially set to NULL
        length = 0;
    }

    int getLength() const {
        return length;
    }

    int insertFirst(int item) {
        // insert at the beginning

        ListNode* newNode = new ListNode();
        newNode->item = item;

        newNode->next = head;
        newNode->previous = NULL;

        if(head == NULL) {
            // inserting the first item
            head = tail = newNode;
        }
        else {
            head->previous = newNode;
            head = newNode;
        }

        length++;
        return SUCCESS_VALUE ;
    }

    ListNode* searchItem(int item) const {
        ListNode* temp = head; // start at the beginning

        while(temp != NULL) {
            if (temp->item == item) {
                return temp;
            }

            temp = temp->next ; // move to next node
        }

        return NULL;
    }

    void printListForward() const {
        ListNode* temp = head;

        while(temp != NULL) {
            printf("%d->", temp->item);
            temp = temp->next;
        }

        printf("\nLength: %d\n", length);
    }

    //------------write code for the functions below-----------
    int insertLast(int item) {
        ListNode* newNode = new ListNode();

        newNode->item = item;
        newNode->next = NULL;
        newNode->previous = tail;

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

    int deleteLast() {
        if(tail == NULL) {
            return NULL_VALUE; // List is empty
        }

        ListNode* temp = tail;  /*NOTICE*/

        if(head == tail) {
            // only one element left

            head = tail = NULL;
        }
        else {
            // containing more than one element

            tail->previous->next = NULL;
            tail = tail->previous;
        }

        delete[] temp;  /*IMPORTANT*/
        length--;
        return SUCCESS_VALUE;
    }

    void printListBackward() const {
        ListNode* temp = tail;

        while(temp != NULL) {
            printf("%d->", temp->item);
            temp = temp->previous;
        }

        printf("\nLength: %d\n", length);
    }

    /*ADDED*/
    ~LinkedListDoubly() {
        while(length != 0) {
            deleteLast();
        }
    }
};


int main(void) {
    LinkedListDoubly ll;
    int choice, item;

    while(1) {
        printf("1. Insert item (First)\n2. Inset item (Last)\n");
        printf("3. Delete item (Last)\n");
        printf("4. Search item\n5. Print list forward\n6. Print list backward\n7. exit\n");

        printf("\nEnter choice: ");
        scanf("%d",&choice);

        if(choice == 1) {
            printf("\nEnter item: ");
            scanf("%d", &item);

            ll.insertFirst(item);
        }
        else if(choice == 2){
            printf("\nEnter item: ");
            scanf("%d", &item);

            ll.insertLast(item);
        }
        else if(choice == 3) {
            if(ll.deleteLast() == NULL_VALUE) {
                printf("\nDeletion failed\n");
            }
            else {
                printf("\nDeletion successful\n");
            }
        }
        else if(choice == 4) {
            printf("\nEnter item: ");
            scanf("%d", &item);

            ListNode* returnNode = ll.searchItem(item);

            if(returnNode != NULL) {
                printf("\nItem found\n");
            }
            else {
                printf("\nItem not found\n");
            }
        }
        else if(choice == 5) {
            ll.printListForward();
        }
        else if(choice == 6) {
            ll.printListBackward();
        }
        else if(choice == 7) {
            break;
        }
        else {
            printf("\nInvalid choice\n");
        }

        printf("\n---------------------------------------------\n\n");
    }

    return 0;
}
