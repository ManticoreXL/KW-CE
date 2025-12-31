module bus(clk, reset_n, m0_req, m0_wr, m0_address, m0_dout, 
			  m1_req, m1_wr, m1_address, m1_dout, s0_dout, s1_dout,
			  m0_grant, m1_grant, m_din, s0_sel, s1_sel, s_address, s_wr, s_din);	  
	input clk, reset_n;
	input m0_req, m0_wr, m1_req, m1_wr;
	input [7:0] m0_address, m1_address;
	input [31:0] m0_dout, m1_dout, s0_dout, s1_dout;
	output m0_grant, m1_grant;
	output s0_sel, s1_sel, s_wr;
	output [7:0] s_address;
	output [31:0] m_din, s_din;
	
	// declare variables
	reg state;
	wire next_state;
	wire w_s0_sel, w_s1_sel;
	wire [7:0] w_address;
	wire [31:0] w_din;
	
	// register for state
	always@(posedge clk or negedge reset_n)
	begin
		if(reset_n == 0)
			state <= 1'b0;
		else
			state <= next_state;
	end
	
	// arbiter (next state logic)
	arbiter u0_arbiter(.clk(clk), .state(state), .m0_req(m0_req), .m1_req(m1_req), .m0_grant(m0_grant), .m1_grant(m1_grant), .next_state(next_state));
	
	// select wr, address, s_din
	mux2 u1_mux2(.d0(m0_wr), .d1(m1_wr), .s(state), .y(s_wr));
	mux2_8bit u2_mux2_8bit(.d0(m0_address), .d1(m1_address), .s(state), .y(w_address));
	mux2_32bit u3_mux2_32bit(.d0(m0_dout), .d1(m1_dout), .s(state), .y(w_din));

	// address decoder
	address_decoder u4_address_decoder(.address(w_address), .s0_sel(w_s0_sel), .s1_sel(w_s1_sel));

	// select m_din
	mux3_32bit u5_mux3_32bit(.d00(32'h0), .d01(s1_dout), .d10(s0_dout), .s({w_s0_sel, w_s1_sel}), .y(m_din));
	
	// assign area
	assign s0_sel = w_s0_sel;
	assign s1_sel = w_s1_sel;
	assign s_address = w_address;
	assign s_din = w_din;
endmodule
