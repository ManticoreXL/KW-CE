module tb_arbiter;
	reg tb_clk;
	reg tb_state;
	reg tb_m0_req, tb_m1_req;
	wire tb_m0_grant, tb_m1_grant;
	wire tb_next_state;
	
	always #10 tb_clk = ~tb_clk;
	
	arbiter u0_arbiter(.clk(tb_clk), .state(tb_state), .m0_req(tb_m0_req), .m1_req(tb_m1_req), .m0_grant(tb_m0_grant), .m1_grant(tb_m1_grant), .next_state(tb_next_state));
	
	initial
	begin
		tb_clk = 0; #10;
		
		tb_state = 0; #10;
		tb_m0_req = 0; tb_m1_req = 0; #50;
		tb_m0_req = 1; tb_m1_req = 0; #50
		tb_m0_req = 0; tb_m1_req = 1; #50;
		tb_m0_req = 1; tb_m1_req = 1; #50;
		
		tb_state = 1; #10;
		tb_m0_req = 0; tb_m1_req = 0; #50;
		tb_m0_req = 1; tb_m1_req = 0; #50
		tb_m0_req = 0; tb_m1_req = 1; #50;
		tb_m0_req = 1; tb_m1_req = 1; #50;

		$stop;
	end
endmodule
