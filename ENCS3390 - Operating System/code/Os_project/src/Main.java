import java.util.InputMismatchException ;
import java.io.BufferedReader ;
import java.util.ArrayList ;
import java.io.IOException ;
import java.io.FileReader ;
import java.util.Scanner ;
import java.util.Random ;
import java.util.List ;
import java.io.File ;


//Tariq Odeh 1190699
//Qays Safa 1190880
//Mahmoud Samara 1191602

public class Main {
	static final int C = 100 ;   //Virtual frame numbers
    public static void main(String[] args) throws IOException {

    	File conf_file = new File("Config.txt") ;  			//to read the Config file 
    	FileReader cf_1 =new FileReader(conf_file) ;
    	BufferedReader buffer_1 = new BufferedReader(cf_1) ;
    	String line = null ;
    	
    	int N = 0 ;			//number of processes
    	int M = 0 ;			//size of physical memory in frames
    	int S = 0 ;			//minimum frames per process 
    	int r = 3 ;			//to read N, M and S

    	while((line=buffer_1.readLine()) != null) {   //loop to read number of processes, size of physical memory in frames and minimum frames per process 
    		String[]temp = line.trim().split(" ") ;
    		for(String str:temp) {
    			if(r == 3) {			//read number of processes
    				N = Integer.parseInt(str) ;
    				r-- ;
    			}
    			else if(r == 2) {			//read size of physical memory in frames
    				M = Integer.parseInt(str) ;
    				r-- ;
    			}
    			else if(r == 1) {			//read minimum frames per process
    				S = Integer.parseInt(str) ;
    				r-- ;
    			}
    		}  
    	}//end of while loop 	
    	
    	ArrayList<String>[] memory_tra = new ArrayList[N] ; //make array of array list to save memory traces for each process
    	for (int i = 0 ; i < N ; i++) {  //make array list in each element in memory_tra array 
    		memory_tra[i] = new ArrayList<String>() ;
        }
    	
    	FileReader cf_2 = new FileReader(conf_file) ;
    	BufferedReader buffer_2 = new BufferedReader(cf_2) ;
    	String [] PID = new String [N] ;  	//PID for process
    	int [] Start = new int [N] ;  		//Start time for process
    	int [] Duration = new int [N] ;  	//Duration for process
    	int [] Size = new int [N] ;  		//Size for process
    	
    	
    	int v = 4 ;		//to read PID, start, Duration and Size
    	int x = -4 ;	//to skip PID, start, Duration and Size that read before
    	int y = 3 ;		//to skip N, M and S that read before
    	
    	while((line = buffer_2.readLine()) != null) {
    		String[]temp = line.trim().split(" ") ;
    		x++ ;
    		if (y > 0) {	//skip N, M and S that read before
    		    y-- ;
    			continue ;
    		}
    		int t = 0 ;    //to read first 4 data from line
    		v = 4 ;
    		for(String str:temp) {
    			if(t < 4) {
    				switch (v) {
                	case 4:					//read PID of processes
                		PID[x] = str ;   
                		break ;
                		
                	case 3:					//read Start time of processes
                		Start[x] = Integer.parseInt(str) ; 
                		break ;
                		
                	case 2:					//read Duration of processes
                		Duration[x] = Integer.parseInt(str) ;
                		break;
                		
                	case 1:					//read Size of processes
                		Size[x] = Integer.parseInt(str) ;
                		break ;
    				}
    			v-- ;
    			t++ ;
    			}
    			else {
    				memory_tra[x].add(str) ;	//storing memory traces in an array
    			}
    		}
    	}
    	
    	//in two loop below to truncate addresses to default page numbers by removing the lower 12 bits
    	for(int t = 0 ; t < N ; t++) {
    		int index = memory_tra[t].size() - 1 ;
    		memory_tra[t].remove(index) ;		//remove (lower 8 bits) 
    	}
    		
    	String temp , new_temp  = "" ;
    	for(int t = 0 ; t < N ; t++) {
    		int index = memory_tra[t].size() - 1;
    		temp = memory_tra[t].get(index).toString() ;
    		new_temp = temp.substring(0,temp.length()-1) ; 		//remove (lower 4 bits) 	
            memory_tra[t].add(new_temp) ;
    	}	
    	    	
//-------------------------------------------------------------------------------------------------------------
    	System.out.println("+-------------------------------------------------+") ;
        System.out.println("|--------------------Welcome----------------------|") ;
        System.out.println("+-------------------------------------------------+") ;
    	
    	Scanner sc = new Scanner(System.in) ;								 //read physical frame numbers
        ReferenceString Ref_string = null ;				 //to save data for each process for use in algorithms
        PagingMemory inf_p ;  				
        int read_1 ; 
        
        while (true) {    				//Main loop & Main menu
        	System.out.println("+-------------------------------------------------+") ;
            System.out.println("|-------------------Main menu---------------------|") ;
            System.out.println("+-------------------------------------------------+") ;
        	System.out.println("[Please choose from the following options]") ;
            System.out.println("[1] - Read from Confing.txt file reference string") ;
            System.out.println("[2] - Display current reference string") ;
            System.out.println("[3] - Simulate Round Robin") ; 
            System.out.println("[4] - Simulate FIFO / LRU") ;
            System.out.println("[0] - Exit") ;
            System.out.println() ;

            read_1 = Integer.parseInt(sc.next()) ; 	 //read input from user
            sc.nextLine() ;
           
            switch (read_1) {
                case 0:				//exit from program        
                    System.out.println("# [Ending Simulation]") ;
                    System.exit(0);
                    break ;
                    
                case 1:				//read reference string       
                	System.out.println("# [Config.txt has been successfully read]") ;
                	System.out.println() ;
                    break ;
                    
                case 2:			   //print reference string           
                    if (memory_tra != null) {
                        System.out.println("Number of processes: [" + N + "]") ;
                        System.out.println("Size of physical memory in frames: [" + M + "]") ;
                        System.out.println("Minimum frames per process: [" + S + "]") ;
                        System.out.println("--------|-------|--------|-------|---------------") ;
                        System.out.println("PID\t|Start\t|Duration|Size\t |Memory traces");
                        System.out.println("--------|-------|--------|-------|---------------") ;
                        
                        for(int t = 0 ; t<N ; t++) {  //print processes data
                            System.out.println(PID[t]  + "\t|" + Start[t]+ "\t|" + Duration[t] + "\t |" + Size[S] + "\t |" + memory_tra[t]) ;
                        }   
                    }
                    else {
                        System.out.println("Error!!!: please read the Config.txt file first") ;
                    }
                    break ;
                        
                case 3:  				//Round-robin scheduling
                	System.out.println("+-------------------------------------------------+") ;
                    System.out.println("|------------------Round Robin--------------------|") ;
                    System.out.println("+-------------------------------------------------+") ;
                    
                    System.out.println("[Plase enter time Quantum]") ;
                    int Q = sc.nextInt() ;
                    Scheduling RR = new RoundRobin() ;
                    RR.setTimeQuantum(Q) ;
                    
                    for(int t = 0 ; t<N ; t++) {						 //enter process from file
                    	RR.add(new RowsInFile(PID[t], Start[t], Duration[t])) ;
                    }
                    RR.process() ;
                    RR_Data(RR) ;    //print the round-robin scheduling
                    break ;          
                    
                case 4:    			//FIFO / LRU scheduling algorithm
                	System.out.println("Plese enter the number of Physical Page Frames:") ;
                    int Physical_frames = sc.nextInt() ;
                    System.out.println("Number of page frames set to [" + Physical_frames + "]") ;
                    int read_2 ;
                    
                    Back_Menu:		//use it to exit from switch and while loop
	                    while (true) {
	                        System.out.println();
	                    	System.out.println("+-------------------------------------------------+") ;
	                        System.out.println("|------------------FIFO / LRU---------------------|") ;
	                        System.out.println("+-------------------------------------------------+") ;     
	                        System.out.println("[Please choose from the following options]") ;
	                        System.out.println("[1] - Read reference string") ;
	                        System.out.println("[2] - Generate reference string") ;
	                        System.out.println("[3] - Display current reference string") ;
	                        System.out.println("[4] - Simulate FIFO") ;
	                        System.out.println("[5] - Simulate LRU") ;
	                        System.out.println("[0]- Go back") ;
	                        System.out.println() ;
	
	                        read_2 = Integer.parseInt(sc.next()) ; 			 //read input from user
	                        sc.nextLine() ;
	                        switch (read_2) {
	                            case 0:		   		//Go back	        
	                                System.out.println("Back to menu") ;
	                                break Back_Menu ;
	                                
	                            case 1:				
	                            	Ref_string = read_Ref(sc) ;    	//read reference string
	                            	confirm_Ref(Ref_string) ;       //confirm reference string
	                                break ;
	                                
	                            case 2:          					//generate reference string
	                                System.out.println("[Please enter the length of the reference string]") ;
	                                int size_Ref = get_Ref_size(sc) ;
	                                Ref_string = generate_Ref(size_Ref , C) ;         //generate the string
	                                confirm_Ref(Ref_string) ;
	                                break ;
	                                  
	                            case 3:								//print reference string           
	                                if (Ref_string != null) {
	                                    System.out.print("Current reference string[") ;
	                                    Ref_string.print() ;
	                                    System.out.print("]") ;
	                                }
	                                else {
	                                    System.out.println("Error!!!: No reference string entered") ;
	                                }
	                                break ;
	                                
	                            case 4:  			//FIFO 
	                                if (is_Ref_set(Ref_string)){    	 //check that reference string has been set, test reference string
	                                	inf_p = new PagingMemory(Ref_string , Physical_frames , C) ;  //create simulation conditions, run it, and print
	                                	inf_p.generate("FIFO") ;
	                                	inf_p.display() ;
	                                }
	                                break ;
	                                
	                            case 5:  			//LRU
	                                if (is_Ref_set(Ref_string)) {    	 //check that reference string has been set, test reference string
	                                	inf_p = new PagingMemory(Ref_string , Physical_frames , C) ;  // create simulation conditions, run it, and print
	                                    inf_p.generate("LRU") ;
	                                    inf_p.display() ;
	                                }
	                                break ;
	                                
	                            default:
	                                break ;
	                        } //end switch
	                    } //end second while loop
                    break;
                    
                default:
                    break;
            } // end switch
        } // end first  while loop
} //end main
    
//-------------------------------------------------------------------------------------------------------------

public static void RR_Data(Scheduling RR) {   //function to print round robin data for each process & Average of WT and TAT 
	System.out.println("Process\t|AT\t|BT\t|WT\t|TAT") ;
    System.out.println("--------|-------|-------|-------|---") ;
    
    for (RowsInFile row : RR.getRows()) {   //print Round robin data for each process 
        System.out.println(row.getProcessName() + "\t|" + row.getStartTime() + "\t|" + row.getDurationTime() + "\t|" + row.getWaitingTime() + "\t|" + row.getTurnaroundTime()) ;
    }
    System.out.println() ;

    for (int i = 0 ; i < RR.getTimeline().size() ; i++) {
        List<AlgorithmeEvent> RR_time = RR.getTimeline() ;
        System.out.print(RR_time.get(i).getStartTime() + "-->(" + RR_time.get(i).getProcessName() + ")") ;

        if (i == RR.getTimeline().size() - 1) {
            System.out.print(RR_time.get(i).getFinishTime()) ;
        }
    }
    System.out.println("\n\nAverage WT: [" + RR.getAverageWaitingTime() +"]"+ "\nAverage TAT: " + "["+RR.getAverageTurnAroundTime()+"]") ;
}


public static ReferenceString read_Ref(Scanner sc) {
	ArrayList<Integer> series_num = new ArrayList<Integer>() ;
	ReferenceString memory_tra = null ;     //create RefString 
	System.out.println("[Enter a series of numbers]") ;
    
    while (series_num.size() < 1) {
        String line = sc.nextLine() ; 				// read in a line
        Scanner line_sc = new Scanner(line) ;   	// create a scanner to operate on that line
        String temp ;            					//extract the ints
        int temp_int = -1 ;	
        boolean is_int ;  							//to check if it integer
        
        while (line_sc.hasNext()) {
            temp = line_sc.next() ;
            is_int = false ;
            try {
            	temp_int = Integer.parseInt(temp) ;     //read int
                is_int = true ;							//set it integer
            } 
            catch (NumberFormatException E) {
                System.out.println("Warning!!!: Non-integer was entered [" + temp + "] ignored") ;
            }
          
            if (is_int && (temp_int < 0 || temp_int >= C)) {  	// ensure that the numbers entered are between 0 and 100
                System.out.println("Warning!!!: Numbers must be between 0 and " + (C - 1) + "[" + temp + "] ignored") ;
            } 
            else if (is_int) {
            	series_num.add(temp_int) ;   //added to reference string
            }
        }

        if (series_num.size() < 1) {     //make sure at least 1 valid int was entered
            System.out.println("Error!!!: You must enter at least 1 valid integer Please try again") ;
        }
    } 
    memory_tra = new ReferenceString(series_num) ;
    return memory_tra ;     //return reference string
}
 

public static void confirm_Ref(ReferenceString memory_tra) {		//to confirm if there is reference string or was read
    if (memory_tra != null) {	
        System.out.print("Valid reference string saved[") ;
        memory_tra.print() ;							//print reference string
        System.out.print("]") ;
    } 
    else {
        System.out.println("Invalid reference string. Please try again.") ;
    }
}


public static int get_Ref_size(Scanner sc) {    //function to read string size from user
    int size_Ref = 0 ;
    while (size_Ref < 1) {
        try {							//to check input
        	size_Ref = sc.nextInt() ;
        }
        catch (InputMismatchException E) {
            System.out.println("Error!!!: You must enter an integer") ;
        }
        sc.nextLine() ;
        if (size_Ref < 1) {
            System.out.println("Error!!!: You must enter a positive integer") ;
        }
    }
    return size_Ref ;
}


public static boolean is_Ref_set(ReferenceString memory_tra) {  //function to check if reference string entered/generated
    if (memory_tra != null) {
        return true ;
    }
    System.out.println("Error!!!: Reference string not yet entered/generated!") ;
    return false ;
}


public static ReferenceString generate_Ref(int x , int max) { 	//function to generate reference string
    if (x < 1) {
        System.out.println("Error!!!: Reference string shorter than 1") ;
        return null ;
    }
    Random random = new Random() ;				//create random integer

    ArrayList<Integer> series_num = new ArrayList<Integer>() ; 	// create ArrayList for ints
    for (int i = 0 ; i < x ; i++) {
    	series_num.add(random.nextInt(max)) ;
    }

    ReferenceString memory_tra = new ReferenceString(series_num) ;        	//use the ArrayList to create a RefString
    return memory_tra ;
}

}




