----------------------------------------------------
--                  COURSE PROJECT 	   			  --
---------------------------------------------------- 
-- 					 Tariq Odeh  				  --
-- 					  1190699	 	       		  --
-- 					   sec: 2	 				  --
----------------------------------------------------


---------------Basic gates with delay---------------

----------------------------------------------------
--             INVERTER GATE (1 PORT)             --
----------------------------------------------------
LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL; 

ENTITY NOT_1P IS
	PORT(A: IN STD_LOGIC:= '0';     --1 bit Input
	  	 F: OUT STD_LOGIC:= '0');	--1 bit Output
END ENTITY NOT_1P;

ARCHITECTURE STRUCT_NOT_1P OF NOT_1P IS
    BEGIN
		F <= NOT A AFTER 2 NS;		--2 ns delay
END ARCHITECTURE STRUCT_NOT_1P; 	


----------------------------------------------------
--               NAND GATE (N-BIT)                --
----------------------------------------------------
LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL; 

ENTITY NAND_NBIT IS
	GENERIC ( N : POSITIVE := 2); 		  --N bit Input
	PORT(A: IN STD_LOGIC_VECTOR (N-1 DOWNTO 0):= "00000000"; 	
		 F: OUT STD_LOGIC:= '0');		--1 bit Output
END ENTITY NAND_NBIT;

ARCHITECTURE STRUCT_NAND_NBIT OF NAND_NBIT IS
	SIGNAL TEMP : STD_LOGIC_VECTOR (N-1 DOWNTO 0); 
    BEGIN
		TEMP(0) <= A(0);
	    FLOOP: FOR i IN 1 TO (N-1) GENERATE
	           	TEMP(i) <= TEMP(i-1) AND A(i);		
	    END GENERATE FLOOP; 
	    F <= NOT(TEMP(N-1)) AFTER 5 NS;	--NAND = NOT(AND)
END ARCHITECTURE STRUCT_NAND_NBIT;		--5 ns delay


----------------------------------------------------
--              NAND GATE (2 PORTS)               --
----------------------------------------------------
LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL; 

ENTITY NAND_2P IS
	PORT(A,B: IN STD_LOGIC:= '0';  --2 bit Input
	  	   F: OUT STD_LOGIC:= '0');	--1 bit Output
END ENTITY NAND_2P;

ARCHITECTURE STRUCT_NAND_2P OF NAND_2P IS
    BEGIN
		F <= A NAND B AFTER 5 NS; 		--5 ns delay
	 -- F <= NOT(A AND B) AFTER 5 NS;
END ARCHITECTURE STRUCT_NAND_2P;


----------------------------------------------------
--               NOR GATE (N-BIT)                 --
----------------------------------------------------
LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL; 

ENTITY NOR_NBIT IS
	GENERIC ( N : POSITIVE := 2);  --N bit Input
	PORT(A: IN STD_LOGIC_VECTOR (N-1 DOWNTO 0):= "00000000"; 	
		 F: OUT STD_LOGIC:='0');			--1 bit Output
END ENTITY NOR_NBIT;

ARCHITECTURE STRUCT_NOR_NBIT OF NOR_NBIT IS
	SIGNAL TEMP : STD_LOGIC_VECTOR (N-1 DOWNTO 0); 
    BEGIN
		TEMP(0) <= A(0);
	    FLOOP: FOR i IN 1 TO (N-1) GENERATE
	           	TEMP(i) <= TEMP(i-1) OR A(i);		
	    END GENERATE FLOOP; 
	    F <= NOT(TEMP(N-1)) AFTER 5 NS;	--NOR = NOT(OR)
END ARCHITECTURE STRUCT_NOR_NBIT;	--5 ns delay


----------------------------------------------------
--              NOR GATE (2 PORTS)               --
----------------------------------------------------
LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL; 

ENTITY NOR_2P IS
	PORT(A,B: IN STD_LOGIC:= '0';   --2 bit Input
	  	   F: OUT STD_LOGIC:= '0');	--1 bit Output
END ENTITY NOR_2P;

ARCHITECTURE STRUCT_NOR_2P OF NOR_2P IS
    BEGIN
		F <= A NOR B AFTER 5 NS; 	--5 ns delay
	 -- F <= NOT(A OR B) AFTER 5 NS;
END ARCHITECTURE STRUCT_NOR_2P;


----------------------------------------------------
--               AND GATE (N-BIT)                 --
----------------------------------------------------
LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL; 

ENTITY AND_NBIT IS
	GENERIC ( N : POSITIVE := 2); 	--N bit Input
	PORT(A: IN STD_LOGIC_VECTOR (N-1 DOWNTO 0):= "00000000"; 	
		 F: OUT STD_LOGIC:= '0');		--1 bit Output
END ENTITY AND_NBIT;

