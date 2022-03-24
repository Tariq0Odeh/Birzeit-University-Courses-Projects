
public class RowsInFile {

	// defining the instance viriables

	private String processName; // String processName we will use it to know the name of each process in the
								// input file.
	private int StartTime; // int StartTime we will use it to know when the exact time to start of each
							// process in the input file.
	private int DurationTime; // int DurationTime we will use it to know how many time each process must stay
								// in the input file.
	private int waitingTime; // int waitingTime we will use it to count how many time each process has waited
								// until it started.
	private int turnaroundTime; // int turnaroundTime we will use it to count the time that each process has
								// stayed in the memory.

	// No-argument constructor it includes the default values about for the
	// variables.

	private RowsInFile(String processName, int StartTime, int DurationTime, int waitingTime, int turnaroundTime) {
		this.processName = processName;
		this.StartTime = StartTime;
		this.DurationTime = DurationTime;
		this.waitingTime = waitingTime;
		this.turnaroundTime = turnaroundTime;
	}

	// Constructing a RowsInFile object that has the same name as the class itself
	// we will
	// put in it all information that given in the schedule in question.
	// No-argument constructor it includes the default information about the given
	// Rows

	public RowsInFile(String processName, int StartTime, int DurationTime) {
		this(processName, StartTime, DurationTime, 0, 0);
	}

	public void setDurationTime(int DurationTime) { // declare a method it's called DurationTime and it sets a new
													// DurationTime for the new given or the new chosen process.

		this.DurationTime = DurationTime;
	}

	public void setWaitingTime(int waitingTime) { // declare a method it's called waitingTime and it sets a new
													// waitingTime for the new given or the new chosen process.
		this.waitingTime = waitingTime;
	}

	public void setTurnaroundTime(int turnaroundTime) { // declare a method it's called turnaroundTime and it sets a new
														// turnaroundTime for the new given or the new chosen process.
		this.turnaroundTime = turnaroundTime;
	}

	public String getProcessName() { // declare a method it's called ProcessName and it's kind is String and it
										// returns ProcessName.

		return this.processName;
	}

	public int getStartTime() { // declare a method it's called StartTime and it's kind is integer and it
								// returns StartTime.
		return this.StartTime;
	}

	public int getDurationTime() { // declare a method it's called DurationTime and it's kind is integer and it
									// returns DurationTime.
		return this.DurationTime;
	}

	public int getWaitingTime() { // declare a method it's called waitingTime and it's kind is integer and it
									// returns waitingTime.
		return this.waitingTime;
	}

	public int getTurnaroundTime() { // declare a method it's called turnaroundTime and it's kind is integer and it
		// returns turnaroundTime.
		return this.turnaroundTime;
	}
}
