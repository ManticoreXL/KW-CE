module fa(a, b, ci, co, s);
	input a, b, ci;
	output co, s;
	wire c0, c1, sm;
	
	ha u0_ha(.a(b), .b(ci), .s(sm), .co(c0));
	ha u1_ha(.a(a), .b(sm), .s(s), .co(c1));
	_or2 u2_or2(.a(c0), .b(c1), .y(co));	
endmodule
