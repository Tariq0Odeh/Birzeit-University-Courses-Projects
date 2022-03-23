	AREA Tariq_Odeh,CODE,READONLY						;to assemble a new code with attributes CODE and READONLY
	ENTRY												;an entry point to a program
	
	LDR R0,=0x40000000									;load R0 with address 0x40000000 which is the location where we want to store the string 
STRING	DCB	"Don't let your fear destroy you!",0		;to allocate a byte size memory for each char and initialize the values  	
	ADR R1,STRING										;make R1 point to STRING (load R1 with the addresses of STRING)
	
STORE 													;loop to pass over each char and store it, and when you reach the char 0, then it ends
	LDRB R2,[R1]										;load R2 with the byte from contents of the location pointed to by R1 register
	CMP R2,#0											;compare R2 with zero and set the flags (to check of if we reach zero, it means we have reached the end of the string)
	BEQ FINISH											;if zero flag is set exit from loop (branch to FINISH)
	STR R2,[R0]											;store register R2 into locations pointed to by R0
	ADD R1,R1,#1										;add 1 to R1 and save the result in R1 (To make R1 point to the next character)
	ADD R0,R0,#4										;add 4 to R0 and save the result in R0 (To make R4 have the address that we want to store in it in the next loop)
	B STORE												;loop back	
FINISH													;jump on it when reached the end of the string 
	MOV R7,#0											;load R7 with 0 (to add it in the end of string)
	STR R7,[R0]											;store register R7 into locations pointed to by R0
	
	BL encryption										;Branch and Link (call encryption)
	BL decryption										;Branch and Link (call decryption)
HERE BAL HERE											;infinite loop to keep the microcontroller busy

;---------------------------------------------------------------------------------------;
encryption 												;encryption procedure (takes the text message stored in the memory at specific address and applies the encryption method on every single character and then stores the encrypted message in a different location in the memory)
	LDR R8,=0x40000000									;load R8 with address 0x40000000 which is the location where we want to read the string from it
	LDR R9,=0x400000EC									;load R9 with address 0x400000EC which is the location where we want to store the encrypted character
READ													;loop to pass over each char and make encryption on it
	LDR R2,[R8]											;load R2 with contents of the location pointed to by R8 register
	CMP R2,#0											;compare R2 with zero and set the flags (to check of if we reach zero, it means we have reached the end of the string)
	BEQ DONE											;if zero flag is set exit from loop (branch to DONE)
	MOV R3,R2, ROR #30									;make a encryption by Rotate left ASCII code of character two bits (we use the rotate right (ROR) 32–n bits to do the job of rotate left because there is no rotate left option) and store the result in R3
	STR R3,[R9]											;store register R3 into locations pointed to by R9 (store encryption char)
	ADD R8,R8,#4										;add 4 to R8 and save the result in R8 (To make R8 point to the next character)
	ADD R9,R9,#4										;add 4 to R9 and save the result in R9 (To make R9 have the address that we want to store encryption char in it in the next loop)
	B READ												;loop back					
DONE													;jump on it when reached the end of the string 
	MOV R7,#0											;load R7 with 0 (to add it in the end of encryption string) to know the end of encryption string
	STR R7,[R9]											;store register R7 into locations pointed to by R9
	BX LR												;return to caller
;---------------------------------------------------------------------------------------;
	
decryption 												;decryption procedure (takes the encrypted message and applies the reverse of the encryption process, which is called the key)
	LDR R5,=0x400000EC									;load R5 with address 0x400000EC which is the location where we want to read the encryption string from it
	LDR R6,=0x400001D8									;load R6 with address 0x400001D8 which is the location where we want to store the decryption character
AGAIN													;loop to pass over each char and make decryption on it
	LDR R2,[R5]											;load R2 with contents of the location pointed to by R8 register
	CMP R2,#0											;compare R2 with zero and set the flags (to check of if we reach zero, it means we have reached the end of the encryption string)
	BEQ EXIT											;if zero flag is set exit from loop (branch to EXIT)
	MOV R3,R2, ROR #2									;make a decryption by Rotate Right ASCII code of character two bits (applies the reverse of the encryption process, which is called the key) and store the result in R3
	STR R3,[R6]											;store register R3 into locations pointed to by R6 (store decryption char)
	ADD R5,R5,#4										;add 4 to R5 and save the result in R5 (To make R5 point to the next encryption character)
	ADD R6,R6,#4										;add 4 to R6 and save the result in R6 (To make R6 have the address that we want to store decryption char in it in the next loop)
	B AGAIN												;loop back			
EXIT													;jump on it when reached the end of the encryption string 
	MOV R7,#0											;load R7 with 0 (to add it in the end of decryption string) to know the end of decryption string
	STR R7,[R6]											;store register R7 into locations pointed to by R6
	BX LR												;return to caller
;---------------------------------------------------------------------------------------;

	END													;informs the assembler that it has reached the end of a source file
