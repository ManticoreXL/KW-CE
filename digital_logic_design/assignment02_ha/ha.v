module ha(a, b, co, s);
	input a, b;
	output co, s;
	
	_xor2 u0_xor2(.a(a), .b(b), .y(s));
	_and2 u1_and2(.a(a), .b(b), .y(co));
endmodule
