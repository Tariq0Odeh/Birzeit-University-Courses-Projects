drop database law_office;
Create database Law_Office;
use Law_Office;

######################################################
CREATE TABLE C_Date(
	Date_id int  PRIMARY KEY NOT NULL, 
    Date_of_session date,
    D_time varchar(32)
    #PRIMARY KEY (Date_id)
);
insert into C_Date (Date_id, Date_of_session, D_time) values 
	(1, "2022-08-15" , " 1:00 pm"),
	(2, "2022-09-25" , " 11:30 am "),
	(3, "2022-02-21" , " 12:30 PM "),
    (4, "2022-11-30" , " 1:00 pm"),
    (5, "2022-07-21" , " 1:00 pm"),
    (6, "2022-03-04" , " 1:00 pm"),
    (7, "2022-04-05" , " 1:00 pm"),
    (8, "2022-06-15" , " 1:00 pm"),
	(9, "2022-12-02" , " 11:00 am "),
    (10, "2022-01-15" , " 1:00 pm"),
	(11, "2022-04-02" , " 11:30 am "),
	(12, "2022-09-21" , " 12:30 PM "),
    (13, "2022-10-30" , " 1:00 pm"),
    (14, "2022-07-20" , " 1:00 pm"),
    (15, "2022-03-17" , " 1:00 pm"),
    (16, "2022-04-14" , " 1:00 pm"),
    (17, "2022-06-15" , " 1:00 pm"),
	(18, "2022-11-02" , " 11:00 am ");

######################################################
CREATE TABLE Plaintiff(
	P_id int NOT NULL, 
    P_name varchar(32),
    P_address varchar(32),
    P_phone_number varchar(32),
    PRIMARY KEY (P_id)
);
 
 insert into Plaintiff (P_id, P_name,P_address, P_phone_number) values 
	(300, "Qusay Abu Omar" , "Tulkarem" , "0568753159"),
    (301, "Omar Ahmad" , "Qalqilya" , "056312005"),
    (302, "Naseem sammara" , "Nablus" , "0598524522"),
    (303, "Qays Ali" , "Tubas" , "05653156155"),
    (304, "Qusay Jawad" , "Tubas" , "0568753889"),
    (305, "raji Tawfeeq" , "Ramallh" , "056879999"),
    (306, "Youins Fadi" , "Nablus" , "0561236159"),
    (307, "Amera Abdullah" , "Qalqilya" , "05954159"),
    (308, "Lana Omar" , "Jenin" , "0568255159");

######################################################
CREATE TABLE Lawyer( 
	ID_number int NOT NULL, 
    Lawyer_Name varchar(32), 
    Address varchar(50), 
	Phone_number varchar(50), 
    Email_registered varchar(60), 
	L_Password varchar(32), 
    Gender varchar(20), 
    manager_ssn int,
	PRIMARY KEY (ID_number)
); 

insert into Lawyer (ID_number, Lawyer_Name, Address, Phone_number, Email_registered, L_Password, Gender, manager_ssn) values 
	(100, "Ali Saeed" , "Beit Imreen - Nablus" , "0599979806" , "aliali23@gmail.com" , "admin" , "male" , 101),
    (101, "Qays Safa" , "Dail Alghsoon - Tulkarem" , "0597608739" , "qayssafa4@gmail.com" , "1234" , "male" , 101),
    (102, "Tariq Odeh" , " Huwara - Nablus" , "0599979806" , "odehtariq@gmail.com" , "0000" , "male" , 101),
    (103, "Mahmoud Samara" , "Birzeit - Ramallh" , "0599979806" , "m.s103@gmail.com" , "root1234" , "male" , 101),
    (104, "Yousef Ahamd" , "Dura - Hebron" , "0599979806" , "yousef11@gmail.com" , "admin" , "female" , 101),
    (105, "Ahmad Ali" , " Nablus" , "0599979806" , "Ahmadali@gmail.com" , "admin" , "male" , 101),
	(106, "Heba Odeh" , "Tubas" , "0592142876" , "happylife12@icloud.com" , "rr1234" , "female" , 101); 
    
######################################################
create TABLE Payement( 
	Payement_ID int NOT NULL, 
    Currency varchar(32),
    Payment_Method varchar(50),
    Amount double,
    PRIMARY KEY (Payement_ID)
); 