ARCHITECTURE STRUCT_AND_NBIT OF AND_NBIT IS
	SIGNAL TEMP : STD_LOGIC_VECTOR (N-1 DOWNTO 0); 
    BEGIN
		TEMP(0) <= A(0);
	    FLOOP: FOR i IN 1 TO (N-1) GENERATE
	           	TEMP(i) <= TEMP(i-1) AND A(i);		
	    END GENERATE FLOOP; 
	    F <= TEMP(N-1) AFTER 7 NS;	--7 ns delay
END ARCHITECTURE STRUCT_AND_NBIT;


----------------------------------------------------
--              AND GATE (2 PORTS)                --
----------------------------------------------------
LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL; 

ENTITY AND_2P IS
	PORT(A,B: IN STD_LOGIC:= '0'; 	--2 bit Input
	  	   F: OUT STD_LOGIC:= '0');	--1 bit Output
END ENTITY AND_2P;

ARCHITECTURE STRUCT_AND_2P OF AND_2P IS
    BEGIN
		F <= A AND B AFTER 7 NS;	--7 ns delay
END ARCHITECTURE STRUCT_AND_2P;


----------------------------------------------------
--                OR GATE (N-BIT)                 --
----------------------------------------------------
LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL; 

ENTITY OR_NBIT IS
	GENERIC ( N : POSITIVE := 2); --N bit Input
	PORT(A: IN STD_LOGIC_VECTOR (N-1 DOWNTO 0):= "00000000"; 	
		 F: OUT STD_LOGIC:= '0');		--1 bit Output
END ENTITY OR_NBIT;

ARCHITECTURE STRUCT_OR_NBIT OF OR_NBIT IS
	SIGNAL TEMP : STD_LOGIC_VECTOR (N-1 DOWNTO 0); 
    BEGIN
		TEMP(0) <= A(0);
	    FLOOP: FOR i IN 1 TO (N-1) GENERATE
	           	TEMP(i) <= TEMP(i-1) OR A(i);		
	    END GENERATE FLOOP; 
	    F <= TEMP(N-1) AFTER 7 NS;	--7 ns delay
END ARCHITECTURE STRUCT_OR_NBIT;
----------------------------------------------------
--               OR GATE (2 PORTS)                --
----------------------------------------------------
LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL; 

ENTITY OR_2P IS
	PORT(A,B: IN STD_LOGIC:= '0';	--2 bit Input
	  	   F: OUT STD_LOGIC:= '0');	--1 bit Output
END ENTITY OR_2P;

ARCHITECTURE STRUCT_OR_2P OF OR_2P IS
    BEGIN
		F <= A OR B AFTER 7 NS;		--7 ns delay
END ARCHITECTURE STRUCT_OR_2P;


----------------------------------------------------
--              XNOR GATE (2 PORTS)               --
----------------------------------------------------
LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL; 

ENTITY XNOR_2P IS
	PORT(A,B: IN STD_LOGIC:= '0';	--2 bit Input
	  	   F: OUT STD_LOGIC:= '0');	--1 bit Output
END ENTITY XNOR_2P;

ARCHITECTURE STRUCT_XNOR_2P OF XNOR_2P IS
    BEGIN
		F <= A XNOR B AFTER 9 NS; 	--9 ns delay
END ARCHITECTURE STRUCT_XNOR_2P;


----------------------------------------------------
--              XOR GATE (2 PORTS)                --
----------------------------------------------------
LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL; 

ENTITY XOR_2P IS
	PORT(A,B: IN STD_LOGIC:= '0'; --2 bit Input
	  	   F: OUT STD_LOGIC:= '0');	--1 bit Output
END ENTITY XOR_2P;

ARCHITECTURE STRUCT_XOR_2P OF XOR_2P IS
    BEGIN
		F <= A XOR B AFTER 12 NS; 	--12 ns delay
END ARCHITECTURE STRUCT_XOR_2P;


----------------------------------------------------
--                  Half Adder                    --
----------------------------------------------------
LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL; 

ENTITY HA IS
	PORT(A,B: IN STD_LOGIC:= '0';			--Input
	  	 Sum,Cout: OUT STD_LOGIC:= '0'); 	--Output
END ENTITY HA;

ARCHITECTURE STRUCT_HA OF HA IS
	SIGNAL X : STD_LOGIC_VECTOR (1 DOWNTO 0):= "00";
    BEGIN
		X <= A & B;
		H1:	ENTITY WORK.XOR_2P(STRUCT_XOR_2P) PORT MAP (A,B,Sum);  		--Sum = A XOR B
		H2:	ENTITY WORK.AND_NBIT(STRUCT_AND_NBIT) GENERIC MAP(2) PORT MAP (X,Cout); 	--Cout = A AND B
END ARCHITECTURE STRUCT_HA;	


----------------------------------------------------
--                  Full Adder                    --
---------------------------------------------------- 
LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL; 

ENTITY FAD IS
	PORT(A,B,Cin: IN STD_LOGIC:= '0';
	  	 Sum,Cout: OUT STD_LOGIC:= '0');
END ENTITY FAD;

