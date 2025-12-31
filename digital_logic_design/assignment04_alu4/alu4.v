// 4 bits ALU
module alu4(a, b, op, result, c, n, z, v);
	input [3:0] a, b;
	input [2:0] op;
	output [3:0] result;
	output c, n, z, v;
	wire [3:0] w_add_b;
	wire [3:0] w_not_a, w_not_b, w_and, w_or, w_xor, w_xnor, w_add;
	wire c3_add, co_add;
	
	// inverted inputs for subtraction
	_inv_4bits u0_inv_4bits(.a(a), .y(w_not_a));
	_inv_4bits u1_inv_4bits(.a(b), .y(w_not_b));
	
	// ports for operation
	_and2_4bits u2_and2_4bits(.a(a), .b(b), .y(w_and));
	_or2_4bits u3_or2_4bits(.a(a), .b(b), .y(w_or));
	_xor2_4bits u4_xor2_4bits(.a(a), .b(b), .y(w_xor));
	_xnor2_4bits u5_xnor2_4bits(.a(a), .b(b), .y(w_xnor));
	
	// data selector to select between addition and subtraction.
	mx2_4bits u6_mx2_4bits(.d0(b), .d1(w_not_b), .s(op[0]), .y(w_add_b));
	cla4_ov u7_adder(.a(a), .b(w_add_b), .ci(op[0]), .c3(c3_add), .co(co_add), .s(w_add));
	
	// data selector to select operation
	mx8_4bits u7_mx8_4bits(.a(w_not_a), .b(w_not_b), .c(w_and), .d(w_or), .e(w_xor), .f(w_xnor), .g(w_add), .h(w_add), .s2(op[2]), .s1(op[1]), .s0(op[0]), .y(result));
	cal_flags4 u8_cal_flags4(.op(op), .result(result), .co_add(co_add), .c3_add(c3_add), .c(c), .n(n), .z(z), .v(v));
endmodule
