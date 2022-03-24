import java.util.ArrayList;
import java.util.List;

 public abstract class Scheduling{
   
	private final List<RowsInFile> NumOFInputRows;
    
	private final List<AlgorithmeEvent> timeline; 
    
    private int timeQuantum;  // int timeQuantum we will use it to read the input number that user will enter for time quantum for round robin algorithm

 // No-argument constructor it includes the default values about for the variables.
 
    //Constructing a Scheduling object that has the same name as the class itself  
    public Scheduling(){
    	
    	NumOFInputRows = new ArrayList();
        timeline = new ArrayList();
        timeQuantum = 1;
    }

    public boolean add(RowsInFile row){    // adding the sum number of all rows in the input file to use it calculate the average of TA and WT.
        return NumOFInputRows.add(row);
    }

    public int getTimeQuantum(){   // declare a method it's called timeQuantum and it's kind is integer and it returns timeQuantum.
        return timeQuantum;
    }

    public void setTimeQuantum(int timeQuantum){ // declare a method it's called timeQuantum and it sets a new timeQuantum for the new given or the new chosen process.
        this.timeQuantum = timeQuantum;
    }

    public double getAverageWaitingTime(){  //  declare a method it's called getAverageWaitingTime and it's kind is integer and it returns the average WaitingTime for all processes.
        
    	double average = 0.0; // declare average variable from double kind

        for (RowsInFile row : NumOFInputRows){
        	average += row.getWaitingTime();
        }
        return average / NumOFInputRows.size(); // return the calculation the average from the sum of waiting time and the number of rows 
    }

    public double getAverageTurnAroundTime(){ //  declare a method it's called getAverageTurnAroundTime and it's kind is integer and it returns the average TurnAroundTime for all processes.
        
    	double average = 0.0; // declare average variable from double kind

        for (RowsInFile row : NumOFInputRows){
        	
        	average += row.getTurnaroundTime();
        }

        return average / NumOFInputRows.size();   // return the calculation the average from the sum of waiting time and the number of rows 
    }

    public AlgorithmeEvent getEvent(RowsInFile row){
       
    	for (AlgorithmeEvent event : timeline){
           
    		if (row.getProcessName().equals(event.getProcessName())) {
                return event;
            }
        }

        return null;
    }

    public RowsInFile getRow(String process){
        for (RowsInFile row : NumOFInputRows)
        {
            if (row.getProcessName().equals(process)){
                return row;
            }
        }

        return null;
    }

    public List<RowsInFile> getRows(){
        return NumOFInputRows;
    }

    public List<AlgorithmeEvent> getTimeline() {
        return timeline;
    }

    public abstract void process();
}
