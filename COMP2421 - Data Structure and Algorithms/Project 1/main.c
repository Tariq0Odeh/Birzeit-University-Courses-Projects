#include <stdlib.h>             //Tariq Nazieh Odeh
#include <stdio.h>              //1190699
#include <math.h>               //declares a set of functions to compute common mathematical operations and transformations
#include <string.h>             //this header defines several functions to manipulate  strings and arrays --> to declare a set of functions to work strings(manipulating arrays of characters).

typedef struct node* D_node ;                //use to give a type a new name --> give a new name struct node* which is D_node.
typedef struct Doubly_Linked_List* Doubly_List ; //use to give a type a new name --> give a new name Doubly_Linked_List* which is Doubly_List.


struct node{                                //the structure of this memory block is defined by struct node, that allows to combine data items of different kinds.
	int Coefficient ;                       //each node contains Coefficient,Exponent and [a pointer to the next node in the list][a pointer to the Prevus node in the list].
	int Exponent ;
	struct node* Next ;
	struct node* Prev ;
};


struct Doubly_Linked_List{          //to create header and tiler for Doubly Linked List
  struct node* Head ;
  struct node* Tail ;
};


void head_tail(Doubly_List List) ;                            //a function declaration for head_tail, parameters is Doubly Linked List, no return type because it void
void insert_node(Doubly_List Dlist ,int coeff , int pow) ;    //a function declaration for insert_node, parameters is Doubly Linked List and two intger, no return type because it void
void inset_into(Doubly_List Dlist , D_node tmp) ;             //a function declaration for inset_into, parameters is Doubly Linked List and node, no return type because it void
int Is_empty(Doubly_List Dlist) ;                             //a function declaration for Is_empty, parameters is Doubly Linked List,return type integer
void Print_list(Doubly_List Dlist) ;                          //a function declaration for Print_list, parameters is Doubly Linked List, no return type because it void
void substitute_x(Doubly_List Dlist , int X) ;                //a function declaration for substitute_x, parameters is Doubly Linked List and interger, no return type because it void
Doubly_List Add_equations(Doubly_List Dlsit1 , Doubly_List Dlist2) ;     //a function declaration for Add_equations, parameters is two Doubly Linked List,return type Doubly Linked List
Doubly_List Sub_equations(Doubly_List Dlsit1 , Doubly_List Dlist2) ;     //a function declaration for Sub_equations, parameters is two Doubly Linked List,return type Doubly Linked List
Doubly_List Mul_equations(Doubly_List Dlist1, Doubly_List Slidt2) ;      //a function declaration for Mul_equations, parameters is two Doubly Linked List,return type Doubly Linked List
void Fractionation_equation(char equ[500]);                              //a function declaration for Fractionation_equation, parameters is String, no return type because it void
void Extracting_factors(char part[] , char signal[500] , int parts_num); //a function declaration for Extracting_factors, parameters two array of char, no return type because it void
void Insert_factors() ;                                                  //a function declaration for Insert_factors, no parameters, no return type because it void                                                //a function declaration for Insert_factors, no parameters, no return type because it void
void Read_file() ;                                                       //a function declaration for Read_file, no parameters, no return type because it void
void Write_file(Doubly_List List, int op);


int counter_part = 0 ;          //to counter number of parts in each equations
int counter_equation = -1 ;     //to counter number of equations and start form -1 To store them in the correct way as it increases with each new equation


Doubly_List L[500] ; //array of Doubly List where we are store the Coefficient & Exponent for each equation
int num_equations = 0 ;     //to count number of equtions
int Array_Coefficient[500][250] ;    //store Coefficient in array where it follows the equation and the part which it in
int Array_Exponent[500][250] ;      //store Exponent in array where it follows the equation and the part which it in



