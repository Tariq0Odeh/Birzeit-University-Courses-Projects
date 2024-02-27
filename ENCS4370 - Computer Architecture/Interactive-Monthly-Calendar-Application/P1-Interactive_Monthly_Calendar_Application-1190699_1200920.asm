################# Informations #####################
# Title: Interactive Monthly Calendar Application		
# Author: Tariq Odeh - 1190699 | Wasim Atta - 1200920
# Date: 1 December, 2023
# Description: MIPS code for viewing, editing, and managing appointments within a monthly calendar. The application provide a user-friendly interface to interact with the calendar functionality, allowing them to add, edit, and view appointments for specific dates.
# Filename: P1-Interactive_Monthly_Calendar_Application-1190699_1200920
# File Name: calendar.txt

################# Data segment #####################
.data
    file_path:    		.asciiz "C:\\Users\\tariq\\OneDrive\\Desktop\\P1-Arch\\calendar.txt" 	# The path of input file 
    #file_path:    		.asciiz "C:\\Users\\wasim\\Desktop\\calendar.txt" 	# The path of input file 
    menu:  	  		.asciiz "*--------------------------------*\n*            {Main Menu}         *\n*--------------------------------*\n*  [1]--> View the calendar      *\n*  [2]--> View Statistics        *\n*  [3]--> Add a new appointment  *\n*  [4]--> Delete an appointment  *\n*  [0]--> Exit                   *\n*--------------------------------*\nEnter your choice: "
    view_menu:  	  	.asciiz "\n\n*-------------------------------------*\n*             {View Menu}             *\n*-------------------------------------*\n*   [1]--> Per day                    *\n*   [2]--> Per set of days            *\n*   [3]--> Given slot in a given day  *\n*   [0]--> Back                       *\n*-------------------------------------*\nEnter your choice: "
    view_per_day_str:  		.asciiz "\nEnter the day in range(1-31): "
    view_per_set_days_str: 	.asciiz "\nEnter a comma-separated list of integers (1,2,3,...): "
    invalid_day_str:   		.asciiz "\nInvalid day input. Please enter a day between 1 and 31.\n"
    char_L:       		.asciiz "L"
    char_M:       		.asciiz "M"
    char_O:       		.asciiz "O"
    char_H:       		.asciiz "H"
    space:       		.asciiz "   "
    number_of_L:		.asciiz "\nNumber of lectures (in hours): "
    number_of_OH:		.asciiz "\nnumber of OH (in hours): "
    number_of_M	:		.asciiz "\nNumber of Meetings (in hours): "
    The_average:		.asciiz "\nThe average lectures per day: "
    The_ratio:		        .asciiz "\nThe ratio between total number of hours reserved for L and the OH: "
    slot_start: 		.asciiz "\nEnter the slot start: "
    slot_end: 			.asciiz "\nEnter the slot end: "
    wrong_input: 		.asciiz "\nInvalid time input. Please enter a time between 8AM and 5PM. "
    slot_type: 			.asciiz "\n*-------------------*\n*   Type of slot    *\n*-------------------*\n*    [1]--> L       *\n*    [2]--> M       *\n*    [3]--> OH      *\n*-------------------*\nEnter your choice:"
    invalid_delete: 		.asciiz "Invalid time input. Please make sure that the appointment exists\n"
    type:			.asciiz "\nEnter th type of slot L,OH and M : "
    wrong_slot:			.asciiz "\nThe slot is wrong\n"
        
    print_buffer:  		.space 100         	# Buffer to store the day as a string
    newline: 			.asciiz "\n"
    day_buffer:        		.space 100         	# Buffer to store the day as a string
    input_string: 		.space 91      		# Maximum length of the input string (we calculated it) 
    calendar_mem: 		.space 2790     	# Memory space to store the calendar (we calculated it 31 × 10 × 9)
    END: 			.asciiz "E"		
        
################# Code segment #####################
.text
main:
    li $v0, 13       			# Open file - syscall 13
    la $a0, file_path			# Load address of file_path into $a0
    li $a1, 0        			# Read only mode
    syscall		 		# System call
    move $t0, $v0   	 		# Save file handle

    la $a1, calendar_mem 		# Load address of calendar_mem into register $a1
    li $v0, 14        			# Read file - syscall 14
    move $a0, $t0     			# File handle
    la $a2, 2790      			# Maximum number of bytes to read
    syscall				# System call

    li $v0, 16        			# Close file - syscall 16
    move $a0, $t0     			# File handle
    syscall				# System call

    li $v0, 4          			# Print string - syscall 4
    la $a0, menu     			# Load the menu
    syscall				# System call

    li $v0, 5          			# Read integer - syscall 5
    syscall				# System call
    move $t2, $v0     			# Save the user input

    beq $t2, 1, view_calendar 		# Check the user input, if it 1 that mean view_calendar
    beq $t2, 2, view_statistics		# Check the user input, if it 2 that mean view_statistics
    beq $t2, 3, add_appointment		# Check the user input, if it 3 that mean add_appointment
    beq $t2, 4, delete_appointment	# Check the user input, if it 4 that mean delete_appointment
    beq $t2, 0, exit_program		# Check the user input, if it 0 that mean exit_program
    j main 				# Check the user input, if it invalid that mean jump back to the menu

# -------------------------------------------------

view_calendar:
    li $v0, 4           		# Print string - syscall 4
    la $a0, view_menu   		# Load the view_menu
    syscall             		# System call

    li $v0, 5           		# Read integer - syscall 5
    syscall             		# System call
    move $t3, $v0       		# Save the user input

    beq $t3, 1, view_per_day            # Check the user input, if it's 1, that means view_per_day
    beq $t3, 2, view_per_set_of_days    # Check the user input, if it's 2, that means view_per_set_of_days
    beq $t3, 3, view_given_slot_in_day  # Check the user input, if it's 3, that means view_given_slot_in_day
    beq $t3, 0, back                    # Check the user input, if it's 0, that means back

# ++++++++++++++++

    view_per_day:    	
    	jal give_day			# Call give_day function to read the number of the day and save the day in buffer    
    	li $v0, 4         		# System call for print_str
    	la $a0, day_buffer   		# Load the address of the string into $a0
   	syscall          		# System call
    	j view_calendar
 
# ++++++++++++++++

    view_per_set_of_days:
      	li $v0, 4           		# Print string - syscall 4
    	la $a0, view_per_set_days_str	# Load address of input_prompt into $a0
    	syscall             		# System call
    	
        li $v0, 8           		# Read string - syscall 8
        la $a0, input_string		# Load address of input_string into $a0
        li $a1, 91  			# Maximum length of the input string
        syscall             		# System call

        li $t0, 0          		# Counter for indexing the string)
        li $t9, 0          		# Temporary register to 0

    	extract_loop:
        lb $t2, input_string($t0)   	# Load the current character from the string
        beqz $t2, end_extract		# Check if the character is null (end of string)
        li $t7, 48          		# ASCII code for '0'
        li $t4, 57          		# ASCII code for '9'
        li $t8, 44          		# ASCII code for ','
        blt $t2, $t7, p_day		# Check if it in range
        bgt $t2, $t4, p_day		# Check if it in range
        sub $t2, $t2, $t7   		# Convert ASCII to integer
        mul $t9, $t9, 10    		# Multiply previous result by 10
        add $t9, $t9, $t2   		# Add the digit to the result
        j continue_extract		# Continue extracting

	p_day:
	li $v0, 4             		# Print string - syscall 4
        la $a0, newline     		# Load the newline character
        syscall             		# System call
	
	li $t1, 1			# Flag to skip reader in give_day function						
	jal give_day			# Call give_day function to read the number of the day and save the day in buffer
	
	li $v0, 4         		# System call for print_str
    	la $a0, day_buffer   		# Load the address of the string into $a0
   	syscall          		# System call
   	
   	li $t9, 0          		# Reset the temporary register for the next integer
    	j continue_extract
	
    	continue_extract:
        addi $t0, $t0, 1         	# Increment the counter
        j extract_loop        		# Continue the loop

    	end_extract:
    	li $t1, 0		
    	j view_calendar			# Back to the calendar view
        
