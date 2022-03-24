package employees;													//package includes classes

import java.util.*;													//import Date because we want use Array List


	public class Driver {											//defines driver class Driver

		public static void main(String []args) {					// main method definition
	     
		 ArrayList <Employee> employees = new ArrayList<> ();			//define array list and name it employee to Store information about employee in it
			
																	//create several projects from different rows and store them in the class for the employee
		 	Employee em1=new ProductionWorker( "Tariq" , "154-N" , 2012,12,12 , new Address("Sofyan-Street","Palestine","Nablus","103") , 2 , 19 , 300 ) ;
		 	Employee em2=new ProductionWorker( "Yazan" , "150-B" , 2019,7,3 , new Address("Alquds-Street","Palestine","Nablus","110") , 1 , 16.5 , 250 ) ;
		 	Employee em3=new ShiftSupervisor( "Qutauba" , "149-A" , 2007,8,3 , new Address("Howwara-Street","Palestine","Howwara","212") , 3000 , 600 , 600 , 650 ) ;
		 	Employee em4=new ShiftSupervisor( "Maria" , "131-B", 2020,1,5, new Address("New York-Street","USA","New York","4410") ,5000 , 750 , 700 , 550 ) ;
		 	Employee em5=new TeamLeader( "Muath" , "939-Ab" , 2013,3,5 , new Address("Alaersal-Streert","Palestine","Ramallah","794") , 1 , 16 , 250 , 300 , 35 , 55 ) ;
		 	Employee em6=new TeamLeader("morad odeh" , "729-M" , 2011,4,5 , new Address("Howwara-Street","Palestine","Howwara","212") , 2 , 12 , 350 , 420 , 22 , 21 ) ;

		 															//to store the objects employees  in array Lest
		 	employees.add(em1) ;
		 	employees.add(em2) ;
		 	employees.add(em3) ;
		 	employees.add(em4) ;
		 	employees.add(em5) ;
		 	employees.add(em6) ;

		 	listGreaterThenAverage(employees) ;					//call method to print personnel information above avarege
		}

																//method to calculate all employees total salary 
		public static double getAllTotalSalary( ArrayList < Employee > empSalary ) {
			double allSalary = 0.0 ;											//to store total salary
      
			for(int a = 0 ; a < empSalary.size() ; a++) {					
				if(empSalary.get(a) instanceof ProductionWorker) {				//comparison if current object is a instance of ProductionWorker
					
					ProductionWorker prodWorker = (ProductionWorker)empSalary.get(a) ;	//type cast current object
					allSalary += prodWorker.getTotalSalary() ;							//collect all of your salaries ProductionWorker through the method and store them in allSalary
				}																// end condtion											
          
          
           else if (empSalary.get(a) instanceof ShiftSupervisor) {				//otherwise comparison if current object is a instance of ShiftSupervisor
        	   
               ShiftSupervisor shftSup = (ShiftSupervisor)empSalary.get(a) ;	//type cast current object
               allSalary += shftSup.getTotalSalary() ;							//collect all of your salaries ShiftSupervisor through the method and store them in allSalary
           		}  																// end condtion	
				
           else if(empSalary.get(a) instanceof TeamLeader) {					//otherwise comparison if current object is a instance of TeamLeader
        	   
               TeamLeader teamLead = (TeamLeader)empSalary.get(a) ;				//type cast current object
               allSalary += teamLead.getTotalSalary() ;							//collect all of your salaries TeamLeader through the method and store them in allSalary

           		}																// end condtion	
		}
			System.out.println("\n\t**[Total Salary= " + allSalary + " $]\n\n" );
       return allSalary ;														//return All total salary
       
   }
   
		
		
												//a method of printing the salaries of all employees whose salaries are greater than the average salary
		public static void listGreaterThenAverage( ArrayList < Employee > list) {
			double avarge = getAllTotalSalary (list) / list.size() ;			//calling the Methodists to obtain the salaries of all employees
																				//avarge salary account and store it in avarge
			for( int a = 0 ; a < list.size() ; a++) {
				if(list.get(a) instanceof ProductionWorker) {					//checks if this object is an instance of ProductionWorker

          
					ProductionWorker prodWorker = (ProductionWorker)list.get(a) ;   // casting this object to ProductionWorker type
              
					if(prodWorker.getTotalSalary() > avarge) {				 	//checks whether it is greater than the average
						System.out.println( prodWorker ) ;                  	//print the prodWorker employee information

					}
				}
                      
				else if (list.get(a) instanceof ShiftSupervisor) {				//checks if this object is an instance of ShiftSupervisor
       
					ShiftSupervisor shiftSup = (ShiftSupervisor)list.get(a) ;	//casting this object to ShiftSupervisor type
              
					if(shiftSup.getTotalSalary() > avarge) {					//checks whether it is greater than the average
						System.out.println( shiftSup ) ;                 	  	// print the ShiftSupervisor employee information

						}
           			}                      

				else if (list.get(a) instanceof TeamLeader) {					//checks if this object is an instance of TeamLeader
					TeamLeader teamLed = (TeamLeader)list.get(a) ;				// casting this object to TeamLeader type
              
					if(teamLed.getTotalSalary() > avarge) {						//checks whether it is greater than the average
						System.out.println(teamLed) ;                  			// print the TeamLeader employee information

					}
				}					//end of if condition
				
			}						//end of for loop
		
	}								//end of method
  
	
		
}
   
 
  
  
  