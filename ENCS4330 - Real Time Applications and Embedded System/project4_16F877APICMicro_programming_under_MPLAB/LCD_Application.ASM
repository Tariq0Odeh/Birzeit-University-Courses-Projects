	PROCESSOR 16F877A
	__CONFIG	0x3731

	#INCLUDE "P16F877A.INC"
	#define PRECISION 3 
	#define two_bytes 2
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

letter		EQU	30	; current letter
pos			EQU	31	; value for currsor position
flag		EQU	32	; variable to store space ascii
ms			EQU	33	; time counter
currIndex	EQU 34
operation	EQU 35
counter		EQU 36
flag_zero	EQU	37
first_digit	EQU	38
clicks		EQU 39

M_STOR_STATUS macro WHERE
    movf    STATUS,w
    movwf   WHERE
    endm

M_RETR_STATUS macro WHERE
    movf    WHERE,w
    movwf   STATUS
    endm

    cblock 0x40
	    REG_X:PRECISION
	    REG_Y:PRECISION
	    REG_Z:PRECISION
		REG_TEMP:PRECISION
		DIVIDER:PRECISION
	    REG_COUNTER
	    REG_STATUS
	    REG_T1
	    REG_T2
	    REG_ROT_COUNTER
		NUM1:two_bytes
		NUM2:two_bytes
		RESULT:PRECISION
		REMAINDER:PRECISION
    endc

; PROGRAM BEGINS ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

			ORG		0	
			NOP			
			GOTO	init
	
; Interrupt ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
			ORG		004
			;MOVFW	currIndex
			;SUBLW	';'
			;BZ		EOI

			BTFSC	INTCON, 1
			GOTO 	clicked
			GOTO 	jump
clicked		
			MOVFW	currIndex
			SUBLW	';'
			BNZ		skip1
			
			MOVFW	flag
			SUBLW	0x0
			BZ		skip9
			
			INCF	clicks
skip9		CLRF	ms
			BCF		PORTB, 0
			BCF		INTCON, 1
			GOTO	jump

			;INCF	letter
skip1		CALL	increment
			CALL	index
			BCF		PORTB, 0
			BCF		INTCON, 1
			CALL	printDigit
			CLRF	ms
			GOTO	jump

jump		INCF	ms

			MOVFW	currIndex
			SUBLW	';'
			BNZ		skip2
			MOVFW	ms
			SUBLW	0x30   ;0x20
			BTFSC	STATUS, Z
			GOTO	SS
			BCF		INTCON, 2
			GOTO	EOI
				

skip2		MOVFW	ms
			SUBLW	0x20   ;0x20
			BTFSC	STATUS, Z
			GOTO	SS
			BCF		INTCON, 2
			GOTO	EOI

SS			BTFSC	INTCON, 2
			GOTO 	timerFinished
			GOTO 	EOI

timerFinished
			CLRF	ms
			MOVFW	currIndex
			SUBLW	'*'
			BNZ		skip10
			MOVFW	letter
			MOVWF	operation
			
			MOVLW 	';'
			MOVWF	currIndex

			MOVLW 	0x0
			MOVWF	clicks

			MOVLW 	0x0
			MOVWF	flag

			;Divider = 100,000
			MOVLW	0x80
			MOVWF	DIVIDER
			MOVLW	0x96
			MOVWF	DIVIDER+1
			MOVLW	0x98
			MOVWF	DIVIDER+2
		
			GOTO	calRes
			
skip10		MOVFW	currIndex
			SUBLW	';'
			BNZ		skip6
			;;check yes/no
			;;decide how to print each
			MOVFW	flag
			SUBLW	0x0
			BNZ		skip7
			MOVLW 	0xC0
			MOVWF	pos
			CALL	inid
			CALL	keepMes
			INCF	flag
			GOTO	EOI
			
skip7		MOVFW	clicks
			SUBLW	0x01
			BNZ		next1
			
			MOVLW 	0xC0
			MOVWF	pos
			CALL	inid
			CALL	initMes
			BCF		PORTB, 0
			BCF		INTCON, 1
			MOVLW	0x0C
			MOVWF	TMR0
			BCF		INTCON, 2

			;Divider = 10,000
			MOVLW	0x10
			MOVWF	DIVIDER
			MOVLW	0x27
			MOVWF	DIVIDER+1
			MOVLW	0x0
			MOVWF	DIVIDER+2

			MOVFW	NUM1
			MOVWF	REG_TEMP
			MOVFW	NUM1+1
			MOVWF	REG_TEMP+1
			CLRF	REG_TEMP+2

			CALL	printNum

			INCF 	pos
			MOVLW 	'+'
			MOVWF	letter
			CALL	printDigit

			MOVLW	0x10
			MOVWF	DIVIDER
			MOVLW	0x27
			MOVWF	DIVIDER+1
			MOVLW	0x0
			MOVWF	DIVIDER+2

			MOVFW	NUM2
			MOVWF	REG_TEMP
			MOVFW	NUM2+1
			MOVWF	REG_TEMP+1
			CLRF	REG_TEMP+2

			CALL	printNum
			
			MOVLW 	0xC5
			MOVWF	pos

			BCF		Select,RS	; set display command mode
			MOVfW	pos
			CALL	send		; output it to display
			BSF		Select,RS

			MOVLW 	'*'
			MOVWF	currIndex

			MOVLW 	'+'
			MOVWF	letter
			
			MOVLW 	'+'
			MOVWF	operation

			CLRF	ms
			GOTO	EOI


next1		;MOVFW	clicks
			;SUBLW	0x02
			;BNZ		EOI
			CALL	initialize
			CALL	inid
			CALL	initMes
			BCF		PORTB, 0
			BCF		INTCON, 1
			MOVLW	0x0C
			MOVWF	TMR0
			BCF		INTCON, 2
			CLRF	ms
			GOTO	EOI


skip6		CALL	printDigit
			CALL	storeDigit

			MOVFW	currIndex
			SUBLW	'0'
			BNZ		skip4
			MOVFW	letter
			MOVWF	first_digit
			;GOTO	skip42;;;;;
			GOTO	SK2

