
package TAriq ;									//the package that contains this class of Vehicles

import java.util.* ;							//used to import an entire package, because we will use GregorianCalendar class


public abstract class Vehicles implements Comparable < Vehicles > , Cloneable{		//definition of class vehicles and the use of interface Cloneable for copying Comparable and comparison

	
	protected String modelName ;				//define the properties in the class of Vehicles
	protected String modelNo ;
	protected String brand ;
	protected String engineType ;
	protected double tunkSize ;
	protected double fuel_consumption ;
	public Owner owner ;
	
	public Vehicles( ){							 //create a default constructor to assign default values 
		
	}
	
												//create a constructor with values to put these values inside the properties
	public Vehicles( String modelName , String modelNo , String brand , String engineType ,
						double tunkSize , double fuel_consumption , Owner owner ){
		super( ) ;
		this.modelNo = modelNo ;
		this.modelName = modelName ;
		this.brand = brand ;
		this.fuel_consumption = fuel_consumption ;
		this.engineType = engineType ;
		this.tunkSize = tunkSize ;
		this.owner = owner ;								//new object of Owner
	}
	
	
	public String getModelName( ){							//getter method to return instance properties value
		return modelName ;
	}

	public String getModelNo( ){
		return modelNo ;
	}
	
	public double getTunkSize( ){
		return tunkSize ;
	}
	
	public String getEngineType( ){
		return engineType ;
	}
	
	public String getBrand( ){
		return brand ;
	}
	
	public Owner getOwner( ){
		return owner ;
	}

	public double getFuel_consumption( ){
		return fuel_consumption ;
	}

	public double getDieselPrice( ){					//getter the price of Diesel and gasoline from PetrolType class
		return PetrolType.getDieselPrice() ;
	}
	
	public double getGasolinePrice( ){
		return PetrolType.getGasolinePrice() ;
	}
	
	
	public void setModelName( String modelName ){			//setter method to set instance properties value
		this.modelName = modelName ;
	}

	public void setBrand( String brand ){
		this.brand = brand ;
	}
	
	public void setOwner( Owner owner ){
		this.owner = owner ;
	}
	
	public void setModelNo( String modelNo ){
		this.modelNo = modelNo ;
	}

	public void setEngineType( String engineType ){
		this.engineType = engineType ;
	}
	
	public void setFuel_consumption( double fuel_consumption ){
		this.fuel_consumption = fuel_consumption ;
	}
	
	public void setTunkSize( double tunkSize ){
		this.tunkSize = tunkSize ;
	}
	 
	
	public int comparTo(Vehicles veh) {
		return 0;
	}
	
	
	public double moveable_distance( ){								 	//method of calculating the vehicle transported distance by multiplying the fuel consumption (km / liter) by the volume of the vehicle's fuel tank (liter) The result is the distance km
		return this.tunkSize * fuel_consumption ;	
	}

	
	public abstract boolean setAirCondtionOFF( ) ; 					  	//setting the air-condition of the vehicle to off , abstract was created for use on subclass
	
	
	public abstract boolean setAirCondtionON( ) ;						//setting the air-condition of the vehicle to on , abstract was created for use on subclass
	
	
	public abstract double costFor100Km( ) ;							//calculation of the vehicle cost of running 100 km depending on the type of engine, abstract was created for use on subclass

	
	@Override																//overrides clone() method 
	protected Object clone( ) throws CloneNotSupportedException {  			//method deep clone to copy the object and pass it through CloneNotSupportedException
		Vehicles vehicle_clone = (Vehicles)super.clone( ) ;					//Create clone for the first layer, which is the vehicle
																			//Create clone for the second layer, which is the GregorianCalendar,This is for the do deep Clone because GregorianCalendar it gives reference
		vehicle_clone.setOwner(new Owner( " " , " " , " " , " " , (GregorianCalendar)GregorianCalendar.getInstance( ) ) ) ;		
		return vehicle_clone ;                								//return the cloned object
	} 
	
	
	
	@Override						//overrides toString method to return Vehicles information
	public String toString( ) {		//method to return Vehicles information
		String vehicles_tostring = "[Vehicles_inf]--> " + "{Model name} " + modelName + " | " + "{Model Number} " + modelNo +
									" | " + "{Brand} " + brand + " | " + "{Owner name} " + owner.getName() + " | " + "{Engine Type} " +
									engineType + " | " + "{Tank Size} "+ tunkSize + " | " + "{Fuel consumption} "+ fuel_consumption  ;
		
		return vehicles_tostring;
	}
	
	
	
	public void importantAdvice( ){								//my owns methods that print important Advice		
		System.out.println("\t#[Check the wheels of the Vehicle]") ;
		System.out.println("\t#[Check the patrol in the Vehicle]") ;
		System.out.println("\t#[Check the Vehicle oil]") ;
		System.out.println("\t#[Do not use the phone while driving]") ;
		
	}

	
}									//end of class Vehicles
