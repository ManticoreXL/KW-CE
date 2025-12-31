module tb_dff_en;
	reg tb_clk;
	reg tb_d, tb_en;
	wire tb_q;

	_dff_en u0_dff_en(.clk(tb_clk), .en(tb_en), .d(tb_d), .q(tb_q));
	
	// make clock signal
	always #7.5 tb_clk = ~tb_clk;

	
	initial
	begin
	tb_clk = 0; tb_en = 0; tb_d = 0;
	
	#10; tb_en = 0; tb_d = 1;
	#10; tb_en = 1; tb_d = 1;
	#10; tb_en = 0; tb_d = 0;
	#10; tb_en = 1; tb_d = 0;
	#10; tb_en = 0; tb_d = 1;
	#10; tb_en = 1; tb_d = 1;
	#10; tb_en = 0; tb_d = 0;
	#10; tb_en = 1; tb_d = 0;
	#10; tb_en = 0; tb_d = 1;
	#10; tb_en = 1; tb_d = 1;
	
	#10; $finish;
	end
endmodule
