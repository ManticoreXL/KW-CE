module ns_logic(state, Ta, Tb, next_state);
	input [1:0] state;
	input Ta, Tb;
	output [1:0] next_state;
	
	wire w_state1_n, w_state0_n;
	wire w_Ta_n, w_Tb_n;
	wire w_d0_1, w_d0_2;
	
	// inversed inputs
	_inv u0_inv(.a(state[1]), .y(w_state1_n));
	_inv u1_inv(.a(state[0]), .y(w_state0_n));
	_inv u2_inv(.a(Ta), .y(w_Ta_n));
	_inv u3_inv(.a(Tb), .y(w_Tb_n));
	
	// state[1]
	_xor2 u4_xor2(.a(state[1]), .b(state[0]), .y(next_state[1]));

	// state[0]
	_and3 u5_and3(.a(w_state1_n), .b(w_state0_n), .c(w_Ta_n), .y(w_d0_1));
	_and3 u6_and3(.a(state[1]), .b(w_state0_n), .c(w_Tb_n), .y(w_d0_2));
	_or2 u7_or2(.a(w_d0_1), .b(w_d0_2), .y(next_state[0]));
endmodule