int main(){

    int add_flag = 0 ;      //to check if add opration intered
    int sub_flag = 0 ;      //to check if subtraction opration intered
    int mul_flag = 0 ;      //to check if mult opration intered

    Doubly_List addition_res ;              //to store result of additional opration
    Doubly_List subtraction_res ;           //to store result of subtraction opration
    Doubly_List multiply_res ;              //to store result of multiply opration

    for (int a = 0; a < 500; a++){              //loop for create Doubly List
        L[a]=(Doubly_List)malloc(sizeof(Doubly_List));
        head_tail(L[a]);
    }

    printf("\n\t\t\t       ^^--------Welcome to Polynomial ADT--------^^\n");
    int x ;                 //to store value of x that want to subsite in equation
    int check = 0 ;       //to check if file read
    int inter ;          //to store the enter opration
	while(1){           //open loop to keep run until enter 6 to save result and exit
        printf("-----------------------------------------------------------------------------------------------------------------------\n");
        printf("\n\t\t\t\t\t  [Operations to Perform]\n");                                      //menu of opration
        printf("  \t\t\t***********************************************************");
        printf("  \n\t\t\t*\t\t1. Read File                              *");
        printf("  \n\t\t\t*\t\t2. Show Equations                         *");
        printf("  \n\t\t\t*\t\t3. Perform Addition                       *");
        printf("  \n\t\t\t*\t\t4. Perform Subtraction                    *");
        printf("  \n\t\t\t*\t\t5. Perform Multiplication                 *");
        printf("  \n\t\t\t*\t\t6. Save Result & Exit                     *");
        printf("  \n\t\t\t***********************************************************\n");
        printf("-----------------------------------------------------------------------------------------------------------------------\n");
        printf("\nEnter Operation 1, 2, 3, 4, 5 or 6:-->");
        scanf("%d" , &inter);

        if (inter == 1 && check == 1){      //it came first because in the event that the process of reading the file was entered while it was readed
            printf("\n\n\t\t\t#The File has already been read !!! \n");
		}
		if (inter == 1 && check == 0){     //if it the first time to read file
			Read_file() ;                //call function to read file
			Insert_factors() ;          //call function to save equation in list
			printf("\n\n\t\t\t#The File has been read successfully\n") ;
			check = 1 ;     //make check equal 1 that mean the file was readed
		}
		else if (inter == 2){           //if enter 2 that mean print the equations
                printf("-----------------------------------------------------------------------------------------------------------------------\n");
                printf("\n\nThe Equations in File: \n\n");
                for (int a = 0 ; a < num_equations ; a++){      //loop to move on all equations that store in array L and print them
                    printf("\t\t%d. ", a+1) ;
                    Print_list(L[a]) ;      //call function print list
                }
		}
		else if (inter == 3){       //if enter 3 that mean addition the equations
		    if (num_equations == 1){        //if that one equation that mean no additional
                printf("There is only one equation: ");
                Print_list(L[0]);
                printf("Enter value of x: ");
                scanf("%d", &x);
                substitute_x(L[0], x);
                add_flag = 1;
		    }
		    else{               //if that more than one equation
                if (num_equations >= 2) {
                    addition_res = Add_equations(L[0], L[1]) ;
                }
                for(int a = 2 ; a < num_equations ; a++) {  //loop to addition the equation
                    addition_res = Add_equations(addition_res, L[a]) ;      //add result to list
                }

                printf("\n\nAddition Result\n\t") ;
                Print_list(addition_res);                    //print the result of additional
                printf("Enter value of x: ") ;
                scanf("%d", &x) ;                            //read value of x
                substitute_x(addition_res, x) ;             //to substitute value of x
                add_flag = 1;
		    }
		}
		else if (inter == 4){                   //if enter 4 that mean subtraction the equations
		    if (num_equations == 1){           //if that one equation that mean no subtraction
                printf("There is only one equation:") ;
                Print_list(L[0]);
                printf("Enter value of x: ") ;
                scanf("%d", &x);                //read value of x
                substitute_x(L[0], x) ;         //to substitute value of x
                sub_flag = 1 ;
		    }
		    else{               //if that more than one equation
                if (num_equations >= 2) {
                    subtraction_res = Sub_equations(L[0], L[1]) ;
                }
                for(int a = 2 ; a < num_equations ; a++) {  //loop to subtraction the equation
                    subtraction_res = Sub_equations(subtraction_res, L[a]) ;     //add result to list
                }
                printf("\n\nSubtraction Result\n\t") ;
                Print_list(subtraction_res) ;               //print the result of subtraction
                printf("Enter value of x: ") ;
                scanf("%d", &x) ;                             //read value of x
                substitute_x(subtraction_res, x) ;          //to substitute value of x
                sub_flag = 1 ;
            }
		}
		else if (inter == 5){                   //if enter 5 that mean multiply the equations
		    if (num_equations == 1){           //if that one equation that mean no multiply
                printf("There is only one equation:") ;
                Print_list(L[0]);
                printf("Enter value of x: ") ;
                scanf("%d", &x);                //read value of x
                substitute_x(L[0], x) ;         //to multiply value of x
                mul_flag = 1 ;
		    }
		    else{               //if that more than one equation
                if (num_equations >= 2) {
                    multiply_res = Mul_equations(L[0], L[1]) ;
                }
                for(int a = 2 ; a < num_equations ; a++) {  //loop to multiply the equation
                    multiply_res = Mul_equations(multiply_res, L[a]) ;     //add result to list
                }
                printf("\n\nSubtraction Result\n\t") ;
                Print_list(multiply_res) ;               //print the result of multiply
                printf("Enter value of x: ") ;
                scanf("%d", &x) ;                             //read value of x
                substitute_x(multiply_res, x) ;          //to multiply value of x
                mul_flag = 1 ;
            }
		}
		else if (inter == 6){                   //if enter 6 that mean print the result that user inter it in file
            if (add_flag == 1){
                Write_file(addition_res , 3) ;      //if add opration is inter by user write it on file
            }
            if (sub_flag == 1){
                Write_file(subtraction_res , 4) ;   //if sub opration is inter by user write it on file
            }
            if (mul_flag == 1){
                Write_file(multiply_res , 5) ;   //if mul opration is inter by user write it on file
            }
            return 0 ;      //exit
		}
	}

	return 0;

}

