// 2-to-1 multiplexer module
module mx2(d0, d1, s, y);
	input d0, d1, s;
	output y;
	
	wire sb, w0, w1;
	
	_inv iv0(s, sb);
	
	_nand2 nd20(d0, sb, w0);
	_nand2 nd21(d1, s, w1);
	_nand2 nd22(w0, w1, y);
	
endmodule
