package employees;												//package includes classes

import java.util.* ;								    		//import Date because we want use Date

	public class ProductionWorker extends Employee { 			//defines sub class ProductionWorker extends from super class Employee

		 private int shift ;									//instance variables to store ProductionWorkerployee information
		 private double hourlyPayRate ;
		 private int hoursPerMonth ;
 
  			
	public ProductionWorker() {									//default constructor to assign default values to instance variables
 
		 shift = 0 ;
		 hourlyPayRate = 0.0 ;
		 hoursPerMonth = 0 ;
	}
 
	
  															//create a constructor with information to put these values inside the parameters
	public ProductionWorker( String name , String number , int year , int month , int day  , Address address ,
								int shift , double houlyPayRate , int numHoursPerMonth ) {

		 super( name , number , year , month , day , address ) ;			//calls super class parameterized constructor
		 this.setShift(shift) ;
     	 this.hourlyPayRate = houlyPayRate ;
     	 this.hoursPerMonth = numHoursPerMonth ;
 	}
 
  
  
	public int getShift() {									//getter method to return instance variable value
  
		 return shift ;
	}
 
	public double getHourlyPayRate() {
  
		 return hourlyPayRate ;
	}
 
	public int getHoursPerMonth() {
  
		 return hoursPerMonth ;
 	}
 
  
  
  	public void setShift( int shift ) {						//setter method to change instance variable value
	  
  		  this.shift = shift ;
  	}
 
  	public void setHourlyPayRate( double hourlyPayRate ) {
  
    	  this.hourlyPayRate = hourlyPayRate ;
  	}
 
  	public void setHoursPerMonth( int hoursPerMonth ) {
 
  		 this.hoursPerMonth = hoursPerMonth ;
  	}
 
  
  
  										
  	public double getTotalSalary() {						//method to calculate salary and returns it
 
  		double sum = 0 ;
      
  		if(shift == 1) {									//checks if shift is 1
  			if(hoursPerMonth <= 208) { 		 				//checks if monthly hours worked is less then or equals to 208
              sum = hoursPerMonth * hourlyPayRate ;
  			}
          
          else {											//otherwise calculates over time
              sum = hoursPerMonth * hourlyPayRate + ((hoursPerMonth - 208) * 1.25) ;
          }
      }
      
      
      else if(shift == 2) {									 //otherwise checks if shift is 2
   	    if(hoursPerMonth <= 182) {							 //checks if monthly hours worked is less then or equals to 182
              sum = hoursPerMonth * hourlyPayRate ;
   	    }
         
        else {												 //otherwise calculates over time
              sum = hoursPerMonth * hourlyPayRate + ((hoursPerMonth -182) * 1.5) ;
        }
      }
          
  		return sum ; 											//returns salary
  	}
  
  	
  	public String isShiftValid() {								//method to  warn from errors in information or failure to work
	   String res = "" ;						
	   
	   if( shift != 1 && shift !=2 ) {							//check that the information on the shift is correct, must be 1 or 2
		   res+= "\n\t #{Warning!!!The shift is not vaild the shift must be only 1 to day or 2 to night}" ;
	   }
	   if(shift == 1 && hoursPerMonth < 208) {					//to check the number of employee working hours monthly in Shift 1, are they within the required rate
			   res+= "\t #{Warning!!! Please check with your manager because your working hours per month are less than the required rate 208 in month}" ;
		   }
	   if(shift == 2 && hoursPerMonth < 182) {					//to check the number of employee working hours monthly in Shift 2, are they within the required rate
			   res+= "\n\t #{Warning!!! Please check with your manager because your working hours per month are less than the required rate 182 in month}" ;
	   }
	   
	   return res ;												//return appropriate warning
  	}
  	
  	
  	public String toMotivational() {							//method for printing words that motivate the employee to work according to his own shift
  		
  		String res = "" ;
  		if(shift == 1 ) {										//to motivate the employee to work
			   res+= "\t [Hard work is what successful people do!]" ;
		   }
	   if(shift == 2 ) {										//to motivate the employee to work
			   res+= "\t [\"Descipline is not a pain, is a training, is your best friend, it'll take care of you like nothing else!]";
	   }
	   
	   return res ;												//return appropriate motivate
  	}
	  

  
 
  
  	@Override													//overrides toString method to return production worker employee information
  	public String toString() {									//method to return production worker employee information

	   String production_inf = super.toString() + "\n\t -Production Worker shift: " + shift + 
			   "\n\t -Houly Pay Rate: " + hourlyPayRate +
			   "\n\t -Number Hours Per Month: " + hoursPerMonth + "\n" + toMotivational() + "\n\t" + isShiftValid() ;
	   return  production_inf ;
  	}
  	
}																// End of class ProductionWorker
														