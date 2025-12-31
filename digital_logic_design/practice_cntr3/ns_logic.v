module ns_logic(state, inc, next_state);
	input [1:0] state;
	input inc;
	output [1:0] next_state;
	
	wire w_s1_n, w_s0_n, w_inc_n;
	wire w_d1_1, w_d1_2;
	wire w_d0_1, w_d0_2;
	
	// inversed inputs
	_inv u0_inv(.a(state[1]), .y(w_s1_n));
	_inv u1_inv(.a(state[0]), .y(w_s0_n));
	_inv u2_inv(.a(inc), .y(w_inc_n));
	
	// d1 = !q1!q0!inc + !q1q0inc
	_and3 u3_and3(.a(w_s1_n), .b(w_s0_n), .c(w_inc_n), .y(w_d1_1));
	_and3 u4_and4(.a(w_s1_n), .b(state[0]), .c(inc), .y(w_d1_2));
	_or2 u5_or2(.a(w_d1_1), .b(w_d1_2), .y(next_state[1]));
	
	// d0 = !q1!q0inc + q1!q0!inc
	_and3 u6_and3(.a(w_s1_n), .b(w_s0_n), .c(inc), .y(w_d0_1));
	_and3 u7_and3(.a(state[1]), .b(w_s0_n), .c(w_inc_n), .y(w_d0_2));
	_or2 u8_or2(.a(w_d0_1), .b(w_d0_2), .y(next_state[0]));
endmodule
