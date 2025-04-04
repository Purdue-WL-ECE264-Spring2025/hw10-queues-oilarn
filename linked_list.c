#include "linked_list.h"

#include <stdlib.h>

struct list_node *new_node(size_t value) 
{ 
  struct list_node *node = malloc(sizeof(struct list_node));
  node->value = value;
  node->next = NULL;
  return node;
}

void insert_at_head(struct linked_list *list, size_t value) 
{
  struct list_node *ptr = new_node(value);
  ptr->next = list->head;
  list->head = ptr;
}

void insert_at_tail(struct linked_list *list, size_t value) 
{
  struct list_node *ptr = new_node(value);

  if (list->head == NULL)
  {
    list->head = ptr;
    return;
  }

  struct list_node *temp = list->head;
  while (temp->next != NULL)
  {
    temp = temp->next;
  }

  temp->next = ptr;
}

size_t remove_from_head(struct linked_list *list) 
{
  if (list == NULL || list->head == NULL) 
  {
    return 0; 
  }

  struct list_node *old_head = list->head;
  size_t removed_val = old_head->value;
  list->head = old_head->next; 

  free(old_head);

  return removed_val;
}

size_t remove_from_tail(struct linked_list *list) 
{
  if (!list || !list->head)
  {
    return 0;
  }

  struct list_node *ptr = list->head;
  size_t removed_val = ptr->value;

  list->head = NULL;
  return removed_val; 
}

void free_list(struct linked_list list) 
{
  while (list.head != NULL)
  {
    struct list_node *ptr = list.head->next;
    free(list.head);
    list.head = ptr;
  }
}

// Utility function to help you debugging, do not modify
void dump_list(FILE *fp, struct linked_list list) {
  fprintf(fp, "[ ");
  for (struct list_node *cur = list.head; cur != NULL; cur = cur->next) {
    fprintf(fp, "%zu ", cur->value);
  }
  fprintf(fp, "]\n");
}