void head_tail(Doubly_List Dlist){          //function to make header and tailer pointer to NULL to use it later to make it pointer on node
  Dlist->Head = NULL ;
  Dlist->Tail = NULL ;
}


int Is_empty(Doubly_List Dlist){            //function to check if doubly list is empty or not
    return Dlist->Tail == NULL ;
}


void insert_node(Doubly_List Dlist , int coeff , int pow){           //function to crate new node then insert it in list
  D_node tmp = (D_node)malloc(sizeof(struct node)) ;                //create new node tmp
  tmp->Coefficient = coeff ;                        //store Coefficient in new node
  tmp->Exponent = pow ;                            //store Exponent in new node

  inset_into(Dlist , tmp) ;                       //call function to insert new node in doubly linked list
}


void inset_into(Doubly_List Dlist , D_node tmp){      //function to insert in doubly linked list
   if (Is_empty(Dlist)) {           //if list is empty
    Dlist->Tail = tmp ;             //make the tailer point to the new node because it is the first node in the list
    Dlist->Tail->Next = NULL ;      //next of tailer point to NULL
    Dlist->Tail->Prev = NULL ;      //previous of tailer point to NULL
    Dlist->Head = Dlist->Tail ;     //make the head point to the new node because it is the first node in the list
  }
  else{                             //if list is not empty insert at end
    Dlist->Tail->Next = tmp ;       //next of tailer point to new node
    tmp->Next = NULL ;              //next of new node point to NULL
    tmp->Prev =Dlist->Tail ;        //previous of new node point to last node in list
    Dlist->Tail = tmp ;             //make tailer point to last node (new node)
  }
}


void Print_list(Doubly_List Dlist){     //function to print lsit
  D_node tmp = Dlist->Head ;            //node to pointer on node which want print it

  while(tmp){                       //while tmp not NULL -->loop to move on all node and print it
    if (tmp->Coefficient >= 0){     //if coefficient is positive print +
      printf("+") ;
    }
    printf("%dx^%d ", tmp->Coefficient, tmp->Exponent) ;
    tmp = tmp->Next ;       //move to next node
  }

  printf("\n") ;
}


void substitute_x(Doubly_List Dlist , int X){     //function to substitute x into equation and find the result of substitute x
    D_node tmp = Dlist->Head ;    //node to pointer on node which want print it
    int result = 0 ;              //to store result of substitute x
    int power_x = 0 ;             //to store result of power
    while(tmp){                   //while tmp not NULL -->loop to move on all node and find the result of substitute x
        power_x = pow(X , tmp->Exponent) ;      //find result of substitute x in power
        result = result + (tmp->Coefficient *  power_x) ;   //result of substitute x in equation
        tmp = tmp->Next ;       //move to next node
  }
  printf("\nSubstituted %d in equation and the result equal [%d]\n", X , result) ;   //print the result of substitute x
}


