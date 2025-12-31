module tb_BUS;
	reg tb_clk, tb_reset_n;
	reg tb_m_req, tb_m_wr;
	reg [15:0] tb_m_addr;
	reg [63:0] tb_m_dout, tb_s0_dout, tb_s1_dout;
	wire tb_m_grant;
	wire tb_s0_sel, tb_s1_sel, tb_s_wr;
	wire [15:0] tb_s_addr;
	wire [63:0] tb_m_din, tb_s_din;
	
	always #5 tb_clk = ~tb_clk;
	
	BUS u0_BUS(.clk(tb_clk), .reset_n(tb_reset_n), .m_req(tb_m_req), .m_wr(tb_m_wr), .m_addr(tb_m_addr), .m_dout(tb_m_dout),
				  .s0_dout(tb_s0_dout), .s1_dout(tb_s1_dout), .m_grant(tb_m_grant), .s0_sel(tb_s0_sel), .s1_sel(tb_s1_sel), 
				  .s_wr(tb_s_wr), .s_addr(tb_s_addr), .m_din(tb_m_din), .s_din(tb_s_din));
				  
	initial
	begin
		tb_clk = 0; tb_reset_n = 0; tb_m_req = 0; tb_m_wr = 0; tb_m_addr = 0; tb_m_dout = 0; tb_s0_dout = 0; tb_s1_dout = 0; #10;
		tb_reset_n = 1; #10;
		
		tb_s0_dout = 64'hdead_dead_dead_dead; tb_s1_dout = 64'habcd_abcd_abcd_abcd; #10;
		
		// test m to s0
		tb_m_req = 1; #10;
		tb_m_wr = 1; tb_m_addr = 16'h0000; tb_m_dout = 64'hffff_ffff_ffff_ffff; #50;
		tb_m_addr = 16'h07FF; #50;
		
		// test m to s1
		tb_m_wr = 1; tb_m_addr = 16'h7000; tb_m_dout = 64'h1111_1111_1111_1111; #50;
		tb_m_addr = 16'h71FF; #50;
		
		$stop;
	end
endmodule
	