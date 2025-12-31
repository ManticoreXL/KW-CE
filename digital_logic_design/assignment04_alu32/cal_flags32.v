// 32 bits flag calculator
module cal_flags32(op, result, co_add, co_prev_add, c, n, z, v);
	input [2:0] op;
	input [31:0] result;
	input co_add, co_prev_add;
	output c, n, z, v;
	
	// carry out
	assign c = (op[2:1] != 2'b11) ? 1'b0 : co_add;
	// negative
	assign n = result[31];
	// zero
	assign z = (result == 32'b0) ? 1'b1 : 1'b0;
	// overflow
	assign v = (op[2:1] != 2'b11) ? 1'b0 : co_add ^ co_prev_add;
endmodule
