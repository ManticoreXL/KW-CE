module rca32(a, b, ci, co, s);
	input [31:0] a, b;
	input ci;
	output co;
	output [31:0] s;
	
	wire w0, w1, w2, w3, w4, w5, w6;
	
	rca4 u0_rca4(.a(a[3:0]), .b(b[3:0]), .ci(ci), .co(w0), .s(s[3:0]));
	rca4 u1_rca4(.a(a[7:4]), .b(b[7:4]), .ci(w0), .co(w1), .s(s[7:4]));
	rca4 u2_rca4(.a(a[11:8]), .b(b[11:8]), .ci(w1), .co(w2), .s(s[11:8]));
	rca4 u3_rca4(.a(a[15:12]), .b(b[15:12]), .ci(w2), .co(w3), .s(s[15:12]));
	rca4 u4_rca4(.a(a[19:16]), .b(b[19:16]), .ci(w3), .co(w4), .s(s[19:16]));
	rca4 u5_rca4(.a(a[23:20]), .b(b[23:20]), .ci(w4), .co(w5), .s(s[23:20]));
	rca4 u6_rca4(.a(a[27:24]), .b(b[27:24]), .ci(w5), .co(w6), .s(s[27:24]));
	rca4 u7_rca4(.a(a[31:28]), .b(b[31:28]), .ci(w6), .co(co), .s(s[31:28]));
	
endmodule