skip4		MOVFW	currIndex
			SUBLW	'6'
			BNZ		skip5
			MOVFW	letter
			MOVWF	first_digit
			GOTO	SK2

;skip42		MOVFW	currIndex
;			SUBLW	'5'
;			BNZ		skip5
;			MOVFW	letter
;			MOVWF	first_digit
			
			
skip5		MOVFW	currIndex
			SUBLW	':'
			BNZ		skip3	;;change to result
			INCF	currIndex
calRes		CALL	findResult
			CALL	inid
			MOVLW 	0xC0
			MOVWF	pos
			CALL	resMes
			;;check if num2 = 0 when / %
			MOVFW	operation
			SUBLW	'+'
			BZ		printRes

			MOVFW	NUM2
			SUBLW	0x0
			BNZ		printRes

			MOVFW	NUM2+1
			SUBLW	0x0
			BNZ		printRes
			CALL	errorMes
			GOTO	EOI

printRes	CALL	printResult
			GOTO 	EOI
			
skip3		MOVFW	currIndex
			SUBLW	'5'
			BNZ		SK2		
			MOVFW	letter
			MOVWF	operation

SK2			INCF	currIndex;;;;;;;;;;;;
			BCF		PORTB, 0
			BCF		INTCON, 1
			
			INCF 	pos
			
			BCF		Select,RS	; set display command mode
			MOVfW	pos
			CALL	send		; output it to display
			BSF		Select,RS
			
			MOVFW	currIndex
			SUBLW	'5'
			BTFSS	STATUS, Z
			GOTO	addZero
			MOVLW 	'+'
			GOTO	storeChar
addZero		MOVLW 	'0'
storeChar	MOVWF	letter

			CALL	printDigit

			MOVLW	0x0C
			MOVWF	TMR0
			BCF		INTCON, 2
			CLRF	ms
			;GOTO	endInput
EOI			RETFIE

; Port & display setup.....................................
init		nop
	
			BANKSEL PORTB
			BSF 	TRISB, 0
	
			BANKSEL	TRISA		; Select bank 1
	    	CLRF	TRISA          	
			MOVLW	B'00000110' ;  
			MOVWF	ADCON1 			; CONVERT PORTA FROM ANALOG TO DIGITAL
	
			MOVLW	B'00000000' 			; TO MAKE PORT A OUTPUT
			MOVWF	TRISA
			BANKSEL OPTION_REG
			MOVLW	0x47		; TMR0 initialisation code
			MOVWF	OPTION_REG	
	
			BANKSEL PORTA
			CLRF	TMR0
			MOVLW	0xD9
			MOVWF	TMR0
			MOVLW	b'10110000'	; INTCON init. code
			MOVWF	INTCON

; Initial Values ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;	
initVar		CALL	inid		; Initialise the display
			CALL	initialize
			CALL	initMes	
			;CALL 	nextChar
			;GOTO	display
start		GOTO	start		; loop to main loop forever

; Delay ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
nextChar
			;BCF		INTCON, 2
			MOVLW	D'255'
			CALL 	xms
			GOTO	nextChar
endInput	RETURN
;display		CALL 	inid

; Initialize ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
initialize	MOVLW 	'0'
			MOVWF	letter

			MOVLW 	0
			MOVWF	ms
			
			MOVLW 	0
			MOVWF	clicks
	
			MOVLW 	0xC0
			MOVWF	pos
			
			MOVLW 	0
			MOVWF 	flag

			MOVLW 	'0'
			MOVWF	currIndex	

			MOVLW   REG_X
		    CALL    M_CLR               ; clear register X
		
		    MOVLW   REG_Y
		    CALL    M_CLR               ; clear register Y
		
		    MOVLW   REG_Z
		    CALL    M_CLR               ; clear register Z

			MOVLW   REG_TEMP
		    CALL    M_CLR               ; clear register TEMP
			
			;Divider = 100,000
			MOVLW	0x80
			MOVWF	DIVIDER
			MOVLW	0x96
			MOVWF	DIVIDER+1
			MOVLW	0x98
			MOVWF	DIVIDER+2
			RETURN
; Limit digits increment ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
index		MOVFW	currIndex
			SUBLW	'0'
			BZ		six_n

			MOVFW	currIndex
			SUBLW	'1'
			BZ		five_n

			MOVFW	currIndex
			SUBLW	'2'
			BZ		five_n

			MOVFW	currIndex
			SUBLW	'3'
			BZ		three_n

			MOVFW	currIndex
			SUBLW	'4'
			BZ		five_n

			MOVFW	currIndex
			SUBLW	'6'
			BZ		six_n

			MOVFW	currIndex
			SUBLW	'7'
			BZ		five_n

			MOVFW	currIndex
			SUBLW	'8'
			BZ		five_n

			MOVFW	currIndex
			SUBLW	'9'
			BZ		three_n

			MOVFW	currIndex
			SUBLW	':'
			BZ		five_n
			GOTO	leave

six_n		MOVFW	letter
			SUBLW	'7'
			BTFSS 	STATUS,Z
			GOTO	leave
			GOTO 	zero
		
five_n		MOVFW	first_digit
			SUBLW	'6'
			BNZ		nsix1

			MOVFW	letter
			SUBLW	'6'
			BZ		skipSix
nsix1		MOVFW	letter
			SUBLW	':'
skipSix		BTFSS 	STATUS,Z
			GOTO	leave
			GOTO 	zero

three_n		MOVFW	first_digit
			SUBLW	'6'
			BNZ		nsix2

			MOVFW	letter
			SUBLW	'4'
			BZ		skipSix1
nsix2		MOVFW	letter
			SUBLW	':'
skipSix1	BTFSS 	STATUS,Z
			
			GOTO	leave
			GOTO 	zero

zero		MOVLW	'0'
			MOVWF	letter

leave		RETURN

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
increment	MOVFW	currIndex
			SUBLW	'5'
			BTFSS	STATUS, Z
			GOTO	skip8
			GOTO	opIncrement

skip8		MOVFW	currIndex
			SUBLW	'*'
			BTFSS	STATUS, Z
			GOTO	normalIncrement	
			GOTO	opIncrement

normalIncrement
			INCF	letter
			GOTO	return1
