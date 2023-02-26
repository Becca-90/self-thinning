// A linked list demo
// Rebecca Stolper, 2022

#include <stdio.h>
#include <stdlib.h>

struct node {           // a node is a type of struct which has some data and a pointer
    int data;           // data and a reference to another struct for its address
    struct node *next;  //pointer to another struct in memory, to 
                        //follow in memory to chain together a series of structs
};

// define functions to manipulate linked list

struct node* create_node(int data, struct node *address);
void print_linked_list(struct node *head);
struct node* insert_at_end(int data,   struct node *head_ptr);
struct node* remove_tail(struct node *head_ptr);
int size_of_linked_list(struct node *head_ptr);
struct node* delete_node_at_position(struct node *head_ptr, int position);
struct node* delete_head(struct node *head_ptr);
struct node* insert_in_sequence(struct node **head, int data);

int main(void) {
    
    // declare a pointer to a node (not the node, pointer to empty node):
    struct node *head_ptr;
    
    // create a node, with the data 3 and point to the null pointer
    head_ptr = create_node(3, NULL);
    
    insert_in_sequence(&head_ptr, 5); //address of head_ptr with &head_ptr
    insert_in_sequence(&head_ptr, 7);
    insert_in_sequence(&head_ptr, 3);
    insert_in_sequence(&head_ptr, 6);
    insert_in_sequence(&head_ptr, 4);
    
    // changing what head_ptr is pointing to:
    // head_ptr = create_node(2, head_ptr);
    // head_ptr = create_node(1, head_ptr);
    
    // insert_at_end(50, head_ptr);
    // print_linked_list(head_ptr);
    // printf"Deleting at position 1\n");
    // head_ptr = delete_node_at_position(head_ptr, 1);    
    //remove_tail(head_ptr);
    
    print_linked_list(head_ptr);
    
    return 0;
}


// function to create a new node from the node struct
// returns a pointer to a node
// accepts parameters: an int data, and memory address of the node (2 essential ingredients)
struct node *create_node(int data, struct node *address) {
                // make the node, where amount of memory is that of struct node or *new_node
                // below line basically tells malloc the amount of memory needed, gets me on the 
                // heap enough data to store a node, and then returns its address, which we assign 
                // as new_node
    struct node *new_node = malloc(sizeof(struct node)); 
                                            //or *new_node, this is what puts
                                            //the data on the heap so not lost after function ends!
                                            //new_node is a memory location, and address
    
                // then (below) initialise the data, and initialise the address to be the address 
                // passed in, and return it, the address defined when malloc was called, 
                // i.e. new_node
    new_node->data = data;
    new_node->next = address; //(address is the next address)
    
    return new_node; //returns pointer to node
}

// will need to traverse the linked list, printing each node's data value
// returns: VOID
// parameters: accepts a pointer to a struct node (address)
void print_linked_list(struct node *head) { // head is what we call the first node in our list
    struct node *current = head; // find current node: make new node and node pointer and say that 
                                 // it points to same position as head pointer, then loop through 
                                 // with while loop: 
    while (current != NULL) {
        printf("%d->", current->data);
        current = current->next; // prints current.data, then sets current to be 
                                 // equal to current.next, & repeat until 
                                 // current = NULL 
                                 // so track via pointer rather than iterate with 
                                 // a counter like i from 0 - n
    }
    printf("NULL\n");
}

// insert in sequence, takes a SORTED linked list, and adds a node in the correct position in the linked list...
// so if our linked list was something like: 3->5->10;
// 6 will be inserted after 5.
struct node* insert_in_sequence(struct node **head, int data) {
    // step 1... we need to go through the linked list until we find the
    // position we want. **head is a pointer to a pointer to a struct node
    struct node *current = *head; // following the head ptr once
    struct node *previous = NULL;

    while (current != NULL && current->data < data) {
        // we are not yet at the correct position
        previous = current;
        current = current->next;
    }
    // ok, the linked list value is > data, therefore we insert at previous
    struct node *new_node = create_node(data, current);
    if (previous == NULL) {
        *head = new_node; // this is the reason we pass in **head also written *(*head)
    } else {
        previous->next = new_node;
    }
    return *head;
}



// a function to add a node at the end of a linked list.
// will need to traverse to the end of the linked list, not doing anything as 
// we traverse... just gets there
// RETURNS: address of head
// PARAMETERS: the pointer to the linked list to add to theint size_of_linked_list(struct node *head_ptr); end of...
struct node *insert_at_end(int data, struct node *head_ptr) {
    struct node *current = head_ptr;
    while (current->next != NULL) {
        current = current->next;
    }
    // now, current is at the end...because its next points to NULL
    struct node *new_node = create_node(data, NULL);
    current->next = new_node;
    return head_ptr;
}


int size_of_linked_list(struct node *head_ptr) {
    struct node *current = head_ptr;
                                       // alternate:
                                       // if (head_ptr = NULL) {
                                       //     return 0;
                                       // }
                                       //
    int i = 0;                          // if using above if statement:
    while (current != NULL) {           //  while(current->next != NULL) {
        current = current->next;        //      current = current->next;
        i++;                            //      i++;
    }   
    return i;                           //      return i++;
}

struct node *remove_tail(struct node *head_ptr) {
    struct node *current = head_ptr;
    struct node *previous = head_ptr;
    while (current->next != NULL) {
        previous = current;
        current = current->next;
    }
    
    previous->next = NULL;
    free(current);
    return head_ptr;
    
} // OR: while(current->next->next != NULL)
  // then: free(current->next) at end of loop


// new_node is a pointer to a struct, use new arrow operator to dereference, get struct, access data field, assign it "data

// delete a node in a linked list at a specified position
// PARAMETERS: a pointer to the head of the linked list
// RETURNS: a head to the linked list
struct node* delete_node_at_position(struct node *head_ptr, int position) {
    struct node *current = head_ptr;
    struct node *previous = NULL; 
    
    int i = 0;
    
    while (current != NULL) {        
        if (i == position) {       
               
        if (previous == NULL) {
            // then we are in item zero
            free(current);
            return NULL;
        }             
            previous->next = current->next;
            free(current);
            head_ptr = NULL;
            return head_ptr;                
        }
        previous = current;
        current = current->next;
        i++;
    }
    return head_ptr;
}

// doesnt do anything new but maybe a bit nicer to use.
struct node* delete_head(struct node *head_ptr) {
    return delete_node_at_position(head_ptr, 0);
}

// 