insert into Payement (Payement_ID, Currency, Payment_Method,Amount) values
	(10 , "Dolar $ " , "Cash",2550) ,
	(11 , "Shekel" , "Cheques",1500),
	(12 , "Shekel" , "Cash",1550),
    (13 , "Dolar $ " , "Cash",2500) ,
	(14 , "Shekel" , "Cheques",11000),
	(15 , "Shekel" , "Cash",1800),
    (16 , "Dolar $ " , "Cash",2500) ,
	(17 , "Shekel" , "Cheques",1500),
	(18 , "Shekel" , "Cash",1000),
    (19 , "Dolar $ " , "Cash",2550) ,
	(20 , "Shekel" , "Cheques",15000),
	(21 , "Shekel" , "Cash",12000),
    (22 , "Dolar $" , "Cheques",1100),
    (23 , "Shekel" , "Cash",7000),
    (24 , "Shekel" , "Cheques",1880),
    (25 , "Shekel" , "Cash",1800),
    (26 , "Shekel" , "Cash",15000),
    (27 , "Dolar $" , "Cash",3000);
    
######################################################
CREATE TABLE Defendent( 
	ID_number int NOT NULL, 
    Defendent_Name varchar(32), 
    Address varchar(50), 
	Phone_number varchar(50), 
    PRIMARY KEY (ID_number)
);  

insert into Defendent (ID_number, Defendent_Name, Address, Phone_number) values 
	(200, "Qays AHmad" , "Burqa - Nablus" , "0569874522"),
	(201, "Huda Dar Ali" , "Tulkarm" , "055412041"),
    (202, "Rayan Ghanem" , "Nablus" , "056545159"),
    (203, "Ahmad AHmad" , " Nablus" , "059994522"),
	(204, "Ali Dar Ali" , "Tulkarm" , "05616841"),
    (205, "Akram ishtya" , "Nablus" , "0591461159"),
	(206, "Ramiz Faqeeh" , "Hebron" , "0561611532"),
    (207, "Saleh Arja" , "Jenin" , "05616102"),
    (208, "Ali Siaj" , "Ramallah" , "059511512");
 
######################################################
CREATE TABLE Cases(
	Case_id int NOT NULL,
	case_number_in_the_court varchar(32),
	PRIMARY KEY (Case_id) 
); 

insert into Cases (Case_id, case_number_in_the_court) values 
	(1000, "11AB"),
	(1001, "12AA"),
	(1002, "12CB"),
    (1003, "13AB"),
	(1004, "12AA"),
	(1005, "12DB"),
    (1006, "11AD"),
	(1007, "12CA"),
	(1008, "12CB"),
	(1009, "112A"),
    (1010, "11AC"),
	(1011, "12AA"),
	(1012, "12CB"),
    (1013, "11AB"),
	(1014, "12AA"),
	(1015, "12CB"),
    (1016, "13AB"),
	(1017, "12AA");
 
######################################################
CREATE TABLE Rights_cases(
	Case_id int NOT NULL,
    file_state varchar(32),
	court_type varchar(32),
	case_description varchar(100),
	PRIMARY KEY (Case_id),
	FOREIGN KEY (Case_id) REFERENCES  Cases (Case_id) ON DELETE CASCADE ON UPDATE CASCADE);

insert into Rights_cases (Case_id, file_state, court_type, case_description) values 
	(1000, "judged","Magistrate's Court" , "legacy issue"),
    (1009, "awaiting verdict","First Instance Court" , "check case"),
    (1017, "Delayed","Magistrate's Court" , "legacy issue"),
    (1011, "is being reviewed","Magistrate's Court" , "debt payment case"),
    (1005, "Delayed","First Instance Court" , "check case");

######################################################
CREATE TABLE Penalty_cases(
	Case_id int NOT NULL,
	penalty_type varchar(32),
	court_type varchar(32),
	case_description varchar(100),
	PRIMARY KEY (Case_id),
	FOREIGN KEY (Case_id) REFERENCES Cases (Case_id) ON DELETE CASCADE ON UPDATE CASCADE 
);
insert into Penalty_cases (Case_id, penalty_type, court_type, case_description) values 
	(1001, "property crimes","Magistrate's Court" , "premeditated murder case"),
    (1010, "Financial Crimes","Magistrate's Court" , "Waiting for the judge's ruling"),
    (1003, "Financial Crimes","Magistrate's Court" , "Waiting for the judge's ruling"),
    (1015, "Unfinished Crimes","Magistrate's Court" , "Waiting for the judge's ruling"),
    (1012, "Unfinished Crimes","Magistrate's Court" , "Waiting for the judge's ruling"),
    (1004, "Financial Crimes","Magistrate's Court" , "Waiting for the judge's ruling");

