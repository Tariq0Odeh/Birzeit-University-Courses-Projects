import java.util.ArrayList;
import java.util.List;

public class CheckAllInputs {
	
	public static List<RowsInFile> deepCopy(List<RowsInFile> PreviousList) {
		
	List<RowsInFile> CurrentList = new ArrayList();

		// for loop to see all inputs and put them in lists this for loop will keep put
		// informations in lists and when the list is full it will be called previous
		// list and we will put new information in new list.
		
		for (RowsInFile row : PreviousList) {
			
			CurrentList.add(new RowsInFile(row.getProcessName(), row.getStartTime(), row.getDurationTime()));
		}
		return CurrentList;
	}
}
