module o_logic(state, La, Lb);
	input [2:0] state;
	output [1:0] La, Lb;
	
	wire w_state2_n, w_state1_n, w_state0_n;
	wire w_La1;
	wire w_La0_1, w_La0_2, w_La0_3, w_La0_4;
	wire w_Lb1;
	wire w_Lb0_1, w_Lb0_2, w_Lb0_3, w_Lb0_4;
	
	// inversed inputs
	_inv u0_inv(.a(state[2]), .y(w_state2_n));
	_inv u1_inv(.a(state[1]), .y(w_state1_n));
	_inv u2_inv(.a(state[0]), .y(w_state0_n));
	
	// La[1]	
	_and2 u3_and2(.a(state[1]), .b(w_state0_n), .y(w_La1));
	_or2 u4_or2(.a(state[2]), .b(w_La1), .y(La[1]));
	
	// La[0]
	_and2 u5_and2(.a(state[2]), .b(w_state0_n), .y(w_La0_1));
	_and2 u6_and2(.a(state[2]), .b(w_state1_n), .y(w_La0_2));
	_and2 u7_and2(.a(state[1]), .b(state[0]), .y(w_La0_3));
	_and2 u8_and2(.a(w_state2_n), .b(state[0]), .y(w_La0_4));
	_or4 u9_or4(.a(w_La0_1), .b(w_La0_2), .c(w_La0_3), .d(w_La0_4), .y(La[0]));
	
	// Lb[1]
	_and2 u10_and2(.a(state[1]), .b(w_state0_n), .y(w_Lb1));
	_or2 u11_or2(.a(w_state2_n), .b(w_Lb1), .y(Lb[1]));
	
	// Lb[0]
	_and2 u12_and2(.a(w_state2_n), .b(w_state0_n), .y(w_Lb0_1));
	_and2 u13_and2(.a(w_state2_n), .b(w_state1_n), .y(w_Lb0_2));
	_and2 u14_and2(.a(state[2]), .b(state[0]), .y(w_Lb0_3));
	_and2 u15_and2(.a(state[1]), .b(state[0]), .y(w_Lb0_4));
	_or4 u16_or4(.a(w_Lb0_1), .b(w_Lb0_2), .c(w_Lb0_3), .d(w_Lb0_4), .y(Lb[0]));
endmodule
