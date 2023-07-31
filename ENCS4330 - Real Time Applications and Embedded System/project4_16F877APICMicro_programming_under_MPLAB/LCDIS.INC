;--------------------------------------------------------------
; 	LCDIS.INC		MPB	19-12-05
;
;	Include file to operate 16x2 LCD display
; 	Uses GPR 70 - 75
; 	
;	Final version
;--------------------------------------------------------------

Timer1	EQU	70		; 1ms count register
TimerX	EQU	71		; Xms count register
Var	EQU	72		; Output variable
Point	EQU	73		; Program table pointer
Select	EQU	74		; Used to set or clear RS bit
OutCod	EQU	75		; Temp store for output code


E	EQU	5		; Enable display input
RS	EQU	4		; Register select output bit

;--------------------------------------------------------------
;	1ms delay with 1us cycle time (1000 cycles)
;--------------------------------------------------------------
onems	MOVLW	D'249'		; Count for 1ms delay 
	MOVWF	Timer1		; Load count
loop1	NOP			; Pad for 4 cycle loop
	DECFSZ	Timer1		; Count
	GOTO	loop1		; until Z
	RETURN			; and finish

;--------------------------------------------------------------
;	Delay Xms
;	Receives count in W, uses Onems
;--------------------------------------------------------------
xms	MOVWF	TimerX		; Count for X ms
loopX	CALL	onems		; Delay 1ms
	DECFSZ	TimerX		; Repeat X times 
	GOTO	loopX		; until Z
	RETURN			; and finish

;--------------------------------------------------------------
;	Generate data/command clock siganl E
;--------------------------------------------------------------
pulseE	BSF	PORTA,E		; Set E high
	CALL	onems		; Delay 1ms
	CALL	onems		; Delay 1ms
	CALL	onems		; Delay 1ms
	CALL	onems		; Delay 1ms
	CALL	onems		; Delay 1ms

	BCF	PORTA,E		; Reset E low

	CALL	onems		; Delay 1ms
	CALL	onems		; Delay 1ms
	CALL	onems		; Delay 1ms
	CALL	onems		; Delay 1ms
	CALL	onems		; Delay 1ms
	RETURN			; done

;--------------------------------------------------------------
;	Send a command byte in two nibbles from RB4 - RB7
;	Receives command in W, uses PulseE and Onems
;--------------------------------------------------------------
send	MOVWF	OutCod		; Store output code
	ANDLW	0xF0		; Clear low nybble
	MOVWF Var
	SWAPF Var
	MOVF Var, w
	MOVWF	PORTA		; Output high nybble


	BTFSC	Select,RS	; Test RS bit
	BSF	PORTA,RS	; and set for data

	CALL	pulseE		; and clock display register
	CALL	onems		; wait 1ms for display

	MOVF	OutCod,W	; Retrieve output code
	ANDLW	0x0F		; Clear low nybble
	CLRF PORTA
	MOVWF	PORTA		; Output low nybble

	BTFSC	Select,RS	; Test RS bit
	BSF	PORTA,RS	; and set for data

	CALL	pulseE		; and clock display register
	CALL	onems		; wait 1ms for display
	RETURN			; done

;--------------------------------------------------------------
;	Initialise the display
;	Uses Send
;--------------------------------------------------------------
inid	MOVLW	D'100'		; Load count for 100ms delay
	CALL	xms		; and wait for display start
	MOVLW	0x0F	; Mask for select code
	MOVWF	Select		; High nybble not masked


	;BANKSEL TRISA
	;CLRF TRISA
	
	BANKSEL PORTA
	CLRF PORTA
	; to convert to digital outputs
	BANKSEL ADCON1
	MOVLW 0x06
	MOVWF ADCON1

	BANKSEL PORTA

	;D5 = 0, D4 = 0, OF LCD SO PORTA0 = 1, PORTA1 = 1
	MOVLW	0x03		; Load initial nibble
	MOVWF	PORTA		; and output it to display
	CALL	pulseE		; Latch initial code
	MOVLW	D'5'		; Set delay 5ms
	CALL	xms		; and wait
	CALL	pulseE		; Latch initial code again
	CALL	onems		; Wait 1ms
	CALL	pulseE		; Latch initial code again
	BCF	PORTA,0		; Set 4-bit mode
	CALL	pulseE		; Latch it
	
	MOVLW	0x28		; Set 4-bit mode, 2 lines
	CALL	send		; and send code
	MOVLW	0x08		; Switch off display
	CALL	send		; and send code
	MOVLW	0x01		; Code to clear display
	CALL	send		; and send code
	MOVLW	0x06		; Enable cursor auto inc  
	CALL	send		; and send code
	MOVLW	0x80		; Zero display address
	CALL	send		; and send code
	MOVLW	0x0C		; Turn on display  
	CALL	send		; and send code
	MOVLW	0x0E		; Turn on display  
	CALL	send		; and send code
	MOVLW	0x0F		; Turn on display  
	CALL	send		; and send code

	RETURN			; Done

;--------------------------------------------------------------