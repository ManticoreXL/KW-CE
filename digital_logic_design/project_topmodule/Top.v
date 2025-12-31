module Top(clk, reset_n, m_req, m_wr, m_addr, m_dout, m_grant, m_din, interrupt);
	input clk, reset_n;
	input m_req, m_wr;
	input [15:0] m_addr;
	input [63:0] m_dout;
	output m_grant;
	output [63:0] m_din;
	output interrupt;
	
	// s0 = Memory, 
	// slave 0's address is 0x0000-0x07ff
	// s1 = FactoCore
	// slave 1's address is 0x7000-0x71ff
	
	// wire instance
	wire w_s0_sel, w_s1_sel, w_s_wr;
	wire [15:0] w_s_addr;
	wire [63:0] w_s_din, w_s0_dout, w_s1_dout;
	wire [7:0] w_RAM_addr;
	
	assign w_RAM_addr = w_s_addr[10:3];
	
	BUS u0_BUS(.clk(clk), .reset_n(reset_n), .m_req(m_req), .m_wr(m_wr), .m_addr(m_addr), 
				  .m_dout(m_dout), .s0_dout(w_s0_dout), .s1_dout(w_s1_dout),
				  .m_grant(m_grant), .s0_sel(w_s0_sel), .s1_sel(w_s1_sel), .s_wr(w_s_wr),
				  .s_addr(w_s_addr), .m_din(m_din), .s_din(w_s_din));
				  
	RAM u1_RAM(.clk(clk), .cen(w_s0_sel), .wen(w_s_wr), .addr(w_RAM_addr), .din(w_s_din), .dout(w_s0_dout));
	
	FactoCore u2_FactoCore(.clk(clk), .reset_n(reset_n), .s_sel(w_s1_sel), .s_wr(w_s_wr), .s_addr(w_s_addr), 
								  .s_din(w_s_din), .s_dout(w_s1_dout), .interrupt(interrupt));

endmodule
