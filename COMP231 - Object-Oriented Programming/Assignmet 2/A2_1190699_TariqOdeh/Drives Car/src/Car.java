import java.util.*;      //to import classes related to date and time, 

public class Car{   	//Create Car.java
	
	     private String plateNo ;        //The definition of proparities with their different types of private lano type is before it - in the chart of UML
	     private int yearManufacture ;
	     private int monthManufacture ;
	     private String color ;
	     private double price ;
	     private String manufactureBy ; 
	     private int guranteedDueYear ;
	     private int guranteedDueMonth ;
	 
	
	public Car(){						//No-argument constructor: that creates a car object using the default value.
		Date d = new Date() ;			
		int current_year= d.getYear()+1900 ; //to find date in current year by add 1900 Find it in our time because computer time is calculated at 1970 and in date 1900
   	 	int current_month= d.getMonth()+1 ; //to find date in current month by add 1 Find it in our time because computer time is calculated first month by 0
   	 	
         this.plateNo= "0123-A" ; 				//default value.
         this.yearManufacture= current_year ;
         this.monthManufacture= current_month ;
         this.color= "red " ;
         this.price= 50000.00  ;
         this.manufactureBy= "Mercedes" ;
         this.guranteedDueYear= current_year+((current_month+6)/12) ;
         this.guranteedDueMonth= ((current_month+6)%12) ;         //in default value we will add 6 month ass guranteed
    }
	
	
	public Car( String plateNo , int yearManufacture , int monthManufacture , String color	//constructor that creates a car object using Passing vehicle information from the project in main
		 , double price , String manufactureBy , int guranteedDueYear , int guranteedDueMonth ){
		 
         this.plateNo= plateNo ;
         this.yearManufacture= yearManufacture ;           //using this to adjustment of properties values
         this.monthManufacture= monthManufacture ;
         this.color= color ;
         this.price= price ;
         this.manufactureBy= manufactureBy;
         this.guranteedDueYear= guranteedDueYear ;
         this.guranteedDueMonth= guranteedDueMonth ;
    }

	
	public int getYearManufacture(){				//method To fetch YearManufacture and return it
         return yearManufacture ;
    }

	
    public int getMonthManufacture(){			//method To fetch MonthManufacture and return it
         return monthManufacture ;
    }

    
    public String getColor(){				//method To fetch Color and return it
         return color.toUpperCase() ;
    }

    
    public double getPrice() {				//method To fetch Price and return it
        return price ;
    }

    
    public void setYearManufacture ( int year ){   //method To modify a YearManufacture value 
        this.yearManufacture= year ;
    }

    
    public void setMonthManufacture ( int month ){		//method To modify a MonthManufacture value 
        this.monthManufacture= month ;
    }

    
    public void setColor( String color ){		//method To modify a color value 
        this.color= color ;
    }

    
    public void setGurantee( int month , int year ){		//method To modify a guarantee value
        this.guranteedDueMonth = month ;
        this.guranteedDueYear = year ;
    }
    
    
    public String getCarAge(){						//method must calculate the age of car in years and months and return data as string type
    	 Date date = new Date() ;
    	 int current_year= date.getYear()+1900 ;    // to find current date
    	 int current_month= date.getMonth()+1 ;
    	
    	 int year = current_year - yearManufacture ;      // to find age can in year
         int month = current_month - monthManufacture ;   // to find age can in month
         
         String age = "\n\t-Car age in year= " +year+ " || "+"Car age in month= " +month ;
         return age.toUpperCase() ;         			 //return car age value in string upper case
    }
    
    
    public String printCarInfo(){						//method to print car information and return it by string
       String car_inf = "\t\t*************************\n"+"\t\t\t[Car Info]\n\t\t*************************\n"+
        		"-Plate Number:"+plateNo+ "\t\t-Year of Manufacture: "+yearManufacture+ 
     			"\n-Month of Manufacture:"+monthManufacture+ "\t\t-Color: "+color+
     			"\n-Price:"+price+ "\t\t\t-Manufactured By: "+manufactureBy+
     			"\n-Year of Gurantee:"+guranteedDueYear+ "\t\t-Month of Gurantee: "+guranteedDueMonth ;
     
       return car_inf.toUpperCase() ;
    }
       
    public String getManufactureBy(){     			//method To fetch ManufactureBy and return it
        return manufactureBy.toUpperCase() ;
    }    
    
    public String getCalculateGurantee(){				//method should calculate the reaming years and months for guarantee	
    	Date date= new Date() ;
    	int current_year= date.getYear()+1900 ;
   	 	int current_month= date.getMonth()+1 ;
   	 													//Convert time to months to calculate remaining guarantee time 
   	 	int time_gurantee= ((guranteedDueYear*12) + guranteedDueMonth)-((current_year*12) + current_month) ; 
   	 	int year_gurantee= time_gurantee/12 ;      	//transfer to years and months
   	 	int month_gurantee= time_gurantee%12 ;
   	 	
   	 		if (time_gurantee <=0 ) 					//to check if the guarantee time has expired or not
   	 			return "\t-Reaming years= 0 Reaming month= 0\n";
   	 		else 										//return the time of guarantee ass string
   	 			return "\n\t-Reaming years for gurantee = "+year_gurantee+ " || Reaming monthfor gurantee= "+month_gurantee+"\n" ;
      
    }
}
	