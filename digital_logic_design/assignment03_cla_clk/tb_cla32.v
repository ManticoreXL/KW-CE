`timescale 1ns/100ps

module tb_cla32;
	reg [31:0] tb_a, tb_b;
	reg tb_ci;
	wire tb_co;
	wire [31:0] tb_s;
	
	cla32 u0_cla32(.a(tb_a), .b(tb_b), .ci(tb_ci), .co(tb_co), .s(tb_s));
	
	initial
	begin
		tb_a = 0; tb_b = 0; tb_ci = 0;
		
		// tests each input
		#10; tb_a = 32'hffff_ffff; tb_b = 0; tb_ci = 0;
		#10; tb_a = 0; tb_b = 32'hffff_ffff; tb_ci = 0;
		#10; tb_a = 0; tb_b = 0; tb_ci = 1'b1;
		
		// tests sum
		#10; tb_a = 32'hf0f0_f0f0; tb_b = 32'h0f0f_0f0f; tb_ci = 0;
		
		// tests sum and carry in
		#10; tb_a = 32'h0000_0001;	tb_b = 32'h0000_0001; tb_ci = 0;
		#10; tb_a = 32'h0000_0001;	tb_b = 32'h0000_0001; tb_ci = 1'b1;		
		
		// tests carry out
		#10; tb_a = 32'hffff_ffff; tb_b = 0; tb_ci = 1'b1;
		
		#10; $finish;
	
	end	
endmodule
