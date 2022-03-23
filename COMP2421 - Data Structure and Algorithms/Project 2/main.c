#include <stdio.h>          //Tariq Nazieh Odeh
#include <stdlib.h>         //1190699
#include <String.h>         //this header defines several functions to manipulate  strings and arrays --> to declare a set of functions to work strings(manipulating arrays of characters).


typedef struct node* Str_Node ;     //use to give a type a new name --> give a new name struct node* which is Str_Node.
typedef Str_Node Stack ;            //use to give a type a new name --> give a new name Str_Node which is Stack --> We can create struct node* using Stack.


struct node{                            //the structure of this memory block is defined by struct node, that allows to combine data items of different kinds.
    char statement[100] ;              //each node contains [statements --> Character Array(String)  with a maximum of 100 characters] and [a pointer to the next node in the list].
    Str_Node Next ;
} ;


int compare_string(char A[] , char B[]) ;       //a function declaration for compare_string, parameters is two array of char, return type is int
int Is_empty(Stack s) ;                         //a function declaration for Is_empty, parameters is Stack, return type is int
int Is_last(Str_Node A, Str_Node S) ;           //a function declaration for Is_last, parameters is struct node and list that node in it, return type is int
Str_Node last_entered(Stack s) ;                //a function declaration for last_entered, parameters is Stack, return type is node
void Delete_undo(Stack s) ;                     //a function declaration for Delete_undo, parameters is Stack, no return because void function
void Make_empty(Stack s) ;                      //a function declaration for Make_empty, parameters is Stack, no return because void function
Stack Make_stack();                             //a function declaration for Make_stack, return type is Stack which was created
void Insert_redo(char X[], Stack s) ;           //a function declaration for Insert_redo, parameters is array of char(string) and Stack, no return because void function
void Print_inf(Stack s) ;                       //a function declaration for Print_inf, parameters is Stack, no return because void function
void write_result(Stack s);                     //a function declaration for write_result, parameters is Stack, no return because void function


FILE *fp ;                                //file pointer

int main(){

    Stack s = Make_stack() ;            //creates a stack
    Stack reply = Make_stack() ;        //creates a stack to store removed element in it when enter undo

    printf("\n\t^^ Welcome  to program that simulates a simple text editor with the undo/redo ^^\n\n");
    printf("\t\t\t[There will be some special commands as follows:]\n");
    printf("\t**********************************************************************************\n");
    printf("\t*\t undo: this will undo (i.e., remove) that last entered statement         *\n");
    printf("\t*\t redo: this will redo (i.e., re-add) that last removed statement         *\n");
    printf("\t*\t print: this command will print the entire stored input text             *\n");
    printf("\t*\t save: will save the text to a file called (output.txt)                  *\n");
    printf("\t*\t quit: will exit the program and save all results to output.txt          *\n");
    printf("\t**********************************************************************************\n\n");


    while(1){                                   //infinite loop to continue reading sentences until the user quit the program
        printf("MyCommand > ") ;
        char sta[100] ;
        gets(sta) ;                             //read string from user and save it in sta

        if(compare_string(sta , "undo")){             //compare if user enter undo
            if(!Is_empty(s)){                         //to check if the list is not empty to remove last element
                Str_Node n = last_entered(s) ;        //store the last entered in list s
                Insert_redo(n->statement , reply) ;   //store the last entered element in reply
                Delete_undo(s) ;                      //delete the last entered statement
                Print_inf(s) ;                        //print the element in list
            }
             else{                                  //if the list empty
                printf("[There is no sentence to undo]\n");
                Print_inf(s) ;                         //print same list to know that no element to undo
            }
        }
        else if ( compare_string(sta ,"redo")){     //compare if user enter redo
            if(!Is_empty(reply)){                   //to check if the list is not empty to remove last element
                Str_Node n =last_entered(reply);    //store the last entered in list of removed elements
                Insert_redo(n->statement , s) ;     //insert the last removed statement in Stack
                Delete_undo(reply);                 //delete the elements that inserte in Stack
                Print_inf(s) ;                      //print the element in list insert
            }
            else{                                   //if the list empty
                printf("[There is no sentence to redo]\n");
                Print_inf(s) ;                         //print same list to know that no element to redo
            }

        }
        else if ( compare_string(sta , "print")){     //compare if user enter print
            Print_inf(s) ;                            //print the element in list
        }
        else if ( compare_string(sta , "save")){       //compare if user enter save
            printf("result > Saved successfully\n\n") ;
            write_result(s) ;                          //to write result on file

        }
        else if ( compare_string(sta , "quit")){        //compare if user enter quit
            printf("result > Good Bye!\n\n") ;
            write_result(s) ;             //to write result on file
            break ;                      //exit from while loop which exit the program
        }
        else{                           //If the user entered any sentences except for (undo, redo, print, save and quit) they will be saved in list
            Insert_redo(sta , s) ;
        }
   }        //end of while loop


    return 0;
}



