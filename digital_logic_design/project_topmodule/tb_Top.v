module tb_Top;
	reg tb_clk, tb_reset_n;
	reg tb_m_req, tb_m_wr;
	reg [15:0] tb_m_addr;
	reg [63:0] tb_m_dout;
	wire tb_m_grant;
	wire [63:0] tb_m_din;
	wire tb_interrupt;
	
	// generate clock
	always#5 tb_clk = ~tb_clk;
	
	// duv
	Top u0_Top(.clk(tb_clk), .reset_n(tb_reset_n), .m_req(tb_m_req), .m_wr(tb_m_wr), .m_addr(tb_m_addr),
				  .m_dout(tb_m_dout), .m_grant(tb_m_grant), .m_din(tb_m_din), .interrupt(tb_interrupt));
				  
	initial
	begin
		tb_clk = 0; tb_reset_n = 0; tb_m_req = 0; tb_m_wr = 0; #10;
		tb_reset_n = 1; #10;
		
		tb_m_req = 1; tb_m_wr = 1; #10;
		
		// set operand
		tb_m_addr = 16'h7020; tb_m_dout = 64'h0000_0000_0000_0005; #50;
		
		// set opstart
		tb_m_addr = 16'h7000; tb_m_dout = 64'h0000_0000_0000_0001; #50;
		
		tb_m_wr = 0; tb_m_addr = 16'h7030;
		#50000;
		
		$stop;
	end
endmodule
