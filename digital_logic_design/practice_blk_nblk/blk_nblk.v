module blk_nblk(clk, a, b, c, d, e);
	input clk;
	input a;
	output b, c, d, e;
	
	blk u0_blk(.clk(clk), .a(a), .b(b), .c(c));
	nblk u1_nblk(.clk(clk), .a(a), .b(d), .c(e));	
endmodule

module blk(clk, a, b, c);
	input clk;
	input a;
	output reg b, c;
	
	always@ (posedge clk)
	begin
		b = a;
		c = b;
	end
endmodule

module nblk(clk, a, b, c);
	input clk;
	input a;
	output reg b, c;
	
	always@ (posedge clk)
	begin
		b <= a;
		c <= b;
	end
endmodule