opIncrement
op_plus		MOVFW	letter
			SUBLW	'+'
			BNZ		op_div
			MOVLW 	'/'
			MOVWF	letter
			GOTO	return1


op_div		MOVFW	letter
			SUBLW	'/'
			BNZ		op_mod
			MOVLW 	'%'
			MOVWF	letter
			GOTO	return1

op_mod		MOVFW	letter
			SUBLW	'%'
			BNZ		return1
			MOVLW 	'+'
			MOVWF	letter

return1		RETURN

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
printDigit	MOVFW	letter
			CALL 	send
			BCF		Select,RS	; set display command mode
			MOVfW	pos
			CALL	send		; output it to display
			BSF		Select,RS
			RETURN

; Initial msg ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
initMes		BCF		Select,RS	; set display command mode
			MOVLW	0x80		; code to home cursor
			CALL	send		; output it to display
			BSF		Select,RS	; and restore data mode
			MOVLW	'E'			; load volts code
			CALL	send		; and output
			MOVLW	'n'			; load volts code
			CALL	send		; and output
			MOVLW	't'			; load volts code
			CALL	send		; and output
			MOVLW	'e'			; load volts code
			CALL	send		; and output
			MOVLW	'r'			; load volts code
			CALL	send		; and output
	
			MOVLW	' '			; load volts code
			CALL	send		; and output
	
			MOVLW	'O'			; load volts code
			CALL	send		; and output
			MOVLW	'p'			; load volts code
			CALL	send		; and output
			MOVLW	'e'			; load volts code
			CALL	send		; and output
			MOVLW	'r'			; load volts code
			CALL	send		; and output
			MOVLW	'a'			; load volts code
			CALL	send		; and output
			MOVLW	't'			; load volts code
			CALL	send		; and output
			MOVLW	'i'			; load volts code
			CALL	send		; and output
			MOVLW	'o'			; load volts code
			CALL	send		; and output
			MOVLW	'n'			; load volts code
			CALL	send		; and output
			
			BCF		Select,RS	; set display command mode
			MOVfW	pos
			CALL	send		; output it to display
			BSF		Select,RS
			
			MOVLW	letter
			CALL	send	
			BCF		Select,RS	; set display command mode
			MOVFW	pos
			CALL	send		; output it to display
			BSF		Select,RS
			RETURN				; done
			#INCLUDE "LCDIS.INC"
; Result msg ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
resMes		BCF		Select,RS	; set display command mode
			MOVLW	0x80		; code to home cursor
			CALL	send		; output it to display
			BSF		Select,RS	; and restore data mode
			MOVLW	'r'			; load volts code
			CALL	send		; and output
			MOVLW	'e'			; load volts code
			CALL	send		; and output
			MOVLW	's'			; load volts code
			CALL	send		; and output
			MOVLW	'u'			; load volts code
			CALL	send		; and output
			MOVLW	'l'			; load volts code
			CALL	send		; and output
			MOVLW	't'			; load volts code
			CALL	send		; and output

			
			BCF		Select,RS	; set display command mode
			MOVfW	pos
			CALL	send		; output it to display
			BSF		Select,RS
			
			MOVLW	'='
			CALL	send	
			BCF		Select,RS	; set display command mode
			MOVfW	pos
			CALL	send		; output it to display
			BSF		Select,RS
			INCF	pos
			BCF		Select,RS	; set display command mode
			MOVfW	pos
			CALL	send		; output it to display
			BSF		Select,RS
			RETURN				; done
; Keep msg ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
keepMes		BCF		Select,RS	; set display command mode
			MOVLW	0x80		; code to home cursor
			CALL	send		; output it to display
			BSF		Select,RS	; and restore data mode
			MOVLW	'K'			; load volts code
			CALL	send		; and output
			MOVLW	'e'			; load volts code
			CALL	send		; and output
			MOVLW	'e'			; load volts code
			CALL	send		; and output
			MOVLW	'p'			; load volts code
			CALL	send		; and output
			MOVLW	' '			; load volts code
			CALL	send		; and output
			MOVLW	'['			; load volts code
			CALL	send		; and output
			MOVLW	'1'			; load volts code
			CALL	send		; and output
			MOVLW	':'			; load volts code
			CALL	send		; and output
			MOVLW	'Y'			; load volts code
			CALL	send		; and output
			MOVLW	','			; load volts code
			CALL	send		; and output
			MOVLW	' '			; load volts code
			CALL	send		; and output
			MOVLW	'2'			; load volts code
			CALL	send		; and output
			MOVLW	':'			; load volts code
			CALL	send		; and output
			MOVLW	'N'			; load volts code
			CALL	send		; and output
			MOVLW	']'			; load volts code
			CALL	send		; and output

			BCF		Select,RS	; set display command mode
			MOVfW	pos
			CALL	send		; output it to display
			BSF		Select,RS
			RETURN				; done
; Error msg ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
errorMes	;BCF		Select,RS	; set display command mode
			;MOVLW	0x80		; code to home cursor
			;CALL	send		; output it to display
			;BSF		Select,RS	; and restore data mode
			MOVLW	'm'			; load volts code
			CALL	send		; and output
			MOVLW	'a'			; load volts code
			CALL	send		; and output
			MOVLW	't'			; load volts code
			CALL	send		; and output
			MOVLW	'h'			; load volts code
			CALL	send		; and output
			MOVLW	' '			; load volts code
			CALL	send		; and output
			MOVLW	'E'			; load volts code
			CALL	send		; and output
			MOVLW	'r'			; load volts code
			CALL	send		; and output
			MOVLW	'r'			; load volts code
			CALL	send		; and output
			MOVLW	'o'			; load volts code
			CALL	send		; and output
			MOVLW	'r'			; load volts code
			CALL	send		; and output
			MOVLW	'!'			; load volts code
			CALL	send		; and output
			;BCF		Select,RS	; set display command mode
			;MOVfW	pos
			;CALL	send		; output it to display
			;BSF		Select,RS
			RETURN				; done
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
storeDigit	
			MOVLW   REG_X
		    CALL    M_CLR               ; clear register X
		
		    MOVLW   REG_Y
		    CALL    M_CLR               ; clear register Y
		
		    MOVLW   REG_Z
		    CALL    M_CLR               ; clear register Z

			MOVFW	currIndex
			SUBLW	'0'
			BNZ		BR1
			MOVLW   REG_TEMP
		    CALL    M_CLR               ; clear register TEMP
			MOVLW	0x10
			MOVWF	REG_X
			MOVLW	0x27
			MOVWF	REG_X+1
			MOVFW	letter
			SUBLW	0x30
			MOVWF	REG_Y
			COMF	REG_Y
			INCF	REG_Y
			;MOVFW	REG_Y
			;ADDLW	0x1
			;MOVWF	REG_Y

			CALL	M_MUL
			MOVFW	REG_TEMP
			MOVWF	REG_X
			CALL	M_ADD
			MOVFW	REG_Z
			MOVWF	REG_TEMP
			MOVFW	REG_Z+1
			MOVWF	REG_TEMP+1
			MOVFW	REG_Z+2
			MOVWF	REG_TEMP+2
			GOTO	BR10

