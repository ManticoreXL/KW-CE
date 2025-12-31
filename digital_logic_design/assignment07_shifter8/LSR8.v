module LSR8(d_in, shamt, d_out);
	input [7:0] d_in;
	input [1:0] shamt;
	output [7:0] d_out;
	
	mx4 u0_mx4(.d0(d_in[7]), .d1(0), .d2(0), .d3(0), .s(shamt), .y(d_out[7]));
	mx4 u1_mx4(.d0(d_in[6]), .d1(d_in[7]), .d2(0), .d3(0), .s(shamt), .y(d_out[6]));
	mx4 u2_mx4(.d0(d_in[5]), .d1(d_in[6]), .d2(d_in[7]), .d3(0), .s(shamt), .y(d_out[5]));
	mx4 u3_mx4(.d0(d_in[4]), .d1(d_in[5]), .d2(d_in[6]), .d3(d_in[7]), .s(shamt), .y(d_out[4]));
	mx4 u4_mx4(.d0(d_in[3]), .d1(d_in[4]), .d2(d_in[5]), .d3(d_in[6]), .s(shamt), .y(d_out[3]));
	mx4 u5_mx4(.d0(d_in[2]), .d1(d_in[3]), .d2(d_in[4]), .d3(d_in[5]), .s(shamt), .y(d_out[2]));
	mx4 u6_mx4(.d0(d_in[1]), .d1(d_in[2]), .d2(d_in[3]), .d3(d_in[4]), .s(shamt), .y(d_out[1]));
	mx4 u7_mx4(.d0(d_in[0]), .d1(d_in[1]), .d2(d_in[2]), .d3(d_in[3]), .s(shamt), .y(d_out[0]));
endmodule
