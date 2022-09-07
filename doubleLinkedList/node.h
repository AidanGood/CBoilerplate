#ifndef _NODE_H_
#define _NODE_H_


struct node {
	struct node *prev;
	struct node *next;
	void *data;
};

struct node *node_create();

void node_setdata(struct node *n, void *ptr);

void *node_deallocate(struct node *n);

void node_obliterate(struct node *n);

#endif