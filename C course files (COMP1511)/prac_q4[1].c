#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct node {
    struct node *next;
    int          data;
};

int product(struct node *head1, struct node *head2);
struct node *read_list(void);

// DO NOT CHANGE THIS MAIN FUNCTION
int main(void) {
    // create two linked lists from standard input
    struct node *head1 = read_list();
    struct node *head2 = read_list();

    int result = product(head1, head2);
    printf("%d\n", result);

    return 0;
}

// product should return the sum of the elements in list1 multiplied by 
// the corresponding element in list2
// if one list is longer than the other, the extra list elements are ignored 
int product(struct node *head1, struct node *head2) {

    // PUT YOUR CODE HERE (change the next line!)
    return 42;

}

// DO NOT CHANGE THIS FUNCTION
// create linked list from integers on standard input
struct node *read_list(void) {
    struct node *head = NULL;
    struct node *tail = NULL;
    int num;
    while (scanf("%d", &num) == 1 && num != -1) {
        struct node *new = malloc(sizeof(struct node));
        new->data = num;
        new->next = NULL;
        if (head == NULL) {
            head = new;
        } else {
            tail->next = new;
        }
        tail = new;
    }
    return head;
}
