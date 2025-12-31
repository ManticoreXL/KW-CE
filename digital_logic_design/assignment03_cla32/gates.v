// gates.v for CED2 assignment of Verilog Implementation.
// includes inverter, and, or, nand, nor, xor, xnor
// 2023-09-26

// Inverter gate
module _inv(a, y);
	input a;
	output y;
	
	assign y = ~a;
endmodule

//// AND Series ////
// 2 input AND gate
module _and2(a, b, y);
	input a, b;
	output y;
	
	assign y = a & b;
endmodule

// 3 input AND gate
module _and3(a, b, c, y);
	input a, b, c;
	output y;
	
	assign y = a & b & c;
endmodule

// 4 input AND gate
module _and4(a, b, c, d, y);
	input a, b, c, d;
	output y;
	
	assign y = a & b & c & d;
endmodule

// 5 input AND gate
module _and5(a, b, c, d, e, y);
	input a, b, c, d, e;
	output y;
	
	assign y = a & b & c & d & e;
endmodule



//// NAND Series ////
// 2 input NAND gate
module _nand2(a, b, y);
	input a, b;
	output y;
	
	assign y = ~ (a & b);
endmodule



//// OR Series ////
// 2 input OR gate
module _or2(a, b, y);
	input a, b;
	output y;
	
	assign y = a | b;
endmodule

// 3 input OR gate
module _or3(a, b, c, y);
	input a, b, c;
	output y;
	
	assign y = a | b | c;
endmodule

// 4 input OR gate
module _or4(a, b, c, d, y);
	input a, b, c, d;
	output y;
	
	assign y = a | b | c | d;
endmodule

// 5 input OR gate
module _or5(a, b, c, d, e, y);
	input a, b, c, d, e;
	output y;
	
	assign y = a | b | c | d | e;
endmodule



//// NOR Series ////
// 2 input NOR gate
module _nor2(a, b, y);
	input a, b;
	output y;
	
	assign y = ~ (a | b);
endmodule



//// XOR Series ////
// 2 input XOR gate
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



//// XNOR Series ////
// 2 input XNOR gate
module _xnor(a, b, y);
	input a, b;
	output y;
	wire w0;
	
	_xor2 u0_xor(.a(a), .b(b), .y(w0));
	
	_inv u1_inv(.a(w0), .y(y));
endmodule
