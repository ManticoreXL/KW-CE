module tb_tl_cntr_w_left_struct;
	reg tb_clk, tb_reset_n,  tb_Ta, tb_Tal, tb_Tb, tb_Tbl;
	wire [1:0] tb_La,  tb_Lb;
	
	tl_cntr_w_left_struct u0_tl_cntr_w_left_struct(.clk(tb_clk), .reset_n(tb_reset_n),
												.Ta(tb_Ta), .Tal(tb_Tal), 
												.Tb(tb_Tb), .Tbl(tb_Tbl),
												.La(tb_La), .Lb(tb_Lb));
												
	always #5 tb_clk = ~tb_clk;
	
	initial
	begin
		tb_clk = 0; tb_reset_n = 0; tb_Ta = 0; tb_Tal = 0; tb_Tb = 0; tb_Tbl = 0; #10;
		tb_reset_n = 1; #10;
		
		// S0: Academic Avenue is GREEN, Bravado Boulevard is RED.
		tb_Ta = 1; #20;
		
		// S1: Academic Avenue is YELLOW, Bravado Boulevard is still RED.
		tb_Ta = 0; #20;
		
		// S2: Academic Avenue is LEFT, Bravado Boulevard is still RED.
		tb_Tal = 1; #20;
		
		// S3: Academic Avenue is YELLOW, Bravado Boulevard is still RED.
		tb_Tal = 0; #20;
		
		// S4: Academic Avenue is RED, Bravado Boulevard is GREEN.
		tb_Tb = 1; #20;
		
		// S5: Academic Avenue is still RED, Bravado Boulevard is YELLOW.
		tb_Tb = 0; #20;
		
		// S6: Academic Avenue is still RED, Bravado Boulevard is LEFT.
		tb_Tbl = 1; #20;
		
		// S7: Academic Avenue is still RED, Bravado Boulevard is YELLOW.
		tb_Tbl = 0; #20;
		
		$stop;
	end
endmodule		
