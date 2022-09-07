#include <stdlib.h>
#include <stdio.h>

#include "node.h"
#include "dlist.h"

struct dlist *dlist_create() {
	return calloc(1, sizeof(struct dlist));
}

void dlist_deallocate(struct dlist *l) {
	struct node *p = l->front;

	do {
		l->front = l->front->next;
		free(p->data);
		free(p);
		p = l->front;
	} while (l->front != NULL);

	l->front = l->back = NULL;
	l->counter = 0;
}


void dlist_obliterate(struct dlist *l) {
	dlist_deallocate(l);
	free(l);
}

void dlist_add_front(struct dlist *l, void *ptr) {
    struct node *node;
    node = node_create();
    node_setdata(node, ptr);
    if (l->counter == 0){
        l->front = node;
        l->back = node;
        l->counter = l->counter + 1;
    }
    else{
        node->next = l->front;
        l->front->prev = node;
        l->front = node;
        l->counter = l->counter + 1;
    }
    #ifdef DEBUG
	printf("counter= %d, %s\n", l->counter, (char *) ptr);
	printf("front= %s\n", (char *) l->front->data);
	printf("back= %s\n\n", (char *) l->back->data);
    #endif /* DEBUG */
}

void dlist_add_back(struct dlist *l, void *ptr) {
    struct node *node;
    node = node_create();
    node_setdata(node, ptr);
    if (l->counter == 0){
        l->back = node;
        l->front = node;
        l->counter = l->counter + 1;
    }
    else{
        node->prev = l->back;
        l->back->next = node;
        l->back = node;
        l->counter = l->counter + 1;
    }
    #ifdef DEBUG
	printf("counter= %d, %s\n", l->counter, (char *) ptr);
	printf("front= %s\n", (char *) l->front->data);
	printf("back= %s\n\n", (char *) l->back->data);
    #endif /* DEBUG */
}

void *dlist_remove_front(struct dlist *l) {
    void *ptr;
    struct node *node = l->front;
    ptr = node->data;
    
    if (1 == l->counter) {
        l->back = l->front = NULL;
    }
    else {
        l->front = l->front->next;
        l->front->prev = NULL;
    }
    (l->counter)--;
    free(node);

	return ptr;
}

void *dlist_remove_back(struct dlist *l) {
	struct node *n = l->back;
	void *ptr = n->data;

	if (1 == l->counter) {
		l->front = l->back = NULL;
	} else {
		l->back = l->back->prev;
		l->back->next = NULL;
	}

	(l->counter)--;
	free(n);
	return ptr;
}

void *dlist_find_remove(struct dlist *l, void *ptr) {
	struct node *n = l->front;
	void *ret_ptr = NULL;

	while ((n != NULL) && (n->data != ptr)) {
	  n = n->next;
	}

	if (n != NULL) {
	  if (l->front == n) {
	    return dlist_remove_front(l);
	  } else if (l->back == n) {
	    return dlist_remove_back(l);
	  } else {
	    if (1 == l->counter) {
	      l->front = l->back = NULL;
	    } else {
	      n->prev->next = n->next;
	      n->next->prev = n->prev;
	    }
	    (l->counter)--;
	  }
	  
	  ret_ptr = n->data;
	  free(n);
	}
	
	return ret_ptr;
}

uint32_t dlist_num_elems(struct dlist *l) {
	return l->counter;
}

void *dlist_iter_begin(struct dlist *l) {
	void *ret_val = NULL;

	l->iter = l->front;
	if (l->iter != NULL) {
		ret_val = l->iter->data; 
	}

	return ret_val;
}

void *dlist_iter_next(struct dlist *l) {
	void *ret_val = NULL;

	if (l->iter != NULL) {
		l->iter = l->iter->next;
		if (l->iter != NULL) {
			ret_val = l->iter->data;
		}
	}

	return ret_val;
}

bool dlist_iter_has_next(struct dlist *l) {
	bool ret_val = false;

	if (l->iter != NULL) {
		ret_val = (l->iter->next != NULL);
	}

    #ifdef DEBUG
	if (ret_val) {
		printf("dlist_has_next: current is %s\n", (char *) l->iter->data);
		printf("dlist_has_next: returning %d\n\n", ret_val);
	}
    #endif /* DEBUG */

	return ret_val;
}

void *dlist_iter_end(struct dlist *l) {
	void *ret_val = NULL;

	l->iter = l->back;
	if (l->iter != NULL) {
		ret_val = l->iter->data;
	}

	return ret_val;
}

void *dlist_iter_prev(struct dlist *l) {
	void *ret_val = NULL;

	if (l->iter != NULL) {
		l->iter = l->iter->prev;
		if (l->iter != NULL) {
			ret_val = l->iter->data;
		}
	}

	return ret_val;
}

bool dlist_iter_has_prev(struct dlist *l) {
	bool ret_val = false;

	if (l->iter != NULL) {
		ret_val = (l->iter->prev != NULL);
	}

	return ret_val;
}
