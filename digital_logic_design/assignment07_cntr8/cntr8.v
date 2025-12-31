module cntr8(clk, reset_n, inc, load, d_in, d_out, o_state);
	input clk, reset_n, inc, load;
	input [7:0] d_in;
	output [7:0] d_out;
	output [2:0] o_state;
	
	wire [2:0] next_state;
	wire [2:0] state;
	
	// display state
	assign o_state = next_state;
	
	// instances
	_register3_r u0_register3_r(.clk(clk), .reset_n(reset_n), .d(state), .q(next_state));
	ns_logic u1_ns_logic(.load(load), .inc(inc), .state(next_state), .next_state(state));
	os_logic u2_os_logic(.state(next_state), .d_in(d_in), .d_out(d_out));
endmodule