Doubly_List Add_equations(Doubly_List Dlsit1 , Doubly_List Dlist2){         //function to addition all polynomials and return the result(Doubly List)

	Doubly_List result=(Doubly_List)malloc(sizeof(struct Doubly_Linked_List)) ;     //create Doubly List to store the result of addition all polynomials
    head_tail(result) ;                 //make header and tailer pointer to NULL
	D_node equ1 = Dlsit1->Head ;        //make equ1 node pointer to header to start from first node in equation
    D_node equ2 = Dlist2->Head ;         //make equ2 node pointer to header to start from first node in equation


	while(equ1){                    //loop to move on all nodes in first equation and added them in result Doubly List
        insert_node(result , equ1->Coefficient , equ1->Exponent) ; //insert node with Coefficient and Exponent in result Doubly List
        equ1 = equ1->Next ;         //move to next node
	}

    while(equ2){                    //loop to move on all nodes in first equation and added them in result Doubly List
        insert_node(result , equ2->Coefficient , equ2->Exponent) ;  //insert node with Coefficient and Exponent in result Doubly List
        equ2 = equ2->Next ;       //move to next node
    }

    D_node p1 = result->Head ;    //create node to pointer to node that we store result addition in it
	D_node p2 ;                   //create node to pointer on node that want addition to node pointer one if power equal
	D_node rem ;            //to remove the node which we are added to pointer 1 node

	while(p1 && p1->Next){      //first loop to compare first node with other nodes
		p2 = p1 ;
		while (p2->Next){        //loop to move on all node and added nodes that his power equal
			if (p1->Exponent == p2->Next->Exponent){    //check if two node have same power
				p1->Coefficient = p1->Coefficient + p2->Next->Coefficient ;     //addition Coefficient to nodes that have same power
				rem = p2->Next ;          //make node rem pointer on the node who added to another node
				p2->Next = p2->Next->Next ; //make p2 pointer to next node that we are not added to another node
				free(rem) ;             //delete node that added to another node
			}
			else {          //if two node haven't same power
				p2 = p2->Next ; //move to next node
			}
		}
		p1 = p1->Next ; //move to next node that we want to compare
	}
	return result ;     //return result of addition all polynomials
}


Doubly_List Sub_equations(Doubly_List Dlsit1 , Doubly_List Dlist2){ //function to subtraction all polynomials and return the result(Doubly List)

	Doubly_List result=(Doubly_List)malloc(sizeof(struct Doubly_Linked_List)) ;     //create Doubly List to store the result of addition all polynomials
    head_tail(result) ;                 //make header and tailer pointer to NULL
	D_node equ1 = Dlsit1->Head ;        //make equ1 node pointer to header to start from first node in equation
    D_node equ2 = Dlist2->Head ;         //make equ2 node pointer to header to start from first node in equation


	while(equ1){                    //loop to move on all nodes in first equation and sub them in result Doubly List
        insert_node(result , equ1->Coefficient , equ1->Exponent) ; //insert node with Coefficient and Exponent in result Doubly List
        equ1 = equ1->Next ;         //move to next node
	}

    while(equ2){                    //loop to move on all nodes in first equation and sun them in result Doubly List
        insert_node(result , (-1) * equ2->Coefficient , equ2->Exponent) ;  //insert node with Coefficient and Exponent in result Doubly List, we mult the Coefficient whith -1 because we sub first equation from second
        equ2 = equ2->Next ;       //move to next node
    }

    D_node p1 = result->Head ;    //create node to pointer to node that we store result subtraction in it
	D_node p2 ;                   //create node to pointer on node that want subtraction to node pointer one if power equal
	D_node rem ;              //to remove the node which we are sub to pointer 1 node

	while(p1 && p1->Next){      //first loop to compare first node with other nodes
		p2 = p1 ;
		while (p2->Next){        //loop to move on all node and sub nodes that his power equal
			if (p1->Exponent == p2->Next->Exponent){    //check if two node have same power
				p1->Coefficient = p1->Coefficient + p2->Next->Coefficient ;     //subtraction Coefficient to nodes that have same power
				rem = p2->Next ;          //make node rem pointer on the node who sub to another node
				p2->Next = p2->Next->Next ; //make p2 pointer to next node that we are not sub to another node
				free(rem) ;             //delete node that sub to another node
			}
			else {          //if two node haven't same power
				p2 = p2->Next ; //move to next node
			}
		}
		p1 = p1->Next ; //move to next node that we want to compare
	}
	return result ;     //return result of subtraction all polynomials
}


