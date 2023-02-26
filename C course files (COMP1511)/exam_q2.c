#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct node {
    struct node *next;
    int          data;
};

int have_smalls(struct node *head1, struct node *head2);
struct node *read_list(void);

// DO NOT CHANGE THIS MAIN FUNCTION
int main(void) {
    // create two linked lists from user input
    struct node *head1 = read_list();
    struct node *head2 = read_list();

    int result = have_smalls(head1, head2);
    printf("%d\n", result);

    return 0;
}

// have_smalls should return 0 if neither list contains numbers less than ten.
// have_smalls should return 1 one list contains numbers less than ten, but the other doesn't.
// have_smalls should return 2 if both lists contain numbers less than ten.
int have_smalls(struct node *head1, struct node *head2) {

    // PUT YOUR CODE HERE (change the next line!)
    int lists_count = 0;
    
    struct node *current1 = head1;
    struct node *current2 = head2;
    
    if (current1 == NULL && current2 == NULL) {    
        return lists_count;
    }
    
    
    if ((current1->data) < 10) {
        lists_count++;
    } else {
        while (current1->next != NULL) {
            if (current1->data < 10) {
                lists_count++;
            } else {
                current1 = current1->next;
            }
        }
    }

    
    if ((current2->data) < 10) {
        lists_count++;
    } else {
        while (current2->next != NULL) {
            if (current2->data < 10) {
                lists_count++;
            } else {
                current2 = current2->next;
            }
            
        }
    }
    
    return lists_count;

}

// DO NOT CHANGE THIS FUNCTION
// create linked list from user input
// NOTE: -1 is NOT part of the final list.
struct node *read_list(void) {
    int num;
    struct node *head = NULL;
    struct node *tail = NULL;
    while (scanf("%d", &num) == 1 && num != -1) {
        struct node *new_node = malloc(sizeof(struct node));
        new_node->data = num;
        new_node->next = NULL;
        if (head == NULL) {
            head = tail = new_node;
        } else {
            tail = tail->next = new_node;
        }
    }
    return head;
}
