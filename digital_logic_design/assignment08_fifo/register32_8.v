module register32_8(clk, reset_n, en, d_in, d_out0, d_out1, d_out2, 
						  d_out3, d_out4, d_out5, d_out6, d_out7);
	input clk, reset_n;
	input [7:0] en;
	input [31:0] d_in;
	output [31:0] d_out0, d_out1, d_out2, d_out3,
					  d_out4, d_out5, d_out6, d_out7;
	
	register32_r_en u0_register32_r_en(.clk(clk), .reset_n(reset_n), .en(en[0]), .d(d_in), .q(d_out0));
	register32_r_en u1_register32_r_en(.clk(clk), .reset_n(reset_n), .en(en[1]), .d(d_in), .q(d_out1));
	register32_r_en u2_register32_r_en(.clk(clk), .reset_n(reset_n), .en(en[2]), .d(d_in), .q(d_out2));
	register32_r_en u3_register32_r_en(.clk(clk), .reset_n(reset_n), .en(en[3]), .d(d_in), .q(d_out3));
	register32_r_en u4_register32_r_en(.clk(clk), .reset_n(reset_n), .en(en[4]), .d(d_in), .q(d_out4));
	register32_r_en u5_register32_r_en(.clk(clk), .reset_n(reset_n), .en(en[5]), .d(d_in), .q(d_out5));
	register32_r_en u6_register32_r_en(.clk(clk), .reset_n(reset_n), .en(en[6]), .d(d_in), .q(d_out6));
	register32_r_en u7_register32_r_en(.clk(clk), .reset_n(reset_n), .en(en[7]), .d(d_in), .q(d_out7));
endmodule
