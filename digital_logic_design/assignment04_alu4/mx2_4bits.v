// 4 bits 2-to-1 multiplexer.
module mx2_4bits(d0, d1, s, y);
	input [3:0] d0, d1;
	input s;
	output [3:0] y;
	
	mx2 u0_mx2(.d0(d0[0]), .d1(d1[0]), .s(s), .y(y[0]));
	mx2 u1_mx2(.d0(d0[1]), .d1(d1[1]), .s(s), .y(y[1]));
	mx2 u2_mx2(.d0(d0[2]), .d1(d1[2]), .s(s), .y(y[2]));
	mx2 u3_mx2(.d0(d0[3]), .d1(d1[3]), .s(s), .y(y[3]));
endmodule
