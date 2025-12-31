module mux2_8bit(d0, d1, s, y);
	input [7:0] d0, d1;
	input s;
	output [7:0] y;
	
	// behavioral multiplexer implementation
	assign y = (s == 0)? d0 : d1;
endmodule
