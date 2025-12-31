module ns_logic(state, Ta, Tal, Tb, Tbl, next_state);
	input [2:0] state;
	input Ta, Tal, Tb, Tbl;
	output [2:0] next_state;
	
	wire w_state2_n, w_state1_n, w_state0_n;
	wire w_Ta_n, w_Tal_n, w_Tb_n, w_Tbl_n;
	wire w_d2_1, w_d2_2, w_d2_3;
	wire w_d0_1, w_d0_2, w_d0_3, w_d0_4;
		
	// inversed inputs
	_inv u0_inv(.a(state[2]), .y(w_state2_n));
	_inv u1_inv(.a(state[1]), .y(w_state1_n));
	_inv u2_inv(.a(state[0]), .y(w_state0_n));
	_inv u3_inv(.a(Ta), .y(w_Ta_n));
	_inv u4_inv(.a(Tal), .y(w_Tal_n));
	_inv u5_inv(.a(Tb), .y(w_Tb_n));
	_inv u6_inv(.a(Tbl), .y(w_Tbl_n));
	
	// state[2]
	_and3 u7_and3(.a(w_state2_n), .b(state[1]), .c(state[0]), .y(w_d2_1));
	_and2 u8_and2(.a(state[2]), .b(w_state1_n), .y(w_d2_2));
	_and3 u9_and2(.a(state[2]), .b(state[1]), .c(w_state0_n), .y(w_d2_3));
	_or3 u10_or3(.a(w_d2_1), .b(w_d2_2), .c(w_d2_3), .y(next_state[2]));
	
	// state[1]
	_xor2 u11_xor2(.a(state[1]), .b(state[0]), .y(next_state[1]));
	
	// state[0]
	_and4 u12_and4(.a(w_state2_n), .b(w_state1_n), .c(w_state0_n), .d(w_Ta_n), .y(w_d0_1));
	_and4 u13_and4(.a(w_state2_n), .b(state[1]), .c(w_state0_n), .d(w_Ta_n), .y(w_d0_2));
	_and4 u14_and4(.a(state[2]), .b(w_state1_n), .c(w_state0_n), .d(w_Ta_n), .y(w_d0_3));
	_and4 u15_and4(.a(state[2]), .b(state[1]), .c(w_state0_n), .d(w_Ta_n), .y(w_d0_4));
	_or4 u16_or4(.a(w_d0_1), .b(w_d0_2), .c(w_d0_3), .d(w_d0_4), .y(next_state[0]));
endmodule