# ++++++++++++++++

    view_given_slot_in_day:
    	jal give_day			# Call give_day to store the day that want to search in
    	jal read_slot			# Call read_slot to read the slot time
    	
    	li $t9, 0          		# Reset the temporary register for the next integer	
    	li $t7, 1  			# Flag for start/end appointment who want to check
    	li $t8, 0			# Flag for start/end appointment
    	li $t5, 1			# Flag to make the output have good view
    	la $s0, day_buffer  		# Pointer to the day buffer

        li $v0, 11      		# Set the system call code for printing a character
	li $a0, '|'     		# Load the '|' to print
	syscall             		# System call
	li $v0, 11       		# System call for print_char
    	li $a0, 32       		# ASCII code for space
   	syscall          		# Make system call
	
    	search_loop:			# Search for the start of an appointment 
    	lb $t2, 0($s0)	 		# Load a character from the input buffer
    	beqz $t2, view_calendar 	# Check if we've reached the end of the string
    	beq $t2, ':', check_start_time  # Check for the start of an appointment
        addi $s0, $s0, 1  		# Continue to the next character
        j search_loop			# Continue the loop

    	check_start_time: 		# Reach the start of an appointment 
        addi $s0, $s0, 1 		# Move to the next character (skip the space)

   	extract:			# Extract the numbers from string
        lb $t2, 0($s0)	 		# Load a character from the input buffer
        beqz $t2, view_calendar		# Check if the character is null (end of string)
        li $t1, 48          		# ASCII code for '0'
        li $t4, 57          		# ASCII code for '9'
        blt $t2, $t1, pr_day		# Check if it in range
        bgt $t2, $t4, pr_day		# Check if it in range
        sub $t2, $t2, $t1   		# Convert ASCII to integer
        mul $t9, $t9, 10    		# Multiply previous result by 10
        add $t9, $t9, $t2   		# Add the digit to the result
        j continue_ext			# Continue extracting

        pr_day:				# Check the number and make it in formula
       	beq $t9, $zero, continue_ext	# Check if it number
	beq $t9, 1, add_12        	# Add 12 if the number is 1 to make the time in 24-formula	
	beq $t9, 2, add_12        	# Add 12 if the number is 2 to make the time in 24-formula
	beq $t9, 3, add_12        	# Add 12 if the number is 3 to make the time in 24-formula
	beq $t9, 4, add_12        	# Add 12 if the number is 4 to make the time in 24-formula
	beq $t9, 5, add_12        	# Add 12 if the number is 5 to make the time in 24-formula
	
	after_add12:
	beq $t7, 0, inv0_1		# Check the flag to know start/end appointment
	beq $t7, 1, inv1_0		# Check the flag to know start/end appointment
	
	bac_inv:
	beq $t8, $zero, greater		# Check the start of appointment
	j less				# Check the end of appointment
	
	inv1_0:				# Change the flag to know start/end appointment
	li $t7, 0			# inverter the start/end appointment flag
	j bac_inv
	
	inv0_1:				# Change the flag to know start/end appointment
	li $t7, 1			# inverter the start/end appointment flag
	j bac_inv
	
	greater:
       	bge $t9, $t0, gte_start		# Check if the number is larger than or equal than start slot
       	li $t9, 0 			# Reset the temporary register for the next integer	         		
	j continue_ext			# Skip this round
	
	less:
       	ble $t9, $t6, gte_end		# Check if the number is less than or equal than end slot
       	bne $t7, $zero, p_end		# Check start/end appointment
	j view_calendar			# Done worke - go back to the vire menu
	
	p_end:		
	li $v0, 1			# Set the system call code for printing a integer
       	move $a0, $t6			# Set the end of slot in $a0
    	syscall				# System call
        j good_p        		# Continue the loop
	
	continue_ext:
        addi $s0, $s0, 1         	# Increment the counter
        j extract        		# Continue the loop
       	
       	add_12:
	addi $t9, $t9, 12		# Add 12 to make the time in 24-formula
	j after_add12			# Go back to continue work
       	
       	gte_start:
       	beq $t7, $zero, is_zero		# Check start/end appointment
	li $t9, 0          		# Reset the temporary register for the next integer
        j continue_ext        
       	
       	is_zero:			
       	li $v0, 1			# Set the system call code for printing a integer
       	move $a0, $t0			# Set the start of slot in $a0
    	syscall				# System call
	li $t9, 0          		# Reset the temporary register for the next integer
	li $t8,1			# Set flag for start/end appointment to be end appointment
	li $v0, 11      		# Set the system call code for printing a character
	li $a0, '-'     		# Load the ASCII value of the character to print
	syscall				# System call
        j continue_ext       		# Continue the loop
       	
       	gte_end:
       	li $v0, 1			# Set the system call code for printing a integer
       	move $a0, $t9			# Set the integer that checked in $a0
    	syscall				# System call
    	li $t9, 0          		# Reset the temporary register for the next integer
    	beq $t5, 1, good_p		# To separate appointments
    	li $v0, 11      		# Set the system call code for printing a character
	li $a0, '-'     		# Load the ASCII value of the character to print
	syscall				# System call
    	
    	end_good_p:	
       	beq $t5, 0, to_1		# inverter the flag
	beq $t5, 1, to_0		# inverter the flag
        j continue_ext       		# Continue the loop
       	
       	good_p:	
       	 li $v0, 11       		# System call for print_char
    	li $a0, 32       		# ASCII code for space
    	syscall          		# Make system call
	lb $t3, 1($s0)			# Load the types of an appointments
	li $v0, 11      		# Set the system call code for printing a character
	move $a0, $t3     		# Load the ASCII value of the character to print
	syscall				# System call
    	beq $t3, 'O', print_next_char 	# If the char O than go to print H
	j delo

	print_next_char:		# Print char H after print H
    	lb $t3, 2($s0)			# Load the H char
    	li $v0, 11      		# Set the system call code for printing a character
    	move $a0, $t3     		# Load the ASCII value of the character to print
    	syscall				# System call
	j delo
       	
       	delo:
       	li $v0, 11       		# System call for print_char
    	li $a0, 32       		# ASCII code for space
   	syscall          		# Make system call
       	li $v0, 11      		# Set the system call code for printing a character
	li $a0, '|'     		# Load the ASCII value of the character to print
	syscall				# System call
	li $v0, 11       		# System call for print_char
    	li $a0, 32       		# ASCII code for space
   	syscall          		# Make system call
       	j end_good_p			# Go to make the output good view
       	
	to_0:
	li $t5, 0			# inverter the start/end appointment flag
	j continue_ext			# Go back to continue work
	
	to_1:
	li $t5, 1			# inverter the start/end appointment flag
	j continue_ext			# Go back to continue work
    
    	j view_calendar			# Go back to the view menu
    
