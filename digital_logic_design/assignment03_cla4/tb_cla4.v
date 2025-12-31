`timescale 1ns/100ps

module tb_cla4;
	reg [3:0] tb_a, tb_b;
	reg tb_ci;
	wire tb_co;
	wire [3:0] tb_s;
	
	cla4 u0_cla4(.a(tb_a), .b(tb_b), .ci(tb_ci), .co(tb_co), .s(tb_s));
	
	initial
	begin
	tb_a = 0; tb_b = 0; tb_ci = 0;
	
	#10; tb_a = 4'b1111; tb_b = 0; tb_ci = 0;
	#10; tb_a = 0; tb_b = 4'b1111; tb_ci = 0;
	#10; tb_a = 0; tb_b = 0; tb_ci = 1'b1;
	
	#10; tb_a = 4'b1010; tb_b = 4'b0101; tb_ci = 0;
	
	#10; tb_a = 4'b0010; tb_b = 4'b0010; tb_ci = 0;
	#10; tb_a = 4'b0001; tb_b = 4'b0001; tb_ci = 1'b1;
	
	#10; tb_a = 4'b1111; tb_b = 4'b0001; tb_ci = 0;
	
	#10; $finish;
	end
endmodule
