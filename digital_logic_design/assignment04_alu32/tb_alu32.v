`timescale 1ns/100ps
module tb_alu32;
	reg clk, reset;
	reg [31:0] vectornum, errors;
	reg [99:0] testvectors[10000:0];
	
	reg [31:0] tb_a, tb_b, tb_rexp;
	reg [3:0] tb_op; // added 1 bit to align with testvector.
	wire [31:0] tb_result;
	wire tb_c, tb_n, tb_z, tb_v;
	
	alu32 u0_alu32(.a(tb_a), .b(tb_b), .op(tb_op), .result(tb_result), .c(tb_c), .n(tb_n), .z(tb_z), .v(tb_v));
	
	// generating clock
	always
	begin
		clk = 1; clk = 0; #5;
	end
		
	// read testvector file and store testvectors to testvectors register.
	initial
	begin
		$readmemh("C:/Users/user/Desktop/verilog/assignment04-alu32/tb_alu32.tv", testvectors);
		vectornum = 0; errors = 0;
		reset = 1; #27; reset = 0;
	end
	
	// as clock becomes a rising edge,  the value of testvectors register is stored to tb registers.
	always@ (posedge clk)
	begin
		#1; {tb_a, tb_b, tb_op, tb_rexp} = testvectors[vectornum];
	end
	
	// as clock becomes a falling edge, the value of testvectors register is stored to tb registers.
	always@ (negedge clk)
	if(~reset)
	begin
		// check the real value and expected value.
		if(tb_result !== tb_rexp)
		begin
			$display("Error: inputs = %h", {tb_a, tb_b, tb_op});
			$display("Error: outputs = %h (%h expected)", tb_result, tb_rexp);
			errors = errors + 1;
		end
		
		// move to next testvector.
		vectornum = vectornum + 1;
		
		// end of tb. display the result of testbench.
		if(testvectors[vectornum] === 100'bx)
		begin
			$display("%d tests completed with %d errors", vectornum, errors);
			$finish;
		end
	end
endmodule