# ++++++++++++++++

    back: 				# Go bake to the main manu
    	j main				# Jump to the amin

#  -------------------------------------------------

view_statistics:
    la $t3, calendar_mem 		# Load address of calendar_mem into register $t2
    li $s0, 0                      	# Counter for L in H
    li $s1, 0				# Counter for OH in H
    li $s2, 0				# Counter for M in H
	
    Statistics_loop:
    lb $t6, 0($t3)           		# Load a byte from the calendar
    lb $t0, char_L  		
    beq $t6, $t0,L_inc			# check if the char = "L" 
    lb $t0, char_O
    beq $t6, $t0,OH_inc			# check if the char = "O" 
    lb $t0, char_M
    beq $t6, $t0,M_inc			# check if the char = "M" 
    lb $t0, END
    beq $t6, $t0,END_COUNT		# check if calender is end
    continue:
    addi $t3, $t3, 1          		# Move to the next position in memory
    j Statistics_loop   		# Continue the loop

    L_inc:
    move $a0,$t3			# take copy of addrees of calender  to function
    jal get_slot			# call the function to find sum of hours
    add $s0 , $s0 , $v0 		# add the hours for the counter 
    j continue 				# back to the loop 
	
    OH_inc:
    move $a0,$t3			# take copy of addrees of calender  to function
    jal get_slot			# call the function to find sum of hours
    add $s1 , $s1, $v0 			# add the hours for the counter 
    j continue				# back to the loop 
	
    M_inc:
    move $a0,$t3			# take copy of addrees of calender  to function
    jal get_slot			# call the function to find sum of hours
    add $s2 , $s2, $v0 			# add the hours for the counter 
    j continue				# back to the loop 

    END_COUNT:
    li $v0, 4          			
    la $a0, number_of_L        		# load the text 		
    syscall					
    li $v0,1  		    		# print int
    move $a0, $s0 	            	# load number of H  
    syscall	
    li $v0, 4          			
    la $a0,newline   	    		# add new line  		
    syscall
   	
    li $v0, 4          			
    la $a0, number_of_OH        	# load the text 		
    syscall				
    li $v0,1  		    		# print int
    move $a0, $s1 	            	# load number of H  
    syscall	
    li $v0, 4          			
    la $a0,newline   	    		# add new line  		
    syscall	
   	 
    li $v0, 4          			
    la $a0, number_of_M        		# load the text 		
    syscall				
    li $v0,1  		    		# print int
    move $a0, $s2 	            	# load number of H  
    syscall	
    li $v0, 4          			
    la $a0,newline   	    		# add new line  		
    syscall
	
    li $s5 ,0                  		# s4 to save the ratio
    li $t1,31 
    mtc1 $s0, $f0  
    cvt.s.w $f0, $f0 	    		# Convert the integer to a float in $f0                        	
    mtc1 $t1, $f1 
    cvt.s.w $f1, $f1	    		# Convert the integer to a float in $f1                       
    div.s $f12, $f0, $f1  
    	
    li $v0, 4          			
    la $a0, The_average       		# load the text 		
    syscall				
    li $v0, 2 
    syscall	
    li $v0, 4          			
    la $a0,newline   	    		# add new line  		
    syscall

    mtc1 $s0, $f0  
    cvt.s.w $f0, $f0 	    		# Convert the integer to a float in $f0                        	
    mtc1 $s1, $f1 
    cvt.s.w $f1, $f1	    		# Convert the integer to a float in $f1                      
    div.s $f12, $f0, $f1  
    	
    li $v0, 4          			
    la $a0, The_ratio      		# load the text 		
    syscall				
    li $v0, 2 
    syscall	
    li $v0, 4          			
    la $a0,newline   	    		# add new line  		
    syscall
   	 
    j main     				# Jump back to the menu
#  -------------------------------------------------    

