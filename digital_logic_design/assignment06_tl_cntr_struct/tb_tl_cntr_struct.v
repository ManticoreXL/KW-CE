module tb_tl_cntr_struct;
	reg tb_clk, tb_reset_n, tb_Ta, tb_Tb;
	wire [1:0] tb_La, tb_Lb;
	
	tl_cntr_struct u0_tl_cntr_struct(.clk(tb_clk), .reset_n(tb_reset_n), 
							 .Ta(tb_Ta), .Tb(tb_Tb),
							 .La(tb_La), .Lb(tb_Lb));
		
	// clock generation
	always #5 tb_clk = ~tb_clk;
	
	initial
	begin
	tb_clk = 0; tb_reset_n = 0; tb_Ta = 0; tb_Tb = 0; #10;
	tb_reset_n = 1;
	
	// S0: Academic Avenue is GREEN, Bravado Boulevard is RED.
	tb_Ta = 1; #50;
	
	// S1: Academic Avenue is YELLOW, Bravado Boulevard is still RED.
	tb_Ta = 0; #50;
	
	// S2: Academic Avenue is RED, Bravado Boulevard is GREEN.
	tb_Tb = 1; #50;
	
	// S3: Academic Avenue is still RED, Bravado Boulevard is YELLOW.
	tb_Tb = 0; #50;
	
	// return to S0.
	tb_Ta = 1; #50;
	
	$stop;
	end
endmodule
