module mx4(d0, d1, d2, d3, s, y);
	input d0, d1, d2, d3;
	input[1:0] s;
	output y;
	
	wire w1, w2;
	
	mx2 u0_mx2(.d0(d0), .d1(d1), .s(s[0]), .y(w1));
	mx2 u1_mx2(.d0(d2), .d1(d3), .s(s[0]), .y(w2));
	mx2 u2_mx2(.d0(w1), .d1(w2), .s(s[1]), .y(y));
endmodule
	