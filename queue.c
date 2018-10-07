/*
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new() {
  queue_t *q = malloc(sizeof(queue_t));
  if (q != NULL) {
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
  }
  return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q) {
  if (q == NULL)
    return;

  list_ele_t *access = q->head; //將access指向qhead

  while (access != NULL) { //檢查access是否為NULL
    q->head = access;
    access = access->next;

    free(q->head->value);

    free(q->head);

    q->size--;
  }

  access = NULL;
  free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s) {
  list_ele_t *ptr;
  if (q == NULL)
    return false;

  list_ele_t *newh = (list_ele_t *)malloc(sizeof(list_ele_t));
  if (newh == NULL)
    return false;

  newh->value = (char *)malloc(
      strlen(s) + 1); //因為s是從0開始要加一才能表示其真正所需的記憶體
  if (!newh->value) {
    free(newh);
    return false;
  }
  strcpy(newh->value, s); //將接受的字串指標s傳入newh的value中
  s = NULL;

  ptr = q->head;    //將前一個結構位址儲存在ptr中
  newh->next = ptr; //將新創的結構指向之前生成的結構

  if (q->size == 0) {
    q->tail = newh;
  }

  q->head = newh; // newh所存的位址指派給q的head中
  q->size++;

  return true;
}

/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s) {
  // list_ele_t *ptr2=q->tail;

  if (q == NULL)
    return false;

  list_ele_t *newh = (list_ele_t *)malloc(sizeof(list_ele_t));
  if (newh == NULL)
    return false;

  newh->value = (char *)malloc(strlen(s) + 1);
  if (newh->value == NULL) {
    free(newh);
    return false;
  }
  strcpy(newh->value, s);
  s = NULL;

  newh->next = NULL;
  if (q->size != 0) {
    q->tail->next = newh;
    // ptr2->next = newh;
  } else {
    q->head = newh; //把newh的位址傳給qhead

    newh->next = NULL;
  }
  q->tail = newh;
  q->size++;

  return true;

  // if (newh != NULL) {
  // newh->next = q->head;
  // newh->value = strdup(s);}
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize) {
  // if queue is NULL or empty
  if (q == NULL || q->size == 0)
    return false;

  int size;
  // if sp is non-NULL
  if (sp != NULL) {
    size = strlen(q->head->value);
    if (size > bufsize - 1) {
      size = bufsize - 1;
    } else {
      size = size;
    }

    strncpy(sp, q->head->value, size);
    sp[size] = '\0';
    // int kkk;
  }

  list_ele_t *tmp1 = q->head;

  q->head = q->head->next;
  q->size--;

  free(tmp1->value);
  free(tmp1);

  return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q) {
  /* You need to write the code for this function */
  /* Remember: It should operate in O(1) time */
  return (q != NULL) ? q->size : 0;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q) {
  if (!q || q->size == 0)
    return;

  list_ele_t *last = NULL;
  list_ele_t *current;
  q->tail = q->head;

  while (current != NULL) {
    current = q->head->next;
    q->head->next = last;

    last = q->head;

    q->head = current;
  }
  q->head = last;
  // int test;
}
