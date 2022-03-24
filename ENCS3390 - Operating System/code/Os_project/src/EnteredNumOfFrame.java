public class EnteredNumOfFrame {

	int numberofframes; // integer numberofframes we will use it to know the number of frames the user
						// will enter.
	int insertNum; // integer insertNum we will use it to know the entered number of frames the
					// user has inserted.
	int nextUse; // integer nextUse we will use it to know the next frame we will use from all
					// frames.
	int lastUse; // integer lastUse we will use it to know the last frame we used from all
					// frames.
	int timesUsed;

	// No-argument constructor it includes the default values about for the
	// variables.

	// Constructing a Scheduling object that has the same name as the class itself

	EnteredNumOfFrame(int n) {
		numberofframes = n;
		insertNum = -1;
		nextUse = -1;
		lastUse = -1;
		timesUsed = 0;
	}
	// getters and setters

	void setNum(int n) {
		numberofframes = n;
	}

	int getNumOfFrames() { // declare a method it's called NumOfFrames and it's kind is integer and it
							// returns NumOfFrames.
		return numberofframes;
	}

	void setInserted(int n) { // declare a method it's called insertNum and it sets a new insertNum for the new given or the new chosen frame.
		insertNum = n;
	}

	int getInserted() { // declare a method it's called getInserted and it's kind is integer and it
						// returns Inserted number.
		return insertNum;
	}

	void setNextUse(int n) { // declare a method it's called nextUse and it sets a new nextUse for the new given or the new chosen frame.
		nextUse = n;
	}

	int getNextUse() { // declare a method it's called nextUse and it's kind is integer and it returns
						// nextUse of frame.
		return nextUse;
	}

	void setLastUse(int n) {  // declare a method it's called lastUse and it sets a new lastUse for the new given or the new chosen frame.
		lastUse = n;
	}

	int getLastUse() { // declare a method it's called lastUse and it's kind is integer and it returns
						// lastUse of frame.
		return lastUse;
	}

	void incrementTimesUsed() {
		timesUsed += 1;
	}

	int getTimesUsed() { // declare a method it's called timesUsed and it's kind is integer and it
							// returns timesUsed for each frame.
		return timesUsed;
	}
}
