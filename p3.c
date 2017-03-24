#include <stdlib.h>
#include <string.h>
#include <stdio.h>

    
//the required struct    
struct node {
  int count; // positive integers only, and non-increasing order
  char* symbol; //no two nodes should have the same symbol  
  struct node *next; 
} *head, *temp;


void insert_node(struct node**, struct node**, char[]);
  /* Pointers to the first and last nodes of list are used */

int main(void) {


  char command[25];  //receives the command
  //initial query
  printf("command?  ");
  scanf("%s", command);
  printf("%s\n", command);
   
  //while loop for new commands
  while (strcmp(command,"end") != 0) {
  
    
    if (strcmp(command,"ins") == 0) {
     puts("we got something"); 
     scanf("%s", command);

     insert_node(&head,&temp,command);
     struct node * tell = head;
     do{
         printf(" %d\n %s\n", tell->count,tell->symbol);
         tell = tell->next;
    } while( tell->next != NULL);
    tell = head;
    }
    printf("command?  ");
    scanf("%s", command);
  


}
}

void insert_node(struct node **h, struct node **t, char *v ) {
  /* Creates a new node with value given by parameter v */
  /* and inserts that node at the end of the list whose */
  /* first and last nodes are pointed to by *h and *t */
  /* respectively. */
  struct node *temp;
  if ((temp = (struct node *)malloc(sizeof(struct node))) == NULL) {
    printf("Node allocation failed. \n");
    exit(1); /* Stop program */
  }
  /* Space for node obtained. Copy the value v into the node */
  /* and insert the node at the end of the list. */
  (*temp).symbol = v;
  temp->next = NULL;
  if (*h == NULL) {
    /* List is currently empty. */
    *h = *t = temp;
  }
  else { /* The list is not empty. Use *t to add the node */
    /* at the end. */
    (*t)->next = temp; *t = (*t)->next;
  }
} /* End of insert_node. */


