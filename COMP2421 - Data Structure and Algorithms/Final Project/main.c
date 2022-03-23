#include <stdio.h>          //Tariq Nazieh Odeh
#include <stdlib.h>         //1190699
#include <conio.h>          //to use inbuilt functions like getch()
#include <string.h>         //this header defines several functions to manipulate  strings and arrays --> to declare a set of functions to work strings(manipulating arrays of characters)
#define INFINITY 9999


typedef struct Graph* graph ;        //use to give a type a new name --> give a new struct Graph* which is graph
typedef struct node* edge ;         //use to give a type a new name --> give a struct node** which is edge


struct node{            //the structure of this memory block is defined by struct node, that allows to combine data items of different kinds
  int vertex ;
  int distance ;
  char Name[50] ;
  struct node* next ;
};



struct Graph{            //the structure of this memory block is defined by struct Graph, that allows to combine data items of different kinds
  int numVertices ;
  struct node** adjLists ;
};



struct item{       //structure for the elements in the priority queue
    int value ;
    int priority ;
};



int print_menu() ;
struct Graph* createAGraph(int vertices) ;
void Read(graph*) ;
void trim(char **buffer);
void addEdge(struct Graph* graph, int s, int d, int distance, char p[50]) ;
struct node* createNode(int v, int distance, char Name[50]) ;
void printGraph(struct Graph* graph) ;
void enqueue(int value, int priority) ;
int peek() ;
void dequeue() ;
void Dijkstra(graph );

/*-------------------------------------------------------------------------------------------------------*/
int main(){

    graph vertices = createAGraph(400) ;
    int choice = 0 ;
    do{
        choice = print_menu() ;     //show menu
        system("cls") ;
        if(choice == 1)
        {
            Read(&vertices) ;       //read data from file
            getch() ;
        }
        if(choice == 2)
        {
            Dijkstra(vertices) ;    //get the shortest path between two points
        }
        fflush(stdin) ;            //to clear the data stored in buffer and can read another data from user

    }while(choice != 3) ;

    return 0 ;
}

/*-------------------------------------------------------------------------------------------------------*/

int print_menu(){           //function to print menu and read the input from user
    system("cls") ;         //to clearing the Screen
    int option ;
    printf("|````````````````````````````````````````````````````````````````````````|\n");
    printf("|                             [Wellcome]                                 |\n");
    printf("|                                                                        |\n");
    printf("|           >>>> This is  system to to find shortest route <<<<          |\n");
    printf("|________________________________________________________________________|\n");
    printf("\n1- Read input file\n") ;
    printf("2- Get the shortest path between two points\n") ;
    printf("3- Exit program\n") ;
    scanf("%d" , &option) ;
    return option ;
}


struct Graph* createAGraph(int vertices){               //create a graph
  struct Graph* graph = malloc(sizeof(struct Graph)) ;
  graph->numVertices = vertices ;

  graph->adjLists = malloc(vertices * sizeof(struct node*)) ;       //reserve a place for the array, whose size is vertices

  for (int i = 0; i < vertices; i++)
    graph->adjLists[i] = NULL ;

  return graph ;
}


void Read(graph *vertices){         //function to read data from file and store it and call function to print the data
    char filename[33] ;
    printf("Please enter the input file name: ");
    fflush(stdin) ;         //to clear the data stored in buffer and can read another data from user
    gets(filename) ;
    FILE* sc = fopen(filename , "r") ;

    if(!sc){    //if file does not exist
        printf("File does not exist\n") ;
        return ;
    }

    char line_read[133] ;                       //loop to read all data from file line by line and exit if if we reach the end of the file and the data has expired
    while(fgets(line_read , sizeof(line_read) , sc)){
        int src = atoi(strtok(line_read, " ")) ;    //use strtok to cut the line at each space
        int dest = atoi(strtok(NULL, " ")) ;
        char *next = strtok(NULL, "\n") ;
        trim(&next) ;       //call function trim to add ',' before the distance
        char *name = strtok(next, ",") ;
        int distance = atoi(strtok(NULL,"\0")) ;
        addEdge(*vertices, src, dest, distance, name) ;
        }

    printGraph(*vertices) ;

}

void trim(char **buffer){   //function replace the space before the distance with ',' to can extract the distance
    int i ;
    for( i = 0; (*buffer)[i] != '\0'; i ++){ //to find end to reach the end string
        continue ;
    }

    for(int j = i; j > 0 ; j-- ){   //to find space(" ") before the distance and replace it with ','
        if((*buffer)[j] == ' '){
            (*buffer)[j] = ',' ;    //replace the space before the distance with ','
            return ;
        }
    }
}

