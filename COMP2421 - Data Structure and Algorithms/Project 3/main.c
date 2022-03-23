#include <stdio.h>          //Tariq Nazieh Odeh
#include <stdlib.h>         //1190699
#include <conio.h>          //to use inbuilt functions like getch() and clrscr()
#include <time.h>           //to get and manipulate date and time information.
#include <String.h>         //this header defines several functions to manipulate  strings and arrays --> to declare a set of functions to work strings(manipulating arrays of characters).


typedef struct avl_node* AVL ;         //use to give a type a new name --> give a new struct avl_node* which is AVL
typedef struct tm* date ;              //use to give a type a new name --> give a new tm* which is date


struct avl_node{                      //the structure of this memory block is defined by struct avl_node, that allows to combine data items of different kinds
    char name[59] ;                   //each node contains these data
    char gender ;
    date addmissionDate ;
    date birthDate ;
    char Illness[59] ;
    char Address[59] ;
    char BloodType[9] ;
    AVL left ;
    AVL right ;
    int height ;
};


int flag_same = 1 ;                 //to flag if the patient already exists or not
void print_start();                 //a function declaration for print_start, to print information

int avl_height(AVL T) ;             //a function declaration for avl_height, parameters is AVL Tree, return type is int
int max_num(int x , int y) ;        //a function declaration for max_num, parameters is two integer number, return type is int
int get_balance(AVL T) ;            //a function declaration for get_balance, parameters is AVL Tree, return type is int
AVL create_node(char name[59] , char gender , date admission , date birth , char illness[59] , char address[59] , char bloodtype[9]) ; //a function declaration for create_node, parameters is patient information, return type is node of avl tree
AVL min_value_node(AVL T) ;               //a function declaration for min_value_node, parameters is AVL Tree, return type is avl
AVL read_from_file(AVL T) ;               //a function declaration for read_from_file, parameters is AVL Tree, return type is avl
date strp_time(char st[8]) ;              //a function declaration for strp_time, parameters is array of char, return type is date struct
void same_illness(AVL T , char illness[59]) ;   //a function declaration for same_illness, parameters is AVL Tree and array of char, void no return type
void save_to_file(AVL T , FILE* outp) ;         //a function declaration for save_to_file, parameters is AVL Tree and file pointer, void no return type
void delete_all_tree(AVL T) ;                   //a function declaration for delete_all_tree, parameters is AVL Tree, void no return type
AVL search_in(AVL T, char name[59]) ;           //a function declaration for search_in, parameters is AVL Tree, return type is avl
void print_in_order(AVL T) ;                    //a function declaration for print_in_order, parameters is AVL Tree, void no return type
AVL insert_inTree(char name[] , char gender , date admission , date birth , char illness[] , char address[] , char bloodtype[] , AVL T) ; //a function declaration for insert_inTree, return type is avl
AVL left_rotate(AVL T) ;                        //a function declaration for left_rotate, parameters is AVL Tree, return type is avl
AVL right_rotate(AVL T) ;                       //a function declaration for right_rotate, parameters is AVL Tree, return type is avl
AVL delete_node(AVL root, char name[59]) ;      //a function declaration for delete_node, parameters is AVL Tree and array of char, return type is avl
AVL insert_from_user(AVL T) ;                   //a function declaration for insert_from_user, parameters is AVL Tree, return type is avl

/*-----------------------------------------------------------------------------------------------*/

typedef struct hash Hash_it ;                      //use to give a type a new name --> give a new struct hash which is Hash_it
typedef struct HashTable HashTable ;                //use to give a type a new name --> give a new struct HashTable which is HashTable


struct hash{                     //the structure of this memory block is defined by struct hash, that allows to combine data items of different kinds
    char name[59] ;              //each node contains these data
    char gender ;
    date addmissionDate ;
    date birthDate ;
    char Illness[59] ;
    char Address[59] ;
    char BloodType[9] ;
    int flag ;
};


struct HashTable{          //define the Hash Table
    Hash_it* items ;
    int totalsize ;
    int size ;
};

int not_empty = 0 ;         //to count number of spots that not empty in hash table

int is_prime(int x) ;                       //a function declaration for is_prime, parameters is integer, return type is integer
void save_table_to_file (HashTable Ta) ;    //a function declaration for save_table_to_file, parameters is HashTable, no return type
int new_size(int old_size) ;                //a function declaration for new_size, parameters is integer, return type is integer
void readfile_HashTable(HashTable *Ta) ;    //a function declaration for readfile_HashTable, parameters is address to hash table, no return type
void insert_table(HashTable *Ta, Hash_it new_item) ;    //a function declaration for insert_table, parameters is address to hash table and hash node, no return type
void replay_size(HashTable *Ta) ;                       //a function declaration for replay_size, parameters is address to hash table and hash node, no return type
void delete_item_table(HashTable Ta, char name[59]) ;   //a function declaration for delete_item_table, parameters is hash table and array of char, no return type
int hash_code(HashTable Ta, char name[59]) ;            //a function declaration for hash_code, parameters is hash table and array of char, return type is integer
int linear_hashing(HashTable Ta, char name[59]) ;       //a function declaration for linear_hashing, parameters is hash table and array of char, return type is integer
void print_hashTable(HashTable Ta) ;                    //a function declaration for print_hashTable, parameters is hash table, no return type
int search_item(HashTable Ta, char name[59]) ;           //a function declaration for serch_item, parameters is hash table nd array of char, return type is integer

/*-----------------------------------------------------------------------------------------------*/

