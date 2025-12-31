module cla6(a, b, ci, co, s);
	input [5:0] a, b;
	input ci;
	output co;
	output [5:0] s;
	
	wire w_co, w_c4;
	
	// cla4 + fa*2
	cla4 u0_cla4(.a(a[3:0]), .b(b[3:0]), .ci(ci), .co(w_co), .s(s[3:0]));
	fa u1_fa(.a(a[4]), .b(b[4]), .ci(w_co), .co(w_c4), .s(s[4]));
	fa u2_fa(.a(a[5]), .b(b[5]), .ci(w_c4), .co(co), .s(s[5]));
endmodule
