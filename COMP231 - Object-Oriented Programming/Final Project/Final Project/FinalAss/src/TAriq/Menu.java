
package TAriq ;								//the package that contains this class of Menu
	
import java.util.GregorianCalendar ;		//used to import an entire package, because we will use GregorianCalendar
import java.util.ArrayList ;				//used to import an entire package, because we will use ArrayList
import java.util.Comparator ;				//used to import an entire package, because we will use Comparator
import java.util.Scanner ;					//used to import an entire package, because we will use Scanner
import java.io.EOFException;
import java.io.FileReader ;					//used to import an entire package, because we will use FileReader
import java.io.FileWriter;					//used to import an entire package, because we will use FileWriter
import java.util.Collections ;				//used to import an entire package, because we will use Collections



public class Menu{																	//definition of class Menu that is to test
	
	static  Scanner sc = new Scanner( System.in ) ;									//define the scanner to be read from the user and static to use it in and out of main
	static ArrayList< Vehicles > vehiclelist = new ArrayList< Vehicles >( ) ;		//define ArrayList to store vehicles information in it and static to use it in and out of main

	
	public static void main ( String[] args ){
		Owner tariq = new Owner( "TariqOdeh", "S1190699", "Palastine", "0599999911", (GregorianCalendar)GregorianCalendar.getInstance( ) ) ;//create a project from the owner with get Instance of the GregorianCalendar		
		//boolean value = true ;									//defining the variable as a value through which the program will continue or end according to its value
		while (true){								//while loop for do operation that user enter
				menuOptions( ) ;						//to show menu the choose operation
			
			System.out.print("- Choose the operation you want: ") ;
			int operation = sc.nextInt() ;				//read operation from user
			
			
			
			if ( operation == 1 ){						//if user enter operation 1
				read_File ( ) ;							//invoked the method read_File by which information is read and stored in AraayList
				System.out.println("\n\t#[The information has been successfully read and passed on to ArrayList]\n\n") ;
			}			//end of operation 1
			
			
			
			
			else if( operation == 2 ){										//if user enter operation 2
					
				System.out.print("\tEnter Price of Gasoline in NIS: ") ;
				
					double gasoline_price = sc.nextDouble() ;				//read the gasoline price from user
					PetrolType.setGasolinePrice(gasoline_price) ;			//store gasoline price entered by the user in PetrolType class
					
					System.out.print("\tEnter Price of Diesel in NIS: ") ;
					
					double diesel_price = sc.nextDouble() ;					//read the diesel price from user
					PetrolType.setDieselPrice(diesel_price) ;				//store diesel price entered by the user in PetrolType class
					
				System.out.print("\t#[Set prices of petroleum was done successfully]\n") ;
			}			//end of operation 2
			
			
			
			
			else if(operation == 3){				//if user enter operation 3
				
				Collections.sort( vehiclelist ) ;		//use abstract method to sort vehiclelist about cost for 100km  
			
				for( int j = 0 ; j < vehiclelist.size() ; ++j ){			//for loop to print the array after sort
					System.out.println( vehiclelist.get(j).toString( ) ) ;	
				}	//end loop
				
				System.out.println("\t\n#[Sorted List according to cost for 100km]");
				
			}					//end of operation 3
					
			
			
			
		else if( operation == 4 ){				//if user enter operation 4
												//the sort(List<T>,Comparator<? super T>) method is used to sort the specified list according to the order induced by the specified comparator, and i to sort about getname().getname
												//i used this sort to sorted order vehicles in an ascending order based on owner name
			Collections.sort( vehiclelist , (veh1 , veh2) -> veh1.getOwner().getName().compareTo(veh2.getOwner().getName() ) ) ;

			printList( vehiclelist ) ;			//invoked printList method to print the array list
			
			System.out.println("\t\n#[Sorted List in an ascending order based on owner name]");

		}										//end of operation 4
				
			
			
			
		else if( operation == 5 ){				//if user enter operation 5
												//the sort(List<T>,Comparator<? super T>) method is used to sort the specified list according to the order induced by the specified comparator, and i to sort about getbrand()
												//i used this sort to sorted order Vehicles in an descending order based on vehicle brand.
				Collections.sort( vehiclelist , (veh1 , veh2) -> veh2.getBrand().compareTo(veh1.getBrand() ) ) ;
				
				 printList(	vehiclelist	) ;		//invoked printList method to print the array list
				 
				System.out.println("\t\n#[Sorted List in an descending order based on vehicle brand]");

			}									//end of operation 5
				
				
			
			
			else if( operation == 6 ){				//if user enter operation 6
				
				for ( int j = 0 ; j < vehiclelist.size() ; ++j ){				//for loop to model name to display it in front of the user to choose the type that he wants to create as a clone for it
					System.out.print( vehiclelist.get(j).getModelName() + " | ") ;
				}		//end for loop
				
	
				System.out.println("\n\n\t- Enter Car name you want to clone: ") ;
				
				String clone_vehicle = sc.next();			//read the type objects the user wants to do cloning him 
	
				for ( int j = 0 ; j < vehiclelist.size() ; j++ ){			//for loop to compare what the user entered with the Model Name type found in Array List
					if ( clone_vehicle.toLowerCase().equals(vehiclelist.get(j).getModelName().toLowerCase() ) ){	//check if the value entered by the user is equal to one Model Name, as all the charecter have been converted to to lower case to avoid the problem of capital and integrity

						
						try{																		//to be tested  block of code for errors while it is being executed.
							if ( vehiclelist.get(j) instanceof Car ){								//if it's the object that we want to work for cloning is car
								Car car_clone = (Car) vehiclelist.get(j).clone() ;					//cloning the Car
								System.out.println( car_clone.toString( ) ) ;							//print the car_clone That we worked out cloning
							}
							
							else if(vehiclelist.get(j) instanceof Minivan){							//if it's the object that we want to work for cloning is Minivan
								Minivan minivan_clone = (Minivan) vehiclelist.get(j).clone( ) ;		//cloning the Minivan	
								System.out.println( minivan_clone.toString( ) ) ;						//print the minivan_clone That we worked out cloning
								
							}
							
							else{																	//if it's the object that we want to work for cloning is Truck 
								Truck truck_clone = (Truck) vehiclelist.get(j).clone( ) ;			//cloning the Truck
								System.out.println( truck_clone.toString( ) ) ;						//print the truck_clone That we worked out cloning						
							}
						}
						
						catch ( CloneNotSupportedException exp ){									//be executed, if an error occurs in the try block about  Clone Not Supported Exception
							exp.printStackTrace( ) ;													//it is a method which prints the throwable along with other details like the line number and class name where the exception occurred
						}		
					}
				}			//end for loop
				
				System.out.println("\t#[Clone Created]") ;
			}				//end of operation 6
			
			
			
			
			else if( operation == 7 ){									//if user enter operation 7	
				
				for ( int j = 0 ; j < vehiclelist.size( ) ;  j++ ){			//for loop to set all air-condition on 
					vehiclelist.get(j).setAirCondtionON( ) ;				//invoked all vehicles to operate the air conditioner

				}		//end of loop
				
				System.out.println("\t#[Air condtion Turned On]") ;
			}			//end of operation 7	
			
			
			
			
			else if( operation == 8 ){														//if user enter operation 8
				try {																		//to be tested  block of code for errors while it is being executed.
					FileWriter writer_out = new FileWriter( "output.txt" ) ;				//definition FileWriter for writing on a file output.txt
					Collections.sort( vehiclelist ) ;		//use abstract method to sort vehiclelist about cost for 100km  

					for( int j = 0 ; j < vehiclelist.size() ; ++j ){						//for loop to To put vehicles information in data_out to write it then on file output
						String data_out = "ModelName: " + vehiclelist.get(j).getModelName() + ", " + "Brand: "+ vehiclelist.get(j).getBrand() +
								", " + "Owner: " + vehiclelist.get(j).getOwner().getName() + ", " + "EngineType: "+ vehiclelist.get(j).getEngineType() +
								", " + "TankSize: " + vehiclelist.get(j).getTunkSize() + ", " + "\n" + "FuelConsumption: " + vehiclelist.get(j).getFuel_consumption() ;
						
						data_out += vehicle_out(j) ;				//call method vehicle_out to get string contains properties specific to each type of vehicle and add it on data_out
					
						writer_out.write(data_out+"\n") ;		//write the data_out on file output
					}		//end of for loop
					
					writer_out.close() ;				//close write on file
				}			
				
				catch(Exception exp){				//be executed, if an error occurs in the try block.
					exp.printStackTrace() ;			//it is a method which prints the throwable along with other details like the line number and class name where the exception occurred
				}
				
				System.out.println("\t#[Data has been written in output.txt]") ;
			}			//end of operation 8
			
			
			
			
			else if( operation == 9 ){				//if user enter operation 9		
				System.out.println("\t[We wish you safety]" + "\n\t[GoodBy]") ;
				
				break ;			//exit from system	
			}
			
			else if( operation == 10 ){										//if user enter operation 10
				
				System.out.print("\n\t-Price of Gasoline in NIS: " + PetrolType.getGasolinePrice() ) ;
					
				System.out.print("\t\t-Price of Diesel in NIS: " + PetrolType.getDieselPrice() + "\n\n" ) ;
					
				System.out.print("\t-Price of Gasoline in Dollar $: " + PetrolType.getGasolinePriceDollar() ) ;
				
				System.out.print("\t\t-Price of Diesel in Dollar $: " + PetrolType.getDieselDollar() + "\n\n") ;
					
				System.out.print("\t-Price of Gasoline in Dinar : " + PetrolType.getGasolinePriceDinar() ) ;
				
				System.out.print("\t\t-Price of Diesel in Dinar : " + PetrolType.getDieselDinar() + "\n\n") ;
				
			}			//end of operation 10
			
			
			else if( operation == 11 ) {			//if user enter operation 11
				vehiclelist.get(1).importantAdvice( ) ;  	//print advice 
			}		//end of operation 11
			
			
			
			
			else if( operation == 12 ) {				//if user enter operation 12
				for( int j = 0 ; j < vehiclelist.size() ; ++j ){		//for loop to print information About Brand
					try {
						if( vehiclelist.get(j) instanceof Car ){							//check if vehicle is car
							System.out.println(((Car)vehiclelist.get(j)).toString() ) ;		//print car inf
							((Car)vehiclelist.get(j)).getAboutBrand_car() ;					//print brand inf
						}
						else if( vehiclelist.get(j) instanceof Minivan ){							//check if vehicle is Minivan
								System.out.println(((Minivan)vehiclelist.get(j)).toString() ) ;		//print Minivan inf
								((Minivan)vehiclelist.get(j)).getAboutBrand_minivan() ;				//print brand inf
						}
						else{																	//check if vehicle is Truck
								System.out.println(((Truck)vehiclelist.get(j)).toString() ) ;		//print Truck inf
								((Truck)vehiclelist.get(j)).getAboutBrand_truck() ;				//print brand inf
						}
					}
				catch(Exception exp) {
					exp.getStackTrace( ) ;
				}
				
								
			}
		}			//end of operation 12
			
			
		else {						//else operation
				System.out.println("\t#[Wrong entry!]") ;
				System.out.println("\t#[Please enter numbers in the MENU]") ;
		}
			
	}	//end while loop for operations
		
		sc.close() ;			//close scanner sc
		
	}		
	
	
	
