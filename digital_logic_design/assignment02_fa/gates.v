// gates.v for CED2 assignment of Verilog Implementation.
// includes inverter, and, or, nand, nor, xor
// 2023-09-19

module _inv(a, y);
	input a;
	output y;
	
	assign y = ~a;
endmodule

module _and2(a, b, y);
	input a, b;
	output y;
	
	assign y = a & b;
endmodule

module _nand2(a, b, y);
	input a, b;
	output y;
	
	assign y = ~ (a & b);
endmodule

module _or2(a, b, y);
	input a, b;
	output y;
	
	assign y = a | b;
endmodule

module _nor2(a, b, y);
	input a, b;
	output y;
	
	assign y = ~ (a | b);
endmodule

// 2 input XOR gate implementation with using inverter, and, or gates
module _xor2(a, b, y);
	input a, b;
	output y;
	wire inv_a, inv_b;
	wire w0, w1;
	
	_inv u0_inv(.a(a), .y(inv_a));
	_inv u1_inv(.a(b), .y(inv_b));
	
	_and2 u2_and2(.a(inv_a), .b(b), .y(w0));
	_and2 u3_and2(.a(a), .b(inv_b), .y(w1));
	
	_or2 u4_or2(.a(w0), .b(w1), .y(y));	
endmodule
	
	
