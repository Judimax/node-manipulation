#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
    
#define SIZE 25    
//the required struct    
struct node {
  int count; // positive integers only, and non-increasing order
  char symbol[SIZE][SIZE]; //no two nodes should have the same symbol, see if you can optimize by changing the 1st size to 0  
  struct node *next; 
} *head, *temp;


void insert_node(struct node**, struct node**, char[],int);
  /* Pointers to the first and last nodes of list are used */
char* print_list(struct node*,float *, int[],char * ,char *); 
  /* handles several of the print commands in the code */
void rearrange_list(struct node**,struct node**);
  /* rearranges list to be in descreasing count order */
void delete_node(struct node**, struct node**, int[], char[]);
  /*decreases count of node or deletes it altogether*/
void forced_delete_node(struct node**, struct node**, int[], char*);
  /*deletes all nodes with counts less than or equal to the specified number*/



int main(void) {


  char command[25];  //receives the command
  //initial query
  int counter =1;    //value to initalize node upon creation
  int calcs[2];      //used to return values for pst
  calcs[1] =1;       //used to preset min count value in the list which can only be one
  calcs[2] =0;       // used to preset max count value in the list,if the list has one onde
  float avgs;       //used to return avg for pst
  char* decision;         //for printing a certain value
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
        
        delete_node(&head,&temp,calcs,command);
        rearrange_list(&head,&temp);
        //print_list(head,avgs,calcs);
        
    }  
      
    if (strcmp(command,"fde") == 0) {
        
        scanf("%s", command);
        
        forced_delete_node(&head,&temp,calcs,command);
        rearrange_list(&head,&temp);
        //print_list(head,avgs,calcs);
        
    }
      
    
    if (strcmp(command,"ppr") == 0) {
        scanf("%s", command);
        print_list(head,&avgs,calcs,"ppr",command);       //to satisfy default print arguments, and get nodes with prefix strings
        
    }
    
   if (strcmp(command,"psu") == 0) {
        scanf("%s", command);
        print_list(head,&avgs,calcs,"psu",command);       //to satisfy default print arguments, and get nodes with prefix strings
        
    }
      
      
      
    if (strcmp(command,"prl") == 0) {
        
        print_list(head,&avgs,calcs,command,decision);
        
    }  
      
    if (strcmp(command,"pcr") == 0) {
        
        char holder[4] = "pcr";                //used to tell print_list node what to do for command
        scanf("%s", command);                  //using calcs array that returns statistics for range values
        calcs[1] = *command- '0';
        scanf("%s", command);
        calcs[2] = *command-'0';
        printf("this is where we begin %d\n", calcs[1]);
        printf("this is where we end %d\n", calcs[2]);
        print_list(head,&avgs,calcs,holder,decision);
        
    }  
    
    if (strcmp(command,"pst") == 0) {
        

        decision = print_list(head,&avgs,calcs,command,"placeholder");   //instruct program to make a choice about printing
        //printf("%s",decision);
        if(strcmp(decision,"The list is empty") != 0) {
            printf(" The number of nodes in the list : %d\n", calcs[0]);
            printf(" The maximum count in the list : %d\n", calcs[1]);    //was not working properly
            printf(" The minimum count in the list : %d\n", calcs[2]);
            printf(" The average count in the list : %f\n", avgs);
        }    
    }   
    printf("command?  ");
    scanf("%s", command);
  
}


free(temp);
  //end of main   
}

void forced_delete_node(struct node **h, struct node **t,int *stats,char val[]) {
    struct node* check = *h;         //used to remove every unsatisfied condition of the linkedlist
    struct node* prev;               // node used to delete specified node if count was less than val
    char value = val[0];                      // to transfer the value
    int num_conv = value - '0';            //required to remove 48 to complete interger conversion

    
    while(check != NULL) {
         
        
        if (check->count <= num_conv) {
            if(check->count == stats[1]) {                 //because when the fde val is the max count, the max count must be reset
                stats[1] = 0;
            }    
            //printf("this is the count of the current check %d\n",check->count);
            //printf("this is the comparsion value %d\n", num_conv);
            if (check == *h) {
                *h = check->next;
                 forced_delete_node(h,t,stats,val);
            }
            else {
                prev->next = check->next;
                forced_delete_node(h,t,stats,val);

            }
        }
        prev = check;
        check = check->next;
    }
    
}
//end of forced delete node




