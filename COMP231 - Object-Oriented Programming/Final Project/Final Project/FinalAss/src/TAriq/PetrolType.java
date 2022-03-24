
package TAriq ;									//the package that contains this class of PetrolType

public class PetrolType{						//definition of class PetrolType
												//determine the properties in the class of petroleum, as the properties are static
	public static final int DIESEL = 1 ;		//DIESEL constant =1
	public static final int GASOLINE = 2 ;		//GASOLINE constant =2
	private static double gasolinePrice = 5.23 ;	
	private static double dieselPrice = 4.02 ;
	
	
	
	public PetrolType( ){						//create a default constructor to assign default values
		PetrolType.gasolinePrice = 0 ;			//we can call dieselPrice & gasolinePrice from name constructor(class) because they define static
		PetrolType.dieselPrice = 0 ;
	}
	
	
	public PetrolType( double gasolinePrice , double dieselPrice ){		//create a constructor with values to put these values inside the properties
		
		super( ) ;
		PetrolType.setDieselPrice( dieselPrice ) ;						//call setDieselPrice to put a value dieselPrice
		PetrolType.setGasolinePrice( gasolinePrice ) ;					//call setGasolinePrice to put a value gasolinePrice
	
	}

	
	
	public static double getGasolinePrice( ){							//getter method to return instance properties value
		return gasolinePrice ;
	}

	public static double getDieselPrice( ){
		return dieselPrice ;
	}
	
	
	
	public static void setDieselPrice( double dieselPrice ){			//setter method to set instance properties value
		PetrolType.dieselPrice = dieselPrice ;							//we can call dieselPrice & gasolinePrice from name constructor(class) because they define static
	}
	
	public static void setGasolinePrice( double gasolinePrice ){
		PetrolType.gasolinePrice = gasolinePrice ; 
	}
	
	
	
	
	public static double getGasolinePriceDollar( ){				//my owns methods from shekels to dollars on  Gasoline Price		
		return gasolinePrice * 0.31 ;							//return price in dollars
	}

	public static double getDieselDollar( ){					//my owns methods from shekels to dollars on  Diesel Price	
		return dieselPrice * 0.31 ;								//return price in dollars
	}
	
	public static double getGasolinePriceDinar( ){				//my owns methods from shekels to Dinar  on  Gasoline Price		
		return gasolinePrice * 0.22 ;							//return price in Dinar
	}

	public static double getDieselDinar( ){						//my owns methods from shekels to Dinar  on  Diesel Price	
		return dieselPrice * 0.22 ;								//return price in Dinar
	}
	
	
}			//end of class PetrolType