ARCHITECTURE STRUCT_FAD OF FAD IS 
	SIGNAL N1,N2,N3,N4,N5,N6,N7: STD_LOGIC := '0';
	BEGIN
					--First way to implement Full Adder Using XOR,AND,OR gates
		--F1: ENTITY WORK.XOR_2P(STRUCT_XOR_2P) PORT MAP(A,B,N1);			--SUM = A XOR B XOR Cin
		--F2: ENTITY WORK.XOR_2P(STRUCT_XOR_2P) PORT MAP(N1,Cin,Sum);	    --Cout = Cin.(A XOR B) + A.B
		--F3: ENTITY WORK.AND_2P(STRUCT_AND_2P) PORT MAP(A,B,N2);
		--F4: ENTITY WORK.AND_2P(STRUCT_AND_2P) PORT MAP(N1,Cin,N3);
		--F5: ENTITY WORK.OR_2P(STRUCT_OR_2P) PORT MAP(N2,N3,Cout);
			
					--Second way to implement Full Adder Using Half Adder	
		--F1: ENTITY WORK.HA(STRUCT_HA) PORT MAP(A,B,N1,N2);
		--F2: ENTITY WORK.HA(STRUCT_HA) PORT MAP(N1,Cin,Sum,N3);
		--F3: ENTITY WORK.OR_2P(STRUCT_OR_2P) PORT MAP(N2,N3,Cout);
		
					--Third way to implement Full Adder Using NAND gate (faster)
		F1: ENTITY WORK.NAND_2P(STRUCT_NAND_2P) PORT MAP(A,B,N1);
		F2: ENTITY WORK.NAND_2P(STRUCT_NAND_2P) PORT MAP(N1,A,N2);
		F3: ENTITY WORK.NAND_2P(STRUCT_NAND_2P) PORT MAP(N1,B,N3);
		F4: ENTITY WORK.NAND_2P(STRUCT_NAND_2P) PORT MAP(N2,N3,N4);
		F5: ENTITY WORK.NAND_2P(STRUCT_NAND_2P) PORT MAP(N4,Cin,N5); 
		F6: ENTITY WORK.NAND_2P(STRUCT_NAND_2P) PORT MAP(N5,N1,Cout);
		F7: ENTITY WORK.NAND_2P(STRUCT_NAND_2P) PORT MAP(N5,Cin,N6);
		F8: ENTITY WORK.NAND_2P(STRUCT_NAND_2P) PORT MAP(N5,N4,N7);
		F9: ENTITY WORK.NAND_2P(STRUCT_NAND_2P) PORT MAP(N6,N7,Sum);					
END ARCHITECTURE STRUCT_FAD;


----------------------------------------------------
--           n-Bit Ripple Adder/subtractor        --
---------------------------------------------------- 
LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL; 

ENTITY NBIT_ADDER IS
	GENERIC ( N : POSITIVE :=8); 
	PORT(A,B: IN STD_LOGIC_VECTOR (N-1 DOWNTO 0):= "00000000";
		 Cin: IN STD_LOGIC :='1';				--Set Cin = 1 to find 2's complemant for B
	  	 Sum: OUT STD_LOGIC_VECTOR(N-1 DOWNTO 0):= "00000000";
		Cout, OV: OUT STD_LOGIC:= '0');	  --OV (overflow)
END ENTITY NBIT_ADDER;

ARCHITECTURE STRUCT_RIPPLE OF NBIT_ADDER IS
	SIGNAL CARRY : STD_LOGIC_VECTOR (N DOWNTO 0):= "000000000";
	SIGNAL X :STD_LOGIC_VECTOR (N-1 DOWNTO 0):= "00000000";	 --to save 2's complemant of B	
    BEGIN
		CARRY(0) <= Cin;    
	    Cout <= CARRY(N);
		R1: ENTITY WORK.XOR_2P(STRUCT_XOR_2P) PORT MAP (CARRY(N),CARRY(N-1),OV);
	    FLOOP: FOR i IN 0 TO (N-1) GENERATE		 --Loop to generate ripple Adder/subtractor
			   R2: ENTITY WORK.XOR_2P(STRUCT_XOR_2P) PORT MAP (B(i),Cin,X(i));  --if Cin = 0 then ripple Adder work, if Cin = 1 ripple subtractor work
			   R3: ENTITY WORK.FAD(STRUCT_FAD) PORT MAP (A(i),X(i),CARRY(i),Sum(i),CARRY(i+1));
	    END GENERATE FLOOP;		
END ARCHITECTURE STRUCT_RIPPLE;


------------------------------------------------------
----                 n-Bit Comparator               --
------------------------------------------------------
LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL; 
										 
ENTITY NBIT_COMPARATOR IS
	GENERIC ( N : POSITIVE :=8); 
	PORT(A,B: IN STD_LOGIC_VECTOR (N-1 DOWNTO 0):= "00000000";	--Input
	  	 F1,F2,F3: OUT STD_LOGIC:= '0');              	--Output: F1(A=B), F2(A>B), and F3 (A<B).