void addEdge(struct Graph* graph, int s, int d, int distance, char p[50]){  //to add edge on graph
    struct node* newNode = createNode(d , distance , p) ;   //add edge from s to d
    newNode->next = graph->adjLists[s] ;
    graph->adjLists[s] = newNode ;

    newNode = createNode(s, distance , p) ;           //add edge from d to s
    newNode->next = graph->adjLists[d] ;
    graph->adjLists[d] = newNode ;
}


struct node* createNode(int v, int distance, char Name[50]) {       //to create a node and return it
  struct node* newNode = malloc(sizeof(struct node)) ;
  newNode->vertex = v ;
  newNode->distance = distance ;
  strcpy(newNode->Name, Name) ;
  newNode->next = NULL ;
  return newNode ;
}


void printGraph(struct Graph* graph){           //print the graph
    int v, nline = 1 ;
    for (v = 0; v < graph->numVertices; v++){   //to pass through all the vertices
        nline = 1 ;
        struct node* temp = graph->adjLists[v] ;
        if(temp != NULL)
                printf("\n Vertex %d\n: ", v) ;
        else
                nline = 0 ;
        while(temp){                //to through all the edges
            printf("%d,%s,%d -> ", temp->vertex, temp->Name, temp->distance) ;
            temp = temp->next ;
        }
        if(nline == 1)
            printf("\n") ;
    }
}


struct item pr[1000] ;       //store the element of a priority queue (min)
int size = -1 ;              //pointer to the last index



void enqueue(int value, int priority){       //function to insert a new element into priority queue
    size++ ;
    pr[size].value = value ;     //insert the element
    pr[size].priority = priority ;
}


int peek(){      //function to check the top element hows have less priority because (priority = distance)
    int highestPriority = 9999 ;
    int ind = -1 ;

    for(int i = 0; i <= size; i++){      //find the element with lowest priority because it priority queue (min)
        if(highestPriority > pr[i].priority){
            highestPriority = pr[i].priority ;
            ind = i ;
        }
    }

    return ind ;
}

void dequeue(){     //function to remove the element with the highest priority

    int ind = peek() ;     //call peek to find the position of the element with highest priority

    for(int i = ind ; i < size ; i++){     //shift the element one index
        pr[i] = pr[i + 1] ;
    }

    size-- ;     //decrease the size of the priority queue
}



