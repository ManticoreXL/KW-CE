// gates.v for CED2 assignment of Verilog Implementation.
// includes inverter, and, or, nand, nor, xor, xnor
// 2023-11-02 added nor series

// Buffer gate
module _buf(a, y);
	input a;
	output y;

	assign y = a;
endmodule

// Inverter gate
module _inv(a, y);
	input a;
	output y;
	
	assign y = ~a;
endmodule

// 4 bits inverter
module _inv_4bits(a, y);
	input [3:0] a;
	output [3:0] y;

	assign y = ~ a;
endmodule

// 32 bits inverter
module _inv_32bits(a, y);
	input [31:0] a;
	output [31:0] y;
	
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

// 4 bits 2-to-1 AND gate
module _and2_4bits(a, b, y);
	input [3:0] a, b;
	output [3:0] y;

	assign y = a & b;
endmodule

// 32 bits 2-to-1 AND gate
module _and2_32bits(a, b, y);
	input [31:0] a, b;
	output [31:0] y;
	
	assign y = a & b;
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

// 4 bits 2-to-1 OR gate
module _or2_4bits(a, b, y);
	input [3:0] a, b;
	output [3:0] y;

	assign y = a | b;
endmodule

// 32 bits 2-to-1 OR gate
module _or2_32bits(a, b, y);
	input [31:0] a, b;
	output [31:0] y;
	
	assign y = a | b;
endmodule



//// NOR Series ////
// 2 input NOR gate
module _nor2(a, b, y);
	input a, b;
	output y;
	
	assign y = ~ (a | b);
endmodule

// 3 input NOR gate
module _nor3(a, b, c, y);
	input a, b, c;
	output y;
	
	assign y = ~ (a | b | c);
endmodule

// 4 input NOR gate
module _nor4(a, b, c, d, y);
	input a, b, c, d;
	output y;
	
	assign y = ~(a | b | c| d);
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

// 4 bits 2-to-1 XOR gate
module _xor2_4bits(a, b, y);
	input [3:0] a, b;
	output [3:0] y;

	_xor2 u0_xor2(.a(a[0]), .b(b[0]), .y(y[0]));
	_xor2 u1_xor2(.a(a[1]), .b(b[1]), .y(y[1]));
	_xor2 u2_xor2(.a(a[2]), .b(b[2]), .y(y[2]));
	_xor2 u3_xor2(.a(a[3]), .b(b[3]), .y(y[3]));
endmodule


// 32 bits 2-to-1 XOR gate
module _xor2_32bits(a, b, y);
	input [31:0] a, b;
	output [31:0] y;
	
	_xor2_4bits u0_xor2_4bits(.a(a[3:0]), .b(b[3:0]), .y(y[3:0]));
	_xor2_4bits u1_xor2_4bits(.a(a[7:4]), .b(b[7:4]), .y(y[7:4]));
	_xor2_4bits u2_xor2_4bits(.a(a[11:8]), .b(b[11:8]), .y(y[11:8]));
	_xor2_4bits u3_xor2_4bits(.a(a[15:12]), .b(b[15:12]), .y(y[15:12]));
	_xor2_4bits u4_xor2_4bits(.a(a[19:16]), .b(b[19:16]), .y(y[19:16]));
	_xor2_4bits u5_xor2_4bits(.a(a[23:20]), .b(b[23:20]), .y(y[23:20]));
	_xor2_4bits u6_xor2_4bits(.a(a[27:24]), .b(b[27:24]), .y(y[27:24]));
	_xor2_4bits u7_xor2_4bits(.a(a[31:28]), .b(b[31:28]), .y(y[31:28]));
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

// 4 bits 2-to-1 XNOR gate

module _xnor2_4bits(a, b, y);
	input [3:0] a, b;
	output [3:0] y;
	wire [3:0] w;

	_xor_4bit u0_xor2_4bit(.a(a), .b(b), .y(w));
	_inv_4bit u1_inv_4bit(.a(w), .y(y));
endmodule

// 32 bits 2-to-1 XNOR gate
module _xnor2_32bits(a, b, y);
	input [31:0] a, b;
	output [31:0] y;
	
	_xnor2_4bits u0_xnor2_4bits(.a(a[3:0]), .b(b[3:0]), .y(y[3:0]));
	_xnor2_4bits u1_xnor2_4bits(.a(a[7:4]), .b(b[7:4]), .y(y[7:4]));
	_xnor2_4bits u2_xnor2_4bits(.a(a[11:8]), .b(b[11:8]), .y(y[11:8]));
	_xnor2_4bits u3_xnor2_4bits(.a(a[15:12]), .b(b[15:12]), .y(y[15:12]));
	_xnor2_4bits u4_xnor2_4bits(.a(a[19:16]), .b(b[19:16]), .y(y[19:16]));
	_xnor2_4bits u5_xnor2_4bits(.a(a[23:20]), .b(b[23:20]), .y(y[23:20]));
	_xnor2_4bits u6_xnor2_4bits(.a(a[27:24]), .b(b[27:24]), .y(y[27:24]));
	_xnor2_4bits u7_xnor2_4bits(.a(a[31:28]), .b(b[31:28]), .y(y[31:28]));
endmodule



