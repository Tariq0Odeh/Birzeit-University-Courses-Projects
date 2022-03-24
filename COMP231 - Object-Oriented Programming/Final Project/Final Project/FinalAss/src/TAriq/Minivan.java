
package TAriq ;									//the package that contains this class of Minivan


public class Minivan extends Vehicles{			//definition of class Minivan that is subsets class of Vehicles
	
	private int numberOfSeats ;					//define the properties in the class of Minivan
	private boolean airCondtionON ;
	private boolean hasAutoDoors ;
	
	
	public Minivan(){							//create a default constructor to assign default values
		
	}
	
												//create a constructor with values to put these values inside the properties
	public Minivan( String modelName , String modelNo , String brand , Owner owner ,String engineType ,
					double tunkSize , double fuel_consumption , int numberOfSeats , boolean hasAutoDoors ){
		   
		super( modelName , modelNo , brand , engineType , tunkSize , fuel_consumption , owner ) ;		//call the construct from the superclass to enter the values
		this.numberOfSeats = numberOfSeats ;
		this.airCondtionON = false ;																	//set air condition false
		this.hasAutoDoors = hasAutoDoors ;
		
		if ( engineType.equalsIgnoreCase("Gasoline")){										//check the engine type and make sure that it is among the available engines
			super.setEngineType( engineType ) ;												//set the engine type according to the check above
		}
		
		else if (engineType.equalsIgnoreCase("Hybrid")){									//check the engine type and make sure that it is among the available engines
			super.setEngineType( engineType ) ;												//set the engine type according to the check above
		}
		
		else if (engineType.equalsIgnoreCase("Diesel")){									//check the engine type and make sure that it is among the available engines
			super.setEngineType( engineType ) ;												//set the engine type according to the check above
		}
		
		else{																				//throwing out an IllegalArgumentException if the engine type of the car is not included
			throw new IllegalArgumentException("Engine type not found") ;
		}

	}
	
	
	
	
	public int getNumberOfSeats( ){									//getter method to return instance properties value
		return numberOfSeats ;
	}
	
	public boolean isHasAutoDoors( ){
			return hasAutoDoors ;
	}
	
	public boolean isAirCondtionON( ){
			return airCondtionON ;
	}

	
	
	public void setNumberOfSeats( int numberOfSeats ){				//setter method to set instance properties value
		this.numberOfSeats = numberOfSeats ;	
	}
	  
	public void setHasAutoDoors( boolean hasAutoDoors ){
		this.hasAutoDoors = hasAutoDoors ;
	}
	   
	public void setAirCondtionON( boolean airCondtionON ){
		this.airCondtionON = airCondtionON ;
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
	
	
	@Override																		//overrides costFor100Km() method
	public double costFor100Km( ){													//method to calculating cost for running 100 Km with the engine type and the petroleum type passed by as parameter
        double fuelPrice = (this.engineType.toLowerCase().equals("gasoline")) ?  super.getGasolinePrice() : super.getDieselPrice(); //the minivan engine type is checked in order to determine the price of gasoline or diesel
               fuelPrice = (this.engineType.toLowerCase().equals("diesel")) ?  super.getDieselPrice()  : super.getGasolinePrice(); //the minivan engine type is checked in order to determine the price of Hybrid or diesel
        double minivan_consumption = ( fuel_consumption ) ;							//minivan conditioner consumption that is distance 100km divide how many km the minivan is traveling per liter (to know how much liter need)						
		double cost = 0.0 ;															// cost for 100 km (we want to store the cost inside to return it)
		
		if (isAirCondtionON()){														//check if the air conditioner is on, because it will increase the minivan's fuel consumption
			cost = ((( 100 / minivan_consumption  ) * fuelPrice ) * (1.2 )); 	//cost when the conditioner on equal consumption of car and conditioner multiply price of petroluemType	
			}
		
			else{
				cost =   ( 100 / minivan_consumption ) * fuelPrice ;								//cost when the conditioner on equal consumption of car multiply price of petroluemType	
			}
		
		return cost ;						//return cost For 100Km
	}
	
	
	
	
	@Override											//overrides setAirCondtionON() method
	public boolean setAirCondtionON( ){
		this.airCondtionON = true ;						//method for setting the condition of the air conditioner on and returning the condition of the air conditioner
		
		return airCondtionON ;
		
	}

	@Override											//overrides setAirCondtionOFF() method
	public boolean setAirCondtionOFF( ){				//method for setting the condition of the air conditioner off and returning the condition of the air conditioner
		this.airCondtionON = false ;	
		
		return airCondtionON ;
				
	}


	

	@Override										//overrides toString method to return Minivan information
	public String toString( ){						//method to return Minivan information
		String minivan_tostring = super.toString() + " | " + "{Number of seats} " + numberOfSeats + " | " + "{Air condtion On?} " + airCondtionON +
										" | " + "{Auto Doors?} " +  hasAutoDoors + " | " + "{Cost For 100Km} " + this.costFor100Km() + " NIS";
		return minivan_tostring ;
	}
	
	
	public void getAboutBrand_minivan() {										//my owns methods to get information about history of the manufacture and where made
		if (super.getModelName().equalsIgnoreCase("Sienna")){					//to check Model Name to print information
				System.out.println("\t##[The history of the manufacture of the first [Toyota Sienna], 2009]");
				System.out.println("\t##[Made in Japan]\n") ;
		}
		else if (super.getModelName().equalsIgnoreCase("Odyssey")){				//to check Model Name to print information
			System.out.println("\t##[The history of the manufacture of the first [Honda Odyssey], 1994]");
			System.out.println("\t##[Made in Japan]\n") ;
		}
		else{																	//to check Model Name to print information
			System.out.println("\t##[The history of the manufacture of the first [Nissan Presage], 1998]");
			System.out.println("\t##[Made in Japan]\n") ;
		}
	}
	
	
	
}			//end of class Minivan