Doubly_List Mul_equations(Doubly_List Dlsit1 , Doubly_List Dlist2){ //function to multiplication all polynomials and return the result(Doubly List)

    Doubly_List result = (Doubly_List)malloc(sizeof(struct Doubly_Linked_List)) ;     //create Doubly List to store the result of addition all polynomials
    head_tail(result) ;                 //make header and tailer pointer to NULL
    D_node equ1 = Dlsit1->Head ;        //make equ1 node pointer to header to start from first node in equation
    D_node equ2 = Dlist2->Head ;         //make equ2 node pointer to header to start from first node in equation

    while(equ1){		// Iterates through both polynomials by taking one term and finding its similar term in second polynomial then multiplies the coefficients and sums the power  of the term
        while (equ2) {
            insert_node(result,(equ2->Coefficient * equ1->Coefficient), (equ2->Exponent + equ1->Exponent));
            equ2 = equ2->Next;
        }
        equ1 = equ1->Next;
        equ2 = Dlist2->Head;
    }

    D_node p1 = result->Head ;    //create node to pointer to node that we store result subtraction in it
	D_node p2 ;                   //create node to pointer on node that want subtraction to node pointer one if power equal
	D_node rem ;              //to remove the node which we are sub to pointer 1 node

	while(p1 && p1->Next){      //first loop to compare first node with other nodes
		p2 = p1 ;
		while (p2->Next){        //loop to move on all node and sub nodes that his power equal
			if (p1->Exponent == p2->Next->Exponent){    //check if two node have same power
				p1->Coefficient = p1->Coefficient + p2->Next->Coefficient ;     //subtraction Coefficient to nodes that have same power
				rem = p2->Next ;          //make node rem pointer on the node who sub to another node
				p2->Next = p2->Next->Next ; //make p2 pointer to next node that we are not sub to another node
				free(rem) ;             //delete node that sub to another node
			}
			else {          //if two node haven't same power
				p2 = p2->Next ; //move to next node
			}
		}
		p1 = p1->Next ; //move to next node that we want to compare
	}
		return result;
}


void Insert_factors(){           //function to create doubly linked list and save equations that read from file
    int b = 0 ;                     //to move on all parts
    for(int a=0 ; a < num_equations ;){         //loop passes on all factors to be stored in a list
        if (Array_Coefficient[a][b] != 0){      //check if coefficient not equal zero that mean the part not equal zero
            insert_node(L[a], Array_Coefficient[a][b] , Array_Exponent[a][b]) ; //insert coefficient & exponent in list
            }
        if (Array_Coefficient[a][b] == 0){          //check if coefficient not equal zero that mean the part equal zero
            a++ ;           //next equation
            b = -1 ;        //to start from first part in next equation
        }
        b++ ;       //next part
    }
}



