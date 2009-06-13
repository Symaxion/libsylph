#include "../csylph.h"
#include <stdlib.h>

SY_list * SY_list_new() {
    return SY_calloc(SY_list, 1);
}

void SY_list_destroy(SY_list * self) {
    for (SY_list_node * nod = self->first; nod != self->last;
            nod = nod->next) {
        SY_free(nod);
    }
    SY_free(nod);
}

void SY_collection_append(SY_list * self, void * append) {
    if (self->first == NULL) {
        self->first = SY_calloc(struct SY_list_node, 1);
        self->first->contents = append;
        self->last = self->first;
    } else {
        self->last->next = SY_calloc(struct SY_list_node, 1);
        self->last->next->contents = append;
        self->last->previous = self->last;
        self->last = self->last->next;
    }
    self->length++;
}

void * SY_list_pop(SY_list * self) {
    void ** tmp = SY_alloc(void*, 1)
    memcpy(tmp, &self->last->contents, sizeof(void*));
    self->last = self->last->previous;
    SY_free(self->last->next);
    return *tmp;
}



SY_iterator * SY_iterator_new(SY_list * list) {
    SY_iterator * self = SY_calloc(SY_iterator, 1);
    self->current = list->first;
    return self;
}

void SY_iterator_destroy(SY_iterator * self) {
    SY_free(self);
}

void * SY_iterator_current(SY_iterator * self) {
    return self->current->contents;
}

bool SY_iterator_forward(SY_iterator * self) {
    if(self->current->next == NULL) return false;
    else {
        self->current = self->current->next;
        return true;
    }
}

bool SY_iterator_backward(SY_iterator * self) {
    if(self->current->previous == NULL) return false;
    else {
        self->current = self->current->previous;
        return true;
    }
}
void SY_iterator_insert(SY_iterator * self, void * p) {
    SY_list_node * tmp = SY_calloc(SY_list_node, 1);
    tmp->contents = p;
    SY_list_node * next = self->current->next;
    self->current->next = tmp;
    tmp->previous = self->current;
    next->previous = tmp;
    tmp->next = next;
}

void SY_iterator_remove(SY_iterator * self) {
    SY_list_node * prev = self->current->previous;
    SY_list_node * next = self->current->next;

    SY_free(self->current);
    prev != NULL && prev->next = next;
    next != NULL && next->previous = prev;
}

SY_def_app_impl(LB);
SY_def_app_impl(LF);
SY_def_app_impl(MB);
SY_def_app_impl(MF);
SY_def_app_impl(Woe);
