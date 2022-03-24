
package TAriq ;									//the package that contains this class of Truck


public class Truck extends Vehicles{			//definition of class Truck that is subsets class of Vehicles
	
	private boolean airCondtionOn ;				//define the properties in the class of Truck
	private int power ;
	private int numberOfSeats ;		
	
	
	public Truck(){								//create a default constructor to assign default values
		
		numberOfSeats = 0 ;
		power = 0 ;
		airCondtionOn = false ;
	}
	
												//create a constructor with values to put these values inside the properties
	public Truck( String modelName , String modelNo , String brand , Owner owner ,	String engineType ,
					double tunkSize , double fuel_consumption , int power , int numberOfSeats ){
		
		super( modelName , modelNo , brand , " " , tunkSize , fuel_consumption , owner ) ;	//call the construct from the father to enter the values

			this.airCondtionOn = false ;						//set air condtionOn off
			this.power = power ;
			this.numberOfSeats = numberOfSeats ;
			
			if (engineType.equalsIgnoreCase("Diesel")){			//to check the engine gasoline type because The Truck uses only diesel 
				
				super.setEngineType(engineType) ;				//use the method from the father to set Engine Type for the engine by use super
		}
		
		else {											
			throw new IllegalArgumentException("Engine type not found") ;		//throwing out an exception if the vehicle's engine type is not Diesel
		}
	}

	

	public int getPower( ){						//getter method to return instance properties value
		return power ;
	}

	public boolean isAirCondtionON( ){
		return airCondtionOn ;
	}
	
	public int getNumberOfSeats( ){
		return numberOfSeats ;
	}

	
	
	public void setAirCondtionON( boolean airCondtionON ){			//setter method to set instance properties value
		this.airCondtionOn = airCondtionON ;	
	}

	public void setPower( int power ){
		this.power = power ;
	}
	
	public void setNumberOfSeats( int numberOfSeats ){
		this.numberOfSeats = numberOfSeats ;
	}
	
	
	@Override																		//overrides costFor100Km() method
	public double costFor100Km( ){													//method to calculating cost for running 100 Km with the engine type and the petroleum type passed by as parameter
		double truck_consumption = ( fuel_consumption ) ;							//truck conditioner consumption that is distance 100km divide how many km the truck is traveling per liter (to know how much liter need)						
		double cost = 0.0 ;															//cost for 100 km (we want to store the cost inside to return it)
		
		if (isAirCondtionON()){														//check if the air conditioner is on, because it will increase the truck's fuel consumption
			cost = ((( 100 / truck_consumption  ) * super.getDieselPrice() ) * (1.2 )); 	//cost when the conditioner on equal consumption of car and conditioner multiply price of petroluemType	
			}
		
			else{
				cost =   ( 100 / truck_consumption ) * super.getDieselPrice() ;								//cost when the conditioner on equal consumption of car multiply price of petroluemType	
			}
		
		return cost ;						//return cost For 100Km
	}
	

	
	
	@Override									//overrides setAirCondtionON() method
	public boolean setAirCondtionON( ){			//method for setting the condition of the air conditioner on and returning the condition of the air conditioner
		this.airCondtionOn = true ;
		
		return airCondtionOn ;
		
	}

	@Override									//overrides setAirCondtionOFF() method
	public boolean setAirCondtionOFF( ){		
		this.airCondtionOn = false ;			//method for setting the condition of the air conditioner off and returning the condition of the air conditioner
		
		return airCondtionOn ;
				
	}


	@Override													//overrides compareTo() method 
	public int compareTo( Vehicles veh ){						// to compare the objects
		if(this.costFor100Km() > veh.costFor100Km() ){			//if cost for 100km for fist car large than second car return 1
			return 1 ;																
		}
		else if (this.costFor100Km() < veh.costFor100Km() ){	//if cost for 100km for fist car large than second car return 1
		return -1 ;

		}
		else {													//if they equal return 0
			return 0 ;
		}
	}
	
	
	@Override							//overrides toString method to return Truck information
	public String toString() {			//method to return Truck information
		String truck_tostring =  super.toString()  + " | " + "{Number of seats} " + numberOfSeats + " | " +
									"{Air condtion On?} " + airCondtionOn + " | " + "{Horse Power} " + power + " | " + "{Cost For 100Km} " + this.costFor100Km() + " NIS"; ;
		
		return truck_tostring ;
	}
	
	
	public void getAboutBrand_truck( ){													//my owns methods to get information about history of the manufacture and where made
		if (super.getModelName().equalsIgnoreCase("Tundra")) {								//to check Model Name to print information
				System.out.println("\t##[The history of the manufacture of the first [Toyota Tundra], 1999]");
				System.out.println("\t##[Made in Japan]\n");
		}
		
		else{																				//to check Model Name to print information
			System.out.println("\t##[The history of the manufacture of the first [Honda Ridgeline], 2006]");
			System.out.println("\t##[Made in Japan]\n");
		}
	}
	
	
}		//end of class Truck
