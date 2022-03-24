
package TAriq ;						//the package that contains this class of Owner

import java.util.* ;				//used to import an entire package, because we will use GregorianCalendar class


public class Owner{					//definition of class Owner 
									//default is defined as given in the UML
	 String name ;					//define the properties in the class of Owner
	 String registrationNo ;
	 String address ;
	 String tel ;
	 GregorianCalendar dateOfRegistration ;
	 
	
	 public Owner( ){												//create a default constructor to assign default values for properties 
		this(null, null, null, null, null);							//because we want to set the owner to null for cloned object
	}
	
	 public Owner( String name ){									//create a constructor with String name to put these values inside the properties
		
		this.name = name ;
		this.address = null ;
		this.tel = null ;
		this.registrationNo = null ;
		this.dateOfRegistration = null ;
	}
	 
	 														//create a constructor with values to put these values inside the properties
	 Owner( String name , String registrationNo , String address , String tel , GregorianCalendar dateOfRegistration ){ 
		super( ) ;
		this.name = name ;
		this.registrationNo = registrationNo ;
		this.address = address ;
		this.tel = tel ;
		this.dateOfRegistration = dateOfRegistration ;
	}
	
	 
	
	 public GregorianCalendar getDateOfRegistration( ){			//getter method to return instance properties value
		return dateOfRegistration ;
	}
	
	 public String getRegistrationNo( ){
		return registrationNo ;
	}
	
	 public String getName( ){
		return name ;
	}
	
	 public String getAddress( ){
		return address ;
	}
	
	 public String getTel( ){
		return tel ;
	}


	
	
	 public void setName( String name ){							//setter method to set instance properties value
		this.name = name ;
	}
	 
	 public void setDateOfRegistration( GregorianCalendar dateOfRegistration ){
		this.dateOfRegistration = dateOfRegistration ;
	}
	 
	 public void setRegistrationNo( String registrationNo ){
		this.registrationNo = registrationNo ;
	}
	
	 public void setAddress( String address ){
		this.address = address ;
	}

	 public void setTel( String tel ){
		this.tel = tel ;
	}
	 
	
	 
	
	@Override							//overrides toString() method to return Owner information
	public String toString() {			//method to return Owner information
		
		String owner_tostring = "[The Owner_inf]" + "{name} " + name + " | " + "{registrationNo} " + registrationNo + " | " + "{address} " +
								address + " | " + "{tel} " + tel + " | " + "{dateOfRegistration} " + dateOfRegistration ;
		
		return owner_tostring ;
	}
	
	
}			//end of class Owner
