//////////////////////////////////////////
//				Prepared By:			//
//			Tariq Odeh - 1190699	   	//
//			Wasim Atta – 1200920	 	//
//			Eyab Ghifari - 1190999	  	//
//////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
//     							  Mux2x1     							   //
///////////////////////////////////////////////////////////////////////////// 

module Mux2x1 #(parameter WIDTH = 32) (
    input wire select,
    input wire [WIDTH-1:0] I0, I1,
    output wire [WIDTH-1:0] out
);

    // Selects I1 if select is true (1), otherwise selects I0.
    assign out = (select) ? I1 : I0;

endmodule


//----------------------------

module Mux2x1_tb();
    reg select;
    reg [31:0] I0, I1;
    wire [31:0] out;
    Mux2x1 #(32) m21 (
        .select(select),
        .I0(I0),
        .I1(I1),
        .out(out)
    );

    initial begin
        I0 = 32'h12345678; 
        I1 = 32'h789ABCDE;
        select = 0;         // Initialize select with 0 (false)
        #5 select = 1;      // After a delay of 5 time units, change select to 1 (true)
        #10 select = 0;     // Change select back to 0 after 10 time units
        $finish;
    end
endmodule


/////////////////////////////////////////////////////////////////////////////
//     							  Mux4x1     							   //
///////////////////////////////////////////////////////////////////////////// 

module Mux4x1 #(parameter WIDTH = 32) (
    input wire [1:0] select,
    input wire [WIDTH-1:0] I0, I1, I2, I3,
    output wire [WIDTH-1:0] out
);

    assign out = (select[1]) ? ((select[0]) ? I3 : I2) : ((select[0]) ? I1 : I0);
endmodule


//----------------------------

module Mux4x1_tb();
    reg [1:0] select;
    reg [32-1:0] I0, I1, I2, I3;
    wire [32-1:0] out;

    // Instantiate the Mux4x1 module
    Mux4x1 #(32) m41 (
        .select(select),
        .I0(I0),
        .I1(I1),
        .I2(I2),
        .I3(I3),
        .out(out)
    );

    initial begin
        I0 = 32'h12345678; 
        I1 = 32'h789ABCDE;
        I2 = 32'hFEDCBA98;
        I3 = 32'h87654321;
        select = 2'b00;         // Initialize select with 00
        #10 select = 2'b01;      // Select input I1 (01)
        #20 select = 2'b10;     // Select input I2 (10)
        #30 select = 2'b11;     // Select input I3 (11)	
		#40 select = 2'b00;     // Select input I0 (00)
        $finish;
    end
endmodule

/////////////////////////////////////////////////////////////////////////////
//     					  Two input adder     							   //
///////////////////////////////////////////////////////////////////////////// 

module Adder_2(
  input [31:0] A, B,
  output [31:0] out
);
  assign out = A + B; // Adds inputs A and B and assigns the result to out
endmodule

//----------------------------

module Adder_2_tb();
  reg [31:0] A, B;
  wire [31:0] out;
  Adder_2 adder2(A, B, out);

  initial begin
    A = 32'h00000002;   
    B = 32'h12345678;   
    #5ns;
    A = 32'h0034500A;   
    B = 32'hFF133456;   
    #5ns;
    $finish;            // Finish the simulation
  end
endmodule


/////////////////////////////////////////////////////////////////////////////
//     					  One input adder     							   //
/////////////////////////////////////////////////////////////////////////////

module Adder_1(
  input [31:0] A,
  output [31:0] out
);
  assign out = A + 1; // Adds 1 to input A and assigns the result to out
endmodule

//----------------------------

module Adder_1_tb();
  reg [31:0] A;
  wire [31:0] out;
  Adder_1 adder1(A, out);

  initial begin
    A = 32'h00000002;
    #5ns;
    A = 32'h0034500A;
    #5ns;
    $finish;            // Finish the simulation
  end
endmodule

/////////////////////////////////////////////////////////////////////////////
//     					  One input subtractor     						   //
/////////////////////////////////////////////////////////////////////////////

module Subtractor_1(
  input [31:0] A,
  output [31:0] out
);
  assign out = A - 1; // Subtracts input B from input A and assigns the result to out
endmodule

//----------------------------

module Subtractor_1_tb();
  reg [31:0] A;
  wire [31:0] out;
  Subtractor_1 subtractor1(A, out);

  initial begin
    A = 32'h12345678;
    #5ns;
    A = 32'hFF133456;
    #5ns;
    $finish; // Finish the simulation
  end
endmodule


/////////////////////////////////////////////////////////////////////////////
//     					 		 Concatenator    						   //
/////////////////////////////////////////////////////////////////////////////

module Concatenator(
  input [25:0] A, // 26-bit input
  input [5:0] B,  // 6-bit input
  output [31:0] out // 32-bit output
);
  assign out = {B, A}; // Concatenates B (6-bit) and A (26-bit) to form a 32-bit output
endmodule

//----------------------------

module Concatenator_tb();
  reg [25:0] A;
  reg [5:0] B;
  wire [31:0] out;
  Concatenator concat1(A, B, out);

  initial begin
    A = 26'hABCDEF12; // Example 26-bit value
    B = 6'h3A;        // Example 6-bit value
    #5ns;
    $finish;          // Finish the simulation
  end
endmodule

/////////////////////////////////////////////////////////////////////////////
//     							  Extender     							   //
/////////////////////////////////////////////////////////////////////////////