add_appointment:
    li $t3, 0          			# Initialize loop counter
    la $t5, print_buffer 		# Load the address of print_buffer 
    clear_2p:				# Clear the print_buffer 
    sb $zero, 0($t5)     		# Store zero in the current byte of print_buffer 
    addi $t3, $t3, 1   			# Increment loop counter
    addi $t5, $t5, 1   			# Increment address
    bne $t3, 100, clear_2p  		# Branch to clear_loop if not all bytes are cleared

    li $a1, 1				# Flag to add \n in the end of print_buffer in give_day function
    jal give_day			# Call give_day function to get the day that we want to work on it
    li $v0, 4          			
    la $a0,newline   	    		# add new line  		
    syscall				# System call
    la $t0, day_buffer  		# Pointer to the day buffer
    print_loop:				# Search for the start of an appointment 
    lb $t3, 0($t0)	 		# Load a character from the input buffer
    beq $t3, 10  ,next_555       	# check if buffer end
    li $v0 ,11				# load 11 too print char 
    move $a0,$t3			# move the byte to a0 to print
    syscall    	   	    		# print it   	   	   	    	
    addi $t0, $t0, 1  			# Continue to the next character
    j print_loop			# Continue the loop
    	
    next_555:				# now the print is end
    jal read_slot			# Call read_slot function to read the start/end of slot
    move $a1,$t0			# save the slot begin from user to a1 
    move $a2,$t6			# save the slot end from user to a1 
  	 
    li $v0, 4   			# ask user which tupe he will add      			
    la $a0,type      	 		# load the text 		
    syscall
    li $v0, 12 				# read char fro muser 
    syscall
    move $a3,$v0			# save the tupe in a3

    li $t4 , 6  			#load 6 to $t2 to check if any number from 1 to 5 
    blt $a1,$t4 ,Add11      		# check if the first number 1-5 then add 12 
    j else_11               		# if not go to else 
    
    Add11:
    addi $a1,$a1,12 			# add 12 to the number
	
    else_11:
    blt $a2,$t4 ,Add22   	        # check the scecond number
    j else_22
    					# if not go to else_2
    Add22:
    addi $a2,$a2,12        		# add 12 to the number
	
    else_22: 				# not the number is ready 
    lb $t6, char_L
    beq $t6, $a3, true			# check if the char = "L" 
    lb $t6, char_M
    beq $t6, $a3, true			# check if the char = "M" 
    lb $t6, char_O
    beq $t6, $a3, true			# check if the char = "OH" 
       					# Convert small letter to capital letter
    li $t3, 32          		# Difference between small and capital letters in ASCII
    sub $a3, $a3, $t3    		# Convert small letter to capital letter
          	
    true:
    move $s0,$a1   			# move the time slot and type to register s0-1-2 
    move $s1,$a2
    move $s2,$a3
    la $t0, day_buffer  		# Pointer to the day buffer

    search_loop1:			# Search for the start of an appointment 
    lb $t3, 0($t0)	 		# Load a character from the input buffer
    beq $t3 ,10,next_55 	
    					# check if the char any letter of types then go to get-slot1
    lb  $t4 ,char_L			# load L int o t4
    beq $t3 ,$t4 ,get_slot1		
    lb  $t4 ,char_M			# load M int o t4
    beq $t3 ,$t4 ,get_slot1
    lb  $t4 ,char_O			# load O int o t4
    beq $t3 ,$t4 ,get_slot1
    	
    j skip_11				# if the char have not cahr then skip the the function			
    	
    get_slot1:			
    move $a0,$t0 			# take copy of addres to function
    jal get_slot			# call function get_slot
    j test_slot				# test now the slopt if true or not 	
    	 
    END_test:   	   	    	   	   	    	
    skip_11:    	   	    	   	   	    	   	   	   	   	    	
    addi $t0, $t0, 1  			# Continue to the next character
    j search_loop1			# Continue the loop

    test_slot:				# s0 ,s1 ,a1,a2				
    bge $s0 ,$a1 ,and_1  		# if (s0 >= a1 && s0 < a2) || (s1 > a1 && s1 <= a2)
    j or_1
    and_1:
    blt $s0 ,$a2 ,invaild_1
    or_1:
    bgt $s1,$a1, t2
    j or_2
    t2:
    ble $s1 ,$a2 ,invaild_1
    or_2:
    j END_test				# if test go good end it and back to loop
    j next_55
    invaild_1:				# if the slot is wrong end loop
    li $v0, 4     			# print to user message the slot is wrong     			
    la $a0,wrong_slot  	    	 		
    syscall
    j main				# wrong slot so back to main
    
    next_55:
    la $t0, day_buffer  		# Pointer to the day buffer
    li $t1,0				# counter for the print buffer
    li $t2,0				# flag used in loop			
    li $t5,0				# flag used in loop
    li $s7,1				# flag used in loop
    li $s6, 0				# counter

    lb $t3, 0($t0)	 		# Load a character from the input buffer
    sb $t3 , print_buffer($t1)      	# store the byte in print buffer
    addi $t1 ,$t1, 1			# Continue to the next address	    	   	   	    	   	   	   	   	    	
    addi $t0, $t0, 1  			# Continue to the next address
    lb $t3, 0($t0)	 		# Load a character from the input buffer
    sb $t3 , print_buffer($t1)		# Load a character from the input buffer
    addi $t1 ,$t1, 1	    		# Continue to the next address  	   	    	   	   	   	   	    	
    addi $t0, $t0, 1  			# Continue to the next character
           	   	 
    add_loop:				# Search for the start of an appointment 
    lb $t3, 0($t0)	 		# Load a character from the input buffer
    addi $s6, $s6, 1			# counter used after loop
    beq $t2 ,1, dont_test		# if teh flag t2 is 1 dont test again
    beq $t5 ,1 ,reset_t5		# if teh flag t5 is 1 go to reset_t5
    j test_place			# go to test place of the new slot
    dont_test:				# to skip test after end 
    next_loop:				# countine the loop
    beq $t3,10 ,next_5555		# check if teh day slots is end 
    sb $t3 , print_buffer($t1)		# store teh byte from day buffer t o print buffer
    addi $t1 ,$t1, 1			# Continue to the next charactercharacter	    	   	   	    	   	   	   	   	    	
    addi $t0, $t0, 1  			# Continue to the next charactercharacter
    j add_loop				# Continue the loop
        
    reset_t5: 				# reset the t5 
    li $t5 ,0				# make t5=0 again
    j next_loop				# go back to loop

    reset_t3 :				# rseet t3 make t3 have it old vlaue before begin the test
    move $t3 ,$t6			# old value saved in t6
    j next_loop				# back to loop
	
    test_place:				# begin test palce function
    move $t6 ,$t3			# first take copy of t3 to be sure his vlaue will not lost
 					# Check if $t3 contains a numeric character (ASCII '0' to '9')
    li $t7, '0'  			# ASCII code for '0'
    li $t8, '9'  			# ASCII code for '9'
					# Check if $t3 is within the ASCII range of numeric characters
    blt $t3, $t7, reset_t3 		# Branch if $t3 is less than '0'
    bgt $t3, $t8, reset_t3 		# Branch if $t3 is greater than '9'
    
					# If the execution reaches here, $t3 contains a numeric character
					# Handle the case where $t3 is a numeric character
					# $t3 contains an integer
    subi $t3,$t3 ,48			# covert from ascii to dec
    move $t9 ,$t3 			# save the value in t3 after convert to t9 	
    addi $t0, $t0, 1  			# Continue to the next character
    lb $t3, 0($t0)	 	        # load next char in day buffer to t3
    subi $t0, $t0, 1  			# Continue to the next character		
        				# Check if $t3 is within the ASCII range of numeric characters
    blt $t3, $t7, test55		# Branch if $t3 is less than '0'	
    bgt $t3, $t8, test55		# Branch if $t3 is greater than '9'
    li $t5 , 1				# if next byte is also number make t5 falg is 1 
    mul $t9,$t9,10			# multi t9 by 10
    subi $t3,$t3 ,48			# covert from ascii to dec	
    add $t9,$t9,$t3			# make the two didgit one number again
	
    test55:
    move $t3,$t9			# but the new value in t3
    li $t4 , 6  			# load 6 to $t2 to check if any number from 1 to 5 
	
    blt $t3,$t4 ,Add111           	# check if the first number 1-5 then add 12 
    j else_111               		# if not go to else 
    Add111:
    addi $t3,$t3,12 			# add 12 to the number
  
    else_111:
    bgt $t3,$s0, write_temp		# check if this the place to add the new slot	
    j reset_t3 				# reset t3 to his orginal value after end test
    write_temp:				# here the wite palce for new slot 
    li $t2,1				# make the t2 flag 1 to not test again for  place
    li $s7,0				# make the t7 flag 1 
    	
    bgt $s0,12, sub_1_12		# check if type if begin slot after 12 
    j  check_s1				# if not go to check s2 time of end slot
    sub_1_12:				# if time after 12 
    subi $s0,$s0,12			# sub 12  due to we add 12 previse
    check_s1:				# check the end time of slot
    bgt $s1,12, sub_2_12		# same teet if after 12 or not 
    j end_check				# if not go to end check
    sub_2_12:				# if yes after 12 
    subi $s1,$s1,12			# sub 12 again
    end_check:				# end not th slot time not 24h type 
	
    bgt $s0 , 9 , put_2_D 		# check if begin slot time is two digit
    					# if not write it in buffer
    addi $s0, $s0, '0'   		# Convert the integer to ASCII representation
    sb $s0 , print_buffer($t1)		# store the time to buffer
    addi $t1 ,$t1 ,1			# make teh  addrees to nesxt postion
	
    j dont_put_2_D 			# if number not two digits kip
    put_2_D  :				# if number  two 
    li $s4,10				# laod 10 to s4
    div $s0,$s4				# div s0 by 10
	
    mflo $s0				# get first digit to s0
    addi $s0, $s0, '0'    		# Convert the integer to ASCII representation
    sb $s0 , print_buffer($t1)		# store the time to buffer
    addi $t1 ,$t1 ,1			# make teh  addrees to nesxt postion
	
    mfhi $s0				# get seconf digit to s0
    addi $s0, $s0, '0'   		# Convert the integer to ASCII representation
    sb $s0 , print_buffer($t1)		# store the time to buffer
    addi $t1 ,$t1 ,1			# make teh  addrees to nesxt postion
	
    dont_put_2_D :
    li $t8 , 45				# put teh - to t8
    sb $t8 , print_buffer($t1)		# put the -  to bufeer
    addi $t1 ,$t1 ,1			# make teh  addrees to nesxt postion
	
    bgt $s1 , 9 , put_2_D1		# check if end slot time is two digit
    addi $s1, $s1, '0'    		# Convert the integer to ASCII representation
    sb $s1 , print_buffer($t1)		# store the time to buffer
    addi $t1 ,$t1 ,1			# make teh  addrees to nesxt postion
    j dont_put_2_D1 			#if number not two digits skip
    
    put_2_D1  :
    li $s4,10				# laod 10 to s4
    div $s1,$s4				# div s0 by 10
    mflo $s1				# get first digit to s1
    addi $s1, $s1, '0'    		# Convert the integer to ASCII representation
    sb $s1 , print_buffer($t1)		# store the time to buffer
    addi $t1 ,$t1 ,1			# make teh  addrees to nesxt postion
    mfhi $s1				# get seconf digit to s1
    addi $s1, $s1, '0'    		# Convert the integer to ASCII representation
    sb $s1 , print_buffer($t1)		# store the time to buffer	
    addi $t1 ,$t1 ,1			# make the  addrees to nesxt postion
	
    dont_put_2_D1 :
    li $t8 , 32				# load space to t8
    sb $t8 , print_buffer($t1)		# store the space to buffer
    addi $t1 ,$t1 ,1			# make the  addrees to nesxt postion
	
    sb $s2 , print_buffer($t1)		# store the tupe of slot in buffer 
    addi $t1 ,$t1 ,1			# make the  addrees to nesxt postion
    lb  $t8 ,char_O			# load char o to t8
    beq $s2 ,$t8 ,Add_H			# check if the letter if 
    j not_add_H				# if not go on 
    
    Add_H:				# if the cahe if o
    lb  $t8 ,char_H			# laod the char h to t8
    sb $t8 , print_buffer($t1)		# store h to buffer
    addi $t1 ,$t1 ,1			# make the  addrees to nesxt postion
	
    not_add_H:			
    li $t8 , 44				# laod , to t8
    sb $t8 , print_buffer($t1)		# store , to buffer
    addi $t1 ,$t1 ,1			# make the  addrees to nesxt postion
    li $t8 , 32				# laod space to t8
    sb $t8 , print_buffer($t1)		# store space to buffer
    addi $t1 ,$t1 ,1			# make the  addrees to nesxt postion	
    move $t3 ,$t6			# make  t3  have his orginal value before change 
    j next_loop				# back to loop	

    next_5555:
    beq $s7,1 add_slot			# check if slot added to buffer or not
    j slot_added			# if slot added skip
    
    add_slot:				# if not add it 
    addi $t1 ,$t1 ,-1			# first back t oprevise postion before new line
    blt $s6, 4, skip_now		# check if slot postin is in not emity day
    li $t8 , 44				# not emity day so add , to t8
    sb $t8 , print_buffer($t1)		# store , to buffer
    addi $t1 ,$t1 ,1			# make the  addrees to nesxt postion
    
    skip_now:
    li $t8 , 32				# laod space to t8 
    sb $t8 , print_buffer($t1)		# store space to buffer
    addi $t1 ,$t1 ,1			# make the  addrees to nesxt postion
    bgt $s0,12, sub_1_120		# here same code from line 680 to 750 so no need to commant
    j  check_s10
   
     sub_1_120:
    subi $s0,$s0,12
    check_s10:
    bgt $s1,12, sub_2_120
    j end_check0
    sub_2_120:
    subi $s1,$s1,12
    end_check0:
    bgt $s0 , 9 , put_2_D0 
    addi $s0, $s0, '0'    
    sb $s0 , print_buffer($t1)
    addi $t1 ,$t1 ,1
    j dont_put_2_D0 
    
    put_2_D0  :
    li $s4,10
    div $s0,$s4
    mflo $s0
    addi $s0, $s0, '0'    
    sb $s0 , print_buffer($t1)
    addi $t1 ,$t1 ,1
    mfhi $s0
    addi $s0, $s0, '0'    
    sb $s0 , print_buffer($t1)
    addi $t1 ,$t1 ,1
	
    dont_put_2_D0 :	
    li $t8 , 45
    sb $t8 , print_buffer($t1)
    addi $t1 ,$t1 ,1
    bgt $s1 , 9 , put_2_D10
    addi $s1, $s1, '0'    
    sb $s1 , print_buffer($t1)
    addi $t1 ,$t1 ,1
    j dont_put_2_D10 
   
    put_2_D10  :
    li $s4,10
    div $s1,$s4
    mflo $s1
    addi $s1, $s1, '0'    
    sb $s1 , print_buffer($t1)
    addi $t1 ,$t1 ,1
    mfhi $s1
    addi $s1, $s1, '0'    
    sb $s1 , print_buffer($t1)
    addi $t1 ,$t1 ,1
	
    dont_put_2_D10 :
    li $t8 , 32
    sb $t8 , print_buffer($t1)
    addi $t1 ,$t1 ,1
    sb $s2 , print_buffer($t1)
    addi $t1 ,$t1 ,1
    lb  $t8 ,char_O
    beq $s2 ,$t8 ,Add_H0
    j not_add_H0
    
    Add_H0:
    lb  $t8 ,char_H
    sb $t8 , print_buffer($t1)
    addi $t1 ,$t1 ,1
	
    not_add_H0:
    li $t8 , 32
    sb $t8 , print_buffer($t1)
    addi $t1 ,$t1 ,1
					# end of repeted code
    slot_added:
    li $t0, 0x0A			# Add new line in the last
    sb $t0, print_buffer($t1)       	# Store byte to print_buffer

    next_54:
    li,$v0,4				# load 4 to v0 to print string
    la $a0,newline			# laod new line 
    syscall				# print it
    la $a0, print_buffer 		# Load the print_buffer address to print
    li $v0, 4     			# System call number for printing a string
    syscall				# System call
    jal write_file			# Call write_file function to write on calendar.txt file
    j main

