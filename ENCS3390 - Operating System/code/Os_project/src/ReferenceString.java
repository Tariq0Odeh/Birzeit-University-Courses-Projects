import java.util.ArrayList;

public class ReferenceString {
    
	ArrayList<Integer> String; 			// our actual string of numbers

    public ReferenceString() {
    	String = new ArrayList<Integer>() ;
    }

    public ReferenceString(ArrayList<Integer> referenceString) {
    	String = referenceString;
    }

    int getLength() { // declare a method it's called getLength and it's kind is integer and it returns length of the string for the process.
        return String.size() ;
    }
    
    int getAtIndex(int i) { // declare a method it's called getAtIndex and it's kind is integer and it returns the Index of the string for the process.
        
    	return String.get(i) ;
    }
    
    // void function to get all the information from the input file and declare all of it in the string
    void print() {
        int i;
        for (i = 0; i < String.size() - 1; i++) {
            System.out.print(String.get(i) + ", ") ;
        }
        System.out.print(String.get(i)) ;
    }
}
