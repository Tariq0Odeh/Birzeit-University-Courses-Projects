
package TAriq ;									//the package that contains this class of Car		

	
public class Car extends Vehicles{				//definition of class Car that is subsets class of Vehicles
		
	private int numberOfSeats ;					//define the properties in the class of Car
	private boolean airConditonOn ;
	
	
	public Car( ){								//create a default constructor to assign default values
		numberOfSeats = 0;
		airConditonOn = false ;
	}
			
												//create a constructor with values to put these values inside the properties
	public Car( String modelName , String modelNo , String brand , Owner owner ,
				String engineType , double tunkSize , double fuel_consumption , int numberOfSeats ){
		
		super( modelName , modelNo , brand ,  "" , tunkSize , fuel_consumption , owner ) ;  	//call the Construct from the superclass to enter the values

		this.numberOfSeats = numberOfSeats ;
		this.airConditonOn = false ;															//the air conditioner is closed because default airConditonOn value is false 
																								
			if ( engineType.equalsIgnoreCase("Gasoline")){										//check the engine type and make sure that it is among the available engines
				super.setEngineType( engineType ) ;												//set the engine type according to the check above
			}
			
			else if (engineType.equalsIgnoreCase("Hybrid")){									//check the engine type and make sure that it is among the available engines
				super.setEngineType( engineType ) ;												//set the engine type according to the check above
			}
		
			else{																				//throwing out an IllegalArgumentException if the engine type of the car is not included
				throw new IllegalArgumentException("Engine type not found") ;
			}
	}
	
	
	
	public boolean isAirConditonON( ){									//getter method to return instance properties value
		return airConditonOn ;
	}
	public int getNumberOfSeats( ){					
		return numberOfSeats ;
	}
	
	
	public void setAirConditonON( boolean airConditonON ){				//setter method to set instance properties value
		this.airConditonOn = airConditonON ;
	}
	
	public void setNumberOfSeats( int numberOfSeats ){					
		this.numberOfSeats = numberOfSeats ;
	}
	
	

	@Override													//overrides compareTo() method 
	public int compareTo( Vehicles veh ){						// to compare the objects
		if(this.costFor100Km() > veh.costFor100Km() ) {			//if cost for 100km for fist car large than second car return 1
			return 1 ;																
		}
		else if (this.costFor100Km() < veh.costFor100Km() ){	//if cost for 100km for fist car large than second car return 1
		return -1 ;

		}
		else {													//if they equal return 0
			return 0 ;
		}
	}

	
	@Override										//overrides setAirCondtionON() method
	public boolean setAirCondtionON( ){
		this.airConditonOn = true ;					//method for setting the condition of the air conditioner on and returning the condition of the air conditioner
		
		return airConditonOn ;
		
	}

	@Override										//overrides setAirCondtionOFF() method
	public boolean setAirCondtionOFF ( ){				
		this.airConditonOn = false ;				//method for setting the condition of the air conditioner off and returning the condition of the air conditioner
		
		return airConditonOn ;
				
	}
	
	@Override																		//overrides costFor100Km() method
	public double costFor100Km( ){													//method to calculating cost for running 100 Km with the engine type and the petroleum type passed by as parameter
		double car_consumption = ( fuel_consumption ) ;						//car conditioner consumption that is distance 100km divide how many km the car is traveling per liter (to know how much liter need)						
		double cost = 0.0 ;															// cost for 100 km (we want to store the cost inside to return it)
		
		if (isAirConditonON()){														//check if the air conditioner is on, because it will increase the car's fuel consumption
				cost = ((( 100 / car_consumption  ) * super.getGasolinePrice() ) * (1.1 )); 	//cost when the conditioner on equal consumption of car and conditioner multiply price of petroluemType	
			}
		
			else{
				cost =   ( 100 / car_consumption ) * super.getGasolinePrice() ;								//cost when the conditioner on equal consumption of car multiply price of petroluemType	
			}
		
		return cost ;						//return cost For 100Km
	}

	
	
	@Override								//overrides toString method to return Car information
	 public String toString() {				//method to return Car information
		String car_tostring = super.toString() + " | " + "{Number of seats} " + numberOfSeats + " | " + "{Air condtion On?} " + airConditonOn + " | " + "{Cost For 100Km} " + this.costFor100Km() + " NIS";
		
		return car_tostring ;
	}
	
	
	
	public void getAboutBrand_car( ){								//my owns methods to get information about history of the manufacture and where made
		if (super.getModelName().equalsIgnoreCase("Camley")){		//to check Model Name to print information
			System.out.println("\t##[The history of the manufacture of the first [Toyota Camry], 1982]") ;	
			System.out.println("\t##[Made in Japan]\n") ;	
		}
		
		else{														//to check Model Name to print information
			System.out.println("\t##[The history of the manufacture of the first [Toyota Aqua], 1997]") ;
			System.out.println("\t##[Made in Japan]\n") ;
			
		}
	}	//end of getAboutBrand_car method
	
	
}			//end of class Car