BR1			MOVFW	currIndex
			SUBLW	'1'
			BNZ		BR2
			MOVLW	0xE8
			MOVWF	REG_X
			MOVLW	0x03
			MOVWF	REG_X+1
			MOVFW	letter
			SUBLW	0x30
			MOVWF	REG_Y
			COMF	REG_Y
			INCF	REG_Y
			;MOVFW	REG_Y
			;ADDLW	0x1
			;MOVWF	REG_Y
			CALL	M_MUL

			MOVFW	REG_TEMP
			MOVWF	REG_X
			MOVFW	REG_TEMP+1
			MOVWF	REG_X+1
			MOVFW	REG_TEMP+2
			MOVWF	REG_X+2
			CALL	M_ADD
			MOVFW	REG_Z
			MOVWF	REG_TEMP
			MOVFW	REG_Z+1
			MOVWF	REG_TEMP+1
			MOVFW	REG_Z+2
			MOVWF	REG_TEMP+2


			GOTO	BR10

BR2			MOVFW	currIndex
			SUBLW	'2'
			BNZ		BR3
			MOVLW	0x64
			MOVWF	REG_X
			MOVFW	letter
			SUBLW	0x30
			MOVWF	REG_Y
			COMF	REG_Y
			INCF	REG_Y
			;MOVFW	REG_Y
			;ADDLW	0x1
			;MOVWF	REG_Y
			CALL	M_MUL

			MOVFW	REG_TEMP
			MOVWF	REG_X
			MOVFW	REG_TEMP+1
			MOVWF	REG_X+1
			MOVFW	REG_TEMP+2
			MOVWF	REG_X+2
			CALL	M_ADD
			MOVFW	REG_Z
			MOVWF	REG_TEMP
			MOVFW	REG_Z+1
			MOVWF	REG_TEMP+1
			MOVFW	REG_Z+2
			MOVWF	REG_TEMP+2
			GOTO	BR10

BR3			MOVFW	currIndex
			SUBLW	'3'
			BNZ		BR4
			MOVLW	0x0A
			MOVWF	REG_X
			MOVFW	letter
			SUBLW	0x30
			MOVWF	REG_Y
			COMF	REG_Y
			INCF	REG_Y
			;MOVFW	REG_Y
			;ADDLW	0x1
			;MOVWF	REG_Y
			CALL	M_MUL
			MOVFW	REG_TEMP
			MOVWF	REG_X
			MOVFW	REG_TEMP+1
			MOVWF	REG_X+1
			MOVFW	REG_TEMP+2
			MOVWF	REG_X+2
			CALL	M_ADD
			MOVFW	REG_Z
			MOVWF	REG_TEMP
			MOVFW	REG_Z+1
			MOVWF	REG_TEMP+1
			MOVFW	REG_Z+2
			MOVWF	REG_TEMP+2
			GOTO	BR10

BR4			MOVFW	currIndex
			SUBLW	'4'
			BNZ		BR5
			MOVLW	0x01
			MOVWF	REG_X
			MOVFW	letter
			SUBLW	0x30
			MOVWF	REG_Y
			COMF	REG_Y
			INCF	REG_Y
			;MOVFW	REG_Y
			;ADDLW	0x1
			;MOVWF	REG_Y
			CALL	M_MUL
			MOVFW	REG_TEMP
			MOVWF	REG_X
			MOVFW	REG_TEMP+1
			MOVWF	REG_X+1
			MOVFW	REG_TEMP+2
			MOVWF	REG_X+2
			CALL	M_ADD
			MOVFW	REG_Z
			MOVWF	NUM1
			MOVFW	REG_Z+1
			MOVWF	NUM1+1
			MOVFW	REG_Z+2
			MOVWF	NUM1+2
			GOTO	BR10

BR5			MOVFW	currIndex
			SUBLW	'6'
			BNZ		BR6
			MOVLW   REG_TEMP
		    CALL    M_CLR               ; clear register TEMP
			MOVLW	0x10
			MOVWF	REG_X
			MOVLW	0x27
			MOVWF	REG_X+1
			MOVFW	letter
			SUBLW	0x30
			MOVWF	REG_Y
			COMF	REG_Y
			INCF	REG_Y
			;MOVFW	REG_Y
			;ADDLW	0x1
			;MOVWF	REG_Y
			CALL	M_MUL
			MOVFW	REG_TEMP
			MOVWF	REG_X
			MOVFW	REG_TEMP+1
			MOVWF	REG_X+1
			MOVFW	REG_TEMP+2
			MOVWF	REG_X+2
			CALL	M_ADD
			MOVFW	REG_Z
			MOVWF	REG_TEMP
			MOVFW	REG_Z+1
			MOVWF	REG_TEMP+1
			MOVFW	REG_Z+2
			MOVWF	REG_TEMP+2
			GOTO	BR10