int main()
{
    AVL AVL_Tree = NULL ;                   //create empty AVL tree
    HashTable Table = {NULL , 10 , 0} ;  //create empty Hash Table and make totalsize equal 10
    int loadedTable = 0 ;              //to use it to flag if the hash table if empty or not

    int input ;                     //to read from user the input from menu
    do{

    print_start() ;         //call function print_start to print the system inf

    printf("\n     [Tree Table]\n\n") ;
    printf("1- Load patients from a file 'patients.txt'.\n") ;
    printf("2- Insert a new Patient.\n") ;
    printf("3- Search for a specific patient.\n") ;
    printf("4- List all patients with their associated data.\n") ;
    printf("5- List all patients that have the same illness.\n") ;
    printf("6- Delete a specific patient from the system.\n") ;
    printf("7- Save all words in file 'patients_hash.data' and show Hash Table.\n\n") ;

    scanf("%d" , &input) ;  //read input from user
    fflush(stdin) ;                     //to clear the data stored in buffer and can read another data from user

    switch(input){
    case 1:                                      //if enter 1
        system("cls") ;                         //to clearing the Screen
        AVL_Tree = read_from_file(AVL_Tree) ;   //call the function to read the file and insert the data in tree
        getch() ;                               //to pause the Output Console until a key is pressed
        system("cls") ;                          //to clearing the Screen
        break ;                                  //back to menu

    case 2:                                 //if enter 2
        system("cls") ;                     //to clearing the Screen
        AVL_Tree = insert_from_user(AVL_Tree) ;        //to insert patient from user
        break ;                             //back to menu

    case 3:                                 //if enter 3
        system("cls") ;                     //to clearing the Screen
        char name[59] ;                     //to save the name that we want to search for
        printf("Enter patient name:\n") ;
        fflush(stdin) ;                     //to clear the data stored in buffer and can read another data from user
        gets(name) ;
        AVL current = search_in(AVL_Tree , name) ;  //pass the name to function to search for

        if(current){
            system("cls");
            printf("Name: %s, Gender: %c, AdmissionDate: %d-%d-%d, Birthdate: %d-%d-%d, Illness: %s, Address: %s, BloodType: %s\n"
                , current->name , current->gender
                , current->addmissionDate->tm_mday , current->addmissionDate->tm_mon , current->addmissionDate->tm_year + 1900
                , current->birthDate->tm_mday , current->birthDate->tm_mon , current->birthDate->tm_year + 1900
                , current->Illness , current->Address , current->BloodType) ;



            char op ;           //if they enter y which mean he want to uptade
            printf("\nIf you want to Update him press [y] \n") ;
            op = getch() ;
            if(op == 'y'){  //if they want to uptade
                printf("\nChoose what to update: \n") ;
                printf("1- Name\n2- Gender\n3- Admission date\n4- Birth date\n5- Illness\n6- Address\n7- Blood type\n8- Back\n\n") ;

                char option ;           //choose the data which want to update him
            do{
                scanf("%c", &option) ;

                if(option == '1'){                          //if chosen 1
                    char gender = current->gender ;         //enter the patient’s data on a new node and change the name, then delete the old patient’s information and add his information after the update
                    char address[59] ;
                    char blood[9] ;
                    char illness[59] ;
                    strcpy(address, current->Address) ;
                    strcpy(blood, current->BloodType) ;
                    strcpy(illness, current->Illness) ;
                    int add_day = current->addmissionDate->tm_mday ;
                    int add_month = current->addmissionDate->tm_mon ;
                    int add_year = current->addmissionDate->tm_year ;
                    int bir_day = current->birthDate->tm_mday ;
                    int bir_month = current->birthDate->tm_mon ;
                    int bir_year = current->birthDate->tm_year ;

                    date add = (date)malloc(sizeof(struct tm)) ;   //create new struct of date
                    add->tm_mday = add_day ;                            //enter the date into node
                    add->tm_mon = add_month ;
                    add->tm_year = add_year ;

                    date birth = (date)malloc(sizeof(struct tm)) ;    //create new struct of date
                    birth->tm_mday = bir_day ;                            //enter the date into node
                    birth->tm_mon = bir_month ;
                    birth->tm_year = bir_year ;

                    printf("New Name: ") ;      //because the update is on the name and it is the key with which the tree is balanced
                    char name[59] ;             //therefore, it is necessary to delete the previous patient node and add the new node after entering the new name on it
                    fflush(stdin) ;
                    gets(name) ;
                    fflush(stdin) ;
                    AVL_Tree = delete_node(AVL_Tree , current->name) ;
                    AVL_Tree = insert_inTree(name , gender , add , birth , illness , address , blood , AVL_Tree) ;
                    printf("[Done]") ;
                    current = search_in(AVL_Tree , name) ;                   //pass the new name to function to search for and and complete the amendment to the new name
                    printf("\n\nChoose what to update: ") ;

                }

                else if(option == '2'){                                         //if chosen 2
                    printf("Current gender is: %c \n" , current->gender) ;      //print the current gender
                    if(current->gender == 'f' || current->gender == 'F'){       //and check if the gender female make it male and if it male make it female
                        current->gender = 'M' ;
                    }
                    else{
                        current->gender = 'F' ;
                    }
                    fflush(stdin) ;                             //to clear the data stored in buffer and can read another data from user
                    printf("New gender: %c\n" , current->gender) ;
                    printf("[Done]\n") ;
                    printf("\n\nChoose what to update: ") ;
                }

                else if(option == '3'){                          //if chosen 3
                    int day , month , year;                       //to save new data
                    printf("Day: ") ;                           //read from user new addmission Date
                    scanf("%d", &day) ;
                    printf("Month: ") ;
                    scanf("%d", &month) ;
                    printf("Year: ") ;
                    scanf("%d", &year) ;
                    current ->addmissionDate->tm_mday = day ;
                    current->addmissionDate->tm_mon = month ;
                    current->addmissionDate->tm_year = year -1900 ;
                    fflush(stdin) ;                             //to clear the data stored in buffer and can read another data from user
                    printf("[Done]\n") ;
                    printf("\n\nChoose what to update: ") ;
                }

                else if(option == '4'){                          //if chosen 4
                    int day , month , year;                       //to save new data
                    printf("Day: ") ;                           //read from user new addmission Date
                    scanf("%d", &day) ;
                    printf("Month: ") ;
                    scanf("%d", &month) ;
                    printf("Year: ") ;
                    scanf("%d", &year ) ;
                    if((day <=0 || day >30) || (month <=0 || month >12) || (year <=1000 || year >2021)){      //to check if the day in right format
                        printf("-->Not Inserting-->  The date is not in desired form!!!\n") ;
                        getch() ;
                        break ;
                    }
                    current ->birthDate->tm_mday = day ;
                    current->birthDate->tm_mon = month ;
                    current->birthDate->tm_year = year -1900 ;
                    fflush(stdin) ;                             //to clear the data stored in buffer and can read another data from user
                    printf("[Done]\n") ;
                    printf("\n\nChoose what to update: ") ;
                }

                else if(option == '5'){                          //if chosen 5
                    char illness[59] ;
                    printf("New illness: ");
                    fflush(stdin) ;                             //to clear the data stored in buffer and can read another data from user
                    gets(illness) ;                             //read the new illness from user
                    fflush(stdin) ;
                    strcpy(current->Illness , illness) ;
                    printf("[Done]\n") ;
                    printf("\n\nChoose what to update: ") ;
                }

                else if(option == '6'){                          //if chosen 6
                    char address[59] ;
                    printf("New address: ") ;
                    fflush(stdin) ;                             //to clear the data stored in buffer and can read another data from user
                    gets(address) ;                             //read the new illness from user
                    fflush(stdin) ;
                    strcpy(current->Address, address) ;
                    printf("[Done]\n") ;
                    printf("\n\nChoose what to update: ") ;

                }

                else if(option == '7'){                          //if chosen 7

                    char blood[9] ;
                    printf("Blood: ") ;
                    fflush(stdin) ;                             //to clear the data stored in buffer and can read another data from user
                    gets(blood) ;                               //read the new illness from user
                    fflush(stdin) ;
                    strcpy(current->BloodType , blood) ;
                    printf("[Done]\n") ;
                    printf("\n\nChoose what to update: ") ;
                }
                                //if the user enter the wrong
                else if((option == '1') && (option != '2') && (option != '3') && (option != '4') && (option != '5') && (option != '6') && (option != '7') && (option != '8')){
                        printf("Invalid entry\n") ;
                        fflush(stdin) ;                             //to clear the data stored in buffer and can read another data from user
                        getch() ;
                        printf("\n\nChoose what to update: ") ;
                }

            }while(option != '8') ;                 //if chosen 8 exit from update and go to the menu
                system("cls") ;
                break ;
          }
        }

        else{                        //if the name is not in the tree
            system("cls") ;
            printf("This patient is not in the system!") ;
            char op ;                //if they enter y which mean he want to insert a new patientx press
            printf("\n\nIf you want insert a new patientx press [y] \n") ;
            op = getch() ;
            if(op == 'y'){  //if they want to insert a new patient press y
                insert_from_user(AVL_Tree) ;        //to insert patient from user
            }
        }
        system("cls") ;
        break ;

    case 4:                             //if enter 4
        system("cls") ;
        print_in_order(AVL_Tree) ;      //call function print_in_order to patients in lexicographic order with their associated information
        getch() ;
        system("cls") ;
        break ;

    case 5:                          //if enter 5
        system("cls");
        char illness[59] ;
        printf("Illness: ") ;
        fflush(stdin) ;
        gets(illness) ;             //read the illness from user which want to patients that have the same illness
        fflush(stdin) ;
        same_illness(AVL_Tree , illness) ;
        printf("\n\nDone\n") ;
        getch() ;
        system("cls") ;
        break ;

    case 6:                          //if enter 6
         system("cls") ;

        if(AVL_Tree == NULL){       //check if tree if empty
            printf("No data entered !!!\n");
        }
        else{
        char name[59] ;
        printf("Please enter the name of the patient you want to delete:\n") ;
        fflush(stdin) ;
        gets(name) ;        //read the name of the patient from user which want to delete

        while(!search_in(AVL_Tree , name) && strcmp( name ,"0") != 0){      //loop if the user enter the name is not existing to let him enter another name or exit
            system("cls") ;
            printf("patient not found!\nEnter an existing name or 0 to back:\n") ;
            gets(name) ;            //read from user again
        }

        if(strcmp(name,"0") == 0){          //if enter 0 that mean exit
                system("cls") ;
                break ;
            }

        AVL_Tree = delete_node(AVL_Tree , name) ;   //if the name existing then call delete_node to delete this patient
        printf("[Deleted!]\n") ;
        }

        getch() ;
        system("cls") ;
        break ;     //exit and go menu

    case 7:                                 //if enter 6
        system("cls") ;
        FILE *output = fopen("patients_hash.data" , "w") ;  //write on file name patients_hash.data

        while(output == NULL){                  //if the file does not create
           printf("Error!\nCan't create the file!\n\n") ;
           getch() ;
           system("cls") ;
           break ;              //go menu
        }
        save_to_file(AVL_Tree , output) ;   //call function save_to_file to save the data on file name patients_hash.data
        fclose(output) ;
        printf("[Saved!]\nPress any key to show the menu of Hash Table:\n") ;
        getch() ;
        system("cls") ;
        break ;

    default:
        system("cls") ;
        break;
    }
}while(input!= 7) ;

/*-----------------------------------------------------------------------------------------------*/

    int in_hash ;                     //to read from user the input from menu
    do{

        print_start() ;         //call function print_start to print the system inf

        printf("\n     [Hash table]\n\n") ;
        printf("1 -Load hash table from file 'patients_hash.data'.\n") ;
        printf("2 -Print hashed table.\n") ;
        printf("3 -Print out table size.\n") ;
        printf("4 -print out used hashed function.\n") ;
        printf("5 -Insert a new record to hash table.\n") ;
        printf("6 -Search for a specific patient.\n") ;
        printf("7 -Delete a specific record.\n") ;
        printf("8 -Save hash table back to file.\n") ;
        printf("0 -Exit.\n\n") ;


        scanf("%d" , &in_hash) ;                //read input from user
        fflush(stdin) ;                     //to clear the data stored in buffer and can read another data from user

    switch(in_hash){

        case 1:                             //if they enter 1 in hash table
            readfile_HashTable(&Table) ;    //read records from file
            if(Table.totalsize != 0){       //check if the hash table is empty or not
                loadedTable = 1 ;
            }
            getch() ;
            system("cls") ;
            break ;

        case 2:                             //if they enter 2 in hash table
            system("cls") ;
            if(!loadedTable)    //if the hash table is empty
                printf("There is no data!!!\nPress any key to back: ") ;
            else
                print_hashTable(Table) ;        //if the hash table is not empty print the entire table to the screen including empty spots
            getch() ;
            system("cls");
            break ;

        case 3:                             //if they enter 3 in hash table
            system("cls");
            printf("Hash table size: %d\n", Table.totalsize) ;      //print Hash table size
            printf("Number of records: %d\n", not_empty) ;          //print Number of records
            getch() ;
            system("cls") ;
            break ;

        case 4:                             //if they enter 4 in hash table
            system("cls") ;                 //print out the used hash function
            printf("[Open Addressing]\n") ;
            printf("h(x) = (Hash(x) + i) %% Table size\n") ;
            printf("     = (Hash(x) + i) %% %d\n\n" , Table.totalsize) ;
            printf("[Linear Probing]\n") ;
            printf("Linear Probing: h(x) = (index + i) %% Table size\n") ;
            printf("                     = (index + i) %% %d\n", Table.totalsize) ;
            getch() ;
            system("cls") ;
            break ;

        case 5:                             //if they enter 5 in hash table
            system("cls") ;
            if(loadedTable){            //if hash table does not empty
                char name[59] ;             //to save associated data for patient
            char blood[9] ;
            char address[59] ;
            char ill[59] ;
            char gender ;
            int add_day , add_month , add_year ;
            int bir_day , bir_month , bir_year ;
            printf("--> Insert a new patient from user with all its associated data\n\n") ;
            printf("--> Name: ") ;
            fflush(stdin) ;         //to clear the data stored in buffer and can read another data from user
            gets(name) ;            //read string from user
            fflush(stdin) ;         //to clear the data stored in buffer and can read another data from user
            printf("--> Gender: ") ;
            scanf("%c" , &gender) ; //read inger and char do not need to use fflush()function to clear the data stored in buffer
            printf("--> Day of admission: ") ;
            scanf("%d" , &add_day) ;
            printf("--> Month of admission: ") ;
            scanf("%d" , &add_month) ;
            printf("--> Year of admission: ") ;
            scanf("%d" , &add_year) ;
            printf("--> Day of birth: ") ;
            scanf("%d" , &bir_day) ;
            printf("--> Month of birth: ") ;
            scanf("%d" , &bir_month);
            printf("--> Year of birth: ") ;
            scanf("%d" , &bir_year) ;
            printf("--> Illness: ") ;
            fflush(stdin) ;             //to clear the data stored in buffer and can read another data from user
            gets(ill );
            fflush(stdin) ;
            printf("--> Address: ") ;
            fflush(stdin) ;
            gets(address) ;
            fflush(stdin) ;
            printf("--> Blood type: ") ;
            fflush(stdin) ;
            gets(blood) ;
            fflush(stdin) ;

            if((add_day <=0 || add_day >30) || (add_month <=0 || add_month >12) ||(add_year <=1000 || add_year >2021)){      //to check if the day in right format
                printf("-->Not Inserting-->  The date is not in desired form!!!\n") ;
                getch() ;
                system("cls") ;
                break ;
            }

            if((bir_day <=0 || bir_day >30) || (bir_month <=0 || bir_month >12) ||(bir_year <=1000 || bir_year >2021)){      //to check if the day in right format
                printf("-->Not Inserting-->  The date is not in desired form!!!\n") ;
                getch() ;
                system("cls") ;
                break ;
            }

            date add = (date)malloc(sizeof(struct tm)) ;  //create new struct of date
            add->tm_mday = add_day ;
            add->tm_mon = add_month ;
            add->tm_year = add_year - 1900 ;              //subtract 1900 from the value of the year because according to the compressor time, it adds 1900 to the year

            date birth = (date)malloc(sizeof(struct tm)) ;//create new struct of date
            birth->tm_mday = bir_day ;
            birth->tm_mon = bir_month ;
            birth->tm_year = bir_year -1900 ;            //subtract 1900 from the value of the year because according to the compressor time, it adds 1900 to the year
                                                                                            //to check if the data that insrted is in right format

                Hash_it temp ;              //insert data in temp node
                strcpy(temp.name,name) ;
                strcpy(temp.Address, address) ;
                strcpy(temp.BloodType, blood) ;
                strcpy(temp.Illness, ill) ;
                temp.gender = gender ;
                temp.addmissionDate = add ;
                temp.birthDate = birth ;

                if(search_item(Table , name)){          //check if the record exist or not
                    printf("The record is exist!!!\nPress any key to back: ") ;
                    getch() ;
                    break ;
                }

                insert_table(&Table , temp) ;
            }
            else{
                printf("You must read data from file first\nPress any key to back: ") ;
            }
            getch() ;
            system("cls") ;
            break ;

        case 6:                             //if they enter 6 in hash table
            system("cls") ;
            if(!loadedTable){               //if the hash table is empty
                printf("There is no data!!!\nPress any key to back: ") ;
            }
            else{
                printf("Name: ");
                char record[59];        //to save the name of record who want to find it
                fflush(stdin) ;
                gets(record) ;          //get the name
                fflush(stdin) ;
                int a = search_item(Table, record) ;     //call function serch_item to search if the record is exist or not
                if(a){
                    printf("index: %d, %s, %c, %d-%d-%d, %d-%d-%d, %s, %s, %s\n", a , Table.items[a].name,Table.items[a].gender
                            ,  Table.items[a].addmissionDate->tm_mday, Table.items[a].addmissionDate->tm_mon, Table.items[a].addmissionDate->tm_year+1900
                            , Table.items[a].birthDate->tm_mday, Table.items[a].birthDate->tm_mon, Table.items[a].birthDate->tm_year+1900
                            , Table.items[a].Illness, Table.items[a].Address, Table.items[a].BloodType) ;
                }
                else{
                    printf("Not found!!!\nPress any key to back: ");
                }
            }
            getch() ;
            system("Cls") ;
            break ;

        case 7:                             //if they enter 7 in hash table
            system("cls") ;
            if(loadedTable){                //check if the hash table is not empty
                char namede[59];
                printf("Name to delete: ") ;
                fflush(stdin) ;
                gets(namede) ;             //get the name from user
                delete_item_table(Table , namede) ; //call function delete_item_table to delete the record from hash table
            }
            else{       //if the record does not exist
                printf("No data loaded!\nPress any key to back: ");
                getch() ;
                system("cls") ;
                break ;
            }
            printf("[Deleted]\nPress any key to back: ") ;
            getch() ;
            system("cls") ;
            break ;

        case 8:                             //if they enter 8 in hash table
            system("cls") ;                 //to clear the screen
            if(loadedTable){        //if the hash table does not empty save the data in file by calling save_table_to_file
                save_table_to_file(Table) ;
            }
            else{
                printf("No data!!!\nPress any key to back: ") ;
            }
            printf("Press any key to show the menu:\n");
            getch() ;
            system("cls") ;
            break ;

        default:        //if the user enter invalid input read again from user
            system("cls") ;
            break ;
   }
    }while(in_hash!= 0);        //if the user enter 0 that mean exit from program

    delete_all_tree(AVL_Tree) ;     //to delete all AVL Tree
    return 0 ;
}

