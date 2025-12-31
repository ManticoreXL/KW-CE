module tb_register32;
	reg tb_clk;
	reg [31:0] tb_d;
	wire [31:0] tb_q;
	
	_register32 u0_register32(.clk(tb_clk), .d(tb_d), .q(tb_q));
	
	// make clock signal
	always #7.5 tb_clk = ~tb_clk;
	
	initial
	begin
	tb_clk = 0; tb_d = 0;
	
	#30; tb_d = 32'h1234_5678;
	#30; tb_d = 32'hffff_ffff;
	#30; tb_d = 32'h2020_2020;
	
	#30; $finish;
	end
endmodule
