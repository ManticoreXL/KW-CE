module tb_fa;
	reg tb_a, tb_b, tb_ci;
	wire tb_co, tb_s;
	
	fa u0_fa(.a(tb_a), .b(tb_b), .ci(tb_ci), .co(tb_co), .s(tb_s));
	
	initial
	begin
		tb_ci = 0; tb_a = 0; tb_b = 0; #10;
		tb_ci = 0; tb_a = 0; tb_b = 1; #10;
		tb_ci = 0; tb_a = 1; tb_b = 0; #10;
		tb_ci = 0; tb_a = 1; tb_b = 1; #10;
		tb_ci = 1; tb_a = 0; tb_b = 0; #10;
		tb_ci = 1; tb_a = 0; tb_b = 1; #10;
		tb_ci = 1; tb_a = 1; tb_b = 0; #10;
		tb_ci = 1; tb_a = 1; tb_b = 1; #10;
		
		$finish;
	end
endmodule
