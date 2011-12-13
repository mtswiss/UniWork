#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct linked_list {
  struct list_node* head;
  struct list_node* tail;
};

struct list_node {
  struct list_node* link;
  int data;
};

struct linked_list* new_linked_list(void) {
  struct linked_list* l = malloc(sizeof(*l));
  assert(l != NULL && "Memory allocation failed.");
  l->head = NULL;
  l->tail = NULL;
  return l;
}

struct list_node* push_to_front(struct linked_list* list, int data) {
  struct list_node* node = malloc(sizeof(*node));
  assert(node != NULL && "Memory allocation failed.");
  node->data = data;
  node->link = list->head;
  list->head = node;
  if (list->tail == NULL) {
    list->tail = node;
  }
  return node;
}

struct list_node* push_to_tail(struct linked_list* list, int data) {
  struct list_node* node = malloc(sizeof(*node));
  assert(node != NULL && "Memory allocation failed.");
  node->data = data;
  node->link = NULL;
  if (list->tail != NULL) {
    assert(list->tail->link == NULL && "Corrupted list.");
    list->tail->link = node;
    list->tail = node;
  } else {
    assert(list->head == NULL && "Corrupted list.");
    list->head = list->tail = node;
  }
  return node;
}

struct list_node* insert_after(struct linked_list* list,
                               struct list_node* prev_node, int data) {
  assert(prev_node != NULL && "NULL list element.");
  struct list_node* node = malloc(sizeof(*node));
  assert(node != NULL && "Memory allocation failed.");
  node->data = data;
  node->link = prev_node->link;
  prev_node->link = node;
  if (list->tail == prev_node) {
    assert(node->link == NULL && "Corrupted list.");
    list->tail = node;
  }
  return node;
}

struct list_node* get_next_element(struct list_node* node) {
  if (node == NULL) {
    return NULL;
  } else {
    return node->link;
  }
}

int get_data(struct list_node* node) {
  return node->data;
}

void delete_node(struct linked_list* list, struct list_node* node) {
  struct list_node* ptr;
  for (ptr = list->head; ptr != NULL; ptr = ptr->link) {
    if (ptr->link == node) {
      break;
    }
  }

  if (ptr == NULL) {
    assert(list->head == node && "Corrupted list.");
    list->head = node->link;
    if (node->link == NULL) {
      list->tail = NULL;
    }
  } else {
    ptr->link = node->link;
    if (list->tail == node) {
      list->tail = ptr;
    }
  }

  free(node);
}

void delete_list(struct linked_list* list) {
  struct list_node* p;
  struct list_node* q;

  for (p = list->head; p != NULL; p = q) {
    q = p->link;
    free(p);
  }

  free(list);
}

int main(void) {
  struct linked_list *l = new_linked_list();

  for (int i = 0; i < 50; ++i) {
    push_to_tail(l, i);
  }

  struct list_node* n = NULL;
  printf("[ ");
  for (n = l->head; n != NULL; n = get_next_element(n)) {
    printf("%i ", get_data(n));
  }
  printf("]\n");

  delete_list(l);

  return 0;
}
