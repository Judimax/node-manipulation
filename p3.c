#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define SIZE 25    
//the required struct    
struct node {
  int count; // positive integers only, and non-increasing order
  char symbol[SIZE][SIZE]; //no two nodes should have the same symbol  
  struct node *next; 
} *head, *temp;


void insert_node(struct node**, struct node**, char[],int);
  /* Pointers to the first and last nodes of list are used */
void print_list(struct node*); 
  /* prints everything in the list */


int main(void) {


  char command[25];  //receives the command
  //initial query
  int counter =0;
  printf("command?  ");
  scanf("%s", command);

  
  //while loop for new commands
  while (strcmp(command,"end") != 0) {
  
    
    if (strcmp(command,"ins") == 0) {

       scanf("%s", command);

       insert_node(&head,&temp,command, counter);
       print_list(head);


    }
    printf("command?  ");
    scanf("%s", command);
  


}


free(temp);
}

void insert_node(struct node **h, struct node **t, char v[], int c ) {
  /* Creates a new node with value given by parameter v */
  /* and inserts that node at the end of the list whose */
  /* first and last nodes are pointed to by *h and *t */
  /* respectively. */
  struct node *temp;
  int i =0;//counter to properly put value in symbol section
  int a = 0;// flag if string was already in linked list
  printf("value coming in %s\n", v);
  if ((temp = (struct node *)malloc(sizeof(struct node))) == NULL) {
    printf("Node allocation failed. \n");
    exit(1); /* Stop program */
  }
  /* Space for node obtained. Copy the value v into the node */
  /* and insert the node at the end of the list. */

  struct node* check = *h;
  while(check != NULL) {
      if (strcmp(v,check->symbol[0]) == 0) {
         check->count++;
         a = 1;
         break;
      }
      check = check->next;
  }
   
  if (a==0) {
  temp->count = c;


  while(v[i] != NULL) {
     temp->symbol[0][i] = v[i];

     i++;
  }
  temp->next = NULL;
  
  if (*h == NULL) {
    /* List is currently empty. */
    *h = *t = temp;
  }
  else { /* The list is not empty. Use *t to add the node */
    /* at the end. */
    (*t)->next = temp; 
    *t = (*t)->next;
     
  }
  }


}
    /* End of insert_node. */

void print_list(struct node *h) {
  /* Prints the values stored in the nodes of the list */
  /* pointed to by h. */
  int i;
  if (h == NULL) {
    printf("The list is empty.\n");
  }
  else {
    printf("Values in the list are:\n");
    while (h != NULL) {
      printf("%d\n %s\n",h->count,h->symbol[0]);
      //printf("size of string %d\n",sizeof(h->symbol[0]));
      /*while(i != sizeof(h->symbol) ) {
          printf("%s ", h->symbol);
          h->symbol[i];
          i++;
      } */
      i++;
      h = h->next;
    }
  }
} /* End of print_list */
