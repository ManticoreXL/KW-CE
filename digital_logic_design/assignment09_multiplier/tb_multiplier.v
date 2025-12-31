`timescale 1ns/100ps

module tb_multiplier;									
	reg tb_clk, tb_reset_n, tb_op_start, tb_op_clear;		
	reg [63:0] tb_multiplier, tb_multiplicand;
	wire tb_op_done;
	wire [127:0] tb_result;

	// clock generation
	always #5 tb_clk = ~tb_clk;

	//instace of duv
	multiplier u0_multiplier(.clk(tb_clk), .reset_n(tb_reset_n), .multiplier(tb_multiplier), .multiplicand(tb_multiplicand),
									 .op_start(tb_op_start), .op_clear(tb_op_clear), .op_done(tb_op_done), .result(tb_result));
	
	initial
	begin				
		// initialization
		tb_clk = 0; tb_reset_n = 0; tb_op_start = 0; tb_op_clear = 0; #10;
		tb_reset_n=1; #10;
		
		// test multiplication
		tb_multiplier = 12; tb_multiplicand = 4; #10;
		tb_op_start = 1; #100;	
		tb_op_start = 0; #10;
		tb_op_clear = 1; #10;

		$stop;	
	end
		
endmodule