	public static void printList(ArrayList<Vehicles> veh){		//method printList to print Array List 
		
		 for(int j = 0 ; j < veh.size() ; ++j ) {				//for loop to pass to each companion Array List  and print it out
				System.out.println( veh.get(j).toString( ) ) ;
		 }	//end of loop
	}		// end of method printList
	
	
	
	
	
	
	
	public static String vehicle_out(int j ){			//method for return string contains properties specific to each type of vehicle
		String res = "" ;							//the  strings in which the vehicle's properties are stored

			
			if( vehiclelist.get(j) instanceof Car ){			//check if the vehicle type is a car
				Car car_out = (Car)vehiclelist.get(j) ;		//type casting to car
																//put the car's properties in String res
				res = ", " + "NumberOfSeat: " + car_out.getNumberOfSeats() + ", " + "Movable distance: " + car_out.moveable_distance() + " km" 
						+ ", " + "Cost for 100 Km: " + car_out.costFor100Km() + " NIS\n" ;
			}
		
			else if( vehiclelist.get(j) instanceof Minivan ){		//check if the vehicle type is a Minivan
				Minivan mini_out = (Minivan)vehiclelist.get(j) ;	//type casting to Minivan
																//put the Minivan's properties in String res
				res = ", " + "NumberOfSeat: " + mini_out.getNumberOfSeats() + ", " + "Movable distance: " + mini_out.moveable_distance() + " km" 
					+ ", " + "Cost for 100 Km: " + mini_out.costFor100Km() + " NIS\n" ;
			}
		
			else{												//check if the vehicle type is a Truck
				Truck truck_out = (Truck)vehiclelist.get(j) ;		//type casting to Truck
																//put the Truck's properties in String res
				res = ", " + "NumberOfSeat: " + truck_out.getNumberOfSeats() + ", " + "Movable distance: " + truck_out.moveable_distance() + " km" 
						+ ", " + "Cost for 100 Km: " + truck_out.costFor100Km() + " NIS\n" ;
			}
		
		return res ;		//return properties for vehicle by type

	}					// end of method
	
	
	
	
	private static void menuOptions( ){								//method to display menu options to execute the entered operation
																	//options 1-9 to be selected by the user
		System.out.println("****************************************************************************************************");
		System.out.println("|--------------------------------------------------------------------------------------------------|");
		System.out.println("|                                            ---[Manu]---                                          |");
		System.out.println("|--------------------------------------------------------------------------------------------------|\n");
		System.out.println("\t1.. Read the data about objects from the file “inputdata.txt” and stored them in Arraylist.");			
		System.out.println("\t2.. Set prices of petroleum.");
		System.out.println("\t3.. Print sorted order Vehicles in an ascending order based on costFor100Km.");
		System.out.println("\t4.. Print sorted order Vehicles in an ascending order based on owner name.");
		System.out.println("\t5.. Print sorted order Vehicles in an descending order based on vehicle brand.");
		System.out.println("\t6.. Clone Vehicle without owner.");
		System.out.println("\t7.. Turn air-condition on.");
		System.out.println("\t8.. Write Output on the “output.txt” file after sort them.");
		System.out.println("\t9.. Exit from System.");
		System.out.println("\t10. Give prices of petroleum in Dollor $ and Dinar.");
		System.out.println("\t11. Important Advice!.");
		System.out.println("\t12. Get informations about Brand.\n");
		System.out.println("****************************************************************************************************");
	}								//end of menuOptions method
	
	
	
	
	 private static void read_File( ){							//method for reading from the file

		 try {																//try to be through it to send an exposition if it happened
		FileReader readerf = new FileReader("inputdata.txt") ;				//determine the location of the file from which to read the information			
		Scanner read = new Scanner(readerf) ;
		
		while ( read.hasNext( ) ){													//continues reading as long as there is data in the file
			StringBuilder str_forEdit = new StringBuilder(read.nextLine());
			String information =str_forEdit.toString();								//store the reading we write in String
			String [] split_information = information.split(",") ;					//the definition of it is String type, and we store in it the information that we present at each, which separates the information
			Owner ownerlin = new Owner(split_information[4]) ;						//read the owner's name and use the constructor to store the owner's name
																					//checking the vehicle type so that we can store data according to the type of vehicle

			if (split_information[0].toLowerCase().equals("car")){					//checking the first word in the line to know if it is a car
					vehiclelist.add( new Car ( split_information[1] , split_information[2] , split_information[3] ,		//store the information about the car using the Array of string  and summon the car’s contractor to create a new project
							ownerlin , split_information[5] , Double.parseDouble( split_information[6] ) ,				// store owner name 
							Double.parseDouble( split_information[7] ) , Integer.parseInt( split_information[8] ) )) ;	//using both parseInt and parseDouble to convert from stairs to parseInt and parseDouble in order to fit with the car's contractor
			}
			
			else if(split_information[0].toLowerCase().equals("minivan")){			//checking the first word in the line to know if it is a minivan
				if(split_information[9].toLowerCase().equals("true")){				//check if it's for minivan have Auto Doors
					vehiclelist.add(new Minivan(split_information[1] , split_information[2] , split_information[3] , ownerlin , split_information[5] ,	//store the information in vehiclelist about the minivan using the Array of string  and summon the minivan’s contractor to create a new project
					Double.parseDouble(split_information[6]) , Double.parseDouble(split_information[7]) , Integer.parseInt(split_information[8]) , true)) ;//using both parseInt and parseDouble to convert from stairs to parseInt and parseDouble in order to fit with the minivan’s contractor
				}
				else{																//check if it's for minivan have not Auto Doors
					vehiclelist.add(new Minivan(split_information[1] , split_information[2], split_information[3] ,
							ownerlin , split_information[5] ,Double.parseDouble(split_information[6]) , 				//store the information in vehiclelist about the minivan using the Array of string  and summon the minivan’s contractor to create a new project
							Double.parseDouble(split_information[7]) , Integer.parseInt(split_information[8]),false)) ;	//using both parseInt and parseDouble to convert from stairs to parseInt and parseDouble in order to fit with the minivan’s contractor
				}
			}
			
			else if(split_information[0].toLowerCase().equals("truck")){			//checking the first word in the line to know if it is a truck
				vehiclelist.add( new Truck ( split_information[1] , split_information[2] , split_information[3] , ownerlin ,	//store the information in vehiclelist about the truck using the Array of string  and summon the truck’s contractor to create a new project
						split_information[5] , Double.parseDouble( split_information[6] ) , Double.parseDouble( split_information[7] ) ,
								Integer.parseInt( split_information[8] ) , Integer.parseInt(split_information[9] ) ) ) ;		//using both parseInt and parseDouble to convert from stairs to parseInt and parseDouble in order to fit with the truck’s contractor
			}
		}
	
		read.close( ) ;
	}
		
	catch (Exception exp) {				//handing for exception									
		exp.printStackTrace( ) ;		//it is a method which prints the throwable along with other details like the line number and class name where the exception occurred
	}									//end handing for exception	
}										// end of method read_File

	 
	 
}    //end of class Menu