BR6			MOVFW	currIndex
			SUBLW	'7'
			BNZ		BR7
			MOVLW	0xE8
			MOVWF	REG_X
			MOVLW	0x03
			MOVWF	REG_X+1
			MOVFW	letter
			SUBLW	0x30
			MOVWF	REG_Y
			COMF	REG_Y
			INCF	REG_Y
			;MOVFW	REG_Y
			;ADDLW	0x1
			;MOVWF	REG_Y
			CALL	M_MUL
			MOVFW	REG_TEMP
			MOVWF	REG_X
			MOVFW	REG_TEMP+1
			MOVWF	REG_X+1
			MOVFW	REG_TEMP+2
			MOVWF	REG_X+2
			CALL	M_ADD
			MOVFW	REG_Z
			MOVWF	REG_TEMP
			MOVFW	REG_Z+1
			MOVWF	REG_TEMP+1
			MOVFW	REG_Z+2
			MOVWF	REG_TEMP+2
			GOTO	BR10

BR7			MOVFW	currIndex
			SUBLW	'8'
			BNZ		BR8
			MOVLW	0x64
			MOVWF	REG_X
			MOVFW	letter
			SUBLW	0x30
			MOVWF	REG_Y
			COMF	REG_Y
			INCF	REG_Y
			;MOVFW	REG_Y
			;ADDLW	0x1
			;MOVWF	REG_Y
			CALL	M_MUL
			MOVFW	REG_TEMP
			MOVWF	REG_X
			MOVFW	REG_TEMP+1
			MOVWF	REG_X+1
			MOVFW	REG_TEMP+2
			MOVWF	REG_X+2
			CALL	M_ADD
			MOVFW	REG_Z
			MOVWF	REG_TEMP
			MOVFW	REG_Z+1
			MOVWF	REG_TEMP+1
			MOVFW	REG_Z+2
			MOVWF	REG_TEMP+2
			GOTO	BR10

BR8			MOVFW	currIndex
			SUBLW	'9'
			BNZ		BR9
			MOVLW	0x0A
			MOVWF	REG_X
			MOVFW	letter
			SUBLW	0x30
			MOVWF	REG_Y
			COMF	REG_Y
			INCF	REG_Y
			;MOVFW	REG_Y
			;ADDLW	0x1
			;MOVWF	REG_Y
			CALL	M_MUL
			MOVFW	REG_TEMP
			MOVWF	REG_X
			MOVFW	REG_TEMP+1
			MOVWF	REG_X+1
			MOVFW	REG_TEMP+2
			MOVWF	REG_X+2
			CALL	M_ADD
			MOVFW	REG_Z
			MOVWF	REG_TEMP
			MOVFW	REG_Z+1
			MOVWF	REG_TEMP+1
			MOVFW	REG_Z+2
			MOVWF	REG_TEMP+2
			GOTO	BR10

BR9			MOVFW	currIndex
			SUBLW	':'
			BNZ		BR10
			MOVLW	0x01
			MOVWF	REG_X
			MOVFW	letter
			SUBLW	0x30
			MOVWF	REG_Y
			COMF	REG_Y
			INCF	REG_Y
			;MOVFW	REG_Y
			;ADDLW	0x1
			;MOVWF	REG_Y
			CALL	M_MUL
			MOVFW	REG_TEMP
			MOVWF	REG_X
			MOVFW	REG_TEMP+1
			MOVWF	REG_X+1
			MOVFW	REG_TEMP+2
			MOVWF	REG_X+2
			CALL	M_ADD
			MOVFW	REG_Z
			MOVWF	NUM2
			MOVFW	REG_Z+1
			MOVWF	NUM2+1
			MOVFW	REG_Z+2
			MOVWF	NUM2+2
BR10		RETURN

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
findResult
			MOVLW   REG_X
		    CALL    M_CLR               ; clear register X
		
		    MOVLW   REG_Y
		    CALL    M_CLR               ; clear register Y
		
		    MOVLW   REG_Z
		    CALL    M_CLR               ; clear register Z

			MOVFW	operation
			SUBLW	'+'
			BNZ		BRA1
			
			MOVFW	NUM1
			MOVWF	REG_X
			MOVFW	NUM1+1
			MOVWF	REG_X+1
			MOVFW	NUM2
			MOVWF	REG_Z
			MOVFW	NUM2+1
			MOVWF	REG_Z+1
			CALL	M_ADD
			MOVFW	REG_Z
			MOVWF	RESULT
			MOVFW	REG_Z+1
			MOVWF	RESULT+1
			MOVFW	REG_Z+2
			MOVWF	RESULT+2
			GOTO	BRA3

BRA1		MOVFW	operation
			SUBLW	'/'
			BNZ		BRA2
			MOVFW	NUM1
			MOVWF	REG_Z
			MOVFW	NUM1+1
			MOVWF	REG_Z+1

			MOVFW	NUM2
			MOVWF	REG_X
			MOVFW	NUM2+1
			MOVWF	REG_X+1

			CALL	M_DIV
			MOVFW	REG_Y
			MOVWF	RESULT
			MOVFW	REG_Y+1
			MOVWF	RESULT+1
			MOVFW	REG_Y+2
			MOVWF	RESULT+2
			;add remainder function
			MOVFW	REG_Z
			MOVWF	REMAINDER
			MOVFW	REG_Z+1
			MOVWF	REMAINDER+1
			MOVFW	REG_Z+2
			MOVWF	REMAINDER+2
			GOTO	BRA3

BRA2		MOVFW	operation
			SUBLW	'%'
			BNZ		BRA3

			MOVFW	NUM1
			MOVWF	REG_Z
			MOVFW	NUM1+1
			MOVWF	REG_Z+1

			MOVFW	NUM2
			MOVWF	REG_X
			MOVFW	NUM2+1
			MOVWF	REG_X+1

			CALL	M_DIV
			
			MOVLW   REG_X
		    CALL    M_CLR               ; clear register X
			
			MOVFW	NUM2
			MOVWF	REG_X
			MOVFW	NUM2+1
			MOVWF	REG_X+1
			
			CALL M_MUL		

			MOVFW	REG_Z
			MOVWF	REG_X
			MOVFW	REG_Z+1
			MOVWF	REG_X+1
			MOVFW	REG_Z+2
			MOVWF	REG_X+2

			MOVLW   REG_Z
		    CALL    M_CLR               ; clear register X
			
			MOVFW	NUM1
			MOVWF	REG_Z
			MOVFW	NUM1+1
			MOVWF	REG_Z+1

			CALL	M_SUB

			MOVFW	REG_Z
			MOVWF	RESULT
			MOVFW	REG_Z+1
			MOVWF	RESULT+1
			MOVFW	REG_Z+2
			MOVWF	RESULT+2

