#include<stdio.h>
#include<stdlib.h>

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

    /* Online 2 */

    bool sort() {
        if(length == 0) {
            return false;
        }

        ListNode* temp1 = head;
        ListNode* temp2 = NULL;

        while(temp1 != tail) {
            temp2 = temp1->next;

            while(temp2 != NULL) {
                /* NOTICE */
                if(temp1->item > temp2->item) {
                    /* Sorintg only item, not node */
                    temp1->item = temp1->item ^ temp2->item;
                    temp2->item = temp1->item ^ temp2->item;
                    temp1->item = temp1->item ^ temp2->item;
                }

                temp2 = temp2->next;
            }

            temp1 = temp1->next;
        }

        return true;
    }

    void insertSort(int item) {
        if(length == 0) {
            insertFirst(item);
            return ;
        }

        ListNode* newNode = new ListNode();
        newNode->item = item;

        ListNode* temp = head;

        while(temp != NULL) {
            if(newNode->item <= temp->item) {
                /* Problem */
                newNode->previous = temp->previous;
                newNode->next = temp;

                if(temp == head) {
                    head = newNode;
                    temp->previous = newNode;
                }
                else {
                    temp->previous->next = newNode;
                    temp->previous = newNode;
                }

                break;
            }
            if(temp == tail) {
                temp->next = newNode;
                newNode->previous = temp;
                newNode->next = NULL;
                tail = newNode;

                break;
            }

            temp = temp->next;
        }

        length++;
        return ;
    }

    bool mergeList(LinkedListDoubly& list) {
        /* NOTICE - reference accepted as argument */

        if(this->length == 0 || list.length == 0) {
            return false;
        }

        this->tail->next = list.head;
        list.head->previous = this->tail;

        this->tail = list.tail;
        this->length+=list.length;

        sort();
        return true;
    }
};


int main(void) {
    LinkedListDoubly listObj;

    /* taks 1 */
    for(int i = 1; i <= 10; i++) {
        listObj.insertFirst(rand()%10+2);
    }

    listObj.printListForward();
    printf("\n");

    /* task 2 */
    listObj.sort();
    listObj.printListForward();
    printf("\n\n");

    /* task 3 */
    LinkedListDoubly listObj2;

    for(int i = 1; i <= 10; i++) {
        listObj2.insertFirst(rand()%10+2);
    }

    listObj2.printListForward();
    printf("\n");

    listObj2.sort();
    listObj2.printListForward();
    printf("\n\n");

    /* task 4 */
    listObj.mergeList(listObj2);
    listObj.printListForward();
    printf("\n\n");

    /* task 5 */
    listObj.insertSort(1);
    listObj.printListForward();
    printf("\n");


    listObj.insertSort(5);
    listObj.printListForward();
    printf("\n");


    listObj.insertSort(19);
    listObj.printListForward();
    printf("\n");


    return 0;
}