/*-----------------------------------------------------------------------------------------------*/

void print_start(){                         //function print_start to print the system inf
    printf("|````````````````````````````````````````````````````````````````````````|\n");
    printf("|                             [Wellcome]                                 |\n");
    printf("|                                                                        |\n");
    printf("|>>>> This is management system to patients data in Rafedia Hospital <<<<|\n");
    printf("|________________________________________________________________________|\n");
    printf("|                                                                        |\n");
    printf("|                [Important notes for data in system ]                   |\n");
    printf("|      #--> To choose from the table please enter a number only          |\n");
    printf("|      #--> Date format must be (xx)day-(xx)month-(xxxx)year             |\n");
    printf("|      #--> The first char in name must be capital like Ahmad            |\n");
    printf("|      #--> The Gender must be only one char (F or M)                    |\n");
    printf("|________________________________________________________________________|\n");
}


int avl_height(AVL T){              //function to find the height of avl tree
    if (T == NULL){                 //check if avl is empty that mean return zero
        return 0 ;
    }
    else{                           //return the height of avl tree after check if avl is not empty
        return T->height ;
    }
}


int max_num(int x , int y){         //function to find the larger number between two number
    if (x > y){                    //check if first number larger than second number
        return x ;
    }
    else{                         //return the second number after check it is larger than first number
        return y ;
    }
}


