import java.util.Scanner;         //to import scanner
public class Nice {               // Main Method
	public static void main(String[] args) {
		Scanner in =new Scanner(System.in);         // creating a Scanner object
		System.out.println(" <*>This program prints all nice numbers in a given range that user will enter it <*> \n ");
		System.out.println("\tPlease Enter Left bound and Right bound and digit to exclude\n\twhere Left bound is less than Right bound and digit between [0,9]:\n");
		
		// asking user to print the value of the Left,right bound and digit
		// Declare left,right,digit to be an integer variable and user will enter it's
		System.out.print("Enter Left bound:");      
		int left = in.nextInt();                    
		System.out.print("Enter Right bound:");    
		int right = in.nextInt();
		System.out.print("Enter digit to exclude it:");
		int m = in.nextInt();
		
		
		if(left>=right) {                              // to sure that Left bound is less than Right bound    
			System.out.println("Erorr The Lift bound Shoud be less than Right bound");
		}
		else if (m >9 || m<0) {                    // to sure that digit is correct input
			System.out.println("Erorr  digit to exclude Shoud be between [0,9]");
		}
		else {                 //After checking the input, we call the function to find the nice number
     	   System.out.println("Nice Numbers in Range Left=" + left + " ,Right= " + right+ " with exclude digit m=" + m + " are:");
     	   niceNumbers(left, right, m);
		}
		
	}
		//fanction to know the nice number between the numbers entered by the user and their printing
	public static void niceNumbers(int left, int right, int dight) {
		for (int i = left; i <= right; i++) {  //Loop number starts from left to right
			int a;                     //To store the number in it and examine it with the digit
			int v = 0 , c =0 ;         //v --> to boolean flag  ,  c--> to point on digit
			
			int sum = 0;               //To store the sum of numbers from the right
			int numb = i;              //Store the number in a variable for scanning operations
			
			while (numb != 0) {        //Loop to extract the number from the right and perform the examination on it
				 a = numb % 10;
				 if (c!=0  && a <= sum   ) {     //To check digit is larger than the sum of digits
					 v=1 ;					     //which are on the right side of that digit excluding the first right digit 
	
					}
				 if (a == dight) {       //Check if the digit is equal to digit to exclude
					v=1 ;
				 }
				
				sum += a;
				numb /= 10;
				c++;
			}
			
		if (v==0) {                    //print all nice number
			System.out.print(i + "|");
		}
		}
		
	}
}
	