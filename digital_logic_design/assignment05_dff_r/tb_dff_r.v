module tb_dff_r;
	reg tb_clk;
	reg tb_reset_n, tb_d;
	wire tb_q;
	
	_dff_r u0_dff_r(.clk(tb_clk), .reset_n(tb_reset_n), .d(tb_d), .q(tb_q));
	
	// make clock signal
	always #7.5 tb_clk = ~tb_clk;
	
	initial
	begin
	tb_clk = 0; tb_reset_n = 0; tb_d = 0;
	
	#10; tb_reset_n = 0; tb_d = 1;
	#10; tb_reset_n = 0; tb_d = 1;
	#10; tb_reset_n = 1; tb_d = 0;
	#10; tb_reset_n = 1; tb_d = 0;
	#10; tb_reset_n = 1; tb_d = 1;
	#10; tb_reset_n = 1; tb_d = 1;
	#10; tb_reset_n = 0; tb_d = 0;
	#10; tb_reset_n = 0; tb_d = 0;
	
	#10; $finish;
	end
endmodule

	