int get_balance(AVL T){          //function to find the balance of avl tree
    if (T == NULL){             //if tree is empty return balance equal zero
        return 0 ;
    }
    else{                      //if tree is not empty return balance equal height of left tree - height of right tree
        return avl_height(T->left) - avl_height(T->right) ;
    }
}

                                    //function to create node and insert the data (this create root of tree)
AVL create_node(char name[59] , char gender , date admission , date birth , char illness[59] , char address[59] , char bloodtype[9]){
    AVL n_node = (AVL)malloc(sizeof(struct avl_node)) ;     //create new node
    strcpy(n_node->name , name) ;                           //insert all the patient data
    n_node->gender = gender ;
    n_node->addmissionDate = admission ;
    n_node->birthDate = birth ;
    strcpy(n_node->Illness , illness) ;                    //use strcpy function on String to copy the String and save it in array of char
    strcpy(n_node->Address , address) ;
    strcpy(n_node->BloodType , bloodtype) ;

    n_node->height = 1 ;            //make the height of tree equal 1 because this is first(root) node in tree
    n_node->right = NULL ;          //make the right side of tree pointer to NULL because there is no nodes in right
    n_node->left = NULL ;           //make the left side of tree pointer to NULL because there is no nodes in left

    return(n_node) ;                //return the node(root) we created
}


