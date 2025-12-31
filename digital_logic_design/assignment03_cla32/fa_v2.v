// full adder without carry out port.
module fa_v2(a, b, ci, s);
	input a, b, ci;
	output s;
	wire w0, w1;
	
	_xor2 u0_xor2(.a(a), .b(b), .y(w0));
	_xor2 u1_xor2(.a(w0), .b(ci), .y(s));
endmodule
