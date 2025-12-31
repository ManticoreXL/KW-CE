module tb_dff;
	reg tb_clk;
	reg tb_d;
	wire tb_q, tb_q_bar;
	
	_dff u0_dff(.clk(tb_clk), .d(tb_d), .q(tb_q), .q_bar(tb_q_bar));
	
	// make clock signal
	always #7.5 tb_clk = ~tb_clk;
	
	initial
	begin
	tb_clk = 0; tb_d = 0;
	
	#10; tb_d = 1;
	#10; tb_d = 0;
	#10; tb_d = 0;
	#10; tb_d = 1;
	#10; tb_d = 1;
	#10; tb_d = 0;
	#10; tb_d = 0;
	#10; tb_d = 1;
	#10; tb_d = 0;
	
	#10; $finish;
	
	end

endmodule
