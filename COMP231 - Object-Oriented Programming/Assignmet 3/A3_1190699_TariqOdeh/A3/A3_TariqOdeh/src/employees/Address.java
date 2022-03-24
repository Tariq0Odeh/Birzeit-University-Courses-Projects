package employees;										//package includes classes


	public class Address {								//defines class Address

		 private String street ;						//instance variables to store address information
		 private String state ;
		 private String city ; 
		 private String zip_code ;
 
  
	public Address() {									//default constructor to assign default values to instance variables
	   
        street = "street" ;
   		state =  "state" ;
   		city =  "city" ;
   		zip_code = "zip code" ;
	}
 
									
														//create a constructor with information to put these values inside the parameters
	public Address( String street , String state , String city , String zip_code ) {			
  
		 this.street = street ;
		 this.state = state ;
		 this.city = city ;
		 this.zip_code = zip_code ;
	}
 
  
	public String getStreet() {							//getter method to return instance variable value
  
		 return street ;
	}
 
	public String getState() {
  
		 return state ;
	}
 
	public String getCity() {
  
		 return city ;
	}
 
	public String getZip() {
	  
		 return zip_code ;
	}
 
  
  
	public void setStreet( String street ) {			//setter method to change instance variable value
  
		 this.street = street ;
	}
 
	public void setState( String state ) {
  
		 this.state = state ;
	}
 
	public void setCity( String city ) {
  
		 this.city = city ;
	}
 
	public void setZip( String zip ) {
  
		 this.zip_code = zip ;
	}
 
 
  
	@Override											//overrides toString method to return address information
	public String toString(){							// method to return address information
	   
	   String address_inf = "\t *************************" + " \n\t [Address]" +" \n\t\t -Street: " + street + "\n\t\t -State: " + state +
			   "\n\t\t -City: " + city + "\n\t\t -Zip Code: " + zip_code + "\n\t *************************" ;
	   
	   return address_inf ;
	}
	
	
}														//end of class Address

