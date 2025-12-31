module BUS(clk, reset_n, m_req, m_wr, m_addr, m_dout, s0_dout, s1_dout,
			  m_grant, m_din, s0_sel, s1_sel, s_addr, s_wr, s_din);
	input clk, reset_n;
	input m_req, m_wr;
	input [15:0] m_addr;
	input [63:0] m_dout, s0_dout, s1_dout;
	output m_grant;
	output s0_sel, s1_sel, s_wr;
	output [15:0] s_addr;
	output [63:0] m_din, s_din;
	
	// declare variables
	reg state;
	wire next_state;
	wire w_s0_sel, w_s1_sel;
	
	always@(posedge clk or negedge reset_n)
	begin
		if(reset_n == 0) state <= 1'b0;
		else state <= next_state;
	end
	
	// arbiter
	arbiter u0_arbiter(.clk(clk), .state(state), .m_req(m_req), .m_grant(m_grant), .next_state(next_state));
	
	// select s_din
	mux3_64bit u2_mux3_64bit(.d00(64'h0), .d01(s1_dout), .d10(s0_dout), .s({w_s0_sel, w_s1_sel}), .y(m_din));
	
	// address decoder
	address_decoder u3_address_decoder(.address(m_addr), .s0_sel(w_s0_sel), .s1_sel(w_s1_sel));
	
	// assign area
	assign s_wr = m_wr;
	assign s_addr = m_addr;
	assign s0_sel = w_s0_sel;
	assign s1_sel = w_s1_sel;
	assign s_din = m_dout;
endmodule