BRA3		RETURN

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
printResult
			MOVLW   0x08
			MOVWF	counter
			MOVLW	0x0
			MOVWF	flag_zero

			MOVFW	RESULT
			MOVWF	REG_TEMP
			MOVFW	RESULT+1
			MOVWF	REG_TEMP+1
			MOVFW	RESULT+2
			MOVWF	REG_TEMP+2

printLoop	
			MOVFW	counter
			SUBLW	0x0
			BZ		stopPrt
			
			MOVLW   REG_X
		    CALL    M_CLR               ; clear register X
		
		    MOVLW   REG_Y
		    CALL    M_CLR               ; clear register Y
		
		    MOVLW   REG_Z
		    CALL    M_CLR               ; clear register Z

			MOVFW	REG_TEMP
			MOVWF	REG_Z
			MOVFW	REG_TEMP+1
			MOVWF	REG_Z+1
			MOVFW	REG_TEMP+2
			MOVWF	REG_Z+2

			MOVFW	DIVIDER
			MOVWF	REG_X
			MOVFW	DIVIDER+1
			MOVWF	REG_X+1
			MOVFW	DIVIDER+2
			MOVWF	REG_X+2

			CALL	M_DIV

			MOVFW	REG_Y
			SUBLW	0x0
			BNZ		skp4

checkLead	MOVFW	flag_zero
			SUBLW	0x0
			BZ		cntPrt
			
skp4		MOVFW	flag_zero
			ADDLW	0x01
			ADDWF	flag_zero
			
			MOVFW	REG_Y
			ADDLW	0x30
			MOVWF	letter

			CALL	printDigit
			INCF 	pos
			
			BCF		Select,RS	; set display command mode
			MOVfW	pos
			CALL	send		; output it to display
			BSF		Select,RS

			;;restore result 		; Z - X -> Z
			;; res * divider = X 	; X * Y -> Z
			;; Z = original num		; Z / X -> Y;  remainder -> Z
			MOVFW	DIVIDER
			MOVWF	REG_X
			MOVFW	DIVIDER+1
			MOVWF	REG_X+1
			MOVFW	DIVIDER+2
			MOVWF	REG_X+2
			CALL	M_MUL
			
			MOVFW	REG_Z
			MOVWF	REG_X
			MOVFW	REG_Z+1
			MOVWF	REG_X+1
			MOVFW	REG_Z+2
			MOVWF	REG_X+2

			MOVFW	REG_TEMP
			MOVWF	REG_Z
			MOVFW	REG_TEMP+1
			MOVWF	REG_Z+1
			MOVFW	REG_TEMP+2
			MOVWF	REG_Z+2

			CALL 	M_SUB

			MOVFW	REG_Z
			MOVWF	REG_TEMP
			MOVFW	REG_Z+1
			MOVWF	REG_TEMP+1
			MOVFW	REG_Z+2
			MOVWF	REG_TEMP+2

cntPrt		MOVFW	DIVIDER
			MOVWF	REG_Z
			MOVFW	DIVIDER+1
			MOVWF	REG_Z+1
			MOVFW	DIVIDER+2
			MOVWF	REG_Z+2
			
			MOVLW   REG_X
		    CALL    M_CLR               ; clear register X
			
			MOVLW	0x0A
			MOVWF	REG_X

			CALL	M_DIV

			MOVFW	REG_Y
			MOVWF	DIVIDER

			MOVFW	REG_Y+1
			MOVWF	DIVIDER+1
		
			MOVFW	REG_Y+2
			MOVWF	DIVIDER+2
		
			DECF	counter
			GOTO	printLoop
stopPrt		
			MOVFW	flag_zero
			SUBLW	0x0
			BNZ		rtrn1
	
			MOVFW	flag_zero
			ADDLW	0x30
			MOVWF	letter

			CALL	printDigit
			INCF 	pos
			
			BCF		Select,RS	; set display command mode
			MOVfW	pos
			CALL	send		; output it to display
			BSF		Select,RS

rtrn1		
			MOVFW	operation
			SUBLW	'/'
			BNZ		rtrn2
			
			MOVLW	','
			CALL	send	
			BCF		Select,RS	; set display command mode
			MOVfW	pos
			CALL	send		; output it to display
			BSF		Select,RS
			INCF	pos
			BCF		Select,RS	; set display command mode
			MOVfW	pos
			CALL	send		; output it to display
			BSF		Select,RS
			
			MOVLW   0x08
			MOVWF	counter
			MOVLW	0x0
			MOVWF	flag_zero

			MOVFW	REMAINDER
			MOVWF	REG_TEMP
			MOVFW	REMAINDER+1
			MOVWF	REG_TEMP+1
			MOVFW	REMAINDER+2
			MOVWF	REG_TEMP+2

			MOVLW	0x80
			MOVWF	DIVIDER
			MOVLW	0x96
			MOVWF	DIVIDER+1
			MOVLW	0x98
			MOVWF	DIVIDER+2

printLoop2	
			MOVFW	counter
			SUBLW	0x0
			BZ		stopPrt2
			
			MOVLW   REG_X
		    CALL    M_CLR               ; clear register X
		
		    MOVLW   REG_Y
		    CALL    M_CLR               ; clear register Y
		
		    MOVLW   REG_Z
		    CALL    M_CLR               ; clear register Z

			MOVFW	REG_TEMP
			MOVWF	REG_Z
			MOVFW	REG_TEMP+1
			MOVWF	REG_Z+1
			MOVFW	REG_TEMP+2
			MOVWF	REG_Z+2

			MOVFW	DIVIDER
			MOVWF	REG_X
			MOVFW	DIVIDER+1
			MOVWF	REG_X+1
			MOVFW	DIVIDER+2
			MOVWF	REG_X+2

			CALL	M_DIV

			MOVFW	REG_Y
			SUBLW	0x0
			BNZ		skp42

			MOVFW	flag_zero
			SUBLW	0x0
			BZ		cntPrt2
			