END ENTITY NBIT_COMPARATOR;

ARCHITECTURE STRUCT_NBIT_COMPARATOR  OF NBIT_COMPARATOR IS
	SIGNAL SUM : STD_LOGIC_VECTOR (N-1 DOWNTO 0):= "00000000";
	SIGNAL Cout,X,S : STD_LOGIC:= '0';		 --X to check overflow, S to check if sum equal zero
	SIGNAL NC,NS,NX: STD_LOGIC:= '0';  --NC (not Cout) ,NS (not S(N-1)),NX (not Overflow) 
	SIGNAL FF1,FF2,FF3: STD_LOGIC:= '0';  --to save output of F1,F2,F3 if there is overflow 
	SIGNAL FFF1,FFF2,FFF3: STD_LOGIC:= '0';--to save output of F1,F2,F3 if there is not  overflow
	SIGNAL A1,A2,B1,B2: STD_LOGIC:= '0';    
	
	BEGIN
		P1: ENTITY WORK.NBIT_ADDER(STRUCT_RIPPLE) GENERIC MAP(N) PORT MAP(A,B,'1',SUM,Cout,X);  	--ripple subtractor	(the output of overflow save in X) 
		P3: ENTITY WORK.OR_NBIT(STRUCT_OR_NBIT) GENERIC MAP(N) PORT MAP(SUM,S);					--check if sum equal zero
		P4: ENTITY WORK.NOT_1P(STRUCT_NOT_1P)PORT MAP(Cout,NC);						  			--NC (not Cout)
		P5: ENTITY WORK.NOT_1P(STRUCT_NOT_1P)PORT MAP(SUM(N-1),NS);								--NS (not S(N-1))
		P6: ENTITY WORK.NOT_1P(STRUCT_NOT_1P)PORT MAP(X,NX);									--NX (not Overflow)
			
		X1: ENTITY WORK.NOR_2P(STRUCT_NOR_2P) PORT MAP (Cout,S,A1);	     --find the value of F1,F2,F3 if there is overflow
		X2: ENTITY WORK.AND_2P(STRUCT_AND_2P) PORT MAP (NC,S,A2);
		X3: ENTITY WORK.AND_2P(STRUCT_AND_2P) PORT MAP (X,A1,FF1);
		X4: ENTITY WORK.AND_2P(STRUCT_AND_2P) PORT MAP (X,A2,FF2);
		X5: ENTITY WORK.AND_2P(STRUCT_AND_2P) PORT MAP (X,Cout,FF3);	
			
		Y1: ENTITY WORK.NOR_2P(STRUCT_NOR_2P) PORT MAP (SUM(N-1),S,B1);	 --find the value of F1,F2,F3 if there is not overflow
		Y2: ENTITY WORK.AND_2P(STRUCT_AND_2P) PORT MAP (NS,S,B2);
		Y3: ENTITY WORK.AND_2P(STRUCT_AND_2P) PORT MAP (NX,B1,FFF1);
		Y4: ENTITY WORK.AND_2P(STRUCT_AND_2P) PORT MAP (NX,B2,FFF2);
		Y5: ENTITY WORK.AND_2P(STRUCT_AND_2P) PORT MAP (NX,SUM(N-1),FFF3);	
			
		Z1: ENTITY WORK.OR_2P(STRUCT_OR_2P) PORT MAP(FF1,FFF1,F1);	     --final value of F1,F2,F3
		Z2: ENTITY WORK.OR_2P(STRUCT_OR_2P) PORT MAP(FF2,FFF2,F2);
		Z3: ENTITY WORK.OR_2P(STRUCT_OR_2P) PORT MAP(FF3,FFF3,F3);
			
END ARCHITECTURE STRUCT_NBIT_COMPARATOR;


------------------------------------------------------
----      Stage_1 with ripple adder/subtractor      --
------------------------------------------------------
LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL; 

ENTITY STAGE_1 IS
	PORT(A,B: IN STD_LOGIC_VECTOR (7 DOWNTO 0):= "00000000"; 	--8-bit input
		 F1,F2,F3: OUT STD_LOGIC:='0');   						--Output: F1(A=B), F2(A>B), and F3 (A<B).
END ENTITY STAGE_1;

ARCHITECTURE STRUCT_STAGE_1  OF STAGE_1 IS 
	BEGIN
		S1: ENTITY WORK.NBIT_COMPARATOR(STRUCT_NBIT_COMPARATOR) GENERIC MAP(8) PORT MAP(A,B,F1,F2,F3);
END ARCHITECTURE STRUCT_STAGE_1;

--==================================================================================================================================
--==================================================================================================================================

--------------------------------------------------
--           1-Bit Magnitude comparator         --
--------------------------------------------------

LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL; 		

ENTITY MAGNCOMP_1BIT IS						  
	PORT(A,B: IN STD_LOGIC:= '0';		  --1-Bit input
	     F1,F2,F3: OUT STD_LOGIC:= '0');  --Output: F1(A=B), F2(A>B), and F3 (A<B)