#  -------------------------------------------------

delete_appointment:
    li $t3, 0          			# Initialize loop counter
    la $t5, print_buffer 		# Load the address of print_buffer 
    clear_lp:				# Clear the print_buffer 
    sb $zero, 0($t5)     		# Store zero in the current byte of print_buffer 
    addi $t3, $t3, 1   			# Increment loop counter
    addi $t5, $t5, 1   			# Increment address
    bne $t3, 100, clear_lp  		# Branch to clear_loop if not all bytes are cleared
    
    li $a1, 1				# Flag to add \n in the end of print_buffer in give_day function
    jal give_day			# Call give_day function to get the day that we want to work on it
    jal read_slot			# Call read_slot function to read the start/end of slot

    li $v0, 4      			# System call number for printing a string
    la $a0, slot_type 			# Load the address of the prompt string
    syscall				# System call
    li $v0, 5               		# System call number for reading an integer
    syscall				# System call
    move $a1, $v0           		# Move the read integer to register $a1

    la $a0, day_buffer			# Load the address of day_buffer
    beq $a1, 1, load_L			# Check the type of slot 1 mean L
    beq $a1, 2, load_M			# Check the type of slot 2 mean M
    beq $a1, 3, load_OH			# Check the type of slot 3 mean OH
    
    load_L:
    li $t1, 'L'    			# Load the ASCII code for char L into register $t1
    j search_type			# Go to start search to the type of slot
    load_M:
    li $t1, 'M'     			# Load the ASCII code for char M into register $t1
    j search_type			# Go to start search to the type of slot
    load_OH:
    li $t1, 'O'     			# Load the ASCII code for char O into register $t1
    j search_type			# Go to start search to the type of slot	   		
    
    search_char:
    addi $a0, $a0, 1	    		# Move to the next character in the string day_buffer
    
    search_type:			# Loop to search on type of slot
    lb $t2, 0($a0)			# Load the current character from the string into $t2
    beq $t2, 10, not_found   		# If the current character is new line terminator, exit the loop
    beq $t2, $t1, found         	# If the current character is the target character, exit the loop
    addi $a0, $a0, 1	    		# Move to the next character in the string
    j search_type			# Continue search

    found:     				# The target character was found, store the index in $a0 
    jal get_slot			# Call get_slot to get the range of appointment
    j check_process			# Go to check if the slot is avaliable for this appointment
    
    check_process:
    bge $a2, $t6, next_p		# If the end of slot is larger than start of appointment, go to next_p
    j search_char			# If the end of slot is not larger that start of appointment, skip

    next_p:
    ble $a1, $t0, find_space		# If the end of slot is smaller that start of appointment, go to find_space (Beginning of appointment)
    j search_char			# If the end of slot is not smaller than start of appointment, skip
    
    find_space:
    li $t3, 0                 		# Counter for spaces
    move $t1, $a0             		# Copy the address to $t1 for iteration

    find_second_space:
    addi $t1, $t1, -1          		# Move to the previous character
    lb $t2, 0($t1)             		# Load the current character
    beq $t2, 32, found_space    	# Check if the current character is a space
    j find_second_space         	# Continue the loop

    found_space:
    addi $t3, $t3, 1           		# Increment the space counter
    bne $t3, 2, find_second_space  	# If it's not the second space, continue the loop
    j next_dp				# Go to deal with deletion
    
    next_dp:
    beq $a2, $t6, next_start		# If the end of appointment equal the end of slot, go to next_start
    j edit_slot				# If not go to edit the slot based on deletion
    
    next_start:
    beq $a1, $t0, remove_slot		# If the start of appointment equal the start of slot
    move $t6, $a1			# Move the start of new appointment to $t6
    move $a2, $t0			# Move the end of new appointment to $t6
    j edit_slot				# If not go to edit the slot based on deletion
    
    edit_slot:
    la $t3, print_buffer		# Load the addrees of print_buffer
    la $t4, day_buffer			# Load the addrees of day_buffer
    addi $a0, $a0, -1			# Go to previous char
    
    c_loop: 
    lb $t5, 0($t4)           		# Load byte from day_buffer
    beq $t5, 10, d_done			# Check if reach new line
    beq $t4, $t1, j_edit    		# Check if reach the start of appointment we want
    sb $t5, 0($t3)           		# Store byte to print_buffer
    addi $t4, $t4, 1         		# Increment source pointer
    addi $t3, $t3, 1         		# Increment destination pointer
    j c_loop              		# Jump to the end of the loop

    j_edit:	
    li $t9, 45				# Load the '-' ACII
    li $t8, 32				# Load the space ACII
    sb $t8, 0($t3)           		# Store byte to print_buffer
    addi $t3, $t3, 1			# Go to next char
    bgt $t6, 12, to_time1		# Check if the $t6 in 24-Hour formula 
    beq $t6, 10, spi_deal_1		# Check if the time have two digits
    beq $t6, 11, spi_deal_1		# Check if the time have two digits
    beq $t6, 12, spi_deal_1		# Check if the time have two digits
    addi $t6, $t6, 48 			# Convert to ASCII code	
    sb $t6, 0($t3)           		# Store byte to print_buffer
    addi $t3, $t3, 1         		# Increment destination pointer
   
    after_to_time:
    sb $t9, 0($t3)           		# Store byte to print_buffer
    addi $t3, $t3, 1         		# Increment destination pointer
    bgt $a2, 12, to_time2		# Check if the $a2 in 24-Hour formula 
    beq $a2, 10, spi_deal_2		# Check if the time have two digits
    beq $a2, 11, spi_deal_2		# Check if the time have two digits
    beq $a2, 12, spi_deal_2		# Check if the time have two digits
    addi $a2, $a2, 48 			# Convert to ASCII code		
    sb $a2, 0($t3)           		# Store byte to print_buffer
    addi $t3, $t3, 1         		# Increment destination pointer
    move $t4, $a0			# Save the new location in $t4
    j c_loop				# Go back to loop
    
    to_time1:
    subi $t6, $t6, 12			# Convert time to AM/PM formula 
    addi $t6, $t6, 48 			# Convert to ASCII code	
    sb $t6, 0($t3)           		# Store byte to print_buffer
    addi $t3, $t3, 1         		# Increment destination pointer
    j after_to_time			# After convert time to AM/PM formula 

    to_time2:
    subi $a2, $a2, 12			# Convert time to AM/PM formula
    addi $a2, $a2, 48 			# Convert to ASCII code		
    sb $a2, 0($t3)           		# Store byte to print_buffer
    addi $t3, $t3, 1         		# Increment destination pointer
    move $t4, $a0			# Save the new location in $t4
    j c_loop				# After convert time to AM/PM formula 

    spi_deal_1:
    li $t1 ,10				# Load the 10 to $t1
    div $t6, $t1			# Divide $a0 by $t0
    mflo $t5 				# Move the quotient to $t1 (first digit)
    mfhi $t7 				# Move the remainder to $t2 (second digit)
    addi $t5, $t5, 48 			# Add 48 to $t1 to get the char value of '4'
    addi $t7, $t7, 48 			# Add 48 to $t2 to get the char value of '2'
    sb $t5, 0($t3)           		# Store byte to print_buffer
    addi $t3, $t3, 1			# Go to the next char
    sb $t7, 0($t3)           		# Store byte to print_buffer
    addi $t3, $t3, 1			# Go to the next char
    j after_to_time
    
    spi_deal_2:
    li $t1 ,10				# Load the 10 to $t1
    div $a2, $t1			# Divide $a0 by $t0
    mflo $t5 				# Move the quotient to $t1 (first digit)
    mfhi $t7 				# Move the remainder to $t2 (second digit)
    addi $t5, $t5, 48 			# Add 48 to $t1 to get the char value of '4'
    addi $t7, $t7, 48 			# Add 48 to $t2 to get the char value of '2'
    sb $t5, 0($t3)           		# Store byte to print_buffer
    addi $t3, $t3, 1			# Go to the next char
    sb $t7, 0($t3)           		# Store byte to print_buffer
    addi $t3, $t3, 1			# Go to the next char
    move $t4, $a0			# Save the new location in $t4
    j c_loop	

    remove_slot:
    la $t3, print_buffer		# Load the address of print_buffer 
    la $t4, day_buffer			# Load the address of day_buffer
    lb $t5, 0($a0)			# Load the type of slot
    li $t8, 'O'				# Load the 'O' on $t8		
    beq $t5,$t8, add_more		# Check if the type of slot is OH
    addi $a0 , $a0, 2			# Increment the addrees by two to deal with OH
    
    copy_loop: 
    lb $t5, 0($t4)           		# Load byte from day_buffer
    beq $t5, 10, d_done			# Check if reach new line
    beq $t4, $t1, j_delete    		# Check if $t1 is not zero
    sb $t5, 0($t3)           		# Store byte to print_buffer
    addi $t4, $t4, 1         		# Increment source pointer
    addi $t3, $t3, 1         		# Increment destination pointer
    j copy_loop               		# Jump to the end of the loop

    add_more:	
    addi $a0 , $a0, 3			# To deal with OH case
    j copy_loop				# Go bake to loop

    j_delete:
    move $t4, $a0			# Save the new location in $t4
    j copy_loop				# Go bake to loop

    d_done:
    li $t0, 0x0A			# Add new line in the last
    sb $t0, 0($t3)           		# Store byte to print_buffer
    la $a0, print_buffer 		# Load the print_buffer address to print
    li $v0, 4     			# System call number for printing a string
    syscall				# System call
    jal write_file			# Call write_file function to write on calendar.txt file
    j main    				# Jump back to the menu

    not_found:
    la $a0, invalid_delete		# Print invalid_delete in case the input is not valid
    li $v0, 4     			# System call number for printing a string
    syscall				# System call
    j main    				# Jump back to the menu
    