void Dijkstra(graph vertices){      //function to find shortest path between two points and print the path
    system("cls") ;
    int source , destination ;
    printf("Enter source point: ") ;
    scanf("%d", &source) ;
    printf("Enter destination point: ") ;
    scanf("%d", &destination) ;
                                                //check if the source point can be reached
    if(vertices->adjLists[source] == NULL || source < 1){
        printf("Source can't be reached!!!\n") ;
        getch() ;
        return ;
    }                                          //check if the destination point can be reached
    if(vertices->adjLists[destination] == NULL || destination < 1){
        printf("Destination can't be reached!!!\n") ;
        getch() ;
        return ;
    }                          //check if the source point is the same destination point print distance equal 0
    if(source == destination){
        printf("Distance is 0 \n") ;
        getch() ;
        return ;
    }


    int dist[400], visited[400] ;   //to store distance and flag if was vist

    for(int i = 0; i < 400; i++){   //make all vertices not visited and thier distance equal INFINITY(9999)
        dist[i] = INFINITY ;
        visited[i] = 0 ;
    }

    dist[source] = 0 ;              //make the distance of source equal zero
    visited[source] = 1 ;           //make the source was visited
    enqueue(source , dist[source]) ;

    while(peek() != -1){            //loop to find shortest path
        int Location = pr[peek()].value ;
        edge temp = vertices->adjLists[Location] ;

        while(temp != NULL){    //compare the distance
            if(dist[temp->vertex] > (dist[Location]+temp->distance)){
                dist[temp->vertex] = dist[Location]+temp->distance ;
                visited[temp->vertex] = 0 ;
            }

            if(visited[temp->vertex] == 0){     //make it visted after added in priority queue
                enqueue(temp->vertex, dist[temp->vertex]) ;
                visited[temp->vertex] = 1 ;
            }
            temp = temp -> next ;
        }

        dequeue() ; //remove the element with the highest priority
    }


    int solution[400] ;     //to store the path

    for(int i = 0; i < 400; i++){
        solution[i] = INFINITY ;
        visited[i] = 0 ;
    }

    visited[destination] = 1 ; //make the destination was visited
    int back ;                 //to check the process of the path
    int numOfLocations = 1 ;  //to see how many places he passed
    solution[0] = destination ;
    int Location = destination ;

    while(Location != source){      //if i don't get to the source
        back = 1 ;
        Location = solution[numOfLocations-1] ;
        edge temp = vertices->adjLists[Location] ;
        int MinNode = 0 ;         //to find min value of node
        int Minimum = INFINITY ;

        while(temp != NULL){    //loop to find shortest path and know his vertex
            if(visited[temp->vertex] == 0){ //if was not visited
                if(dist[temp->vertex] < dist[Location] && dist[temp->vertex] < Minimum){
                    Minimum = dist[temp->vertex] ;
                    MinNode = temp->vertex ;
                    back = 0 ;
                    visited[temp->vertex] = 1 ;
                }
            }
            temp = temp -> next ;   //go to another vertex
        }

        if(back){       //if reach a dead end or get lost
            solution[numOfLocations] = INFINITY ;
            numOfLocations -- ; //go back to old location
        }
        else{       //if it is the shortest path save his vertex in solution
            solution[numOfLocations] = MinNode ;
            numOfLocations ++ ;             //increase number of location
        }
    }


    char op ;
    printf("Do you want to write the solution to 'routes.txt' file? ([y] for Yes, [default]=No): ") ;
    op = getch() ;
    if(op != 'y' && op != 'Y'){
        printf("\n\nRoute from [%d] to [%d] has [%d] distance and the whole route is: \n\n", source , destination , dist[destination]) ;
        printf("%d %d ", source , solution[numOfLocations-1]) ;
        edge temp = vertices->adjLists[source] ;        //use it to find the vertex which want to print Name of location

        while(temp != NULL){    //find the vertex which want to print Name of location
            if(temp->vertex == solution[numOfLocations-1]){
                printf("%s ", temp->Name) ;
                break ;
            }
            temp = temp->next ;
        }

        for(int i = numOfLocations-1 ; i > 0; i--){     //to print all path from sours to destantion
            printf("-> %d %d ", solution[i], solution[i-1]) ;
            temp = vertices->adjLists[solution[i]] ;

            while(temp != NULL){ //find the vertex which want to print Name of location
                if(temp->vertex == solution[i-1]){
                    printf("%s ", temp->Name) ;
                    break ;
                }
                temp = temp->next ;
            }
        }
    }
    else{
        FILE*out = fopen("routes.txt", "a") ;       //to print on file
        fprintf(out, "\n\nRoute from [%d] to [%d] has [%d] distance and the whole route is: \n", source, destination, dist[destination]) ;
        printf("\n\nRoute from [%d] to [%d] has [%d] distance and the whole route is: \n", source, destination, dist[destination]) ;
        printf("%d %d ", source, solution[numOfLocations-1]) ;
        fprintf(out, "%d %d ", source, solution[numOfLocations-1]) ;
        edge temp = vertices->adjLists[source] ;   //use it to find the vertex which want to print Name of location

        while(temp != NULL){ //find the vertex which want to print Name of location
            if(temp->vertex == solution[numOfLocations-1]){
                printf("%s ", temp->Name) ;
                fprintf(out, "%s ", temp->Name) ;  //print location on file
                break ;
            }
            temp = temp->next ;
        }

        for(int i = numOfLocations-1 ; i > 0; i--){  //to print all path from sours to destantion
            fprintf(out, "-> %d %d ", solution[i], solution[i-1]) ;
            printf("-> %d %d ", solution[i], solution[i-1]) ;
            temp = vertices->adjLists[solution[i]] ;

            while(temp != NULL){        //find the vertex which want to print Name of location
                if(temp->vertex == solution[i-1]){
                    printf("%s ", temp->Name) ;
                    fprintf(out, "%s ", temp->Name) ;
                    break ;
                }
                temp = temp->next ;
            }
        }
        fclose(out) ;       //close the file

    }

    printf("\n[Done]\n") ;
    printf("\nDo you want to continue? ([y] for Yes, [default]=No): ") ;
    op = getch() ;

    if(op == 'y' || op == 'Y')
        Dijkstra(vertices) ;        //recursion function Dijkstra if the user want to find another shortest path
    else
        return ;    //return to main
}
//Tariq Nazieh Odeh
//1190699
