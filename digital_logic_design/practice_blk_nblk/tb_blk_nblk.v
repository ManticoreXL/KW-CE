`timescale 1ns/100ps
module tb_blk_nblk;
	reg clk, a;
	wire b, c, d, e;
	
	blk_nblk u0_blk_nblk(.clk(clk), .a(a), .b(b), .c(c), .d(d), .e(e));

	initial
	begin
		a = 1'b1;
		#5; clk = 0;
		#5; clk = 1'b1;
		#5; clk = 0;
		#5; clk = 1'b1;
		#5; clk = 0;
		#5; clk = 1'b1;
	end
endmodule