skp42		MOVFW	flag_zero
			ADDLW	0x01
			ADDWF	flag_zero
			
			MOVFW	REG_Y
			ADDLW	0x30
			MOVWF	letter

			CALL	printDigit
			INCF 	pos
			
			BCF		Select,RS	; set display command mode
			MOVFW	pos
			CALL	send		; output it to display
			BSF		Select,RS

			;;restore result 		; Z - X -> Z
			;; res * divider = X 	; X * Y -> Z
			;; Z = original num		; Z / X -> Y;  remainder -> Z
			MOVFW	DIVIDER
			MOVWF	REG_X
			MOVFW	DIVIDER+1
			MOVWF	REG_X+1
			MOVFW	DIVIDER+2
			MOVWF	REG_X+2
			CALL	M_MUL
			
			MOVFW	REG_Z
			MOVWF	REG_X
			MOVFW	REG_Z+1
			MOVWF	REG_X+1
			MOVFW	REG_Z+2
			MOVWF	REG_X+2

			MOVFW	REG_TEMP
			MOVWF	REG_Z
			MOVFW	REG_TEMP+1
			MOVWF	REG_Z+1
			MOVFW	REG_TEMP+2
			MOVWF	REG_Z+2

			CALL 	M_SUB

			MOVFW	REG_Z
			MOVWF	REG_TEMP
			MOVFW	REG_Z+1
			MOVWF	REG_TEMP+1
			MOVFW	REG_Z+2
			MOVWF	REG_TEMP+2

cntPrt2		MOVFW	DIVIDER
			MOVWF	REG_Z
			MOVFW	DIVIDER+1
			MOVWF	REG_Z+1
			MOVFW	DIVIDER+2
			MOVWF	REG_Z+2
			
			MOVLW   REG_X
		    CALL    M_CLR               ; clear register X
			
			MOVLW	0x0A
			MOVWF	REG_X

			CALL	M_DIV

			MOVFW	REG_Y
			MOVWF	DIVIDER

			MOVFW	REG_Y+1
			MOVWF	DIVIDER+1
		
			MOVFW	REG_Y+2
			MOVWF	DIVIDER+2
		
			DECF	counter
			GOTO	printLoop2


stopPrt2		
			MOVFW	flag_zero
			SUBLW	0x0
			BNZ		rtrn2
	
			MOVFW	flag_zero
			ADDLW	0x30
			MOVWF	letter

			CALL	printDigit
			INCF 	pos
			
			BCF		Select,RS	; set display command mode
			MOVfW	pos
			CALL	send		; output it to display
			BSF		Select,RS	
			
rtrn2		RETURN
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

printNum
			MOVLW   0x05
			MOVWF	counter

			;MOVFW	RESULT
			;MOVWF	REG_TEMP
			;MOVFW	RESULT+1
			;MOVWF	REG_TEMP+1
			;MOVFW	RESULT+2
			;MOVWF	REG_TEMP+2

printLoop3	
			MOVFW	counter
			SUBLW	0x0
			BZ		stopPrt3
			
			MOVLW   REG_X
		    CALL    M_CLR               ; clear register X
		
		    MOVLW   REG_Y
		    CALL    M_CLR               ; clear register Y
		
		    MOVLW   REG_Z
		    CALL    M_CLR               ; clear register Z

			MOVFW	REG_TEMP
			MOVWF	REG_Z
			MOVFW	REG_TEMP+1
			MOVWF	REG_Z+1
			MOVFW	REG_TEMP+2
			MOVWF	REG_Z+2

			MOVFW	DIVIDER
			MOVWF	REG_X
			MOVFW	DIVIDER+1
			MOVWF	REG_X+1
			MOVFW	DIVIDER+2
			MOVWF	REG_X+2

			CALL	M_DIV
					
			MOVFW	REG_Y
			ADDLW	0x30
			MOVWF	letter

			CALL	printDigit
			INCF 	pos
			
			BCF		Select,RS	; set display command mode
			MOVfW	pos
			CALL	send		; output it to display
			BSF		Select,RS

			MOVFW	DIVIDER
			MOVWF	REG_X
			MOVFW	DIVIDER+1
			MOVWF	REG_X+1
			MOVFW	DIVIDER+2
			MOVWF	REG_X+2
			CALL	M_MUL
			
			MOVFW	REG_Z
			MOVWF	REG_X
			MOVFW	REG_Z+1
			MOVWF	REG_X+1
			MOVFW	REG_Z+2
			MOVWF	REG_X+2

			MOVFW	REG_TEMP
			MOVWF	REG_Z
			MOVFW	REG_TEMP+1
			MOVWF	REG_Z+1
			MOVFW	REG_TEMP+2
			MOVWF	REG_Z+2

			CALL 	M_SUB

			MOVFW	REG_Z
			MOVWF	REG_TEMP
			MOVFW	REG_Z+1
			MOVWF	REG_TEMP+1
			MOVFW	REG_Z+2
			MOVWF	REG_TEMP+2

			MOVFW	DIVIDER
			MOVWF	REG_Z
			MOVFW	DIVIDER+1
			MOVWF	REG_Z+1
			MOVFW	DIVIDER+2
			MOVWF	REG_Z+2
			
			MOVLW   REG_X
		    CALL    M_CLR               ; clear register X
			
			MOVLW	0x0A
			MOVWF	REG_X

			CALL	M_DIV

			MOVFW	REG_Y
			MOVWF	DIVIDER

			MOVFW	REG_Y+1
			MOVWF	DIVIDER+1
		
			MOVFW	REG_Y+2
			MOVWF	DIVIDER+2
		
			DECF	counter
			GOTO	printLoop3
stopPrt3
			RETURN

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
M_CLR                           ; clear a register
    movwf   FSR
    movlw   PRECISION
    movwf   REG_COUNTER
M_CLR_loop
    clrf    INDF
    incf    FSR,f
    decf    REG_COUNTER,f
    btfss   STATUS,Z
    goto    M_CLR_loop
    return

M_INC                           ; increment a register
    movwf   FSR
    movlw   PRECISION
    movwf   REG_COUNTER