END ENTITY MAGNCOMP_1BIT;

ARCHITECTURE STRUCT_MAGNCOMP_1BIT OF MAGNCOMP_1BIT IS
	SIGNAL NA,NB : STD_LOGIC:= '0';   --NA(not A) , NB(not B)
	BEGIN
		M1: ENTITY WORK.XNOR_2P(STRUCT_XNOR_2P)PORT MAP(A,B,F1);
		M2: ENTITY WORK.NOT_1P(STRUCT_NOT_1P)PORT MAP(B,NB);
		M3: ENTITY WORK.AND_2P(STRUCT_AND_2P)PORT MAP(A,NB,F2);	
		M4: ENTITY WORK.NOT_1P(STRUCT_NOT_1P)PORT MAP(A,NA);
		M5: ENTITY WORK.AND_2P(STRUCT_AND_2P)PORT MAP(NA,B,F3);	
END ARCHITECTURE STRUCT_MAGNCOMP_1BIT;


--------------------------------------------------
--           4-Bit Magnitude comparator         --
--------------------------------------------------
LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL; 		

ENTITY MAGNCOMP_4BIT IS 
	PORT(A,B: IN STD_LOGIC_VECTOR (3 DOWNTO 0):= "0000";	--4-Bit input
	  	 F1,F2,F3: OUT STD_LOGIC:= '0');              	--Output: F1(A=B), F2(A>B), and F3 (A<B).
END ENTITY MAGNCOMP_4BIT;

ARCHITECTURE STRUCT_MAGNCOMP_4BIT OF MAGNCOMP_4BIT IS
	SIGNAL E,G,L :STD_LOGIC_VECTOR (3 DOWNTO 0):= "0000";  --E(equal)A=B, G(greater)A>B, L(less)A<B
	SIGNAL GT,LT :STD_LOGIC_VECTOR (3 DOWNTO 0):= "0000"; 
	SIGNAL LL1,GG1 :STD_LOGIC_VECTOR (1 DOWNTO 0):= "00";	
	SIGNAL LL2,GG2 :STD_LOGIC_VECTOR (2 DOWNTO 0):= "000";
	SIGNAL LL3,GG3 :STD_LOGIC_VECTOR (3 DOWNTO 0):= "0000";
	SIGNAL X1,X2,X3,X4,X5,X6 :STD_LOGIC := '0';
	BEGIN
	    FLOOP1: FOR i IN 0 TO (3) GENERATE     --loop to compare 4 bit by using 1-Bit Magnitude comparator	
			M1: ENTITY WORK.MAGNCOMP_1BIT(STRUCT_MAGNCOMP_1BIT) PORT MAP (A(i),B(i),E(i),G(i),L(i));	
	    END GENERATE FLOOP1;

		LL1 <= L(2)&E(3);  --To find out the possibilities for greater or less
		GG1 <= G(2)&E(3);
		LL2 <= L(1)&E(3)&E(2);
		GG2 <= G(1)&E(3)&E(2);
		LL3 <= L(0)&E(3)&E(2)&E(1);
		GG3 <= G(0)&E(3)&E(2)&E(1);
		
		M2: ENTITY WORK.AND_NBIT(STRUCT_AND_NBIT) GENERIC MAP(2) PORT MAP(LL1,X1);
		M3: ENTITY WORK.AND_NBIT(STRUCT_AND_NBIT) GENERIC MAP(2) PORT MAP(GG1,X2);
		M4: ENTITY WORK.AND_NBIT(STRUCT_AND_NBIT) GENERIC MAP(3) PORT MAP(LL2,X3);
		M5: ENTITY WORK.AND_NBIT(STRUCT_AND_NBIT) GENERIC MAP(3) PORT MAP(GG2,X4);
		M6: ENTITY WORK.AND_NBIT(STRUCT_AND_NBIT) GENERIC MAP(4) PORT MAP(LL3,X5);
		M7: ENTITY WORK.AND_NBIT(STRUCT_AND_NBIT) GENERIC MAP(4) PORT MAP(GG3,X6);
				
		GT <= G(3)&X2&X4&X6;  --to check if greater or less
		LT <= L(3)&X1&X3&X5;
		
		M8: ENTITY WORK.AND_NBIT(STRUCT_AND_NBIT) GENERIC MAP(4) PORT MAP(E,F1);
		M9: ENTITY WORK.OR_NBIT(STRUCT_OR_NBIT) GENERIC MAP(4) PORT MAP(GT,F2);
		M10: ENTITY WORK.OR_NBIT(STRUCT_OR_NBIT) GENERIC MAP(4) PORT MAP(LT,F3);
END ARCHITECTURE STRUCT_MAGNCOMP_4BIT;


--------------------------------------------------
--           8-Bit Magnitude comparator         --
--------------------------------------------------
LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL; 		

ENTITY MAGNCOMP_8BIT IS 
	PORT(A,B: IN STD_LOGIC_VECTOR (7 DOWNTO 0):= "00000000";	--8-Bit input
	  	 F1,F2,F3: OUT STD_LOGIC:= '0');              	--Output: F1(A=B), F2(A>B), and F3 (A<B).
