// A linked list demo
// Rebecca Stolper, 2022

#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

struct node *create_node(int data, struct node *address);

int main(void) {
    
    // declare a pointer to a node (not the node, pointer to empty node)
    struct node *head_ptr;
    
    // create a node, with the data 1 and point to the null pointer
    head_ptr = create_node(3, NULL);
    head_ptr = create_node(2, head_ptr);
    head_ptr = create_node(1, head_ptr);
    
    return 0;
}


// function to create a new node from the node struct
// returns a pointer to a node
// accepts parameters: an int data, and memory address of the node (2 essential ingredients)
// want our linked list nodes all to be on the heap, data on the heap, use malloc
// make the node on heap, we want the data on heap so call malloc to get some data on the heap, the size of the node struct

struct node *create_node(int data, struct node *address) {
    // make the node, where amount of memory is that of struct node or *new_node
    // below line basically tells malloc the amount of memory needed, gets me on the 
    // heap enough data to store a node, and then returns its address, which we assign 
    // as new_node
    struct node *new_node = malloc(sizeof(struct node)); //or *new_node
                                           //new_node is a memory location, and address
    
    // then (below) initialise the data, and initialise the address to be the address 
    // passed in, and return it, the address defined when malloc was called, 
    // i.e. new_node
    new_node->data = data;
    new_node->next = address; //(address is the next address)
    
    return new_node; //returns pointer to node
}

// new_node is a pointer to a struct, use new arrow operator to dereference, get struct, access data field, assign it "data