AVL min_value_node(AVL T){            //function to find the smallest value in the avl tree
    AVL temp = T ;                    //make new node to pointer to smallest node

    while(temp->left != NULL){         //loop to go to left of avl tree which mean the smallest value in the avl tree
        temp = temp->left ;
    }

    return temp ;                       //return smallest value which is located on the farthest point on the left of the avl tree
}


date strp_time(char st[8]){          //function to convert string date to integer date to be able to deal with day, month, year ass integer
    date T = (date)malloc(sizeof(struct tm)) ;  //create new struct of date
    int add_day , add_month , add_year ;        //to use it in check if the date is right format

    int flag = 0 ;                      //to flag if the date in right form
    for(int a = 0 ; a < 8 ; a++){       //loop to check every element in date
        if(st[a] == '\0'){              //if the date not equal 8 char which mean the data of date in not form
            flag = 1 ;                  //make flag equal zero
        }
    }

    if(flag == 0){              //if flag equal zero which mean the date in file write in the perfect form
        char day[3] = {st[0] , st[1] , '\0'} ;                      //save the first two char in string like day
        char month[3] = {st[2] , st[3] , '\0'} ;                    //save the tired and forth char in string like month
        char year[5] = {st[4] , st[5] , st[6] , st[7] , '\0'} ;     //save the fifth and sixth and seventh and eight char in string like year

        add_day = atoi(day) ;                        //use function atoi to converts the string argument str to an integer for day, month and year
        add_month = atoi(month) ;                       //store the date after converted in struct of date to return it
        add_year = atoi(year)  ;

        if((add_day <=0 || add_day >30) || (add_month <=0 || add_month >12) || (add_year <=1000 || add_year >2021)){      //to check if the day in right format
            printf("-->Not Inserting-->  The date is not in desired form!!!\n") ;
            return NULL;
        }

        T->tm_mday = atoi(day) ;                        //use function atoi to converts the string argument str to an integer for day, month and year
        T->tm_mon = atoi(month) ;                       //store the date after converted in struct of date to return it
        T->tm_year = atoi(year) - 1900 ;                //subtract 1900 from the value of the year because according to the compressor time, it adds 1900 to the year

        return T ;                                  //return struct of date
    }
    else{                               //if they enter data in wrong way
        printf("-->Not Inserting-->  The date is not in desired form!!!\n") ;
        return NULL ;                   //if the data write in wrong way

    }
}


void same_illness(AVL T , char illness[59]){            //function to print all patients that have the same illness
    if(T == NULL){                                //if the node is empty return NULL
        return ;
    }
    same_illness(T->left , illness) ;                 //recursion to go left and print the informations of patient that have same illness
    if(strcmp(T->Illness, illness) == 0){        //if the patient have the same illness print the informations
        printf("%s , %c , %d-%d-%d , %d-%d-%d , %s , %s , %s\n" , T->name , T->gender ,
                T->addmissionDate->tm_mday , T->addmissionDate->tm_mon , T->addmissionDate->tm_year + 1900 ,
                T->birthDate->tm_mday , T->birthDate->tm_mon , T->birthDate->tm_year+1900 ,
                T->Illness , T->Address , T->BloodType) ;
    }

    same_illness(T->right , illness) ;                 //recursion to go right and print the informations of patient that have same illness
}                               //the first and second recursion it is from which we can check all node in avl tree and print all patients that have the same illness


void save_to_file(AVL T , FILE* outp){            //function to write the data on file like output
    if(T != NULL){                                  //if T have node and it is not empty
    save_to_file(T->left , outp) ;                //recursion to go left and write the data
    fprintf(outp,"%s#%c#%02d%02d%d#%02d%02d%d#%s#%s#%s\n" , T->name , T->gender
                                                          , T->addmissionDate->tm_mday , T->addmissionDate->tm_mon , T->addmissionDate->tm_year + 1900
                                                          , T->birthDate->tm_mday , T->birthDate->tm_mon , T->birthDate->tm_year + 1900
                                                          , T->Illness , T->Address , T->BloodType) ;
    save_to_file(T->right , outp) ;                //recursion to go left and write the data
    }                       //the first and second recursion it is from which we can check all node in avl tree
}


void delete_all_tree(AVL T){   //function to delete all avl tree
    if (T == NULL){          //if the node is empty
           return ;
    }
            delete_all_tree(T -> left) ;       //the first and second recursion it is from which we can check all node in avl tree and delete them
            delete_all_tree(T -> right) ;
            free(T) ;                        //to delete the node
}


AVL search_in(AVL T, char name[59]){               //function to find the node(patient) from the tree
    while(T != NULL){                           //loop while the tree is not empty
        if(strcmp(name , T ->name) < 0){        //if the node smalest than root make recursion to go left
            return search_in(T->left , name) ;
        }
        else if(strcmp(name , T ->name) > 0){   //if the node larger than root make recursion to go right
            return search_in(T->right , name) ;
        }
        else{                                   //that mean if the difference between what we are looking for and the node is equal to zero, return this node because it matches what we are looking for
            return T ;
        }
    }
    return NULL ;           //if we do not found the what we are looking for return NULL
}


void print_in_order(AVL T){         //function to print all patients in lexicographic order with their associated information.
    if(T != NULL){                  //check if the tree is not empty
        print_in_order(T->left) ;   //recursion to go left
        printf("Name: %s, Gender: %c, AdmissionDate: %d-%d-%d, Birthdate: %d-%d-%d, Illness: %s, Address: %s, BloodType: %s\n"
                , T->name , T->gender
                , T->addmissionDate->tm_mday , T->addmissionDate->tm_mon , T->addmissionDate->tm_year + 1900
                , T->birthDate->tm_mday , T->birthDate->tm_mon , T->birthDate->tm_year + 1900 , T->Illness , T->Address , T->BloodType) ;
        print_in_order(T->right) ;      //recursion to go right
    }                                   //the first and second recursion it is from which we can check all node in avl tree
}