int compare_string(char A[] , char B[]){    //function to compare two array of char (String) and return 1 if they equal
    int falg= 1 ;                           //integer variables declaration --> flag indicates the state of comparison

    if(strcmp(A,B) != 0){                   //use strcmp function on string that return 0 if the stings are equals
        falg = 0 ;                          //if the strings are not equals that mean strcmp not equal zero then let flag equal zero to denote a difference in strings
    }

    if(falg == 0){                          //check flag if equal zero that mean the strings are not equals (return 0) else (return 1) that mean the strings are equal
        return 0 ;
    }
    else{
        return 1 ;
    }
}                                           //end of function compare_string


int Is_empty(Stack s){              //function to check if Stack is empty
    return s->Next == NULL ;        //return 1 if empty and 0 if not empty
}


int Is_last(Str_Node A , Str_Node S){   //function to check if the node is last node in list
    return A->Next == NULL ;            //return 1 if is last and 0 if is not last
}


Str_Node last_entered(Stack s){          //function to return the last element entered
    Str_Node last_in ;                  //node to points to the last element entered
    if(!Is_empty(s)){                  //check if the Stake is not empty
        last_in = s ;
        while(last_in->Next != NULL){         //loop to traverse to the element entered in list
            last_in = last_in->Next ;
        }
        return last_in ;          //return the last element entered
    }

    printf("Stack is Empty!!\n") ;   //if the Stack is empty print and return zero
    return 0 ;
}


void Delete_undo(Stack s){                  //function to delete last node in list
    Str_Node bef_last ;                     //bef_last node it points to the element before the last in list
    Str_Node remove ;                       //remove node it points to the last element which we want delete it
    if(Is_empty(s)){                        //check if the Stake is empty
        printf( "Stack is Empty!!\n" ) ;
    }
    else{                                  //if the Stake is not empty
        bef_last = s ;
        remove = s ;
        while(remove->Next != NULL){       //loop to traverse to the last element of the list
            bef_last = remove ;            //to make it points the node before the last in list
            remove = remove->Next ;        //make remove points to the last element in list
        }
        if(remove == s){                    //check if remove equal the header
            s = NULL ;
        }
        else{
            bef_last->Next = NULL ;         //to make the node before the last, to separate from node the last
        }
    }
        free(remove) ;                      //delete last node

}


void Make_empty(Stack s){               //function to make list empty
    if(s == NULL){                      //check if Stack is booked in memory
        printf( "OUT space!!" ) ;
    }
    else{
        while(!Is_empty(s))             //loop to delete all element in list
        Delete_undo(s) ;                //call Delete_undo function to delete element
    }
}


Stack Make_stack(){                             //function to create new a Stack
    Stack s ;
    s = (Stack)malloc(sizeof(struct node)) ;    //malloc to allocates memory of size equal to the size of new node, and casting result to Stack

    if(s == NULL){                              //check if Stack is booked in memory
        printf( "OUT space!!" ) ;
    }

    s->Next = NULL ;                            //the next of header points on NULL
    Make_empty(s) ;                             //call Make_empty function to make list empty

    return s ;                                  //return the created Stack
}


void Insert_redo(char X[], Stack s){             //function to add new a element in list
    Str_Node tmp ;                               //new node tmp which we want to insert in list
    Str_Node last ;                              //new node last to points to last element
    last = s ;
    tmp = (Stack)malloc(sizeof(struct node)) ;   //malloc to allocates memory of size equal to the size of new node, and casting result to Stack

    if(tmp == NULL){                             //check if Stack is booked in memory
        printf("OUT space!!") ;
    }
    else{
        strcpy(tmp->statement , X) ;              //set the sentence in the tmp node
        tmp->Next = NULL ;                       //make tmp points to NULL
        while(last->Next != NULL)                //loop to traverse to the last element of the list
            last = last->Next;
    }
        last->Next = tmp;                       //make the last element points to new element, that mean added tmp to list
}


void Print_inf(Stack s){                        //function to print the elements of list
    Str_Node cell = s ;                         //make new node cell to points on elements
    printf("\nresult >\n") ;
    if(Is_empty(s)){                           //check if Stack is empty
        printf("Stack is Empty!!\n") ;
    }
    else{
        while(!Is_last(cell , s)){              //loop to go through and print all of the elements
            cell = cell->Next ;                 //to point on next element
            printf("%s\n", cell->statement) ;
        }
    }
    printf("\n") ;
}


void write_result(Stack s){                   //function to write result on file name output
    fp  = fopen ("output.txt" , "w") ;        //open the file whose name output to write on it
            Str_Node P = s ;                           //node to point on element which we want write on file
            if(Is_empty(s))                            //check if list is empty
                printf("Stack is Empty!!\n") ;
            else
                while(!Is_last(P, s)){                  //loop to write all element on file
                    P = P->Next ;
                   fprintf(fp,"%s\n" , P->statement) ;
                }

            fprintf(fp,"\n") ;
            fclose(fp) ;                 //close file
}


//Tariq Nazieh Odeh
//1190699

