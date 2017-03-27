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
void print_list(struct node*,float *, int[],char[]); 
  /* handles several of the print commands in the code */
void rearrange_list(struct node**,struct node**);
  /* rearranges list to be in descreasing count order */
void delete_node(struct node**, struct node**, char[]);
  /*decreases count of node or deletes it altogether*/
void forced_delete_node(struct node**, struct node**,char[]);
  /*deletes all nodes with counts less than or equal to the specified number*/



int main(void) {


  char command[25];  //receives the command
  //initial query
  int counter =1;    //value to initalize node upon creation
  int calcs[2];      //used to return values for pst
  calcs[1] =1;       //used to preset min count value in the list which can only be one
  calcs[2] =0;       // used to preset max count value in the list,if the list has one onde
  float avgs;       //used to return avg for pst  
  printf("command?  ");
  scanf("%s", command);

  //while loop for new commands
  while (strcmp(command,"end") != 0) {
  
    
    if (strcmp(command,"ins") == 0) {

       scanf("%s", command);                        //to scan string to be inserted

       insert_node(&head,&temp,command, counter);
       rearrange_list(&head,&temp);
       //print_list(head,avgs,calcs);


    }
      
    if (strcmp(command,"del") == 0) {
        
        scanf("%s", command);
        
        delete_node(&head,&temp,command);
        rearrange_list(&head,&temp);
        //print_list(head,avgs,calcs);
        
    }  
      
    if (strcmp(command,"fde") == 0) {
        
        scanf("%s", command);
        
        forced_delete_node(&head,&temp,command);
        rearrange_list(&head,&temp);
        //print_list(head,avgs,calcs);
        
    }  
    
    if (strcmp(command,"pst") == 0) {
        

        print_list(head,&avgs,calcs,command);
        printf(" The number of nodes in the list : %d\n", calcs[0]);
        printf(" The maximum count in the list : %d\n", calcs[2]);    //was not working properly
        printf(" The minimum count in the list : %d\n", calcs[1]);
        printf(" The average count in the list : %f\n", avgs);
    }   
    printf("command?  ");
    scanf("%s", command);
  
}


free(temp);
  //end of main   
}

void forced_delete_node(struct node **h, struct node **t,char val[]) {
    struct node* check = *h;         //used to remove every unsatisfied condition of the linkedlist
    struct node* prev;               // node used to delete specified node if count was less than val
    char value = val[0];                      // to transfer the value
    int num_conv = value - 48;            //required to remove 48 to complete interger conversion


    while(check != NULL) {
         
        
        if (check->count <= num_conv) {
            //printf("this is the count of the current check %d\n",check->count);
            //printf("this is the comparsion value %d\n", num_conv);
            if (check == *h) {
                *h = check->next;
                 forced_delete_node(h,t,val);
            }
            else {
                prev->next = check->next;
                forced_delete_node(h,t,val);

            }
        }
        prev = check;
        check = check->next;
    }
    
}
//end of forced delete node




void delete_node(struct node **h, struct node **t, char string[]) {
  struct node* check = *h;         //linked list that will be used to check to delete specified string
  struct node* prev;               // node used to delete specified node if count went to zero
  while(check != NULL) {           // algorithm for the job
      if (strcmp(string,check->symbol[0]) == 0) {
         check->count--;
         if (check->count == 0) {
            if (check == *h) {
                *h = check->next;
            }
            else {
                prev->next = check->next;
            }    
         }   
         break;
      }
      prev = check;
      check = check->next;
  }         
}




void rearrange_list(struct node **h, struct node **t) {
      struct node* check = *h;
      struct node* carrier;
      struct node* prev;
      int a =0;                              //counter for recursion to check rest of list
      while(check != NULL) {
      if (check->next == NULL){              //if there is only one node in the list
         *t = check;
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
              rearrange_list(h,t);
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
              rearrange_list(h,t);
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
  int a =0;// flag if string was already in linked list
  //printf("value coming in %s\n", v);
  if ((temp = (struct node *)malloc(sizeof(struct node))) == NULL) {
    printf("Node allocation failed. \n");
    exit(1); /* Stop program */
  }
  /* Space for node obtained. Copy the value v into the node */
  /* and insert the node at the end of the list. */

  struct node* check = *h;         //linked list that will be used to check for string duplicates


  while(check != NULL) {           // algorithm for the job
      if (strcmp(v,check->symbol[0]) == 0) {
         check->count++;
         a = 1;
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
    


}
    /* End of insert_node. */

void print_list(struct node *h, float* avg, int * stats, char c_string[]) {
  /* Prints the values stored in the nodes of the list */
  /* pointed to by h. */
  int i = 0;
  float sum =0.0;  
  struct node * prev;              //to get maximum  and minimun values
  struct node * check;             //check if we are at the beginning of the list  
  if (h == NULL) {
    printf("The list is empty.\n");
  }
  else {
    //printf("Values in the list are:\n");
    while (h != NULL) {
      printf("%d\n %s\n",h->count,h->symbol[0]);
      if(prev != NULL) {
        if (prev->count < h->count) {
            stats[1] = prev->count;   
        }
        if (prev->count > h->count) {
            stats[2] = prev->count;   
        }
      }
      else{
        stats[2] = h->count;    
      }
      sum += h->count;   
      //printf("size of string %d\n",sizeof(h->symbol[0]));
      /*while(i != sizeof(h->symbol) ) {
          printf("%s ", h->symbol);
          h->symbol[i];
          i++;
      } */
      i++;
      prev = h;  
      h = h->next;
    }
    stats[0] = i;  
    *avg = sum/(float)i;  
  }
} /* End of print_list */
