#ifndef _DLIST_H_
#define _DLIST_H_

#include <stdint.h>
#include <stdbool.h>
#include "node.h"


struct dlist {
	struct node *front;
	struct node *back;
	struct node *iter;
	uint32_t counter;
};

struct dlist *dlist_create();

void dlist_deallocate(struct dlist *l);

void dlist_obliterate(struct dlist *l);

void dlist_add_front(struct dlist *l, void *ptr);

void dlist_add_back(struct dlist *l, void *ptr);

void *dlist_remove_front(struct dlist *l);

void *dlist_remove_back(struct dlist *l);

void *dlist_find_remove(struct dlist *l, void *ptr);

uint32_t dlist_num_elems(struct dlist *l);

void *dlist_iter_begin(struct dlist *l);

void *dlist_iter_next(struct dlist *l);

bool dlist_iter_has_next(struct dlist *l);

void *dlist_iter_end(struct dlist *l);

void *dlist_iter_prev(struct dlist *l);

bool dlist_iter_has_prev(struct dlist *l);

#endif /* _DLIST_H_ */
