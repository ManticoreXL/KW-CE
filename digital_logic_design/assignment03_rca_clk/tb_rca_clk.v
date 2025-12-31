`timescale 1ns/100ps

module tb_rca_clk;
	reg clk;
	reg [31:0] tb_a, tb_b;
	reg tb_ci;
	wire tb_co;
	wire [31:0] tb_s;
	
	parameter STEP = 10;
	
	rca_clk u0_rca_clk(.clk(clk), .a(tb_a), .b(tb_b), .ci(tb_ci), .co(tb_co), .s(tb_s));
	
	always #(STEP/2) clk = ~clk;
	
	initial
	begin
	clk = 1'b1; tb_a = 0; tb_b = 0; tb_ci = 0;
	
	// tests a, b, ci
	#(STEP); tb_a = 32'hffff_ffff; tb_b = 0; tb_ci = 0;
	#(STEP); tb_a = 0; tb_b = 32'hffff_ffff; tb_ci = 0;
	#(STEP); tb_a = 0; tb_b = 0; tb_ci = 1'b1;

	// tests summing
	#(STEP); tb_a = 32'hf0f0_f0f0; tb_b = 32'h0f0f_0f0f ; tb_ci = 0;

	// tests sum and carry out
	#(STEP); tb_a = 32'h5555_5555; tb_b = 32'h5555_5555; tb_ci = 0;
	#(STEP); tb_a = 32'h0000_0001; tb_b = 32'h0000_0001; tb_ci = 1;

	// tests overflow (last carry out)
	#(STEP); tb_a = 32'hffff_ffff; tb_b = 0; tb_ci = 1'b1;
	
	#(STEP*2); $stop;
	end		
endmodule
