
public class AlgorithmeEvent {
    private final String processName ; // String processName we will use it to know the name of each process for Round Robin algorithm.
    private final int starttime ; // int starttime we will use it to know the start time of each process for Round Robin algorithm.
    private int finishTime ; // int finishTime we will use it to know the finish Time of each process for Round Robin algorithm.

 // No-argument constructor it includes the default values about for the
 	// variables.
    
    public AlgorithmeEvent(String processName, int starttime, int finishTime) {
        this.processName = processName ;
        this.starttime = starttime ;
        this.finishTime = finishTime ;
    }

    public String getProcessName(){ // declare a method it's called ProcessName and it's kind is String and it returns ProcessName.
        return processName ;
    }

    public int getStartTime(){  // declare a method it's called start time and it's kind is integer and it returns start time.
        return starttime ;
    }

    public int getFinishTime(){  // declare a method it's called finishTime and it's kind is integer and it returns finishTime.
        return finishTime ;
    }

    public void setFinishTime(int finishTime){ // declare a method it's called finishTime and it sets a new finishTime for the new given or the new chosen process.
        this.finishTime = finishTime ;
    }
}
