module rca4(a, b, ci, co, s);
	input [3:0] a, b;
	input ci;
	output co;
	output [3:0] s;
	
	wire w0, w1, w2;
	
	fa u0_fa0(.a(a[0]), .b(b[0]), .ci(ci), .co(w0), .s(s[0]));
	fa u0_fa1(.a(a[1]), .b(b[1]), .ci(w0), .co(w1), .s(s[1]));
	fa u0_fa2(.a(a[2]), .b(b[2]), .ci(w1), .co(w2), .s(s[2]));
	fa u0_fa3(.a(a[3]), .b(b[3]), .ci(w2), .co(co), .s(s[3]));
endmodule
