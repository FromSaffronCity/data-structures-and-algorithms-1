#include<stdio.h>

#define NULL_VALUE -99999
#define SUCCESS_VALUE 99999


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

int main(void) {
    LinkedList ll;
    int choice, item;

    while(1) {
        printf("1. Insert item (First)\n2. Inset item (Last)\n3. Insert item (After)\n");
        printf("4. Delete item (First)\n5. Delete item\n");
        printf("6. Search item\n7. Get item at\n8. Print list\n9. exit\n");

        printf("\nEnter choice: ");
        scanf("%d",&choice);

        if(choice == 1) {
            printf("\nEnter item: ");
            scanf("%d", &item);

            ll.insertItem(item);
        }
        else if(choice == 2){
            printf("\nEnter item: ");
            scanf("%d", &item);

            ll.insertLast(item);
        }
        else if(choice == 3) {
            int oldItem;

            printf("\nEnter oldItem: ");
            scanf("%d", &oldItem);
            printf("Enter newItem: ");
            scanf("%d", &item);

            ll.insertAfter(oldItem, item);
        }
        else if(choice == 4) {
            if(ll.deleteFirst() == NULL_VALUE) {
                printf("\nDeletion failed\n");
            }
            else {
                printf("\nDeletion successful\n");
            }
        }
        else if(choice == 5) {
            printf("\nEnter item: ");
            scanf("%d", &item);

            if(ll.deleteItem(item) == NULL_VALUE) {
                printf("\nDeletion failed\n");
            }
            else {
                printf("\nDeletion successful\n");
            }
        }
        else if(choice == 6) {
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
        else if(choice == 7) {
            int position;

            printf("\nEnter position: ");
            scanf("%d", &position);

            ListNode* returnNode = ll.getItemAt(position);

            if(returnNode->item != NULL_VALUE) {
                printf("\nItem found: %d\n", returnNode->item);
            }
            else {
                printf("\nItem not found\n");
            }
        }
        else if(choice == 8) {
            ll.printList();
        }
        else if(choice == 9) {
            break;
        }
        else {
            printf("\nInvalid choice\n");
        }

        printf("\n---------------------------------------------\n\n");
    }

    return 0;
}