#  -------------------------------------------------

write_file:
    la $t8, print_buffer		# Load print_buffer to $t8 to use it in write_file function
    lb $t0, 0($t8)			# Load the first character of the input_buffer into $t0
    li $t9, 0  				# Initialize $t1 to store the result (integer)
    li $t4, 1				# Counter of new lines to know the end of file
    
    read_digit: 			# Loop to process each character until a non-digit ':' is encountered
    blt $t0, 0x30, end_read_digit   	# If less than '0', exit loop
    bgt $t0, 0x39, end_read_digit   	# If greater than '9', exit loop
    sub $t0, $t0, 0x30             	# Convert ASCII to integer
    mul $t9, $t9, 10               	# Multiply current result by 10
    add $t9, $t9, $t0              	# Add the current digit to result
    addi $t8, $t8, 1        		# Move to the next character in the input_buffer
    lb $t0, 0($t8)			# Load the char in $t8 address
    j read_digit 	        	# Repeat the loop

    end_read_digit:
    li $v0, 13       			# Open file - syscall 13
    la $a0, file_path			# Load address of file_path into $a0
    li $a1, 1        			# Open the file for writing (O_WRONLY)
    li $a2, 0          			# Set the file mode to 0
    syscall		 		# System call
    move $s0, $v0      			# Save the file descriptor in $s0
    la $t3, calendar_mem 		# Load address of calendar_mem into register $t3
    li $t5, 0           		# Initialize newline counter for edit lines
    la $t8, print_buffer		# Load print_buffer to $t8
    beq $t9, 1, skipp			# Check if the input is first day
    subi $t7, $t9, 2    		# subtract 2 from user input to track the day want to print
  	
    skipp:				# In case the inpt is first day
    beq  $t9, 1, second_line		# Check if the input is first day		
    	
    cale_lop:        			# Loop to count newlines
    lb $t6, 0($t3)     			# Load a byte from the calendar
    li $v0, 15        			# syscall 15 (write to file)
    move $a0, $s0     			# file descriptor
    move $a1, $t3     			# character to write
    li $a2, 1         			# number of characters to write
    syscall		 		# System call
    beq $t6, 10, ad_lines  		# Check if the current character is a newline
    j con_lop   			# Continue the loop

    ad_lines:
    beq $t5, $t7, next_line 		# Check if reached the day want to print
    addi $t5, $t5, 1  			# Increment the newline counter of day
    addi $t4, $t4, 1  			# Increment the newline counter of file
    j con_lop   			# Continue the loop

    con_lop:
    addi $t3, $t3, 1  			# Move to the next position in memory
    j cale_lop   			# Continue the loop
    
    next_line:
    addi $t3, $t3, 1  			# Move to the next position in memory
    lb $t6, 0($t3)    			# Load a byte from the calendar
    beq $t6, 10, n_line		        # Check if the current character is a newline
    j next_line
    
    n_line:
    addi $t4, $t4, 1  			# Increment the newline counter of file
    
    write_line:    			# Write the contents of a buffer to a file until a newline character is encountered
    lb $t6, 0($t8)              	# Load a byte from the buffer
    li $v0, 15                   	# syscall 15 (write to file)
    move $a0, $s0                	# file descriptor
    move $a1, $t8                	# character to write
    li $a2, 1                    	# number of characters to write
    syscall		 		# System call
    beq $t6, 10, last_write      	# Check if the current character is a newline
    addi $t8, $t8, 1             	# Increment the buffer index
    j write_line

    last_write: 			# After encountering a newline character, move to the next position in memory
    addi $t3, $t3, 1             	# Move to the next position in memory
    lb $t6, 0($t3)               	# Load a byte from the calendar
    li $v0, 15                   	# syscall 15 (write to file)
    move $a0, $s0                	# file descriptor
    move $a1, $t3                	# character to write
    li $a2, 1                    	# number of characters to write
    syscall		 		# System call
    beq $t6, 10, dn_take         	# Check if the current character is a newline
    j last_write                 	# Continue the loop

    second_line:
    addi $t3, $t3, 1             	# Move to the next position in memory
    lb $t6, 0($t3)               	# Load a byte from the calendar
    li $t4, 1				# Make value of 4t4 is 1
    beq $t6, 10, take_f_line      	# Check if the current character is a newline
    j second_line

    take_f_line:			# After encountering a newline character, move to the next position in memory
    lb $t6, 0($t8)               	# Load a byte from the buffer
    li $v0, 15                   	# syscall 15 (write to file)
    move $a0, $s0                	# file descriptor
    move $a1, $t8                	# character to write
    li $a2, 1                    	# number of characters to write
    syscall		 		# System call
    beq $t6, 10, last_write      	# Check if the current character is a newline
    addi $t8, $t8, 1             	# Increment the buffer index
    j take_f_line

    dn_take:				# Check if 31 lines have been processed, if not, continue the loop
    addi $t4, $t4, 1			# Increment the newline counter of file
    beq $t4, 31, dn_write         	# If 31 lines have been processed, proceed to file closing
    j last_write                  	# Continue the loop

    dn_write:			  	# Close the file and return
    li $v0, 16                    	# Close file - syscall 16
    move $a0, $s0                 	# File handle
    syscall		 		# System call
    jr $ra                        	# Return

