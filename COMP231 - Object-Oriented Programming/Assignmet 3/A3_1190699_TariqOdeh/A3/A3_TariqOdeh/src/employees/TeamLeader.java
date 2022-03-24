package employees;													//package includes classes

import java.util.*;													//import Date because we want use Date



	public class TeamLeader extends ProductionWorker {			  	 //defines sub class TeamLeader extends from super class ProductionWorker
		
		 private double monthlyBonus ;								//instance variables to store team leader employee information			
		 private int requierdTrainingHour ;
		 private int trainingHourAttended ;
 
		 
	public TeamLeader() {											//create a default constructor to assign default values instance values
  
		 super() ;													 //calls super class default constructor
		 monthlyBonus = 0.0 ;
		 requierdTrainingHour = 0 ;
		 trainingHourAttended = 0 ;
	}
 
  																	//parameterized constructor to assign parameter values to instance variables
	public TeamLeader( String name , String number , int year , int month , int day , Address address ,
						int shift , double houlyPayRate , int numHoursPerMonth , double monthlyBonus ,
						int requierdTrainingHour , int trainingHourAttended  ) {
		
	   																//calls super class parameterized constructor
		 super( name , number , year ,  month ,  day , address , shift , houlyPayRate , numHoursPerMonth  );	
		 this.monthlyBonus = monthlyBonus ;
		 this.requierdTrainingHour = requierdTrainingHour ;
		 this.trainingHourAttended = trainingHourAttended ;
	}
 
  
  
	public double getMonthlyBonus() {								//getter method to return instance variable value
		
		 return monthlyBonus ;
	}
 
	public int getRequierdTrainingHour() {
  
		 return requierdTrainingHour ;
	}
 
	public int getTrainingHourAttended() {
  
		 return trainingHourAttended ;
	} 
 
  
	
	public void setMonthlyBonus( double monthlyBonus ) {			//setter method to change instance variable value
  
		 this.monthlyBonus = monthlyBonus ;
	}
 
	public void setRequierdTrainingHour( int requierdTrainingHour ) {
  
	  	 this.requierdTrainingHour = requierdTrainingHour ;
  	}
 
	public void setTrainingHourAttended( int trainingHourAttended ) {
  
	  	 this.trainingHourAttended = trainingHourAttended ;
  	}	
 
  
	
	
	public double getTotalSalary() {								 //method to calculate salary and returns it
  
		 double bonusAchieved = ( (monthlyBonus *  (double)trainingHourAttended ) / requierdTrainingHour ) ;      
		 double salary = super.getTotalSalary() + monthlyBonus + bonusAchieved ;
      
		 
     	return salary;												//returns salary
	}
 
  
  
  	@Override														//overrides toString method to return team leader employee information
  	public String toString() {										//method to return team leader employee information
  
  		String leader_inf = "\n" + super.toString() +"\n\n\t -Monthly Bonus: " + monthlyBonus + 
               "\n\t -Requierd Training Hour: " + requierdTrainingHour + 
               "\n\t -Training Hour Attended: " + trainingHourAttended + 
               "\n\t -Take Home Pay: " + getTotalSalary() ;  
      
  		return leader_inf ;
  	}
  	
}																	//end of class TeamLeader

