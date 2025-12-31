module _register32(clk, d, q);
	input clk;
	input [31:0] d;
	output [31:0] q;
	
	_register8 u0_register8(.clk(clk), .d(d[7:0]), .q(q[7:0]));
	_register8 u1_register8(.clk(clk), .d(d[15:8]), .q(q[15:8]));
	_register8 u2_register8(.clk(clk), .d(d[23:16]), .q(q[23:16]));
	_register8 u3_register8(.clk(clk), .d(d[31:24]), .q(q[31:24]));	
endmodule

module _register8(clk, d, q);
	input clk;
	input [7:0] d;
	output [7:0] q;
	
	_register4 u0_register4(.clk(clk), .d(d[3:0]), .q(q[3:0]));
	_register4 u1_register4(.clk(clk), .d(d[7:4]), .q(q[7:4]));	
endmodule

module _register4(clk, d, q);
	input clk;
	input [3:0] d;
	output [3:0] q;
	
	_dff u0_dff(.clk(clk), .d(d[0]), .q(q[0]));
	_dff u1_dff(.clk(clk), .d(d[1]), .q(q[1]));
	_dff u2_dff(.clk(clk), .d(d[2]), .q(q[2]));
	_dff u3_dff(.clk(clk), .d(d[3]), .q(q[3]));
endmodule