#  -------------------------------------------------

give_day:
    li $t3, 0          			# Initialize loop counter
    la $t5, day_buffer 			# Load the base address of day_buffer
    clear_loop:
    sb $zero, 0($t5)     		# Store zero in the current byte of day_buffer
    addi $t3, $t3, 1   			# Increment loop counter
    addi $t5, $t5, 1   			# Increment address
    bne $t3, 100, clear_loop  		# Branch to clear_loop if not all bytes are cleared
    
    beq $t1, 1, skip_read		# Check if the call from set of days option
    
    li $v0, 4           		# Print string - syscall 4
    la $a0, view_per_day_str		# Load address of view_per_day_str into $a0
    syscall             		# System call

    li $v0, 5          			# Read integer - syscall 5
    syscall            			# System call
    move $t9, $v0       		# Save the user input
    
    skip_read:		
    la $t3, calendar_mem 		# Load address of calendar_mem into register $t3
    li $t5, 0           		# Initialize newline counter
    li $t8, 0				# Reset the $t8 register
    	
    beq $t9, 1, skip1			# Check if the input is first day
    subi $t7, $t9, 2    		# subtract 2 from user input to track the day want to print
  	
    skip1:				# In case the inpt is first day
    bne  $t9, 1, skip2			# Check if the input is not the first day
    j take_first_line			# Print fist day
  			
    skip2:      			# In case not hte first day
    blt $t9, 1, invalid_day 		# Validate the day input (1-31)
    bgt $t9, 31, invalid_day		# Validate the day input (1-31)
    	
    cale_loop:        			# Loop to count newlines
    lb $t6, 0($t3)     			# Load a byte from the calendar
    beq $t6, 10, add_lines  		# Check if the current character is a newline
    j con_loop   			# Continue the loop

    add_lines:
    beq $t5, $t7, take_day 		# Check if reached the day want to print
    addi $t5, $t5, 1  			# Increment the newline counter
    j con_loop   			# Continue the loop

    con_loop:
    addi $t3, $t3, 1  			# Move to the next position in memory
    j cale_loop   			# Continue the loop

    take_day:
    addi $t3, $t3, 1  			# Move to the next position in memory
    lb $t6, 0($t3)    			# Load a byte from the calendar
    beq $t6, 10, done_take 		# Check if the current character is a newline
    sb $t6, day_buffer($t8) 		# Store the character in the buffer
    addi $t8, $t8, 1           		# Increment the buffer index
    j take_day				# Continue the loop
        
    take_first_line:
    lb $t6, 0($t3)           		# Load a byte from the calendar
    beq $t6, 10, done_take  		# Check if the current character is a newline
    sb $t6, day_buffer($t8) 		# Store the character in the buffer
    addi $t3, $t3, 1  			# Move to the next position in memory
    addi $t8, $t8, 1           		# Increment the buffer index
    j take_first_line    		# Continue the loop
    
    invalid_day:
    li $v0, 4           		# Print string - syscall 4
    la $a0, invalid_day_str 		# Print invalid day string
    syscall  				# System call
    j main
                    
    done_take:
    bne $a1, 1, r_back
    li $t0, 0x0A			# Add new line in the last
    sb $t0, day_buffer($t8) 		# Store the character in the buffer
    r_back:
    jr $ra				# Return
 							    				    							