AVL read_from_file(AVL T){                               //function to read from file the information
    FILE *inp ;                                  //file pointer
    inp = fopen("patients.txt" , "r") ;         //open the file whose name patients to read from it
    if(inp == NULL){                            //if file does not exist
        printf("The File Does not exist\n") ;
        return NULL ;
    }

    char line[262] ;            //the line which want read
    while(fgets(line , 262 , inp)){         //loop to read all data from file line by line and exit if if we reach the end of the file and the data has expired
        char *name = strtok(line , "#") ;   //use strtok to cut the line at each # and store the cut portion in the place marked with the pointer (array of char)
        char *gender = strtok(NULL , "#") ;
        char *adate = strtok(NULL , "#") ;  //cut the date ass string to deal with him later on his nature Date
        char *bdate = strtok(NULL , "#") ;
        char *illness = strtok(NULL , "#") ;
        char *address = strtok(NULL , "#") ;
        char *bloodtype = strtok(NULL , "\n") ;     //the cut is at the end of the line, that is when you press Enter

        date admission = strp_time(adate) ;          //call function strp_time which will convert string to integer to be able to deal with day, month, year
        date birth = strp_time(bdate) ;

        if(admission == NULL || birth == NULL){     //if the date of registration or birth is not available, the information is considered incomplete and therefore he does not store it and goes to read the following information
            continue ;                              //go the next loop
        }

        T = insert_inTree(name , gender[0] , admission , birth , illness , address , bloodtype , T ) ;     //call function to insert the information for each patient which read from file into avl tree

        if(flag_same){                  //check if This patient is exists or not
            printf("-->Inserting\n") ;
        }
        flag_same = 1 ;                 //we return the flag to normal
    }

    printf("   [Done!] \n\npress any key to back") ;
    fclose(inp) ;           //close file
    return T ;              //return the avl tree after read data and store it in tree
}

                                    //function to insert the data in the avl tree and balance it
AVL insert_inTree(char name[] , char gender , date admission , date birth , char illness[] , char address[] , char bloodtype[] , AVL T){
    if( T == NULL ){                                //if avl tree is empty
        T = malloc(sizeof(struct avl_node)) ;       //create new node
        if(T == NULL){                              //if they do not create new node that mean no space
           printf("Out of space!") ;
        }
        else{                                       //if they create new node and from the if statement above the avl tree is empty insert the data inside the node(root)
            return create_node(name , gender , admission , birth , illness , address , bloodtype) ;
        }
    }
                                            //if the avl tree is not empty (have root) compare the name alphabetically to determine where to add it, left or right

    if(strcmp(name , T->name) == 0){        //if they are the same name, this means repeating and we do not add it
        printf("This patient already exists!!!\n") ;
        flag_same = 0 ;                     //make flag equal zero that mean this patient already exists
    }
    else{
        if(strcmp(name , T->name) < 0){         //if become smalest than root (comes after in order) insert it in left
            T->left = insert_inTree(name , gender , admission , birth , illness , address , bloodtype , T->left) ;
        }
        else if(strcmp(name , T->name) > 0){    //if become larger than root (comes before in order) insert it in right
            T->right = insert_inTree(name , gender , admission , birth , illness , address , bloodtype , T->right) ;
        }
    }

    int balance = get_balance(T) ;          //get the balance of avl tree after added new node

    if (balance > 1 && strcmp(name , T->left->name) < 0){   //if balance larger than 1 and the newnode smalest than root (insert into the left sub-tree of the left child)
        return right_rotate(T) ;                             //call function to make  right single rotation
    }

    if (balance < -1 && strcmp(name , T->right->name) > 0){ //if balance smalest than -1 and the newnode larger than root (insert into the right sub-tree of the right child)
        return left_rotate(T) ;                              //call function to make left single rotation
    }

    if (balance > 1 && strcmp(name , T->name) > 0){         //if balance larger than 1 and the newnode larger than root (insert into the right of the left sub-tree)
        T->left =  left_rotate(T->left) ;                    //make left rotation
        return right_rotate(T) ;                             //call function to make right single rotation
    }                                                       //(LR - double rotation)

    if (balance < -1 && strcmp(name , T->name) < 0){    //if balance smalest than -1 and the newnode smalest than root (insert into the left of the right sub-tree)
        T->right = right_rotate(T->right) ;              //make right rotation
        return left_rotate(T) ;                          //call function to make left single rotation
    }                                                   //(RL - double rotation)

    T->height = max_num( avl_height( T->left ), avl_height( T->right ) ) + 1 ;  //increase the height by 1 because we insert new node to avl tree
    return T ;                  //return the avl tree after  insert new node
}


AVL left_rotate(AVL T){          //function to make left single rotation
    AVL n = T->right ;           //create node n pointer to right of T
    AVL T2 = n->left ;           //create node T2 pointer to left of n

    n->left = T ;                //let left of n pointer to T (root)
    T->right = T2 ;              //let right of T pointer to T2

    T->height = max_num(avl_height(T->left), avl_height(T->right))+1 ;      //set the height after added node
    n->height = max_num(avl_height(n->left), avl_height(n->right))+1 ;

    return n ;          //return tree after balanced it
}


AVL right_rotate(AVL T){     //function to make right single rotation
    AVL n = T->left ;        //create node n pointer to left of T
    AVL T2 = n->right ;      //create node T2 pointer to right of n

    n->right = T ;           //let right of n pointer to T (root)
    T->left = T2 ;           //let left of T pointer to T2

    T->height = max_num(avl_height(T->left), avl_height(T->right))+1 ;      //set the height after added node
    n->height = max_num(avl_height(n->left), avl_height(n->right))+1 ;

    return n ;          //return tree after balanced it
}


