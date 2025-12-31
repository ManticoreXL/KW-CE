module cntr3(clk, reset_n, inc, cnt);
	input clk, reset_n, inc;
	output [1:0] cnt;
	
	// 00 = 0
	// 01 = 1
	// 10 = 2	
	wire [1:0] state, next_state;
	
	_dff_r_async u0_dff_r_async(.clk(clk), .reset_n(reset_n), .next_state(next_state), .state(state));
	ns_logic u1_ns_logic(.state(state), .inc(inc), .next_state(next_state));
	
	// generate output
	assign cnt[1] = state[1];
	assign cnt[0] = state[0];
endmodule