#  -------------------------------------------------

read_slot:
    li $v0, 4               		# Print string - syscall 4
    la $a0, slot_start      		# Load address of view_per_day_str into $a0
    syscall                 		# System call

    li $v0, 5               		# Read integer - syscall 5
    syscall                 		# System call
    move $t0, $v0           		# Save the user input

    li $v0, 4               		# Print string - syscall 4
    la $a0, slot_end        		# Load address of view_per_day_str into $a0
    syscall                 		# System call

    li $v0, 5               		# Read integer - syscall 5
    syscall                 		# System call
    move $t6, $v0           		# Save the user input


    bge $t0, 1, check_f5    		# Check if the first input is larger or equal to 1 to deal with slot range
    j wrong                 		# The input is wrong
    
    check_f5:
    ble $t0, 5, add12_s      		# Check if the first input is smaller or equal to 5 to deal with slot range

    again_here:
  
    bge $t6, 1, check_e5     		# Check if the second input is larger or equal to 1 to deal with slot range
    j wrong                  		# The input is wrong

    check_e5:
    ble $t6, 5, add12_e      		# Check if the second input is smaller or equal to 5 to deal with slot range
    j last                   		# Go to the last check

    add12_s:                 		# Add 12 to the time in the range [1,5] to deal with slots
    addi $t0, $t0, 12
    j again_here             		# Go to check the second number

    add12_e:                 		# Add 12 to the time in the range [1,5] to deal with slots
    addi $t6, $t6, 12
    j last                   		# Go to the last check

    last:                    		# Last check
    bge $t0, $t6, wrong      		# Check if the start slot is larger than the end slot

    jr $ra                  		# Return

    wrong:                  		# The input is wrong
    li $v0, 4               		# Print string - syscall 4
    la $a0, wrong_input     		# Load address of wrong_input into $a0
    syscall                 		# System call
    
#  -------------------------------------------------

get_slot:
    move $t2,$a0			# take copy of addrees of calender 
    subi $t2, $t2, 3         		# Move to the previce position in memory
    lb $t5 , 0($t2)			# load char from calender
    li $t7, 0x0000002d			# load "-" to $t7 
    beq $t5,$t7 next			# check if char from calender = "-"
    lb $t9,0($t2)			# load the second number in $t9
    sub $t9, $t9, 48         		# Convert ASCII to decimal
    addi $t2,$t2 ,1			# Move to the next position in memory to load the second digit
    lb $t4,0($t2)			# load second digit
	sub $t4, $t4, 48         	# Convert ASCII to decimal

    mul $t9 ,$t9 ,10			# this mul to put the both digit in one register
    add $t9 ,$t9 , $t4
	 
    subi $t2, $t2, 2			# Move to the previce position in memory
    j second_number                	# first number end go to the second
    next:
    addi $t2, $t2, 1     		# Move to the next position in memory
    lb $t9,0($t2)			# Load the number from calender 
    sub $t9, $t9, 48         		# Convert ASCII to decimal
    subi $t2, $t2, 1         		# Move to the previce position in memory
	
    second_number:                  	# same of above but for second number 
    subi $t2, $t2, 2         		# Move to the next position in memory
    li $t7 ,0x00000020
    lb $t5 , 0($t2)
    beq $t5,$t7 next_2
    lb $t8,0($t2)
    sub $t8, $t8, 48         		# Convert ASCII to decimal
    addi $t2,$t2 ,1
    lb $t4,0($t2)
    sub $t4, $t4, 48         		# Convert ASCII to decimal
    mul $t8 ,$t8 ,10
    add $t8 ,$t8 , $t4
    addi $t2,$t2,1
    j next_3
    next_2:
    addi $t2,$t2,1
    lb $t8,0($t2)
    sub $t8, $t8, 48         		# Convert ASCII to decimal

    next_3:
    li $t2 , 6  			# load 6 to $t2 to check if any number from 1 to 5 
    blt $t8,$t2 Add1       		# check if the first number 1-5 then add 12 
	
    j else_1               		# if not go to else 
    Add1:
    addi $t8,$t8,12 			# add 12 to the number
	
    else_1:
    blt $t9,$t2 Add2      		# check the scecond number
	
    j else_2				# if not go to else_2
    Add2:
    addi $t9,$t9,12        		# add 12 to the number
	  
    else_2: 				# not the number is ready 
	
    move $a1,$t8
    move $a2,$t9
	
    sub $v0,$t9,$t8			# find the long of L buy sub
    jr $ra    
				
#  -------------------------------------------------

exit_program:     			# Exit program
    li $v0, 10        			# Program exit - syscall 10
    syscall           			# System call
    
#  -------------------------------------------------