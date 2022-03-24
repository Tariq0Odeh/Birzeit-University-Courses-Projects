package employees;										//package includes classes

import java.util.*;										//import Date because we want use Date


	public class ShiftSupervisor extends Employee {		//defines sub class ShiftSupervisor extends from super class Employee
   
		 private double monthlySalary ;					//instance variables to store shift supervisor employee information
		 private double monthlyProductionBonusHas ;
		 private int numberOfProductsProduced ;
		 private int numberOfProductsMustProduced ;
  
   
	public ShiftSupervisor() {							//create a default constructor to assign default values instance values
  
		 monthlySalary = 0.0 ;							//calls super class default constructor
		 monthlyProductionBonusHas = 0.0 ;	
		 numberOfProductsProduced = 0 ;
		 numberOfProductsMustProduced = 0 ;
	}
	
  
   														//parameterized constructor to assign parameter values to instance variables
	public ShiftSupervisor( String name , String number, int year , int month , int day , Address address ,
							int monthlySalary , double monthlyProductionBonus , int numOfProductsProduced ,
							int numOfProductsMustProduced  ) {
   
    
		 super( name , number , year , month , day , address  );		  	 //calls super class parameterized constructor
		 this.monthlySalary = monthlySalary ;
		 this.monthlyProductionBonusHas = monthlyProductionBonus ;
		 this.numberOfProductsProduced = numOfProductsProduced ;
		 this.numberOfProductsMustProduced = numOfProductsMustProduced ;
	}
  
   
   
	public double getMonthlySalary() {										//getter method to return instance variable value
   
		 return monthlySalary ;
	}
  
	public double getMonthlyProductionBonus() {
   
		 return monthlyProductionBonusHas ;
	}
  
	public int getNumOfProductsProduced() {
   
		 return numberOfProductsProduced ;
	}
  
	public int getNumOfProductsMustProduced() {
   
		 return numberOfProductsMustProduced ;
	}
  
	
   
	public void setMonthlySalary( double monthlySalary ) {					//setter method to change instance variable value
   
		 this.monthlySalary = monthlySalary ;
	}
  
	public void setMonthlyProductionBonus( double monthlyProductionBonus ) {
   
		 this.monthlyProductionBonusHas = monthlyProductionBonus ;
	}
  
	public void setNumOfProductsProduced( int numOfProductsProduced ) {
   
		 this.numberOfProductsProduced = numOfProductsProduced ;
	}
  
	public void setNumOfProductsMustProduced( int numOfProductsMustProduced ) {
   
		 this.numberOfProductsMustProduced = numOfProductsMustProduced ;
	}  
  
	
   
	public double getTotalSalary() {										//method to calculate salary and returns it
   
       double salary = monthlySalary ;								 		//stores the monthly salary
       																		//checks if number of products produced is greater than or equals to
       if(numberOfProductsProduced >= numberOfProductsMustProduced)			// number of products must produced then add bonus 
           salary += monthlyProductionBonusHas ;							
       
       return salary ;														//returns salary
	}
	
	
	public String achieveTheTarget( ) {									//method of congratulations the employee for his extra work on sell products  and encouraging them to work
		String res = "" ;
		
		if(numberOfProductsProduced >= numberOfProductsMustProduced) {		//checks if number of products produced is greater than or equals to
			res += "\t[Congratulations!!! you deserve the bonus for achieving your target]" ;
		}
		
		else {																//otherwise, if the bonus is not achieved by selling above the target
			res += "\t[You need an extra effort to get the bonus]" ;
		}
		
		return res ;														//returns res
	}
  
   
   
	
	@Override																//overrides toString method to return shift supervisor employee information
	public String toString() {												//method to return shift supervisor employee information
       
		String shift_inf = "\n" + super.toString() + "\n\t -Monthly Salary: " + monthlySalary + 
    		   "\n\t -Monthly Production Bonus: " + monthlyProductionBonusHas + 
               "\n\t -Number Of Products Must Produced: " + numberOfProductsMustProduced + 
               "\n\t -Number Of Products Produced: " + numberOfProductsProduced +
               "\n\t"+ achieveTheTarget( ) +
               "\n\t -Take Home Pay: " + getTotalSalary() ;
       
       	return shift_inf ;
   }
	
	
}												//end of class ShiftSupervisor
	
   