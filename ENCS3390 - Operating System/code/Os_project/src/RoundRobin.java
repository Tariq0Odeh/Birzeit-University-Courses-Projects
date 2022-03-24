import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class RoundRobin extends Scheduling{ 
	// in this class we will compare two processes start time together to see who
	// must start at first, so any process can not start enter to memory if its time
	// still not starting
	@Override
    public void process(){
        Collections.sort(this.getRows() , (Object o1, Object o2) -> {
            if (((RowsInFile) o1).getStartTime() == ((RowsInFile) o2).getStartTime()){
                return 0;
            }								// if process 1 start time < process 2 start time , then process 1 came first
            else if (((RowsInFile) o1).getStartTime() < ((RowsInFile) o2).getStartTime()){
                return -1;
            }
            else{							// here it means process 2 came before process 1
                return 1;
            }
        });

        List<RowsInFile> rows = CheckAllInputs.deepCopy(this.getRows());
        int T = rows.get(0).getStartTime();   	// get the start time for each process
        int T_quantum = this.getTimeQuantum();  	// get the time quantum that user has entered
        	
        while (!rows.isEmpty()){					// while loop that run if there are rows but if the input file is empty it will not run
        	RowsInFile row = rows.get(0);			// get all rows that are in the input file
            int b_t = (row.getDurationTime() < T_quantum ? row.getDurationTime() : T_quantum);
            this.getTimeline().add(new AlgorithmeEvent(row.getProcessName(), T, T + b_t));
            T += b_t;
            rows.remove(0);

            if (row.getDurationTime() > T_quantum){ 									// if statement to check if the kept duration of the process is >
                row.setDurationTime(row.getDurationTime() - T_quantum);				// time quantum or not , if yes then new duration = duration - timeQuantum
                for (int i = 0 ; i < rows.size() ; i++){
                    if (rows.get(i).getStartTime() > T){
                        rows.add(i, row);
                        break;
                    }
                    else if (i == rows.size() - 1){
                        rows.add(row);
                        break;
                    }
                }
            }
        }

        Map map = new HashMap();

        for (RowsInFile row : this.getRows()){
            map.clear();
            for (AlgorithmeEvent event : this.getTimeline()){
                if (event.getProcessName().equals(row.getProcessName())){
                    if (map.containsKey(event.getProcessName())){
                        int w = event.getStartTime() - (int) map.get(event.getProcessName());
                        row.setWaitingTime(row.getWaitingTime() + w);
                    }
                    else{
                        row.setWaitingTime(event.getStartTime() - row.getStartTime());
                    }
                    map.put(event.getProcessName(), event.getFinishTime());
                }
            }
            row.setTurnaroundTime(row.getWaitingTime() + row.getDurationTime());
        }
    }
}
