module tl_cntr_w_left_struct(clk, reset_n, Ta, Tal, Tb, Tbl, La, Lb);
	input clk, reset_n;
	input Ta, Tal, Tb, Tbl;
	output [1:0] La, Lb;
	
	wire [2:0] state, next_state;
	
	// seperate filp flop part and combinational logic circuit part.
	// combinational logic circuit part is seperated ns_logic and o_logic.
	_dff_r_async u0_dff_r_async(.clk(clk), .reset_n(reset_n), .next_state(next_state), .state(state));
	ns_logic u1_ns_logic(.state(state), .Ta(Ta), .Tal(Tal), .Tb(Tb), .Tbl(Tbl), .next_state(next_state));
	o_logic u2_o_logic(.state(state), .La(La), .Lb(Lb));
endmodule
