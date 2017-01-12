
#include <stdint.h>
#include <string.h>
#include <stdio.h> 
#include <stdlib.h>  
 
#define SLEN 255
 
struct list {
    int  no;
    char name[SLEN];
    struct list *next;
};
 
int main() {
    int no;
    char s[255];
  
    struct list *head    = NULL;
    struct list *current = NULL;
    struct list *prev    = NULL;
  
    while(1) {
        printf("No. = ");
        scanf("%d", &no);
    
        if (no == 0)
            break;
  
        printf("Name = ");
        scanf("%s", s);
    
        current = (struct list *)malloc(sizeof(struct list));
        if (current == NULL)
            exit(EXIT_FAILURE);
      
        current->next = NULL;
    
        current->no = no;
        strncpy(current->name, s, SLEN -1);
        current->name[SLEN -1] = '\0';
    
        if (head == NULL)
            head = current;
        else
            prev->next = current;
      
        prev = current;
    }
  
    // display linked list
    current = head;
    
    while(current != NULL) {
        printf("No. = %d, Name = %s\n", current->no, current->name);
        current = current->next;
    }
  
    // free linked list
    current = head;
    
    while(current != NULL) {
        prev = current;
        current = current->next;
        free(prev);
    }
}