END ENTITY MAGNCOMP_8BIT;

ARCHITECTURE STRUCT_MAGNCOMP_8BIT OF MAGNCOMP_8BIT IS
	SIGNAL T1,T2,T3,T4 :STD_LOGIC_VECTOR (3 DOWNTO 0):= "0000"; --To save A and B
	SIGNAL E1,G1,L1 :STD_LOGIC:= '0';    --To save the output of the first 4-Bit Magnitude comparator 
	SIGNAL E2,G2,L2 :STD_LOGIC:= '0';    --To save the output of the second 4-Bit Magnitude comparator 
	SIGNAL GG,LL :STD_LOGIC:= '0';
	
	BEGIN
		T1 <= A(3)&A(2)&A(1)&A(0);
		T2 <= B(3)&B(2)&B(1)&B(0);
		T3 <= A(7)&A(6)&A(5)&A(4);
		T4 <= B(7)&B(6)&B(5)&B(4);
		
		M1: ENTITY WORK.MAGNCOMP_4BIT(STRUCT_MAGNCOMP_4BIT) PORT MAP (T1,T2,E1,G1,L1);
		M2: ENTITY WORK.MAGNCOMP_4BIT(STRUCT_MAGNCOMP_4BIT) PORT MAP (T3,T4,E2,G2,L2);
		M3: ENTITY WORK.AND_2P(STRUCT_AND_2P)PORT MAP(E2,G1,GG); --To find out the possibilities for greater or less
	    M4: ENTITY WORK.AND_2P(STRUCT_AND_2P)PORT MAP(E2,L1,LL);
		
		M5: ENTITY WORK.AND_2P(STRUCT_AND_2P)PORT MAP(E1,E2,F1);	
		M6: ENTITY WORK.OR_2P(STRUCT_OR_2P)PORT MAP(G2,GG,F2);
		M7: ENTITY WORK.OR_2P(STRUCT_OR_2P)PORT MAP(L2,LL,F3);
END ARCHITECTURE STRUCT_MAGNCOMP_8BIT;


------------------------------------------------------
----      Stage_2 with Magnitude comparator         --
------------------------------------------------------
LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL; 

ENTITY STAGE_2 IS
	PORT(A,B: IN STD_LOGIC_VECTOR (7 DOWNTO 0):= "00000000"; 	--8-bit input
		 F1,F2,F3: OUT STD_LOGIC:='0');   						--Output: F1(A=B), F2(A>B), and F3 (A<B).
END ENTITY STAGE_2;

ARCHITECTURE STRUCT_STAGE_2  OF STAGE_2 IS 
	SIGNAL X, FF2,FF3 : STD_LOGIC:= '0';
	BEGIN
		
		S1: ENTITY WORK.MAGNCOMP_8BIT(STRUCT_MAGNCOMP_8BIT) PORT MAP(A,B,F1,FF2,FF3);
		S2: ENTITY WORK.XOR_2P(STRUCT_XOR_2P)PORT MAP(A(7),B(7),X);	 --To check sign bit
		S3: ENTITY WORK.XOR_2P(STRUCT_XOR_2P)PORT MAP(X,FF2,F2);     --To get a correct answer
		S4: ENTITY WORK.XOR_2P(STRUCT_XOR_2P)PORT MAP(X,FF3,F3);	

END ARCHITECTURE STRUCT_STAGE_2;   

--==================================================================================================================================
--==================================================================================================================================

------------------------------------------------------
----                Test Generator                  --
------------------------------------------------------
LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;
USE IEEE.STD_LOGIC_SIGNED.ALL;
USE IEEE.STD_LOGIC_ARITH.ALL;

ENTITY TEST_GENERATOR IS
	PORT(Clk: IN STD_LOGIC:= '0';		   						--clock input
		 A,B: OUT STD_LOGIC_VECTOR(7 DOWNTO 0):= "00000000"; 	--8 bit output:
	     F1,F2,F3: OUT STD_LOGIC:= '0'); 						--Output: F1(A=B), F2(A>B), and F3 (A<B)
END ENTITY TEST_GENERATOR;