void Extracting_factors(char part[] , char signal[500] , int parts_num){     //function takes parts of equations and extracts coefficient and power

    char coefficient[500] ;             //to store coefficient
    char Exponent[500] ;                //to store power
    int counter = 0 ;                   //to count number of x and ^ in each part

    for(int a =0 ; a < strlen(part) ; a++ ){        //loop for count number of x and ^ in each part
        if(part[a] == 'x'|| part[a] == 'X'){        //if found x in part increase counter
            counter++ ;
        }
        if(part[a] == '^'){     //if found x in part increase counter
            counter++ ;
        }
    }

    int x = 0 ;
    while (part[x] != 'x' && x < strlen(part)){ //loop for read coefficient that be before x in part
        coefficient[x] = part[x] ;              //store coefficient in array of coefficient
        x++ ;
    }

    int coeff = atoi(coefficient) ;          //function atoi converts the string argument string to an integer (type int)
    if (coeff == 0){                        //if coefficient equal 0 make it equal 1
        coeff = 1 ;                         //this is because if there is no number before the x by default it means that it is 1
    }
    if (signal[parts_num] == '-') {          //check if coeff is minus and if it make it minus by multiply coefficient by -1
        coeff = coeff * (-1) ;
    }


    x = strlen(part) - 1 ;              //make b equal length of part to start reading from the end of the part (read ^)
    int y = 0 ;
    while (part[x] != '^' && x > 0){    //loop for read coefficient that be after ^ in part
        Exponent[y] = part[x] ;         //store power in array of power
        y++ ;
        x-- ;                       //to move from the end of part to the until it is found ^
    }

    int pow = atoi(Exponent) ;      //function atoi converts the string argument string to an integer (type int)

    if(counter == 1){           //if counter equal 1 that mean there is a power equal to 1 since there is an x
        pow = 1 ;
    }
    else if(counter == 0){      //if counter equal 0 that mean there is not an x, so that mean x^0
        pow = 0 ;
    }

    if(parts_num == 0){         //if is the first part from rquation
        counter_part = 0 ;      //set counter of parts equal 0
        counter_equation++ ;     //increases counter equation because it is new equation come
    }

    Array_Coefficient[counter_equation][counter_part] = coeff ; //store Coefficient in array where it follows the equation and the part which it in
    Array_Exponent[counter_equation][counter_part] = pow ;  //store Exponent in array where it follows the equation and the part which it in
    counter_part++ ;        //increases counter of parts in same equation
}


void Fractionation_equation(char equ[500]){ //function for extracting and storing signals, splitting the equation at (+ -) into smaller parts
                                            //then he passes it to another function to extract the coefficients and power
    int f = 1 ;                     //to management the first sign in the equation
    char signal[500] ;              //to store signals

    if(equ[0] == '-'){             //to take first signal in equation --> check if signal -
        signal[0] = '-' ;           //store signal -
        f-- ;
    }
    else if(equ[0] != '-'){         //to take first signal in equation --> check if signal + or no signal mean +
        signal[0] = '+' ;           //store signal +
    }

    for(int a =0 ; a < strlen(equ) ; a++){      //loop to extracting and storing signals from equation
        if(equ[a] == '+' || equ[a] == '-'){     //check signals
            signal[f] = equ[a] ;                 //store signals
            f++ ;
        }
    }

    int parts_num = 0 ;                      //to counter number splitted parts

    char *parts = strtok(equ, "-+");        //split the first part (uses strtok function on string)
    while(parts != NULL){                   //move to other parts
        Extracting_factors(parts , signal , parts_num) ;    //call function to extract the coefficients and power of each parts in equation
        parts_num++ ;                       //increase number of splitted parts
        parts = strtok(NULL, "-+") ;        //split other parts
    }
}


void Read_file(){                            //function to reads the file name equations
    FILE *filp ;                             //file pointer
    char equ[500] ;                         //to store the equation that read from the file
    filp = fopen("equations.txt" , "r") ;   //open the file whose name equations to read from it

    if(filp == NULL){                       //if file does not exist
        printf("The File does not exist!!") ;
    }
    else{                                         //if file exist and was opened successfully
        while(fgets(equ , 500 , filp) != NULL){   //read equations(line by line) and store it in equ string
            num_equations++ ;                     //increase number of equation
            Fractionation_equation(equ) ;         //call function to fractionation the equation then extract the coefficients and power from the equation
        }
    }
    fclose(filp) ;              //close equations file
}

void Write_file(Doubly_List List, int op){ //function to write result on file
    FILE *filp ;                            //file pointer

    filp = fopen("results.txt", "a") ;     //opening file in writing by adding

    if (filp == NULL){                     //if file does not exist
        printf("Error! The file does not exist!!") ;
        exit(1) ;
    }
	if (op == 3) {                      //check which opration is usese
		fprintf(filp, "\n[Addition]  ") ;
	}
	else if (op == 4) {
		fprintf(filp, "\n[Subtraction]  ") ;
	}
	else if (op == 5) {
		fprintf(filp, "\n[Multiplication]  ") ;
	}
	D_node newNode = List->Head;
  	while (newNode) {           //loop to print result of equation on file
    	if (newNode->Coefficient >= 0) {
      		fprintf(filp, "+");
    	}
    	fprintf(filp, "%dx^%d",newNode->Coefficient,newNode->Exponent) ;

    	newNode = newNode->Next ;
    }
    fprintf(filp, "--------------------------------------------------------------------");
    fclose(filp) ;          //exit from file
}
