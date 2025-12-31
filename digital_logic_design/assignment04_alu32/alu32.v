module alu32(a, b, op, result, c, n, z, v);
	input [31:0] a, b;
	input [2:0] op;
	output [31:0] result;
	output c, n, z, v;
	wire [31:0] w_add_b;
	wire [31:0] w_not_a, w_not_b, w_and, w_or, w_xor, w_xnor, w_add;
	wire co_prev, co_add;
	
	// inverted inputs for NOt and subtraction
	_inv_32bits u0_inv_32bits(.a(a), .y(w_not_a));
	_inv_32bits u1_inv_32bits(.a(b), .y(w_not_b));
	
	// logical operation
	_and2_32bits u2_and2_32bits(.a(a), .b(b), .y(w_and));
	_or2_32bits u3_or2_32bits(.a(a), .b(b), .y(w_or));
	_xor2_32bits u4_xor2_32bits(.a(a), .b(b), .y(w_xor));
	_xnor2_32bits u5_xnor2_32bits(.a(a), .b(b), .y(w_xnor));
	
	// data selector to select between addition and subtraction
	mx2_32bits u6_mx_b(.d0(b), .d1(w_not_b), .s(op[0]), .y(w_add_b));
	cla32_ov u7_adder(.a(a), .b(w_add_b), .ci(op[0]), .co_prev(co_prev), .co(co_add), .s(w_add));
	
	// data selector to select operation
	mx8_32bits u8_mx8_32bits (.a(w_not_a), .b(w_not_b), .c(w_and), .d(w_or), .e(w_xor), .f(w_xnor), .g(w_add), .h(w_add), .s2(op[2]), .s1(op[1]), .s0(op[0]), .y(result));
	
	// flag calculator module
	cal_flags32 u9_cal_flags32(.op(op), .result(result), .co_add(co_add), .co_prev_add(co_prev), .c(c), .n(n), .z(z), .v(v));	
endmodule