ARCHITECTURE BEH_TEST_GENERATOR OF TEST_GENERATOR IS 
	SIGNAL IN1,IN2: STD_LOGIC_VECTOR(7 DOWNTO 0):= "00000000";
	BEGIN 
		A <= IN1; 	--set the value of IN1 in A to send it to comparator
		B <= IN2; 	--set the value of IN2 in B to send it to comparator
		PROCESS   	 --changes the values of IN1 and IN2 also (A and B) when the clock positive edge
		BEGIN
			FOR i IN -128 TO 127 LOOP  	--to go through all possible values 
				FOR j IN -128 TO 127 LOOP 
							IN1(7 DOWNTO 0) <= CONV_STD_LOGIC_VECTOR(i,8);	--conv from integer to STD_LOGIC 
							IN2(7 DOWNTO 0) <= CONV_STD_LOGIC_VECTOR(j,8);	--conv from integer to STD_LOGIC  
							WAIT UNTIL rising_edge(Clk); 
				END LOOP; 
			END LOOP;
			WAIT;
		END PROCESS;
			
		PROCESS (IN1,IN2) 	  --implement the system using behavioural logic
			BEGIN
				IF(IN1 > IN2) THEN
					F1 <= '0' ;
					F2 <= '1' ;
					F3 <= '0' ;
				ELSIF (IN1 < IN2) THEN
					F1 <= '0' ;
					F2 <= '0' ;
					F3 <= '1' ;
				ELSE
					F1 <= '1' ;
					F2 <= '0' ;
					F3 <= '0' ;
				END IF;
		END PROCESS;
END ARCHITECTURE BEH_TEST_GENERATOR; 


--------------------------------------------------
--                    Analyze                   --
--------------------------------------------------
LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL; 
USE IEEE.STD_LOGIC_ARITH.ALL;

ENTITY ANALYZE_RESULT IS   
	PORT(SF1,SF2,SF3: IN STD_LOGIC:='0';   --input the result of system
		 CF1,CF2,CF3: IN STD_LOGIC:='0';   --input correct result
		 Clk: IN STD_LOGIC:='0');	       --clock input
END ENTITY ANALYZE_RESULT;

ARCHITECTURE ANALYZE OF ANALYZE_RESULT IS
	BEGIN 
		PROCESS	     		--to ensure that the system output is equal to the theoretical output
			BEGIN
				assert ((SF1 = CF1) AND (SF2 = CF2) AND (SF3 = CF3)) 	  --if the system output is not equal to the theoretical output print an error
				report "The obtained results do not accord with the theoretical result !!" 
				severity ERROR;
				WAIT UNTIL rising_edge(Clk);
		END PROCESS;
END ARCHITECTURE  ANALYZE;


--------------------------------------------------
--              Verification circuit            --
--------------------------------------------------
LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL; 		
USE IEEE.STD_LOGIC_ARITH.ALL;

ENTITY VERIFICATION IS
END ENTITY VERIFICATION;

--------------------------------------------------
--              Verification Stage_1            --
--------------------------------------------------
ARCHITECTURE VERIF_STAGE_1 OF VERIFICATION IS
 	SIGNAL A,B: STD_LOGIC_VECTOR(7 DOWNTO 0):="00000000";
	SIGNAL SF1,SF2,SF3: STD_LOGIC:='0';   --input the result of system
	SIGNAL CF1,CF2,CF3: STD_LOGIC:='0';   --input correct result
	SIGNAL Clk: STD_LOGIC:='0';
	
	
	BEGIN 									   
		Clk <= NOT CLK AFTER 133 NS;
		V1: ENTITY WORK.TEST_GENERATOR(BEH_TEST_GENERATOR) PORT MAP(Clk , A , B , CF1 , CF2 , CF3);	
		V2: ENTITY WORK.STAGE_1(STRUCT_STAGE_1) PORT MAP(A , B , SF1 , SF2 , SF3); 	
		V3: ENTITY WORK.ANALYZE_RESULT(ANALYZE) PORT MAP(SF1 , SF2 , SF3 , CF1 , CF2 , CF3 , Clk);		
END ARCHITECTURE VERIF_STAGE_1;														 


--------------------------------------------------
--              Verification Stage_2            --
--------------------------------------------------
ARCHITECTURE VERIF_STAGE_2 OF VERIFICATION IS
 	SIGNAL A,B: STD_LOGIC_VECTOR(7 DOWNTO 0):="00000000";
	SIGNAL SF1,SF2,SF3: STD_LOGIC:='0';   --input the result of system
	SIGNAL CF1,CF2,CF3: STD_LOGIC:='0';   --input correct result
	SIGNAL Clk: STD_LOGIC:='0';
	
	
	BEGIN 									   
		Clk <= NOT CLK AFTER 25 NS;
		V1: ENTITY WORK.TEST_GENERATOR(BEH_TEST_GENERATOR) PORT MAP(Clk , A , B , CF1 , CF2 , CF3);	
		V2: ENTITY WORK.STAGE_2(STRUCT_STAGE_2) PORT MAP(A , B , SF1 , SF2 , SF3); 	
		V3: ENTITY WORK.ANALYZE_RESULT(ANALYZE) PORT MAP(SF1 , SF2 , SF3 , CF1 , CF2 , CF3 , Clk);		
END ARCHITECTURE VERIF_STAGE_2;		

--|================================================================================================================|	
--|======         D-flip-flop (1-bit)   //   D-flip-flop (n-bit)   //   n-Bit Carry Lookahead     	 		 ======|
--|================================================================================================================|