######################################################
CREATE TABLE Resumption_cases(
	Case_id int NOT NULL,
	case_description varchar(100) ,
	PRIMARY KEY (Case_id) ,
	FOREIGN KEY (Case_id) REFERENCES Cases (Case_id) ON DELETE CASCADE ON UPDATE CASCADE
);

insert into Resumption_cases (Case_id, case_description) values 
	(1002, "Judgment reconsideration"),
    (1013, "Judgment reconsideration"),
    (1016, "Judgment reconsideration"),
    (1008, "Judgment reconsideration");

######################################################
CREATE TABLE Execution_cases(
  Case_id int NOT NULL,
  case_description varchar(100),
  PRIMARY KEY (Case_id),
  FOREIGN KEY (Case_id) REFERENCES Cases (Case_id) ON DELETE CASCADE ON UPDATE CASCADE 
);     

insert into Execution_cases (Case_id, case_description) values 
	(1004, "Execution of the executive bond"),
    (1006, "Execution of the executive bond"),
    (1007, "Execution of the executive bond");  


######################################################
CREATE TABLE Notification(
	Notification_id int NOT NULL, 
    Notification_date date,
    Notification_method varchar(32),
    Case_id int NOT NULL,
    PRIMARY KEY (Notification_id),
    FOREIGN KEY (Case_id) REFERENCES Cases (Case_id) ON DELETE CASCADE ON UPDATE CASCADE
);



insert into Notification (Notification_id, Notification_date, Notification_method, Case_id) values 
	(101, "2022-08-5","Report a first-degree relative" , 1001),
	(102, "2022-09-01","direct notification" , 1002),
    (103, "2022-02-15","Report a first-degree relative" , 1003),
	(104, "2022-11-25","direct notification" , 1004),
    (105, "2022-07-11","Report a first-degree relative" , 1005),
	(106, "2022-02-25","direct notification" , 1006),
    (107, "2022-03-05","Report a first-degree relative" , 1007),
	(108, "2022-05-25","direct notification" , 1008),
    (109, "2022-11-05","Report a first-degree relative" , 1009),
	(110, "2021-12-25","direct notification" , 1010);
 
######################################################
CREATE TABLE Plaintiff2Cases2lawyer(
	P_id int NOT NULL, 
    Case_id int NOT NULL,
    Lawyer_ID int NOT NULL,
    PRIMARY KEY (P_id, Case_id,Lawyer_ID),
	FOREIGN KEY (P_id) REFERENCES Plaintiff (P_id) ON DELETE CASCADE ON UPDATE CASCADE,
	FOREIGN KEY (Case_id) REFERENCES Cases (Case_id) ON DELETE CASCADE ON UPDATE CASCADE,
    FOREIGN KEY (Lawyer_ID) REFERENCES Lawyer (ID_number) ON DELETE CASCADE ON UPDATE CASCADE
);

insert into Plaintiff2Cases2lawyer (P_id, Case_id,Lawyer_ID) values 
	(300, 1000,106),
    (301, 1017,100),
    (302, 1002,105),
    (303, 1006,103),
    (304, 1009,100),
    (305, 1013,104),
    (306, 1005,104),
    (307, 1011,102),
	(308 ,1016,102);

######################################################
CREATE TABLE Date2Cases(
	Date_id int not null, 
    Case_id int not null,
    PRIMARY KEY (Date_id, Case_id),
	FOREIGN KEY (Date_id) REFERENCES C_Date (Date_id) ON DELETE CASCADE ON UPDATE CASCADE,
	FOREIGN KEY (Case_id) REFERENCES Cases (Case_id) ON DELETE CASCADE ON UPDATE CASCADE
); 

insert into Date2Cases (Date_id, Case_id) values 
	(1, 1000),
	(2 ,1001),
	(3 ,1002),
    (4, 1003),
	(5 ,1004),
	(6 ,1005),
    (7, 1006),
	(8 ,1007),
	(9 ,1008),
    (10, 1009),
	(11 ,1010),
	(12 ,1011),
    (13 ,1012),
	(14 ,1013),
    (15, 1014),
	(16 ,1015),
	(17 ,1016),
	(18 ,1017);

