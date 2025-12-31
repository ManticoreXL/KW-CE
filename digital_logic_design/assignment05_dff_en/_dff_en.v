module _dff_en(clk, en, d, q);
	input clk, en, d;
	output q;
	
	wire w_d;
	
	// using mux to select previous q and new d.
	// enable is 1, update d.
	mx2 u0_mx2(.d0(q), .d1(d), .s(en), .y(w_d));
	_dff u1_dff(.clk(clk), .d(w_d), .q(q));
endmodule