----------------------------------------------------
--               D-flip-flop (1-bit)              --
---------------------------------------------------- 
--LIBRARY IEEE;
--USE IEEE.STD_LOGIC_1164.ALL; 
--
--ENTITY DFF_1B IS
--	PORT(D,Clk,Reset: IN STD_LOGIC:= '0'; 		--Input 
--	  	        Q,NQ: OUT STD_LOGIC:= '0');		--Output
--END ENTITY DFF_1B;
--
--ARCHITECTURE STRUCT_DFF_1B OF DFF_1B IS
--    BEGIN
--		PROCESS(Reset,Clk)
--		BEGIN
--			IF (Reset = '1') THEN				--Reset the dff when reset is 1      
--				Q <= '0';
--				NQ <= '0';
--			ELSE 
--				IF (rising_edge(Clk)) THEN     --On positive edge
--					Q <= D ;
--					NQ <= NOT D ;
--				END IF;
--			END IF;
--		END PROCESS;	
--END ARCHITECTURE STRUCT_DFF_1B;


----------------------------------------------------
--           n-Bit (flip-flops/registers)         --
---------------------------------------------------- 
--LIBRARY IEEE;
--USE IEEE.STD_LOGIC_1164.ALL;
--
--ENTITY NBIT_REGISTERS IS
--	GENERIC (N : POSITIVE := 16); 
--	PORT (D: IN STD_LOGIC_vector(N-1 DOWNTO 0):= "00000000";		--Input 		
--	      Clk,Reset: IN STD_LOGIC:= '0';							--Input 
--	  	  Q,NQ : OUT STD_LOGIC_vector(N-1 DOWNTO 0):= "00000000");	--Output      
--END ENTITY NBIT_REGISTERS;
--
--
--ARCHITECTURE STRUCT_NBIT_REGISTERS OF NBIT_REGISTERS IS
--	BEGIN
--		FLOOP : FOR i IN 0 TO (N-1) GENERATE 			--Loop to generate n-bit dff from 1-bit dff
--			G_DFF : ENTITY WORK.DFF_1B(STRUCT_DFF_1B) PORT MAP(D(i),Clk,Reset,Q(i),NQ(i));
--		END GENERATE FLOOP; 
--END ARCHITECTURE STRUCT_NBIT_REGISTERS;


------------------------------------------------------
----              n-Bit Carry Lookahead             --
------------------------------------------------------ 
--LIBRARY IEEE;
--USE IEEE.STD_LOGIC_1164.ALL;
--
--ENTITY LOOK_AHEAD IS           --look ahead adder/subtractor faster than ripple adder/subtractor
--	GENERIC (N : POSITIVE := 8); 
--    PORT (A,B: IN STD_LOGIC_VECTOR(N-1 DOWNTO 0):= "00000000";
--          Cin: IN   STD_LOGIC:='0';
--          Sum: OUT  STD_LOGIC_VECTOR(N-1 DOWNTO 0):= "00000000";
--         Cout: OUT  STD_LOGIC:= '0');
--END ENTITY LOOK_AHEAD;
--
--ARCHITECTURE STRUCT_CARRY_LOOK_AHEAD OF LOOK_AHEAD IS
--	SIGNAL S,G,P: STD_LOGIC_VECTOR(N-1 DOWNTO 0):= "00000000";
--	SIGNAL C: STD_LOGIC_VECTOR(N-1 DOWNTO 1):= "00000000";
--	BEGIN
--	    PROCESS (G,P,C)
--	    BEGIN
--	    	C(1) <= G(0) OR (P(0) AND Cin);
--	        inst: FOR i IN 1 TO N-2 LOOP
--	              C(i+1) <= G(i) OR (P(i) AND C(i));
--	              END LOOP;
--	    Cout <= G(N-1) OR (P(N-1) AND C(N-1));
--	    END PROCESS;
--		
--		FLOOP1: FOR i IN 0 TO (N-1) GENERATE  
--				   G1: ENTITY WORK.XOR_2P(STRUCT_XOR_2P) PORT MAP(A(i),B(i),S(i));
--		END GENERATE FLOOP1;		
--	
--	   	FLOOP2: FOR i IN 0 TO (N-1) GENERATE  
--				   G2: ENTITY WORK.AND_2P(STRUCT_AND_2P) PORT MAP(A(i),B(i),G(i));
--		END GENERATE FLOOP2;
--		
--		FLOOP3: FOR i IN 0 TO (N-1) GENERATE  
--				   G3: ENTITY WORK.OR_2P(STRUCT_OR_2P) PORT MAP(A(i),B(i),P(i));
--		END GENERATE FLOOP3;
--		
--		G4: ENTITY WORK.XOR_2P(STRUCT_XOR_2P) PORT MAP(S(0),Cin,Sum(0));
--	    FLOOP4: FOR i IN 1 TO (N-1) GENERATE  
--				   G5: ENTITY WORK.XOR_2P(STRUCT_XOR_2P) PORT MAP(S(i),C(i),Sum(i));
--		END GENERATE FLOOP4;
--		
--END ARCHITECTURE STRUCT_CARRY_LOOK_AHEAD; 