AVL delete_node(AVL root, char name[59]){            //function to delete patient from the system
    if(root == NULL)                   //if the root is empty
        return root ;
                                            //searching for the patient's name in the tree by using recursion
    if (strcmp(name , root->name) < 0){     //if the name compare less than 0 then go left
        root->left = delete_node(root->left , name) ;
    }
    else if(strcmp(name , root->name) > 0 ){     //if the name compare large than 0 then go right
        root->right = delete_node(root->right , name) ;
    }
    else{
        if((root->left == NULL) || (root->right == NULL)){
            AVL temp ;                      //if root->left NULL make temp equal root->right and if root->left is nor NULL make temp equal root->left
            if(root->left){
               temp =  root->left ;
            }
            else{
                temp =  root->right ;
            }

            if (temp == NULL){      //if node temp null make root null
                temp = root ;
                root = NULL ;
            }
            else{                  //if node temp not null make the root cursor at the pointing location of temp
                *root = *temp ;
                free(temp) ;       //delete temp node
            }
        }
        else{
            AVL temp = min_value_node(root->right) ;    //insert data to temp node
            strcpy(root->name,temp->name) ;
            strcpy(root->Address, temp->Address) ;
            strcpy(root->BloodType, temp->BloodType) ;
            strcpy(root->Illness, temp->Illness) ;
            root->addmissionDate->tm_mday = temp->addmissionDate->tm_mday ;
            root->addmissionDate->tm_mon = temp->addmissionDate->tm_mon ;
            root->addmissionDate->tm_year = temp->addmissionDate->tm_year ;
            root->birthDate->tm_mday = temp->birthDate->tm_mday ;
            root->birthDate->tm_mon = temp->birthDate->tm_mon ;
            root->birthDate->tm_year = temp->birthDate->tm_year ;
            root->gender = temp -> gender ;

            root->right = delete_node(root->right, temp->name) ;
        }
    }

    if (root == NULL){
        return root ;
    }

    root->height = 1 + max_num(avl_height(root->left),avl_height(root->right)) ;

                                                //to achieve balance after a patient deletion procedure
    int balance = get_balance(root) ;

    if (balance > 1 && get_balance(root->left) >= 0){       //make right signal rotate
        return right_rotate(root) ;
    }

    if (balance > 1 && get_balance(root->left) < 0){        //make LR-double rotate
        root->left =  left_rotate(root->left);
        return right_rotate(root) ;
    }

    if (balance < -1 && get_balance(root->right) <= 0){    //make left signal rotate
        return left_rotate(root) ;
    }

    if (balance < -1 && get_balance(root->right) > 0){      //make RL-double rotate
        root->right = right_rotate(root->right) ;
        return left_rotate(root) ;
    }

    return root ;               //return the avl tree after delete node
}

AVL insert_from_user(AVL T){       //function to insert patient from user
        char name[59] ;             //to save associated data for patient
        char blood[9] ;
        char address[59] ;
        char ill[59] ;
        char gender ;
        int add_day , add_month , add_year ;
        int bir_day , bir_month , bir_year ;
        printf("--> Insert a new patient from user with all its associated data\n\n") ;
        printf("--> Name: ") ;
        fflush(stdin) ;         //to clear the data stored in buffer and can read another data from user
        gets(name) ;            //read string from user
        fflush(stdin) ;         //to clear the data stored in buffer and can read another data from user
        printf("--> Gender: ") ;
        scanf("%c" , &gender) ; //read inger and char do not need to use fflush()function to clear the data stored in buffer
        printf("--> Day of admission: ") ;
        scanf("%d" , &add_day) ;
        printf("--> Month of admission: ") ;
        scanf("%d" , &add_month) ;
        printf("--> Year of admission: ") ;
        scanf("%d" , &add_year) ;
        printf("--> Day of birth: ") ;
        scanf("%d" , &bir_day) ;
        printf("--> Month of birth: ") ;
        scanf("%d" , &bir_month);
        printf("--> Year of birth: ") ;
        scanf("%d" , &bir_year) ;
        printf("--> Illness: ") ;
        fflush(stdin) ;             //to clear the data stored in buffer and can read another data from user
        gets(ill );
        fflush(stdin) ;
        printf("--> Address: ") ;
        fflush(stdin) ;
        gets(address) ;
        fflush(stdin) ;
        printf("--> Blood type: ") ;
        fflush(stdin) ;
        gets(blood) ;
        fflush(stdin) ;

        if((add_day <=0 || add_day >30) || (add_month <=0 || add_month >12) ||(add_year <=1000 || add_year >2021)){      //to check if the day in right format
            printf("-->Not Inserting-->  The date is not in desired form!!!\n") ;
            getch() ;
            system("cls") ;
            return T ;
        }

        if((bir_day <=0 || bir_day >30) || (bir_month <=0 || bir_month >12) ||(bir_year <=1000 || bir_year >2021)){      //to check if the day in right format
            printf("-->Not Inserting-->  The date is not in desired form!!!\n") ;
            getch() ;
            system("cls") ;
            return T ;
        }

        date add = (date)malloc(sizeof(struct tm)) ;  //create new struct of date
        add->tm_mday = add_day ;
        add->tm_mon = add_month ;
        add->tm_year = add_year - 1900 ;              //subtract 1900 from the value of the year because according to the compressor time, it adds 1900 to the year

        date birth = (date)malloc(sizeof(struct tm)) ;//create new struct of date
        birth->tm_mday = bir_day ;
        birth->tm_mon = bir_month ;
        birth->tm_year = bir_year -1900 ;            //subtract 1900 from the value of the year because according to the compressor time, it adds 1900 to the year
                                                                                        //to check if the data that insrted is in right format

            AVL temp = search_in(T , name) ;    //search if the patient exists or not

            if(temp){           //if the patient already exists do not added then in system
                printf("This patient already exists\n") ;
                getch() ;
                system("cls") ;
                return T ;
            }
            else{                //if the patient is not exists added then in system
                T = insert_inTree(name , gender , add , birth , ill , address , blood , T) ;
            }
            printf("\n\t[Done]\n") ;
            printf("\nPress any key to show the menu:");
            getch() ;                 //to pause the Output Console until a key is pressed
            system("cls") ;           //to clearing the Screen
            return T ;
}

/*-----------------------------------------------------------------------------------------------*/

int is_prime(int x){                         //function to check if the number is prime or not
    for(int a = 2 ; a < (x/2)+1 ; a++){      //loop to check if the number is divisible by a number other than itself
        if (x%a == 0){
            return 1 ;                      //return 1 which mean that the number is not prime
        }
    }
    return 0 ;    //return 0 which mean that the number is  prime
}


void save_table_to_file(HashTable Ta){                    //function to Save all patients in file “patients_hash.data”
    FILE *output = fopen("patients_hash.data", "w") ;       //file pointer and make it write on file name patients_hash.data

    if(output == NULL){
        printf("Error!!! The file was not created!\n\n") ;
        getch() ;
        system("cls") ;
        return ;
    }
    for(int a = 0 ; a < Ta.totalsize ; a++){
        if (Ta.items[a].flag != 0){
            if(Ta.items[a].flag == 2){
                fprintf(output , "Index %d is empty\n", a);
            }
            else{
                fprintf(output ,"Index %d: %s, %c, %d-%d-%d, %d-%d-%d, %s, %s, %s\n", a ,Ta.items[a].name,Ta.items[a].gender, Ta.items[a].addmissionDate->tm_mday, Ta.items[a].addmissionDate->tm_mon, Ta.items[a].addmissionDate->tm_year+1900
                        , Ta.items[a].birthDate->tm_mday, Ta.items[a].birthDate->tm_mon, Ta.items[a].birthDate->tm_year+1900
                        ,Ta.items[a].Illness, Ta.items[a].Address, Ta.items[a].BloodType);
                }
            }
            else
                 fprintf(output,"Index %d is empty\n", a);
        }
    fclose(output) ;
}


int new_size(int old_size){             //function to determine the size of hash table
    int new_size = 2*old_size + 10 ;       //according to [New size = the first prime > (old size * 2)] and 10 is the first volume of size when defining
    while(is_prime(new_size))       //loop to reach the first prime > (old size * 2)
        new_size++ ;
    return new_size ;       //return new size
}


