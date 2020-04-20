/*
 * list.c - implementation of a linked list
 */


#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <time.h>
#include <signal.h>
#include "listterminal.h"


terminal_t* terminal_new(){
   terminal_t *list;
   list = (terminal_t*) malloc(sizeof(terminal_t));
   list->first = NULL;
   return list;
}


void terminal_destroy(terminal_t *list){
  struct terminal_item *item, *nextitem;

  item = list->first;
  while (item != NULL){
    nextitem = item->next;
    free(item);
    item = nextitem;
  }
  free(list);
}


void insert_new_terminal(terminal_t *list, int pid){
  terminal_item_t *item;

  item = (terminal_item_t *) malloc (sizeof(terminal_item_t));
  item->pid = pid;
  item->next = list->first;
  list->first = item;
}

void remove_terminal(terminal_t *list, int pid){
  struct terminal_item *item, *prev, *aux;
  item = list->first;
  if(item->pid == pid){
    aux = item->next;
    free(item);
    list->first = aux;
  }
  else{
    for(item = list->first, prev = NULL; item != NULL; prev = item, item = item->next){
      if(item->pid == pid){
        if(((item->next)->next) == NULL){
          free(item->next);
          item->next = prev;
          (item->next)->next=NULL;
        }
        else{
          prev->next= item->next;
          free(item);
          return;
        }
      }
    }
  }
}


void kill_terminal(terminal_t *list){
  terminal_item_t *item;
  item = list->first;
  while (item != NULL){
      kill(item->pid, SIGINT);
      item = item->next;
  }
}


void terminal_print(terminal_t *list){
  terminal_item_t *item;

  printf("\nList of processes:\n");
  item = list->first;
  while (item != NULL){
    printf("Process: %d\n",item->pid);
    item = item->next;
  }
  printf("End of list.\n");
}
