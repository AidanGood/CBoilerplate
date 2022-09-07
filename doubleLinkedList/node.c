#include <stdlib.h>
#include "node.h"

/*
 * Allocate a new node and return pointer to data
 */ 
struct node *node_create() {
	return calloc(1, sizeof(struct node));
}

/*
 * Set the note data pointer to a pointer
 * Inputs:
 * ptr: pointer you want to set data attribute to
 */ 
void node_setdata(struct node *n, void *ptr) {
	n->data = ptr;
}

/*
 * Deallocate the node but not its data
 * Inputs:
 * n: pointer to node you want to deallocate
 * Returns: pointer to data stored in node
 */
void *node_deallocate(struct node *n) {
	void *ptr = n->data;
	free(n);
	return ptr;
}

/*
 * Deallocate both node and data stored in node
 * Inputs:
 * n: pointer to node you want to completely deallocate
 */
void node_obliterate(struct node *n) {
	free(n->data);
	free(n);
} 