void delete_node(struct node **h, struct node **t,int * stats, char string[]) {
  struct node* check = *h;         //linked list that will be used to check to delete specified string
  struct node* prev;               // node used to delete specified node if count went to zero
  while(check != NULL) {           // algorithm for the job
      if (strcmp(string,check->symbol[0]) == 0) {
         if (check->count == stats[1]){
            stats[1] -= 1;
         }    
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
              //puts("we almost done with this function");
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

char* print_list(struct node *h, float* avg, int * stats, char  c_string[],char part[]) {
  /* Prints the values stored in the nodes of the list */
  /* pointed to by h. */
  int i = 0;
  int j = 0;  
  float sum =0.0;
  char k_string[SIZE];                 //to keep the value of the command string (c_string) so list doenst print
  strcpy(k_string,c_string);  
  struct node * prev;              //to get maximum  and minimun values
  struct node * check = h;             //check if we are at the beginning of the list  
  if (h == NULL) {
    printf("The list is empty.\n");
    c_string = "The list is empty";
    return c_string;
  }
  else {
    //printf("Values in the list are:\n");
    while (check != NULL) {
      
      if(strcmp(k_string,"prl") == 0) {                           //conditional that prints the whole list
        printf("count: %d  symbol:  %s\n",check->count,check->symbol[0]);
        }
      
      if (strcmp(k_string,"pst") == 0 ) {                //algorithm that uses last node to compare against next node for largest value

            if (stats[1] < check->count) {               //to find the greatest count but if count is deleted stats must be chaged
                stats[1] = check->count;   
            }
            if (stats[2] >= check->count) {               //to find the least count
                stats[2] = check->count;   
            }

        else{
            stats[1] = check->count;                       //initalizes the greatest variable    
        }
      }
      
      sum += check->count;   
      //printf("size of string %d\n",sizeof(h->symbol[0]));
      /*while(i != sizeof(h->symbol) ) {
          printf("%s ", h->symbol);
          h->symbol[i];
          i++;
      } */
      i++;
      prev = check;  
      check = check->next;
    }
    stats[0] = i;  
    *avg = sum/(float)i;
    if (strcmp(k_string,"pst") == 0 ) {  
        return "done";
    }   
  }
  if (strcmp(k_string,"pcr") == 0 ) {      //conditional that prints desired indexes of linked list
    i = 0;
    check = h;
    while(check != NULL) {
        if(i >= stats[1] && i<=stats[2]) {     //used stats indexes as ranges instead
            printf("count: %d  symbol:  %s\n",check->count,check->symbol[0]);
        }
        check = check->next;
        i++;
    }
  } 
    
  if (strcmp(k_string,"ppr") == 0 ) {      //conditional that prints desired indexes of linked list
    i = 0;
    int a;                              //flag to let code know not to print the string
    check = h;
    char * function_compatible;
    function_compatible = part;
    while(check != NULL) {
        a = 0;
        //printf("this is the value the function is returning %d\n", strstr(check->symbol[0],part));
        //printf("this is the value in the node %s\n",part);
        
        while ( function_compatible [j] != '\0' ) {
            //printf(" in your spec string %c\n", function_compatible [j]);
            if (function_compatible[j] == check->symbol[0][j] ) {
                        
            }
            else {
                //puts("break this code");
                a = 1;
                break;                                         //if it does not satisfy the conditional, it will not work anyway
            }
            j++;    
        } 
        j = 0;
        
        if(a != 1) {     //used stats indexes as ranges instead
            printf("count: %d  symbol:  %s\n",check->count,check->symbol[0]);
        }
        check = check->next;
        i++;
    }
    //end of print prefix command  
  }    

  if (strcmp(k_string,"psu") == 0 ) {      //conditional that prints desired indexes of linked list
    i = 0;
    int a;                              //flag to let code know not to print the string
    int b;                              //contains length of test string so loop know to compare against the difference in strings
    check = h;
    char * function_compatible;
    function_compatible = part;
    //printf("this is what strlen says about the string %d\n",strlen(check->symbol[0])); 
    while(check != NULL) {
        a = 0;
        j = strlen(check->symbol[0]) -1;
        b =  strlen(function_compatible) -1;
        //printf("this is the value the function is returning %d\n", strstr(check->symbol[0],part));
        //printf("this is the value in the node %s\n",part);
        
        while ( b != -1 ) {
            //printf(" I compare string %c:  with symbol %c\n", function_compatible[b], check->symbol[0][j] );
            if (function_compatible[b] == check->symbol[0][j] ) {
                        
            }
            else {
                //puts("break this code");
                a = 1;
                break;                                         //if it does not satisfy the conditional, it will not work anyway
            }
            j--;
            b--;
        } 
        j = 0;
        
        if(a != 1) {     //used stats indexes as ranges instead
            printf("count: %d  symbol:  %s\n",check->count,check->symbol[0]);
        }
        check = check->next;
        i++;
    }
    //end of print suffix command  
  } 
  
    
} /* End of print_list */