module Extender(
    input wire [15:0] in,    // 16-bit input
    output wire [31:0] out, // 32-bit output
    input wire is_signed    // Parameter for signed/unsigned extension
);

    // Perform sign extension or zero extension based on is_signed
    assign out = is_signed ? {{16{in[15]}}, in} : {16'b0, in};

endmodule

//----------------------------

module Extender_tb;
    reg [15:0] test_input;        
    wire [31:0] test_output;     
    reg test_is_signed;
	
    Extender uut (
        .in(test_input),
        .out(test_output),
        .is_signed(test_is_signed)
    );
    initial begin
        test_is_signed = 0;
        test_input = 16'hABCD;	 // Unsigned
        #10; 
        test_is_signed = 1;
        test_input = 16'h1234;	// Positive number
        #10;
        test_input = 16'hFFFA; 	// Negative number
        #10;
        $finish;
    end
endmodule


/////////////////////////////////////////////////////////////////////////////
//     					  Arithmetic Logic Unit (ALU)     				   //
/////////////////////////////////////////////////////////////////////////////

module ALU(	
	input clk,
    input [31:0] A, B,       // 32-bit inputs
    input [1:0] Op,          // 2-bit operation code
    output reg [31:0] Result,// 32-bit result
    output reg Zero, Sign    // Zero and Sign flags
);

    // Define operation codes
    parameter AND_OP = 2'b00,
              ADD_OP = 2'b01,
              SUB_OP = 2'b10;

    // Perform the operation based on the operation code
    always @(posedge clk) begin
        case (Op)
            AND_OP: Result = A & B;
            ADD_OP: Result = A + B;
            SUB_OP: Result = A - B;  
            default: Result = 32'b0;
        endcase
        Zero = (Result == 32'b0) ? 1'b1 : 1'b0;
        Sign = Result[31];	 
		$display("ALU:                 clock = %b, in1 = %0d ,in2 = %0d ALU_Result = %0d, Zero = %0d , Sign = %0d", clk, A,B, Result,Zero,Sign);
    end
endmodule

//----------------------------

module ALU_tb;

    reg [31:0] A, B;             // 32-bit test inputs
    reg [1:0] Op;                // 2-bit operation code for test
    wire [31:0] Result;          // 32-bit output from ALU
    wire Zero, Sign;             // Flags from ALU

    // Define operation codes in the test bench
    parameter AND_OP = 2'b00,
              ADD_OP = 2'b01,
              SUB_OP = 2'b10;

    // Instantiate the ALU
    ALU uut (
        .A(A), 
        .B(B), 
        .Op(Op), 
        .Result(Result), 
        .Zero(Zero), 
        .Sign(Sign)
    );

    initial begin
        // Initialize Inputs
        A = 0;
        B = 0;
        Op = 0;

        // Add stimulus here
        // Test ADD operation
        A = 32'h00000001;  // 1
        B = 32'h00000001;  // 1
        Op = ADD_OP;
        #10; // wait 10 ns

        // Test SUB operation
        A = 32'h00000003;  // 3
        B = 32'h00000002;  // 2
        Op = SUB_OP;
        #10; // wait 10 ns

        // Test AND operation
        A = 32'h00000003;  // 3 (binary 0011)
        B = 32'h00000001;  // 1 (binary 0001)
        Op = AND_OP;
        #10; // wait 10 ns

        // Test Zero flag
        A = 32'h00000000;
        B = 32'h00000000;
        Op = ADD_OP;
        #10; // wait 10 ns

        // Test Sign flag (Negative result)
        B = 32'h80000000;  // -2147483648 in 2's complement
        A = 32'h00000001;  // 1
        Op = SUB_OP;
        #10; // wait 10 ns

        // Complete the test
        $display("Test complete");
        $finish;
    end

    // Optional: Monitor changes in signals
    initial begin
        $monitor("Time = %d : A = %h, B = %h, Op = %b, Result = %h, Zero = %b, Sign = %b", 
                 $time, A, B, Op, Result, Zero, Sign);
    end

endmodule

/////////////////////////////////////////////////////////////////////////////
//     					  Program Counter (PC)     						   //
/////////////////////////////////////////////////////////////////////////////

module PC(
    input wire [31:0] input_data,
    output wire [31:0] output_data
);

    reg [31:0] register = 32'b0;

    always @(input_data) begin
        register <= input_data; // Load input data when it changes
    end

    assign output_data = register;

endmodule

//----------------------------

module PC_tb();

    reg [31:0] input_data;
    wire [31:0] output_data;

    PC pc (
        .input_data(input_data),
        .output_data(output_data)
    );

    initial begin
        input_data = 32'h12345678; // Initial input value
        $display("Initial output_data = %h", output_data); // Display initial value
        #10;
        input_data = 32'hABCDEF01;
        #10;
        input_data = 32'h80000000;
        #10;
        $finish;
    end

    // Monitor to display output_data
    always @(output_data) begin
        $display("output_data = %h", output_data);
    end

endmodule

/////////////////////////////////////////////////////////////////////////////
//     					  Stack Pointer (SP)    						   //
/////////////////////////////////////////////////////////////////////////////

module SP(
    input wire [31:0] input_data,
    output wire [31:0] output_data
);

    reg [31:0] register1 = 32'd500; // Initialize register to 500

    always @(input_data) begin
        register1 <= input_data; // Load input data when it changes
    end

    assign output_data = register1;

endmodule

//----------------------------

module SP_tb();

    reg [31:0] input_data;
    wire [31:0] output_data;

    PC pc (
        .input_data(input_data),
        .output_data(output_data)
    );

    initial begin
        input_data = 32'h12345678; // Initial input value
        $display("Initial output_data = %h", output_data); // Display initial value
        #10;
        input_data = 32'hABCDEF01;
        #10;
        input_data = 32'h80000000;
        #10;
        $finish;
    end

    // Monitor to display output_data
    always @(output_data) begin
        $display("output_data = %h", output_data);
    end

endmodule

/////////////////////////////////////////////////////////////////////////////
//     					  Instruction Memory     						   //
/////////////////////////////////////////////////////////////////////////////

module InstructionMemory(
    input wire clk,
    input [31:0] address,
    output reg [31:0] instruction
);

    // Define the space of memory with 32-bit width
    reg [31:0] MemoryInst [0:1024];

    // Define Register Names (R0 to R15)
    parameter R0 = 4'b0000, R1 = 4'b0001, R2 = 4'b0010, R3 = 4'b0011, R4 = 4'b0100, 
              R5 = 4'b0101, R6 = 4'b0110, R7 = 4'b0111, R8 = 4'b1000, R9 = 4'b1001,
              R10 = 4'b1010, R11 = 4'b1011, R12 = 4'b1100, R13 = 4'b1101, R14 = 4'b1110, 
              R15 = 4'b1111;

    // R-Type Instructions Opcode Values
    parameter AND = 6'b000000, ADD = 6'b000001, SUB = 6'b000010;
    // I-Type Instructions Opcode Values
    parameter ANDI = 6'b000011, ADDI = 6'b000100, LW = 6'b000101, LWPOL = 6'b000110, 
              SW = 6'b000111, BGT = 6'b001000, BLT = 6'b001001, BEQ = 6'b001010, BNE = 6'b001011;
    // J-Type Instructions Opcode Values
    parameter JMP = 6'b001100, CALL = 6'b001101, RET = 6'b001110;
    // S-Type Instructions Opcode Values
    parameter PUSH = 6'b001111, POP = 6'b010000;
    
    // Initialize the memory with instructions
    initial begin  	 
	/*	
		 // our code is here to test system
		
		MemoryInst[0] = {ADDI, R1, R0, 16'd7,2'b00};     //R1=7
        MemoryInst[1] = {ADDI, R2, R0, 16'd2,2'b00};    //R2=2    
		MemoryInst[2] = {CALL, 26'd6};	 			   // GO TO LABLE F    IN POSTION 6 IN PC 
		MemoryInst[3] = {SW, R1, R2, 16'd4,2'b00};
		MemoryInst[4] = {SW, R5, R2, 16'd5,2'b00}; 
		
		MemoryInst[5] = {JMP, 26'd15};		// GO TO LABLE L
		
		// LAPEL F:	 
		MemoryInst[6] = {SUB, R3,R1, R2, 14'd0};	   //R3 = 7-2 = 5
		MemoryInst[7] = {ADD, R4,R3, R1, 14'd0}; 	  //R4 = 5+7 = 12
		MemoryInst[8] = {AND, R5,R1, R4, 14'd0};	 // R5 = 0...00111 AND 0...01100 =0...00100 = 4
		MemoryInst[9] = {ANDI,R6,R1, 16'd12,2'b00};	// same above R6 = 4
		MemoryInst[10] = {RET, 26'd0};	 		   // back to line after call  	  
		
	    // LAPEL PUS 
		MemoryInst[11] = {PUSH, R2, 22'd0};	 		   // put 2 to stack 
		MemoryInst[12] = {POP, R11, 22'd0};	 		  // pop 2 to R11
		MemoryInst[13] = {ADD, R12,R11, R2, 14'd0};	 //R4 = 2+2 = 4	 
		MemoryInst[5] = {JMP, 26'd19};				// GO TO LABLE END
		// LAPEL L:
		MemoryInst[15] = {LWPOL, R7, R2, 16'd4,2'b00}; 	    // R7 <--mem[R2+4]  R7 must = 7 and R2=R2+1	 
     	MemoryInst[16] = {LW, R8, R2, 16'd4,2'b00}; 	   // R8 <--mem[R2+4]  R8 must = 4		
		MemoryInst[17] = {BGT, R5, R6, 16'd19,2'b00};	  // go to label END
		MemoryInst[18] = {BEQ, R5, R6, 16'd11,2'b00}; 	 // got to label PUS
		
		// LAPEL END 
		*/	
		 /*
		
		//ppcode test 1]] 
		MemoryInst[0] = {ADDI, R1, R0, 16'd7,2'b00};     //R1=7
        MemoryInst[1] = {ADDI, R2, R0, 16'd2,2'b00};    //R2=2    
		MemoryInst[2] = {CALL, 26'd7};	 			   // GO TO LABLE F    IN POSTION 6 IN PC	 
		
		MemoryInst[3] = {PUSH, R2, 22'd0};	 		   // put 2 to stack 
		MemoryInst[4] = {POP, R11, 22'd0};	 		  // pop 2 to R11
		MemoryInst[5] = {ADD, R12,R11, R2, 14'd0};	 //R12 = 2+2 = 4	 
		MemoryInst[6] = {JMP, 26'd12};				// GO TO LABLE EN
		 // LAPEL F:	 
		MemoryInst[7] = {SUB, R3,R1, R2, 14'd0};	   //R3 = 7-2 = 5
		MemoryInst[8] = {ADD, R4,R3, R1, 14'd0}; 	  //R4 = 5+7 = 12
		MemoryInst[9] = {AND, R5,R1, R4, 14'd0};	 // R5 = 0...00111 AND 0...01100 =0...00100 = 4
		MemoryInst[10] = {ANDI,R6,R1, 16'd12,2'b00};	// same above R6 = 4
		MemoryInst[11] = {RET, 26'd0};	 		   // back to line after call 
		
	// LAPEL END 
		 */
	
	//[[code test 2]]		 
	  MemoryInst[0] = {ADDI, R1, R0, 16'd7,2'b00};     //R1=7
      MemoryInst[1] = {ADDI, R2, R0, 16'd2,2'b00};    //R2=2 
	  MemoryInst[2] = {ADDI, R5, R0, 16'd4,2'b00};    //R5=4   
	  
	  MemoryInst[3] = {JMP, 26'd8};	   // go to label L	
	  
	  // LAPEL PUS
	  MemoryInst[4] = {LWPOL, R7, R2, 16'd4,2'b00}; 	// R7 <--mem[R2+4]  R7 must = 7 and R2=R2+1	 
      MemoryInst[5] = {LW, R8, R2, 16'd4,2'b00}; 	   // R8 <--mem[R2+4]  R8 must = 4	
	  MemoryInst[6] = {ADD, R10,R7, R8, 14'd0};       // R10 = 7+4 =11
	  MemoryInst[7] = {JMP, 26'd12};				 // GO TO LABLE EN
	  
	   // LAPEL L
	  MemoryInst[8] = {SW, R1, R2, 16'd4,2'b00};   		//store R1 =7 in postion mem[R2+4]
	  MemoryInst[9] = {SW, R5, R2, 16'd5,2'b00};   	   //store R5 =4 in postion mem[R2+5
	  MemoryInst[10] = {BEQ, R5, R2, 16'd2,2'b00};	  // go to label END
	  MemoryInst[11] = {BGT, R5, R2, 16'b1111111111111001,2'b00};  // got to label PUS
	  
	  
	  	  // LAPEL END
	  	 
    end

    // Get the instruction
    always @(posedge clk) begin
        instruction = MemoryInst[address];
		$display("MemoryInst:          clock = %b, pc_in = %0d , Output = %b", clk, address, instruction);
    end									

endmodule
						 
//----------------------------

module InstructionMemory_tb;
    reg clk;                
    reg [31:0] address;
    wire [31:0] instruction;

    InstructionMemory o (
        .clk(clk),      
        .address(address),
        .instruction(instruction)
    );

    initial begin
        clk = 0;
        address = 0;
        #10;
        address = 2;
        #10;
        address = 3;
        #10;
        address = 4;
        #10;
        $finish;
    end

    always begin
        #5 clk = ~clk;          // Toggle the clock every 5 time units
    end

    initial begin
        $monitor("At time %dns, the address is %0d, and the instruction is %b", $time, address, instruction);
    end

endmodule

/////////////////////////////////////////////////////////////////////////////
//     					  Registers File     							   //
/////////////////////////////////////////////////////////////////////////////

module Registers_file(
    input wire clk1,	
	input wire clk2,
    input [3:0] RA, RB, RW1, RW2,
    input [31:0] BusW1, BusW2,
    input RegWr1, RegWr2,
    output reg [31:0] BusA, BusB
);

    reg [31:0] Reg [0:15]; // Register file with 16 registers
	 

    initial begin
            for (int i = 0; i < 16; i = i + 1) begin
                Reg[i] = 0; // Initialize all registers in the file to 0   
        end	
    end
											 

    always @(posedge clk1) begin
        BusA = Reg[RA]; // Use non-blocking assignment (<=) for BusA
        BusB = Reg[RB]; // Use non-blocking assignment (<=) for BusB   
			$display("READ Registers_file: clock = %b, RA_in = %0d, RB_in = %0d, RW1 = %0d, RW2 = %0d, BusW1 = %0d, BusW2 = %0d, BusA = %0d, BusB = %0d ", clk1, RA, RB, RW1, RW2, BusW1, BusW2, BusA, BusB);
		end	
	always @(posedge clk2) begin
        if (RegWr1 && RW1 != 0) begin
            Reg[RW1] = BusW1; // Use non-blocking assignment (<=) to update the register
        end

        if (RegWr2 && RW2 != 0) begin
            Reg[RW2] = BusW2; // Use non-blocking assignment (<=) to update the register
        end

        $display("WRITE Registers_file:clock = %b, RA_in = %0d, RB_in = %0d, RW1 = %0d, RW2 = %0d, BusW1 = %0d, BusW2 = %0d, BusA = %0d, BusB = %0d", clk2, RA, RB, RW1, RW2, BusW1, BusW2, BusA, BusB);
    end
endmodule

//----------------------------

 module tb_Registers_file;
    // Inputs
    reg clk1;
    reg clk2;
    reg [3:0] RA;
    reg [3:0] RB;
    reg [3:0] RW1;
    reg [3:0] RW2;
    reg [31:0] BusW1;
    reg [31:0] BusW2;
    reg RegWr1;
    reg RegWr2;

    // Outputs
    wire [31:0] BusA;
    wire [31:0] BusB;

    // Instantiate the Registers_file module
    Registers_file uut (
        .clk1(clk1),
        .clk2(clk2),
        .RA(RA),
        .RB(RB),
        .RW1(RW1),
        .RW2(RW2),
        .BusW1(BusW1),
        .BusW2(BusW2),
        .RegWr1(RegWr1),
        .RegWr2(RegWr2),
        .BusA(BusA),
        .BusB(BusB)
    );

    // Clock generation
    always begin
        #5 clk1 = ~clk1; // Assuming 10ns clock period
    end

    always begin
        #10 clk2 = ~clk2; // Assuming 20ns clock period
    end

    // Testbench stimulus
    initial begin
        // Initialize inputs
        clk1 = 0;
        clk2 = 0;
        RA = 4'b0000;
        RB = 4'b0001;
        RW1 = 4'b0010;
        RW2 = 4'b0011;
        BusW1 = 32'hAABBCCDD;
        BusW2 = 32'h11223344;
        RegWr1 = 1'b0;
        RegWr2 = 1'b0;

        // Monitor the outputs
        $monitor("READ Registers_file: RA = %h, RB = %h, BusA = %h, BusB = %h",
                 RA, RB, BusA, BusB);

        // Test case 1: Reading registers
        #15 RA = 4'b0100;
        #15 RB = 4'b0101;

        // Test case 2: Writing to registers
        RW1 = 4'b0010;
        RW2 = 4'b0011;
        BusW1 = 32'h11223344;
        BusW2 = 32'hAABBCCDD;
        RegWr1 = 1'b1;
        RegWr2 = 1'b1;
        #10 RegWr1 = 1'b0;
        #10 RegWr2 = 1'b0;

        // Add more test cases as needed

        // Finish simulation
        $finish;
    end
endmodule

/////////////////////////////////////////////////////////////////////////////
//     					 	 Data Memory     							   //
/////////////////////////////////////////////////////////////////////////////

module Data_memory (
    input clk,
    input [31:0] address,
    input MemWr,
    input MemRd,
    input [31:0] data_in,
    input SAddress,
    output reg [31:0] data_out
);

	reg [31:0] memory [0:600];				//Assign 600 address location to the memory
											// 500 for data (PC) and 100 for stack (SP)
	always @(posedge clk) begin
		// Condition for Write
	    if (MemWr && ((SAddress == 0 && address > 500) || (SAddress == 1 && address < 500))) begin
	        memory[address] = data_in;
	    end
		// Condition for Read		
	    if (MemRd && ((SAddress == 0 && address > 500) || (SAddress == 1 && address < 500))) begin
	        data_out = memory[address];
	    end
		// Condition for wrong address
		else if (MemRd) begin
	        data_out = 32'h00000000;
	    end	   
		$display("DataMemory:          clock = %b, address = %b , data_in = %0d , MemWr = %b, MemRd = %b ,data_out = %0d", clk, address, data_in ,MemWr,MemRd,data_out);
	end
endmodule

//----------------------------

module Data_memory_tb;
    reg clk;
    reg [31:0] address;
    reg MemWr, MemRd, SAddress;
    reg [31:0] data_in;
    wire [31:0] data_out;

    Data_memory mem (
        .clk(clk),
        .address(address),
        .MemWr(MemWr),
        .MemRd(MemRd),
        .data_in(data_in),
        .SAddress(SAddress),
        .data_out(data_out)
    );

    initial begin
        clk = 0;
        forever #5 clk = ~clk; // Toggle the clock every 5 time units
    end

    initial begin
        MemWr = 0;
        MemRd = 0;
        SAddress = 0;
        data_in = 0;
        #40; // Wait for 4 clock cycles (4*(5+5)) = 40

        // Scenario 1: Write data with address greater than 500 when SAddress is 0
        address = 501;
        SAddress = 0;
        MemWr = 1;
        data_in = 32'hAAAA0001;
        #40;
        MemWr = 0;

        // Scenario 2: Attempt to write data with address less than 500 when SAddress is 0
        address = 499;
        MemWr = 1;
        data_in = 32'hAAAA0002;
        #40; 
        MemWr = 0;

        // Scenario 3: Read data from address 501 with SAddress is 0
        MemRd = 1;
        address = 501;
        #40; 
        MemRd = 0;

        // Scenario 4: Change SAddress to 1 and attempt to write data to address less than 500
        SAddress = 1;
        address = 499;
        MemWr = 1;
        data_in = 32'hBBBB0001;
        #40;
        MemWr = 0;

        // Scenario 5: Attempt to read data from address 499 with SAddress is 1
        MemRd = 1;
        #40;
        MemRd = 0;

        // Scenario 6: Attempt to write data to address greater than 500 with SAddress is 1
        address = 501;
        MemWr = 1;
        data_in = 32'hBBBB0002;
        #40;
        MemWr = 0;
        $finish;
    end
endmodule

/////////////////////////////////////////////////////////////////////////////
//     						 Contol Unit     							   //
/////////////////////////////////////////////////////////////////////////////

module Control_unit(
    input [5:0] Op,
    input zerof, signf,
    output reg RegS, RegWr1, RegWr2, ExtOp, ALUSrc, Rdata, SAddress, MemRd, MemWr, PopSrc, WBdata,
    output reg [1:0] StaS, ALUOp,
    output reg [1:0] PCSrc
);

    // R-Type Instructions
    reg AND = 0, ADD = 0, SUB = 0;
    // I-Type Instructions
    reg ANDI = 0, ADDI = 0, LW = 0, LWPOL = 0, SW = 0, BGT = 0, BLT = 0, BEQ = 0, BNE = 0;
    // J-Type Instructions
    reg JMP = 0, CALL = 0, RET = 0;
    // S-Type Instructions
    reg PUSH = 0, POP = 0;

    always @(*) begin
        // Default values for control signals
        RegS = 0; RegWr1 = 0; RegWr2 = 0; ExtOp = 0; ALUSrc = 0;
        Rdata = 0; SAddress = 0; MemRd = 0; MemWr = 0; PopSrc = 0;
        WBdata = 0;

        // Default value for StaS, ALUOp, and PCSrc
        StaS = 2'b00;
        ALUOp = 2'b00;
        PCSrc = 2'b00;

        // Reset all control signal assignments to zero
        AND = 0; ADD = 0; SUB = 0;
        ANDI = 0; ADDI = 0; LW = 0; LWPOL = 0; SW = 0; BGT = 0; BLT = 0; BEQ = 0; BNE = 0;
        JMP = 0; CALL = 0; RET = 0;
        PUSH = 0; POP = 0;

        case (Op)
            6'b000000: AND = 1; 
            6'b000001: ADD = 1;
            6'b000010: SUB = 1;
            6'b000011: ANDI = 1;
            6'b000100: ADDI = 1;
            6'b000101: LW  = 1;
            6'b000110: LWPOL = 1;
            6'b000111: SW = 1;
            6'b001000: BGT = 1;
            6'b001001: BLT = 1;
            6'b001010: BEQ = 1;
            6'b001011: BNE = 1;
            6'b001100: JMP = 1;
            6'b001101: CALL = 1;
            6'b001110: RET = 1;
            6'b001111: PUSH = 1;
            6'b010000: POP = 1;
            default: begin // Set default values to 0
                AND = 0; ADD = 0; SUB = 0;
                ANDI = 0; ADDI = 0; LW = 0; LWPOL = 0; SW = 0; BGT = 0; BLT = 0; BEQ = 0; BNE = 0;
                JMP = 0; CALL = 0; RET = 0;
                PUSH = 0; POP = 0;
            end
        endcase

        // Additional logic for control signal assignments
        RegS = SW || BGT || BLT || BEQ || BNE || PUSH;
        RegWr1 = AND || ADD || SUB || ANDI || ADDI || LW || LWPOL || POP;
        RegWr2 = LWPOL;
        ExtOp = ADDI || LW || LWPOL || SW || BGT || BLT || BEQ || BNE;
        ALUSrc = ANDI || ADDI || LW || LWPOL || SW;
        Rdata = SW || PUSH;
        SAddress = LW || LWPOL || SW;
        MemRd = LW || LWPOL || RET || POP;
        MemWr = SW || CALL || PUSH;	
        WBdata = LW || LWPOL || RET || POP;
		
        // Logic for StaS assignment
        if (RET || POP) begin
            StaS = 2'b01; // Assign StaS to 01
        end else if (CALL || PUSH) begin
            StaS = 2'b10; // Assign StaS to 10
        end

        // Additional logic for ALUOp assignment
        if (ADD || ADDI || LW || LWPOL || SW) begin
            ALUOp = 2'b01; // Assign ALUOp to 01
        end else if (SUB || BGT || BLT || BEQ || BNE) begin
            ALUOp = 2'b10; // Assign ALUOp to 10
        end
		
        // Additional logic for PCSrc assignment
        case (Op)
            // BGT
            6'b001000:
                if (zerof == 0 && signf == 1) begin
                    PCSrc = 2'b10;
                end 
                else begin
                    PCSrc = 2'b00;
                end
			
            // BLT
            6'b001001:
                if (zerof == 0 && signf == 0) begin
                    PCSrc = 2'b10;
                end 
                else begin
                    PCSrc = 2'b00;
                end
			
            // BEQ
            6'b001010:
                if (zerof == 1) begin
                    PCSrc = 2'b10;
                end 
                else begin
                    PCSrc = 2'b00;
                end
			
            // BNE
            6'b001011:
                if (zerof == 0) begin
                    PCSrc = 2'b10;
                end 
                else begin
                    PCSrc = 2'b00;
                end
			
            6'b001100: PCSrc = 2'b01; // JMP
            6'b001101: PCSrc = 2'b01; // CALL
            6'b001110: PCSrc = 2'b11; // RET
            default:
                PCSrc = 2'b00;
        endcase
    end
endmodule

//----------------------------

module Control_unit_tb();

    // Declare signals to interface with Control_unit module
    reg [5:0] Op;
    reg zerof, signf;
    wire RegS, RegWr1, RegWr2, ExtOp, ALUSrc, Rdata, SAddress, MemRd, MemWr, PopSrc, WBdata;
    wire [1:0] StaS, ALUOp;
    wire [1:0] PCSrc;

    // Instantiate the Control_unit module
    Control_unit dut(
        .Op(Op),
        .zerof(zerof), .signf(signf),
        .RegS(RegS), .RegWr1(RegWr1), .RegWr2(RegWr2), .ExtOp(ExtOp),
        .ALUSrc(ALUSrc), .Rdata(Rdata), .SAddress(SAddress),
        .MemRd(MemRd), .MemWr(MemWr), .PopSrc(PopSrc), .WBdata(WBdata),
        .StaS(StaS), .ALUOp(ALUOp), .PCSrc(PCSrc)
    );

    // Apply different test cases
    initial begin
        $display("Testing Control_unit:");

        // Test case 1: AND instruction
        Op = 6'b000000; zerof = 0; signf = 0;
        #10 $display("Test case 1: Op = AND, zerof = 0, signf = 0:");
        assert(RegS == 0 && RegWr1 == 1 && RegWr2 == 0 && ExtOp == 0 &&
               ALUSrc == 0 && Rdata == 0 && SAddress == 0 &&
               MemRd == 0 && MemWr == 0 && PopSrc == 0 && WBdata == 0 &&
               StaS == 2'b00 && ALUOp == 2'b00 && PCSrc == 2'b00)
               else $display("Test failed for AND instruction");

        // Test case 2: LW instruction
        Op = 6'b000101; zerof = 0; signf = 0;
        #10 $display("Test case 2: Op = LW, zerof = 0, signf = 0:");
        assert(RegS == 0 && RegWr1 == 1 && RegWr2 == 0 && ExtOp == 0 &&
               ALUSrc == 0 && Rdata == 0 && SAddress == 0 &&
               MemRd == 1 && MemWr == 0 && PopSrc == 0 && WBdata == 1 &&
               StaS == 2'b00 && ALUOp == 2'b00 && PCSrc == 2'b00)
               else $display("Test failed for LW instruction");

        // Test case 3: RET instruction
        Op = 6'b001110; zerof = 0; signf = 0;
        #10 $display("Test case 3: Op = RET, zerof = 0, signf = 0:");
        assert(RegS == 0 && RegWr1 == 0 && RegWr2 == 0 && ExtOp == 0 &&
               ALUSrc == 0 && Rdata == 0 && SAddress == 0 &&
               MemRd == 0 && MemWr == 0 && PopSrc == 1 && WBdata == 1 &&
               StaS == 2'b01 && ALUOp == 2'b00 && PCSrc == 2'b00)
               else $display("Test failed for RET instruction");

        // Test case 4: CALL instruction
        Op = 6'b001101; zerof = 0; signf = 0;
        #10 $display("Test case 4: Op = CALL, zerof = 0, signf = 0:");
        assert(RegS == 0 && RegWr1 == 0 && RegWr2 == 0 && ExtOp == 0 &&
               ALUSrc == 0 && Rdata == 0 && SAddress == 0 &&
               MemRd == 0 && MemWr == 0 && PopSrc == 0 && WBdata == 0 &&
               StaS == 2'b10 && ALUOp == 2'b00 && PCSrc == 2'b00)
               else $display("Test failed for CALL instruction");

        // Add more test cases for other instructions here

        $finish; // Finish simulation after all test cases
    end

endmodule

/////////////////////////////////////////////////////////////////////////////
//     					  Clock Organizer     							   //
/////////////////////////////////////////////////////////////////////////////

module Clock_organizer(
    input clock,
    input [5:0] Op,
    output reg IF, ID, MEM, EX, WB,IFF
);

    // Opcode Parameters
    parameter AND = 6'b000000, ADD = 6'b000001, SUB = 6'b000010;
    parameter ANDI = 6'b000011, ADDI = 6'b000100, LW = 6'b000101, LWPOL = 6'b000110,
              SW = 6'b000111, BGT = 6'b001000, BLT = 6'b001001, BEQ = 6'b001010, BNE = 6'b001011;
    parameter JMP = 6'b001100, CALL = 6'b001101, RET = 6'b001110;
    parameter PUSH = 6'b001111, POP = 6'b010000 ;

    // Internal State
    reg [2:0] state;
	reg en =0;
    // Initialization block
    initial begin
        state = 3'b000; // Initialize state
        IF = 1;         // Initialize all output signals
        ID = 0;
        MEM = 0;
        EX = 0;
        WB = 0;
		IFF <= 0;
    end

    // State Machine
    always @(posedge clock) begin
        case (state)
            3'b000: begin
                state <= 3'b001;
                IF <= 0;
                ID <= 1;
                EX <= 0;
                MEM <= 0;
                WB <= 0; 
				IFF <= 0;
            end

            3'b001: begin
                if (Op == JMP) begin
                    state <= 3'b000;
                    IFF <= 1;
					#2ns IF <= 1;
                    ID <= 0;
                    EX <= 0;
                    MEM <= 0;
                    WB <= 0; 
					
                end
                else if (Op == CALL || Op == RET || Op == PUSH || Op == POP) begin
                    state <= 3'b011;
                    IF <= 0;
                    ID <= 0;
                    EX <= 0;
                    MEM <= 1;
                    WB <= 0;
                end
                else begin
                    state <= 3'b010;
                    IF <= 0;
                    ID <= 0;
                    EX <= 1;
                    MEM <= 0;
                    WB <= 0;
                end
            end

            3'b010: begin
                if (Op == BNE || Op == BEQ || Op == BGT || Op == BLT) begin
			        state <= 3'b000;
                    IFF <= 1;
					#2ns IF <= 1;
                    ID <= 0;
                    EX <= 0;
                    MEM <= 0;
                    WB <= 0; 
					
                end
			
                else if (Op == LW || Op == LWPOL || Op == SW) begin
                    state <= 3'b011;
                    IF <= 0;
                    ID <= 0;
                    EX <= 0;
                    MEM <= 1;
                    WB <= 0;
                end
                else begin
                    state <= 3'b100;
                    IF <= 0;
                    ID <= 0;
                    EX <= 0;
                    MEM <= 0;
                    WB <= 1;
                end
            end

            3'b011: begin
                if (Op == LW || Op == LWPOL || Op == POP) begin
                    state <= 3'b100;
                    IF <= 0;
                    ID <= 0;
                    EX <= 0;
                    MEM <= 0;
                    WB <= 1;
                end
                else begin
                      state <= 3'b000;
                    IFF <= 1;
					#2ns IF <= 1;
                    ID <= 0;
                    EX <= 0;
                    MEM <= 0;
                    WB <= 0; 
					
                end
            end

            3'b100: begin
                  state <= 3'b000;
                    IFF <= 1;
					#2ns IF <= 1;
                    ID <= 0;
                    EX <= 0;
                    MEM <= 0;
                    WB <= 0; 
					
                end
			
        endcase
    end
endmodule

//----------------------------

module Clock_organizer_tb;

// Inputs
reg clock;
reg [5:0] Op;

// Outputs
wire IF, ID, MEM, EX, WB;

// Instantiate the Unit Under Test (UUT)
Clock_organizer uut (
    .clock(clock), 
    .Op(Op), 
    .IF(IF), 
    .ID(ID), 
    .MEM(MEM), 
    .EX(EX), 
    .WB(WB)
);

initial begin
    // Initialize Inputs
    clock = 0;
    Op = 0;

    // Apply test cases
   // #10 Op = 6'b001100; // J-Type (e.g., JMP)
    #10 Op = 6'b000101; // I-Type (e.g., LW)
    //#10 Op = 6'b001011; // I-Type (e.g., BNE)
    //#10 Op = 6'b001111; // S-Type (e.g., PUSH)
    //#10 Op = 6'b000001; // R-Type (e.g., ADD)

    #100 $finish;
end

// Clock generation
always #5 clock = ~clock;

// Monitor changes
initial begin
    $monitor("Time=%d, Clock=%b, Op=%b, IF=%b, ID=%b, EX=%b, MEM=%b, WB=%b", $time, clock, Op, IF, ID, EX, MEM, WB);
end
endmodule

/////////////////////////////////////////////////////////////////////////////
//     						   Processer     							   //
/////////////////////////////////////////////////////////////////////////////

module Processer();
	reg CLK;
	reg [31:0] PCnext, PCnow, PCplus;
	reg [31:0] IR, BTA,BTAA, JA;
	reg [3:0] Rs1, Rs2, Rd, RB,Rstemp;
	reg [15:0] Imm16;
	reg [25:0] Imm26;
	reg [5:0] PCj, Op;
	reg [31:0] BusB, BusA, ExtImm, AluB, AluRes;
	reg [31:0] Data_in, MEMaddress, Data_out, WB, BusAplus,temp;
	reg [31:0] SPaddress, SPnext, SPnow, SPplus, SPmins;
	reg clkIF, clkID, clkEX, clkMEM, clkWB;
	reg RegS, RegWr1, RegWr2, ExtOp, ALUSrc, Rdata, SAddress, MemRd, MemWr, PopSrc, WBdata,RegWr11, RegWr22;
	reg [1:0] StaS, ALUOp, PCSrc;
	reg zero, sign;
	
	wire [31:0] PCnextt;
	wire [31:0] BusBt, BusAt;
	wire [31:0]  SPnextt;
	reg [31:0] STK= 32'd500;
	reg [31:0] STK1 =32'd500;
	
	assign Op = IR[31:26]; 
	assign Imm26 = IR[26:0];
	assign Imm16 = IR[17:2];
	assign Rd = IR[25:22];
	assign Rs1 = IR[21:18];
	assign Rs2 = IR[17:14];
	assign PCj = PCnow[31:26];
	
	
	Clock_organizer clocorg(CLK, Op, clkIF, clkID, clkMEM, clkEX, clkWB,clkIFF);
	
	PC get_pc(PCnext, PCnow); 
	InstructionMemory get_IR(clkIF, PCnow, IR);
	Adder_1 adderPC(PCnow, PCplus);	   
	Concatenator cont(Imm26, PCj, JA); 
	
	Control_unit contuni(Op, zero, sign, RegS, RegWr1, RegWr2, ExtOp, ALUSrc, Rdata, SAddress, MemRd, MemWr, PopSrc, WBdata, StaS, ALUOp, PCSrc);
	Mux4x1 mux4PC(PCSrc, PCplus, JA, BTA, WB, PCnextt);	
	
	Mux2x1 muxReg(RegS, Rs2, Rd, RB);
	Registers_file get_registers_file_ID(clkID,clkWB, Rs1, RB,Rd, Rs1,WB, BusAplus, RegWr1, RegWr2, BusA, BusB);
	 
	Extender ext(Imm16, ExtImm, ExtOp);
	Adder_2 adderBTA(ExtImm, PCnow, BTA);
	Adder_1 adderR(BusA, BusAplus);		 
	
	Mux2x1 muxALU(ALUSrc, BusB, ExtImm, AluB);
	ALU alu1(clkEX,BusA, AluB, ALUOp, AluRes, zero, sign);
	
	SP get_sp(STK, SPnow);
	Mux2x1 muxMEMdata_in(Rdata, PCplus, BusB, Data_in);
	Mux2x1 muxMEMaddress(SAddress,SPnow , AluRes, MEMaddress);
	Data_memory datamem(clkMEM, MEMaddress, MemWr, MemRd, Data_in, SAddress, Data_out);								
  
	Mux2x1 mux2DW(WBdata, AluRes, Data_out, WB);  
	
	always @(posedge clkID) begin
    if (StaS !=0 &&PopSrc == 0) begin
        STK <= STK + 1; 
    end	
	else if (StaS !=0 && PopSrc == 1)  begin
			STK1 <= STK - 1; 
		
		end
		end
		always @(posedge clkIFF) begin
	    PCnext = PCnextt;
		 STK <= STK1;
		end	 
		
	initial begin
	    CLK = 0;
	    repeat(100)
	        #5ns CLK = !CLK;
	    $finish;
	end
endmodule

/////////////////////////////////////////////////////////////////////////////