M_INC_loop
    incf    INDF,f
    btfss   STATUS,Z
    return
    incf    FSR,f
    decf    REG_COUNTER,f
    btfss   STATUS,Z
    goto    M_INC_loop
    return


M_DEC                           ; decrement a register
    movwf   FSR
    movlw   PRECISION
    movwf   REG_COUNTER
M_DEC_loop
    decf    INDF,f
    movlw   0xFF
    subwf   INDF,w
    btfss   STATUS,Z
    return
    incf    FSR,f
    decf    REG_COUNTER,f
    btfss   STATUS,Z
    goto    M_DEC_loop
    return


M_ROL                           ; rotate a register to the left
    movwf   FSR
    M_STOR_STATUS REG_STATUS
    clrf    REG_COUNTER
M_ROL_loop
    M_RETR_STATUS REG_STATUS
    rlf     INDF,f
    M_STOR_STATUS REG_STATUS
    incf    FSR,f
    incf    REG_COUNTER,f
    movlw   PRECISION
    subwf   REG_COUNTER,w
    btfss   STATUS,Z
    goto    M_ROL_loop
    return


M_ROR                           ; rotates a register to the right
    movwf   FSR
    movlw   PRECISION-1
    addwf   FSR,f
    M_STOR_STATUS REG_STATUS
    clrf    REG_COUNTER
M_ROR_loop
    M_RETR_STATUS REG_STATUS
    rrf     INDF,f
    M_STOR_STATUS REG_STATUS
    decf    FSR,f
    incf    REG_COUNTER,f
    movlw   PRECISION
    subwf   REG_COUNTER,w
    btfss   STATUS,Z
    goto    M_ROR_loop
    return


M_CMP                           ; Z <=> X -> STATUS(C,Z)
                                ; STATUS,C set if Z => X;
                                ; STATUS,Z set if Z == X
    clrf    REG_COUNTER
M_CMP_loop
    movf    REG_COUNTER,w
    sublw   REG_Z+PRECISION-1
    movwf   FSR
    movf    INDF,w
    movwf   REG_T1
    movf    REG_COUNTER,w
    sublw   REG_X+PRECISION-1
    movwf   FSR
    movf    INDF,w
    subwf   REG_T1,f
    btfss   STATUS,Z
    return
    incf    REG_COUNTER,f
    movlw   PRECISION
    subwf   REG_COUNTER,w
    btfss   STATUS,Z
    goto    M_CMP_loop
    return


M_ADD                           ; Z + X -> Z
    bcf     STATUS,C
    clrf    REG_STATUS
    clrf    REG_COUNTER
M_ADD_loop
    clrf    REG_T1
    btfsc   REG_STATUS,C
    incf    REG_T1,f
    clrf    REG_STATUS
    movlw   REG_X
    addwf   REG_COUNTER,w
    movwf   FSR
    movf    INDF,w
    addwf   REG_T1,f
    btfsc   STATUS,C
    bsf     REG_STATUS,C
    movlw   REG_Z
    addwf   REG_COUNTER,w
    movwf   FSR
    movf    INDF,w
    addwf   REG_T1,f
    btfsc   STATUS,C
    bsf     REG_STATUS,C
    movf    REG_T1,w
    movwf   INDF
    incf    REG_COUNTER,f
    movlw   PRECISION
    subwf   REG_COUNTER,w
    btfss   STATUS,Z
    goto    M_ADD_loop
    return


M_SUB                           ; Z - X -> Z
    clrf    REG_COUNTER
    bsf     REG_STATUS,C
M_SUB_loop
    bsf     REG_T2,C
    movlw   REG_Z
    addwf   REG_COUNTER,w
    movwf   FSR
    movf    INDF,w
    movwf   REG_T1
    movlw   REG_X
    addwf   REG_COUNTER,w
    movwf   FSR
    movf    INDF,w
    subwf   REG_T1,f
    btfss   STATUS,C
    bcf     REG_T2,C
    btfsc   REG_STATUS,C
    goto    M_SUB_no_carry
    movlw   0x01
    subwf   REG_T1,f
    btfss   STATUS,C
    bcf     REG_T2,C
M_SUB_no_carry
    movlw   REG_Z
    addwf   REG_COUNTER,w
    movwf   FSR
    movf    REG_T1,w
    movwf   INDF
    bsf     REG_STATUS,C
    btfss   REG_T2,C
    bcf     REG_STATUS,C
    incf    REG_COUNTER,f
    movlw   PRECISION
    subwf   REG_COUNTER,w
    btfss   STATUS,Z
    goto    M_SUB_loop
    btfss   REG_STATUS,C
    bcf     STATUS,C
    return


M_MUL                           ; X * Y -> Z
    movlw   REG_Z
    call    M_CLR
    movlw   PRECISION*8+1
    movwf   REG_ROT_COUNTER
M_MUL_loop
    decf    REG_ROT_COUNTER,f
    btfsc   STATUS,Z
    return
    btfsc   REG_Y,0
    call    M_ADD
    bcf     STATUS,C
    movlw   REG_Y
    call    M_ROR
    bcf     STATUS,C
    movlw   REG_X
    call    M_ROL
    goto    M_MUL_loop


M_DIV                           ; Z / X -> Y;  remainder -> Z
    movlw   REG_Y
    call    M_CLR
    movlw   PRECISION*8
    movwf   REG_ROT_COUNTER
M_DIV_rot_loop
    btfsc   REG_X+PRECISION-1,7
    goto    M_DIV_loop
    movlw   REG_X
    bcf     STATUS,C
    call    M_ROL
    decf    REG_ROT_COUNTER,f
    btfss   STATUS,Z
    goto    M_DIV_rot_loop
    bsf     STATUS,Z
    return
M_DIV_loop
    call    M_CMP
    M_STOR_STATUS REG_T2
    movlw   REG_Y
    call    M_ROL
    M_RETR_STATUS REG_T2
    btfsc   STATUS,C
    call    M_SUB
    bcf     STATUS,Z
    bcf     STATUS,C
    movlw   REG_X
    call    M_ROR
    incf    REG_ROT_COUNTER,f
    movlw   PRECISION*8+1
    subwf   REG_ROT_COUNTER,w
    btfss   STATUS,Z
    goto    M_DIV_loop
    return
		
END	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;