module cla64(a, b, ci, co, s);
	input [63:0] a, b;
	input ci;
	output co;
	output [63:0] s;
	
	wire w0, w1, w2;

	cla32 u0_cla32(.a(a[31:0]), .b(b[31:0]), .ci(ci), .co(w0), .s(s[31:0]));
	cla32 u1_cla32(.a(a[63:32]), .b(b[63:32]), .ci(w0), .co(w1), .s(s[63:32]));
endmodule
