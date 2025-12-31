module mux2_32bit(d0, d1, s, y);
	input [31:0] d0, d1;
	input s;
	output [31:0] y;
	
	// behavioral multiplexer implementation
	assign y = (s == 0)? d0 : d1;
endmodule
