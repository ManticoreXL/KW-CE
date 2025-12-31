// 2 input NAND gate module
module _nand2(a, b, y);
	input a, b;
	output y;
	
	assign y = ~(a&b);
	
endmodule

// Inverter module
module _inv(a, y);
	input a;
	output y;
	
	assign y = ~a;
endmodule
