module tb_cntr8;
	reg tb_clk, tb_reset_n, tb_inc, tb_load;
	reg [7:0] tb_d_in;
	
	wire [7:0] tb_d_out;
	wire [2:0] tb_o_state;
	
	cntr8 u0_cntr8(.clk(tb_clk), .reset_n(tb_reset_n), .inc(tb_inc), .load(tb_load), .d_in(tb_d_in), .d_out(tb_d_out), .o_state(tb_o_state));
	
	always #10 tb_clk = ~tb_clk;
	
	initial
	begin
		tb_clk = 0; tb_reset_n = 1; tb_inc = 0; tb_load = 0; tb_d_in = 0; #20;
		
		// test load
		tb_load = 1; tb_d_in = 8'b0000_1100; #20;

		// test inc
		tb_load = 0; tb_inc = 1; #50;
		
		// test dec
		tb_inc = 0; #50;
		
		// test over count / under count
		tb_load = 1; tb_d_in = 8'b1111_1111; #20;
		tb_load = 0; tb_inc = 1; #50;
		tb_inc = 0; #50;
		
		#50; $stop;
	end
endmodule
	