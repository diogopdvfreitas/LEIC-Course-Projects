/*
 * listterminal.h - definitions and declarations of the integer list 
 */

#ifndef LIST_TERMINAL_H
#define LIST_TERMINAL_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>



/* lst_iitem - each element of the list points to the next element */
typedef struct terminal_item {
   int pid;
   struct terminal_item *next;
} terminal_item_t;

/* terminal_t */
typedef struct {
   terminal_item_t *first;
} terminal_t;



/* lst_new - allocates memory for list_t and initializes it */
terminal_t* terminal_new();

/* lst_destroy - free memory of list_t and all its items */
void terminal_destroy(terminal_t *list);

/* insert_new_process - insert a new item with process id and its start time in list 'list' */
void insert_new_terminal(terminal_t *list, int pid);

/*remove_process - remove a item with process id*/
void remove_terminal(terminal_t *list, int pid);

/*return a vector with all active process*/
void kill_terminal(terminal_t *list);

/* lst_print - print the content of list 'list' to standard output */
void terminal_print(terminal_t *list);

#endif

