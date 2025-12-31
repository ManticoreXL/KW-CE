module cla8(a, b, ci, co, s);
	input [7:0] a, b;
	input ci;
	output co;
	output [7:0] s;
	
	wire c1;
	
	cla4 u0_cla4(.a(a[3:0]), .b(b[3:0]), .ci(ci), .co(c1), .s(s[3:0]));
	cla4 u1_cla4(.a(a[7:4]), .b(b[7:4]), .ci(c1), .co(co), .s(s[7:4]));
endmodule
