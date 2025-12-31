`timescale 1ns/100ps

module tb_mx2;

	reg tb_d0, tb_d1, tb_s;
	wire tb_y;
	
	mx2 mx20(.d0(tb_d0), .d1(tb_d1), .s(tb_s), .y(tb_y));
	
	// tests whole cases
	initial begin
		tb_d0 = 0; tb_d1 = 0; tb_s = 0;
		#10;
		
		tb_d0 = 0; tb_d1 = 0; tb_s = 1;
		#10;
		
		tb_d0 = 0; tb_d1 = 1; tb_s = 0;
		#10;
		
		tb_d0 = 0; tb_d1 = 1; tb_s = 1;
		#10;
		
		tb_d0 = 1; tb_d1 = 0; tb_s = 0;
		#10;
		
		tb_d0 = 1; tb_d1 = 0; tb_s = 1;
		#10;
		
		tb_d0 = 1; tb_d1 = 1; tb_s = 0;
		#10;
		
		tb_d0 = 1; tb_d1 = 1; tb_s = 1;
		#10;
		
		$finish;		
	end
endmodule
