import java.util.Scanner ;

public class PagingMemory {
	
	ReferenceString Ref ;    			//object from ReferenceString class 
	int Physical_frames ;				//Physical frame numbers
	int Virtual_frames ;				//Virtual frame numbers
    int[][] Physical_memory ;			//Two dimensional array for physical memory
    EnteredNumOfFrame[] Frame_array ;	//object from EnteredNumOfFrame class 
    boolean[] P_fault ;					//To know if there is page fault
    int Ref_length ;					//to store ReferenceString length
    String algorithm ; 					//Type of algorithm
   	int[] P_removed ;					//The page we want to remove
    int[] P_called ;					//The page we want to call

    							
    PagingMemory(ReferenceString R, int P, int V) {			//Constructing a Memory object
    	Ref = R ;
    	Ref_length = Ref.getLength( );
    	P_removed = new int[Ref_length] ;
        P_called = new int[Ref_length] ;
        Physical_frames = P ;
        Virtual_frames = V ;
        Physical_memory = new int[Ref.getLength()][P] ;
        Frame_array = new EnteredNumOfFrame[V] ;
        P_fault = new boolean[Ref_length] ;
    }

    void Launch() {										//function to initialize parameters
        for (int i = 0 ; i < P_fault.length ; i++) {		//loop to initialize page fault
        	P_fault[i] = true ;
        }
        for (int i = 0 ; i < P_removed.length ; i++) { 		//loop to initialize page we want to remove
        	P_removed[i] = -1 ;
        }
        for (int i = 0 ; i < P_called.length ; i++) { 		//loop to initialize page we want to call
        	P_called[i] = -1 ;
        }
        for (int i = 0 ; i < Virtual_frames ; i++) { 			//loop to initialize virtual frame
        	Frame_array[i] = new EnteredNumOfFrame(i);
        }
        for (int i = 0 ; i < Ref_length ; i++) { 		//loop to initialize ReferenceString length
            for (int j = 0 ; j < Physical_frames ; j ++) {
            	Physical_memory[i][j] = -1 ;
            }
        }
        algorithm = "" ;				//initialize the algorithm
    } 
    
    
    void generate(String A) {     //function to generate algorithm
    	Launch() ;
        algorithm = A ;
        int F_replace ;
        int F_insert ;
        int in_memory;
        int part = 0 ;
        int empty ;
        
        while (part < Ref_length) {						//the while loops through each call of the simulation
        	F_insert = Ref.getAtIndex(part) ;
            
            if (A == "LRU") {     					 //to update last used frame
            	Frame_array[F_insert].setLastUse(part) ;
            }
            
            empty = find_index(Physical_memory[part], -1) ;
            in_memory = find_index(Physical_memory[part], F_insert) ;
            
            if (in_memory != -1) {
            	P_called[part] = in_memory ;
                P_fault[part] = false ;
            }
            else if (empty >= 0) {
            	P_called[part] = empty ;
                Physical_memory[part][empty] = F_insert ;
                Frame_array[F_insert].setInserted(part) ;
            }
            else {
                switch (A) {
                    case "FIFO":          
                    	F_replace = findOldest(Physical_memory[part]) ;  	 	// find the oldest frame
                        Frame_array[F_insert].setInserted(part) ;
                        break ;
                        
                    case "LRU":
                    	F_replace = least_recently(Physical_memory[part]) ;		//find least recently used
                        break ;
                        
                    default:
                        System.out.println("Error!!!: Please check the algorithm that entered") ;
                        return ;
                }
                P_removed[part] = Physical_memory[part][F_replace] ;
                P_called[part] = F_replace ;
                Physical_memory[part][F_replace] = F_insert ;
            }      
            
            if ((part + 1) < Ref_length) {
                for (int i = 0 ; i < Physical_frames ; i ++) {
                	Physical_memory[part +1][i] = Physical_memory[part][i] ;
                }
            }
            part += 1 ;
        }	//end while
    } 	 //end of void generate function    
    
    int findOldest(int[] x) {					//function to find the oldest frame
        int old = Frame_array[x[0]].getInserted() ;
        int old_index = 0 ;
        int check ;
        
        for (int i = 1 ; i < x.length ; i++) {
        	check = Frame_array[x[i]].getInserted() ;
            if (check < old) {
            	old = check ;
            	old_index = i ;
            }
        }
        return old_index ;
    }
    
   
    int least_recently(int[] x) {					//function to find least recently used
        int LRU_index = 0 ;
        int last_use = Frame_array[x[LRU_index]].getLastUse() ;

        for (int i = 1 ; i < x.length ; i++) {
            int tempLastUse = Frame_array[x[i]].getLastUse() ;
            if (tempLastUse < last_use) {
            	LRU_index = i ;
            	last_use = tempLastUse ;
            }
        }
        return LRU_index ;
    }
    
    int find_index(int[] x , int y) {						//function to find index
    	for (int i = 0 ; i < x.length ; i++){
            if (x[i] == y) {
                return i ;
            }
        }
      return -1 ;
    }

    
    void display() {       //function to print the operation of algorithm
    	System.out.println("--------------------------------------------------+") ;
        System.out.println("[Basic information]") ;
        System.out.println("Algorithm type [" + algorithm + "]") ;
        System.out.println("Length of reference string [" + Ref_length+ "]") ;
        System.out.println("Number of virtual pages [" + Virtual_frames + "]") ;
        System.out.println("Number of physical pages [" + Physical_frames + "]") ;
        System.out.println("+-------------------------------------------------+") ;
        System.out.println("[*]- Press enter to step through snapshots of physical memory after each string call") ;
        System.out.println("[*]- Press (q) to to return to  menu at any time") ;
             
        Scanner sc = new Scanner(System.in) ;
        int removed_int ;
        int next_part = 0 ;
        int F_number ;			//number of frame
        int faults = 0 ; 		//number of page faults
        String read ;
    
        while (next_part < Ref_length) {
        	read = sc.nextLine() ;
            
            if (read.equals("q") || read.equals("Q")) {
                System.out.println("# Return to  menu") ;
                break ;
            }
        
            System.out.println("Snapshot at call [" + (next_part + 1) + "]") ;
            System.out.println("Program called virtual frame [" + Ref.getAtIndex(next_part) + "]") ;
            
            for (int i = 0 ; i < Physical_frames ; i++) { 
                System.out.print("Physical frame " + i ) ;
                F_number = Physical_memory[next_part][i] ;
                if (F_number >= 0) {
                    if (i == P_called[next_part]) {					//inserted the frame
                        System.out.println(" [" + F_number + "]") ;
                    } else {
                        System.out.println(" " + F_number) ;
                    }
                } 
                else {
                    System.out.println(" X") ;
                }
            }
            
            removed_int = P_removed[next_part] ;						
            if(P_fault[next_part]) {							//found if there is page fault
            	System.out.println("Page fault: [Yes]") ;
            }
            else {
            	System.out.println("Page fault: [No]") ;
            }
                        
            if(P_fault[next_part]) {
            	faults ++ ;
            }
            
            System.out.println("Number of Page faults: [" + faults + "]");
            
            if(removed_int == -1) {							//found if there is victim frame
            	System.out.println("Victim frame: [None]") ;
            }
            else {
            	System.out.println("Victim frame: [" + removed_int +"]") ;
            } 
            next_part += 1 ;
        }
        System.out.print("Simulation complete-->[Press enter to continue]") ;
        sc.nextLine() ;
    }
  
}