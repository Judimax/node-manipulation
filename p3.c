#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define SIZE 25    
//the required struct    
struct node {
  int count; // positive integers only, and non-increasing order
  char symbol[SIZE][SIZE]; //no two nodes should have the same symbol, see if you can optimize by changing the 1st size to 0  
  struct node *next; 
} *head, *temp;


void insert_node(struct node**, struct node**, char[],int);
  /* Pointers to the first and last nodes of list are used */
void print_list(struct node*); 
  /* prints everything in the list */
void rearrange_list(struct node**);
  /* rearranges list to be in descreasing count order */

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
       rearrange_list(&head);
       print_list(head);


    }
    printf("command?  ");
    scanf("%s", command);
  


}


free(temp);
}

void rearrange_list(struct node **h) {
      struct node* check = *h;
      struct node* carrier;
      struct node* prev;
      int a =0;
      while(check != NULL) {
      if (check->next == NULL){              //if there is only one node in the list

         break; 
      }
      //printf("this is what im looking at %d\n", check->count );
      //printf("this is what im looking at next and comparing %d\n", check->next->count );
      if (check->count < check->next->count  ) {

          if (check == *h) {
              puts("we almost done with this function");
              //puts("One try, God is the greatest!!!");
              *h = check->next;
              carrier = check->next->next;
              check->next = carrier;
              (**h).next = check;
              //print_list(*h);
              rearrange_list(h);
              break;
          }
          else {
              check = prev;
              carrier = check->next;
              check->next = check->next->next;
              carrier->next = check->next->next;
              //print_list(carrier);
              //printf("\n");
              check->next->next = carrier;
              rearrange_list(h);
              break;
          }
          
            /*carrier = check->next->next;
            pre_carrier = check;
            check->next->next = pre_carrier;
            pre_carrier->next =carrier;
            */

          

      }
      prev = check;
      check = check->next;
  }   
}

void insert_node(struct node **h, struct node **t, char v[], int c ) {
  /* Creates a new node with value given by parameter v */
  /* and inserts that node at the end of the list whose */
  /* first and last nodes are pointed to by *h and *t */
  /* respectively. */
  struct node *temp;
  int i =0;//counter to properly put value in symbol section
  int a = 0;// flag if string was already in linked list
  //printf("value coming in %s\n", v);
  if ((temp = (struct node *)malloc(sizeof(struct node))) == NULL) {
    printf("Node allocation failed. \n");
    exit(1); /* Stop program */
  }
  /* Space for node obtained. Copy the value v into the node */
  /* and insert the node at the end of the list. */

  struct node* check = *h;         //linked list that will be used to check for string duplicates
  struct node* carrier;            //holds rest of list while list is being adjusted
  struct node* pre_carrier;        //holds everything before the node while the list is changed  
  while(check != NULL) {           // algorithm for the job
      if (strcmp(v,check->symbol[0]) == 0) {
         check->count++;
         a = 1;
         break;
      }
      check = check->next;
  }
   
  if (a==0) {                    //conditional statement referring to flag is string was not in linked list
      
      
      
  temp->count = c;               //algorithm that creates and updates new node
  while(v[i] != NULL) {               //algorithm that properly places string in symbol field;
     temp->symbol[0][i] = v[i];

     i++;
  }
  temp->next = NULL;
  
      
  if (*h == NULL) {                 // algorithm that updates the node
    *h = *t = temp;
  }   
  else {
    (*t)->next = temp; 
    *t = (*t)->next;   
  }
  }
    
  check = *h; // algorithm the take care of any increasing counts in the linked list  

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
    //printf("Values in the list are:\n");
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