######################################################                       
CREATE TABLE Defend(
	Defendent_ID_number int NOT NULL, 
    Case_ID int NOT NULL, 
    Lawyer_ID int NOT NULL,
    PRIMARY KEY (Defendent_ID_number, Case_ID, Lawyer_ID),
	FOREIGN KEY (Defendent_ID_number) REFERENCES Defendent (ID_number) ON DELETE CASCADE ON UPDATE CASCADE,
    FOREIGN KEY (Case_id) REFERENCES Cases (Case_id) ON DELETE CASCADE ON UPDATE CASCADE,
    FOREIGN KEY (Lawyer_ID) REFERENCES Lawyer (ID_number) ON DELETE CASCADE ON UPDATE CASCADE
);

insert into Defend (Defendent_ID_number, Case_id, Lawyer_ID) values 
	(200, 1001, 100),
    (201, 1003, 101),
    (202, 1004, 106),
    (203, 1007, 106),
    (204, 1008, 104),
    (205, 1010, 103),
    (206, 1012, 105),
    (207, 1014, 105),
	(208 ,1015, 102);
######################################################

CREATE TABLE Payement2Cases2lawyer(
	P_id int NOT NULL, 
    Case_id int NOT NULL,
    Lawyer_ID int NOT NULL,
    PRIMARY KEY (P_id, Case_id,Lawyer_ID),
	FOREIGN KEY (P_id) REFERENCES Payement (Payement_ID) ON DELETE CASCADE ON UPDATE CASCADE,
	FOREIGN KEY (Case_id) REFERENCES Cases (Case_id) ON DELETE CASCADE ON UPDATE CASCADE,
    FOREIGN KEY (Lawyer_ID) REFERENCES Lawyer (ID_number) ON DELETE CASCADE ON UPDATE CASCADE
);

insert into Payement2Cases2lawyer (P_id, Case_id,Lawyer_ID) values 
	(10, 1000,106),
    (11, 1001,100),
    (12, 1002,105),
    (13, 1003,101),
    (14, 1004,106),
    (15, 1005,104),
    (16, 1006,103),
    (17, 1007,106),
    (18, 1008,104),
    (19, 1009,100),
    (20, 1010,103),
    (21, 1011,102),
    (22, 1012,105),
    (23, 1013,104),
    (24, 1014,105),
    (25, 1015,102),
    (26, 1016,102),
	(27 ,1017,100);
    

#Main REPORTS:
    
select P_name,Lawyer_Name,Date_of_session,D_time,case_number_in_the_court
from C_Date,Date2Cases,Cases,Lawyer, Plaintiff2Cases2lawyer,Plaintiff
where Date2Cases.Case_id = Cases.Case_id and Date2Cases.Date_id = C_Date.Date_id and Plaintiff2Cases2lawyer.P_id = Plaintiff.P_id and 
Plaintiff2Cases2lawyer.Lawyer_ID = Lawyer.ID_number and Plaintiff2Cases2lawyer.Case_ID = Cases.Case_id;

select  Defendent_Name,Lawyer_Name,Date_of_session,D_time,case_number_in_the_court
from C_Date,Date2Cases,Cases,Lawyer,Defendent,Defend
where Date2Cases.Case_id = Cases.Case_id and Date2Cases.Date_id = C_Date.Date_id and Defend.Lawyer_ID = Lawyer.ID_number and
 Defend.Case_ID = Cases.Case_id and Defend.Defendent_ID_number = Defendent.ID_number;
 
######################################################

select Lawyer_Name, count(*) as Total_number_of_cases_with_Defendents from 
Cases,Lawyer,Defendent,Defend
where Defend.Lawyer_ID = Lawyer.ID_number and Defend.Case_ID = Cases.Case_id and Defend.Defendent_ID_number = Defendent.ID_number
GROUP BY Lawyer.ID_number;


select Lawyer_Name, count(*) as Total_number_of_cases_with_Plaintiffs from 
Cases,Lawyer,Plaintiff,Plaintiff2Cases2lawyer
where Plaintiff2Cases2lawyer.P_id = Plaintiff.P_id and Plaintiff2Cases2lawyer.Lawyer_ID = Lawyer.ID_number and Plaintiff2Cases2lawyer.Case_ID = Cases.Case_id
GROUP BY Lawyer.ID_number;
######################################################

##DONE BY:   MAHMOUD SAMARA , TARIQ ODEH , QAYS SAFA