void readfile_HashTable(HashTable *Ta){              //function to reade data from file and inserte it into the hash table.
    system("cls") ;             //to clear the screen
    FILE *input = fopen("patients_hash.data","r") ;     //pointer file to read from file patients_hash.data

    if(input == NULL){                          //check if the file exist or not
        printf("The file does not exist !!!\n");
        getch() ;
        system("cls") ;
        return ;
    }

    char line[262] ;            //to save the line who readed which we want to take the all information from it
    int line_numbers = 1 ;

    while (fgets(line,262,input) != NULL){  //loop to count numbers of line in file
        line_numbers ++ ;
    }

    (*Ta).totalsize = new_size(line_numbers) ;      //find the new size of the table
    (*Ta).items = (Hash_it *) calloc( (*Ta).totalsize , sizeof(Hash_it) ) ;
    rewind(input) ;  //to sets the file position to the beginning of the file of the given stream.

    while(fgets(line , 262 , input)){
        char *name = strtok(line , "#") ;   //use strtok to cut the line at each # and store the cut portion in the place marked with the pointer (array of char)
        char *gender = strtok(NULL , "#") ;
        char *adate = strtok(NULL , "#") ;  //cut the date ass string to deal with him later on his nature Date
        char *bdate = strtok(NULL , "#") ;
        char *illness = strtok(NULL , "#") ;
        char *address = strtok(NULL , "#") ;
        char *bloodtype = strtok(NULL , "\n") ;     //the cut is at the end of the line, that is when you press Enter

        date admission = strp_time(adate) ;          //call function strp_time which will convert string to integer to be able to deal with day, month, year
        date birth = strp_time(bdate) ;

        if(admission == NULL || birth == NULL){     //if the date of registration or birth is not available, the information is considered incomplete and therefore he does not store it and goes to read the following information
            continue ;                              //go the next loop
        }
        Hash_it new_item ;            //create node  to insere the data in it
        strcpy(new_item.name, name) ;
        strcpy(new_item.Address, address) ;
        strcpy(new_item.BloodType, bloodtype) ;
        strcpy(new_item.Illness, illness) ;
        new_item.addmissionDate = admission ;
        new_item.birthDate = birth ;
        new_item.gender = gender[0] ;
        insert_table(Ta, new_item) ;       //call function insert_table to inserte the new item
        printf("-->Inserting\n") ;
    }
    printf("   [Done]\n\n press any key to back: ") ;
    fclose(input) ;
}


void insert_table(HashTable *Ta, Hash_it new_item){     ////function to insere the item in hash table
     not_empty++ ;           //count number of not empty spots
    (*Ta).size++ ;

    if((*Ta).totalsize < new_size((*Ta).size ) ){   //check if the to make sure the size is right
        replay_size(Ta) ;
    }

    new_item.flag = 1 ;
    int index = linear_hashing(*Ta , new_item.name) ;//to get item index to know place of item
    (*Ta).items[index] = new_item ;     //set the new item in the right place
}


void replay_size(HashTable *Ta){         //function to replay the size of hash table
    int size = (*Ta).totalsize ;    //get the past size
    int new_s = new_size(size) ;    //get the new size
    (*Ta).totalsize = new_s ;

    Hash_it *tmp = (*Ta).items ;
    (*Ta).items = (Hash_it *)calloc(new_s, sizeof(Hash_it)) ;  //to allocate the requested memory and returns a pointer to it
    for (int i = 0 ; i < size ; i++){       //loop to check if that the item is present to insert it
        if( tmp[i].flag == 1)
            insert_table(Ta, tmp[i]) ;              //insert node tmp in hash table after replay the size
    }
    free(tmp) ;         //delete the
}


int hash_code(HashTable Ta, char name[59]){      //function to determine the index of the record
    unsigned int i = 0 ;
    for (int j=0 ; name[j]; j++)        //count number of loop to count the number of letters in a name
        i += 1 ;

    return i % Ta.totalsize ;           //return the index of the record after apply i % Ta.totalsize
}


int linear_hashing(HashTable Ta, char name[59]){     //function to deal with collisions by Linear Hashing
    int index = hash_code(Ta , name) ;          //get the index of record
    int itemIndex = index ;
    int i = 1 ;

    while(Ta.items[itemIndex].flag == 1){       //loop to find the place in hash table to record
        itemIndex = (index + i) % Ta.totalsize ;    //use linear Linear Hashing function (index + i) % Ta.totalsize that i will increase until found the empty place
        i++ ;
    }

    return itemIndex ;          //return the new index
}


void print_hashTable(HashTable Ta){            //function to print  hashed table print the entire table to the screen including empty spots
    for(int a = 0 ; a < Ta.totalsize ; a++){    //to loop to go through all elements
        if (Ta.items[a].flag != 0){             //check if the index not empty
            if(Ta.items[a].flag == 2){          //to check if this record has been deleted
                printf("Index %d is empty\n", a);
            }
            else{
                    printf("Index %d: %s, %c, %d-%d-%d, %d-%d-%d, %s, %s, %s\n", a ,Ta.items[a].name,Ta.items[a].gender
                    , Ta.items[a].addmissionDate->tm_mday, Ta.items[a].addmissionDate->tm_mon, Ta.items[a].addmissionDate->tm_year+1900
                    , Ta.items[a].birthDate->tm_mday, Ta.items[a].birthDate->tm_mon, Ta.items[a].birthDate->tm_year+1900
                    ,Ta.items[a].Illness, Ta.items[a].Address, Ta.items[a].BloodType) ;
            }
        }
        else{               //if the index record is empty
            printf("Index %d is empty\n", a) ;
        }
    }
}


void delete_item_table(HashTable Ta, char name[59]){      //function to delete a specific record
    int index = search_item(Ta , name) ;      //get the index of the item which we want to delete it
    if (index != 0){                         //check if the record in hash table
        Ta.items[index].flag = 2 ;            //make his flag equal 2 which means as it does not exist in hash table
    }
    else{
        printf("This patient is not in the table!!!\n") ;
    }
}


int search_item(HashTable Ta, char name[59]){            //function to find Record from hash table
    int i = 1 ;
    int index = hash_code(Ta , name) ;          //get the index of record
    int index_linear = index ;

        while(Ta.items[index_linear].flag != 0){        //check if the record in hash table
            if (Ta.items[index_linear].flag != 2 &&  strcmp(Ta.items[index_linear].name , name) == 0){ //check if the record was not deleted and if have the same name
                return index_linear ;        //return the index
            }
            else{           //if there is a collision
                index_linear = (index + i) % Ta.totalsize ; //use Linear Hashing to find the index
                i++ ;
            }
    }
    return 0 ;          //if the record is not in hash table
}

//Tariq Nazieh Odeh
//1190699



