module _register8_r(clk, reset_n, d, q);
	input clk, reset_n;
	input [7:0] d;
	output [7:0] q;
	
	_dff_r u0_dff_r(.clk(clk), .reset_n(reset_n), .d(d[0]), .q(q[0]));
	_dff_r u1_dff_r(.clk(clk), .reset_n(reset_n), .d(d[1]), .q(q[1]));
	_dff_r u2_dff_r(.clk(clk), .reset_n(reset_n), .d(d[2]), .q(q[2]));
	_dff_r u3_dff_r(.clk(clk), .reset_n(reset_n), .d(d[3]), .q(q[3]));
	_dff_r u4_dff_r(.clk(clk), .reset_n(reset_n), .d(d[4]), .q(q[4]));
	_dff_r u5_dff_r(.clk(clk), .reset_n(reset_n), .d(d[5]), .q(q[5]));
	_dff_r u6_dff_r(.clk(clk), .reset_n(reset_n), .d(d[6]), .q(q[6]));
	_dff_r u7_dff_r(.clk(clk), .reset_n(reset_n), .d(d[7]), .q(q[7]));	
endmodule
