#include "linked_list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * In this file, we will find the partial implementation of common doubly
 * linked list functions.
 *
 * Our first task is to debug some of the functions!
 *
 * After we have found all of the bugs, you will be writing three doubly
 * linked list functions and test them.
 *
 */

/**
 * find and return the length of the list
 *
 * given a pointer to the head of list
 */
int length_list(node_t *head_list)
{
  int len = 0;
  if (!head_list)
  {
    return len;
  }
  node_t *current = head_list;
  while (current)
  {
    len++;
    current = current->next;
  }
  return len;
}

/**
 * returns the value of the head of the list
 *
 * given pointer to the head of the list
 */
void *get_first(node_t *head_list)
{
  if (head_list == NULL)
  {
    return NULL;
  }
  return head_list->data;
}
/** returns the value of the last element of the list
 *
 * given a pointer to the head of the list
 */
void *get_last(node_t *head_list)
{
  if (!head_list)
  {
    return NULL;
  }
  node_t *curr = head_list;
  while (curr->next)
  {
    curr = curr->next;
  }
  return curr->data;
}

/** TODO: implement this!
 * inserts element at the beginning of the list
 *
 * given a pointer to the head of the list, a void pointer representing the
 * value to be added, and the size of the data pointed to
 *
 * returns nothing
 */
void insert_first(node_t **head_list, void *to_add, size_t size)
{

  node_t *new_node = (node_t *)malloc(sizeof(node_t)); // allocate space for new node
  new_node->data = malloc(size);                       // allocate space for data
  memcpy(new_node->data, to_add, size);                // copy data of that size to node data

  new_node->next = *head_list;
  new_node->prev = NULL; // adjust pointers

  if (*head_list != NULL)
    (*head_list)->prev = new_node; // handle non empty case

  *head_list = new_node; // adjust head

  return;
}

/**
 * inserts element at the end of the linked list
 *
 * given a pointer to the head of the list, a void pointer representing the
 * value to be added, and the size of the data pointed to
 *
 * returns nothing
 */
void insert_last(node_t **head_list, void *to_add, size_t size)
{
  if (!to_add)
  {
    return;
  }
  node_t *new_element = (node_t *)malloc(sizeof(node_t));
  // size must be adjusted
  void *new_data = malloc(size);
  memcpy(new_data, to_add, size);
  new_element->data = new_data;

  if (!(*head_list))
  { // means the list is empty
    *head_list = new_element;
    new_element->prev = NULL;
    new_element->next = NULL;
    return;
  }

  node_t *curr = *head_list;
  while (curr->next)
  {
    curr = curr->next;
  }

  curr->next = new_element;
  new_element->prev = curr;
  new_element->next = NULL; // next must be null if entered last
}

/** TODO: implement this!
 * gets the element from the linked list
 *
 * given a pointer to the head of the list and an index into the linked list
 * you need to check to see if the index is out of bounds (negative or longer
 * than linked list)
 *
 * returns the string associated with an index into the linked list
 */
void *get(node_t *head_list, int index)
{
  if (!head_list)
    return NULL;

  node_t *curr = head_list;
  int len = 0;
  while (curr)
  {
    if (len == index)
    {
      return curr->data;
    }
    curr = curr->next;
    len++;
  }

  return NULL;
}

/**
 * removes element from linked list
 *
 * given a pointer to the head of list, a void pointer of the node to remove
 * you need to account for if the void pointer doesn't exist in the linked list
 *
 * returns 1 on success and 0 on failure of removing an element from the linked
 * list
 */
int remove_element(node_t **head_list, void *to_remove, size_t size)
{
  if (!(*head_list))
  {
    return 0; // element doesn't exist
  }

  node_t *curr = *head_list;

  while (curr)
  {
    if (!memcmp(curr->data, to_remove, size))
    { // found the element to remove
      if (curr->next)
      {
        curr->next->prev = curr->prev;
      }
      if (curr == *head_list)
      {
        *head_list = curr->next;
      }
      else
      {
        curr->prev->next = curr->next;
      }
      free(curr->data);
      free(curr);
      return 1;
    }
    curr = curr->next;
  }

  return 0;
}

/**
 * reverses the list given a double pointer to the first element
 *
 * returns nothing
 */
void reverse_helper(node_t **head_list)
{
  node_t *curr = *head_list;
  if (!curr)
    return; // if no element or one element no swap needed

  node_t *placeholder = NULL;

  // redundant if statement removed as implicit checking of these cases are dpne
  while (curr)
  {
    if (!curr->next)
    {
      *head_list = curr; // finding tail to make it head for reversing
    }

    // implement bubble sort here correctly

    placeholder = curr->next; // suppose 1-> 2 place = 2   curr =1
    curr->next = curr->prev;  // curr-> prev = null  and 1-> next = null as well.
    curr->prev = placeholder; // 1->prev = 2
    curr = curr->prev;        // now curr = 2 Next it goes on
  }
}

/**
 * calls a helper function that reverses the linked list
 *
 * given a pointer to the first element
 *
 * returns nothing
 */
void reverse(node_t **head_list)
{
  if (head_list)
  {
    reverse_helper(head_list);
  }
}

/**
 * removes the first element of the linked list if it exists
 *
 * given a pointer to the head of the linked list
 *
 * returns the void pointer of the element removed
 *
 */
void *remove_first(node_t **head_list)
{
  if (!(*head_list))
  {
    return NULL;
  }
  node_t *curr = *head_list;
  *head_list = (*head_list)->next;

  if (*head_list)
  {
    (*head_list)->prev = NULL;
  }

  void *ret_data = curr->data;  // can handle multiple data types previous one was too specific for string only
  
  free (curr);

  return ret_data;
}

/** TODO: implement this!
 * removes the last element of the linked list if it exists
 *
 * given a pointer to the head of the linked list
 *
 * returns the void pointer of the element removed
 *
 */
void *remove_last(node_t **head_list)
{
  if (*head_list == NULL) // no element case 
    return NULL;

  node_t *curr = *head_list;
  node_t *prev = NULL;

  while (curr->next != NULL)  // get to tail
  {
    prev = curr;
    curr = curr->next;
  }

  void *data = curr->data; // store data to be removed

  if (!prev)                  // handle single element case 
    *head_list = NULL;
  else
    prev->next = NULL;  // normal case 
  
  free(curr);

  return data;
}
