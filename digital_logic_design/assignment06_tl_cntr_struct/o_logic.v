module o_logic(state, La, Lb);
	input [1:0] state;
	output [1:0] La, Lb;
	
	wire w_state1_n;
	
	// inversed input
	_inv u0_inv(.a(state[1]), .y(w_state1_n));
	
	// La[1]
	_buf u1_buf(.a(state[1]), .y(La[1]));
	
	// La[0]
	_and2 u2_and2(.a(w_state1_n), .b(state[0]), .y(La[0]));

	// Lb[1]
	_buf u3_buf(.a(w_state1_n), .y(Lb[1]));

	// Lb[0]
	_and2 u4_and2(.a(state[1]), .b(state[0]), .y(Lb[0]));
endmodule
