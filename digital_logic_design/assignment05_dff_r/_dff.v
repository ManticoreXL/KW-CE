module _dff(clk, d, q, q_bar);
	input clk;
	input d;
	output q, q_bar;
	wire clk_bar, w_q;
	
	_inv u0_inv(.a(clk), .y(clk_bar));
	_dlatch u1_dlatch(.clk(clk_bar), .d(d), .q(w_q));
	_dlatch u2_dlatch(.clk(clk), .d(w_q), .q(q), .q_bar(q_bar));
endmodule
