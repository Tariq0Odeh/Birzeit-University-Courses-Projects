package employees ;								//package includes classes

import java.util.* ;							//import Date because we want use Date   


	public class Employee {						//define of class employees
				
		 private String name ;					//instance variables to store employee information
		 private String number ;
		 private Date hireDate ;
		 private Address address ;


	public Employee() {							//create a default constructor to assign default values instance values

		 name = "some name" ;
		 number = "XXX-L" ;
		 hireDate = new Date() ;				//new object of Date
		 address = new Address() ;				//new object of Address
	}

	
												//create a constructor with information to put these values inside the parameters
	public Employee( String name , String number , int year , int month , int day , Address address ) {	
    
		 this.name = name ;
		 this.number = number ;
		 year -=1900 ;							//because the date adds the time the device is valid on year, which is 1900,That is why we should avoid adding to 1900 over the year, which we subtract from years
		 month -=1 ;							//because the date starts counting months from 0-11, This is why month 12 is available if we subtract one from 1
		 this.hireDate = new Date( year , month , day ) ;    
		 this.address = address ;
	}


	public String getName() {					//getter method to return instance variable value
		 return name ;
	}

	public String getNumber() {
		 return number ;
	}

	public Date getHireDate() {
 	     return hireDate ;
	}

	public Address getAddress() {
		 return address ;
	}



	public void setName( String name ) {		//setter method to change instance variable value
		 this.name = name ;
	}

	public void setNumber( String number ) {
		
		if(isEmpNumberValid( number ) ) {		//to make sure that the employee number is valid
			this.number = number ;
		}
		else {
			this.number = "XXX-L" ;
		}
	}

	public void setHireDate( Date hireDate ) {
		 this.hireDate = hireDate ;
	}

	public void setAddress( Address address ) {
		 this.address = address ;
	}



	

	private boolean isEmpNumberValid( String number ) {								// boolean method to return true if valid employee number otherwise returns false
   
		if( number.length() == 5 ){													//checks if length is not 5 then returns false
			for( int a = 0 ; a < number.length() ; a++ ) {	
				if( a < 3 && number.charAt(a) < '0' && number.charAt(a) > '9' ) {	//to check the first three character is less than 0 and greater then 9
					break ; 														//If it is not between 0 - 9 break is used and is taken out of the conditional sentence then returns an false
				}															
   
				if(number.charAt(3) != '-') {										//checks if 4th character is not '-' then return false
					break ;
				}
		   
   
				if(number.charAt(4) < 'A' && number.charAt(4) > 'M') {				//checks if 5th character is less than 'A' or greater then 'M' 
					break ;															//If it is not between 'A' -'M' break is used and is taken out of the conditional sentence then returns an false
				}	
		   
   
				return true ;														//otherwise valid returns true
			}
		}
   
		return false ;
	}

	
	@ Override																		//overrides toString method to return employee information
	public String toString() {														//method to return employee information
		
		String employee_inf = "~=~=~=~=~=~=~=~=~=~=~=~***=~=~=~=~~=~=~=~=~=~=~=~=~=~="+
							"\n\t -Name: " + name + "\n\t -Employee Number: " + number +
							"\n\t -Hire Date: " + hireDate + "\n" + address.toString() +
							"\n\t -Number Valid: " + isEmpNumberValid( number ) + "\n\t";
   
		return employee_inf ;
	}
	
}																					//end of class Employee

