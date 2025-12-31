module tb_bus;
	reg tb_clk, tb_reset_n;
	reg tb_m0_req, tb_m0_wr, tb_m1_req, tb_m1_wr; 
	reg [7:0] tb_m0_address, tb_m1_address;
	reg [31:0] tb_m0_dout, tb_m1_dout, tb_s0_dout, tb_s1_dout;
	wire tb_m0_grant, tb_m1_grant;
	wire tb_s0_sel, tb_s1_sel, tb_s_wr;
	wire [7:0] tb_s_address;
	wire [31:0] tb_m_din, tb_s_din;
	
	always #5 tb_clk = ~tb_clk;
	
	bus u0_bus(.clk(tb_clk), .reset_n(tb_reset_n), .m0_req(tb_m0_req), .m0_wr(tb_m0_wr), .m1_req(tb_m1_req), .m1_wr(tb_m1_wr),
				  .m0_address(tb_m0_address), .m1_address(tb_m1_address), .m0_dout(tb_m0_dout), .m1_dout(tb_m1_dout), 
				  .s0_dout(tb_s0_dout), .s1_dout(tb_s1_dout), .m0_grant(tb_m0_grant), .m1_grant(tb_m1_grant), 
				  .s0_sel(tb_s0_sel), .s1_sel(tb_s1_sel), .s_wr(tb_s_wr), .s_address(tb_s_address), 
				  .m_din(tb_m_din), .s_din(tb_s_din));
				  
	initial
	begin
		tb_clk = 0; tb_reset_n = 0; tb_m0_req = 0; tb_m0_wr = 0; tb_m1_req = 0; tb_m1_wr = 0; tb_m0_address = 0; tb_m1_address = 0; tb_m0_dout = 0; tb_m1_dout = 0; tb_s0_dout = 0; tb_s1_dout = 0; #10;
		tb_reset_n = 1; #20;
		
		// test using master0-slave0
		tb_m0_req = 1; tb_m0_wr = 1; tb_m0_address = 8'b0000_0000; tb_m0_dout = 32'hffff_ffff; tb_s0_dout = 32'hffff_ffff; #50;
		
		// test using master0-slave1
		tb_m0_address = 8'b0010_0000; tb_m0_dout = 32'hdead_dead; tb_s1_dout = 32'hdead_dead; #50;
		
		tb_m0_req = 0; #20;
		
		// test using master1-slave0
		tb_m1_req = 1; tb_m0_wr = 1; tb_m1_address = 8'b0000_0000; tb_m1_dout = 32'hffff_ffff; tb_s0_dout = 32'hffff_ffff; #50;
		
		// test using master1-slave1
		tb_m1_address = 8'b0010_0000; tb_m1_dout = 32'hdead_dead; tb_s1_dout = 32'hdead_dead; #50;
		
		$stop;
	end
endmodule
	