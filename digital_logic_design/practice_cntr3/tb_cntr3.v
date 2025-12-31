module tb_cntr3;
	reg tb_clk, tb_reset_n, tb_inc;
	wire [1:0] tb_cnt;
	
	cntr3 u0_cntr3(.clk(tb_clk), .reset_n(tb_reset_n), .inc(tb_inc), .cnt(tb_cnt));
	
	// generate clock
	always #5 tb_clk = ~tb_clk;
	
	initial
	begin
		tb_clk = 0; tb_reset_n = 0; tb_inc = 0; #10;
		tb_reset_n = 1; #10;
		
		tb_inc = 1; #50;
		tb_inc = 0; #50;
		
		$finish;
	end
endmodule
