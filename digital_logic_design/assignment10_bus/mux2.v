module mux2(d0, d1, s, y);
	input d0, d1, s;
	output y;
	
	// behavioral mux2 implementation
	assign y = (s == 0)? d0 : d1;
endmodule
