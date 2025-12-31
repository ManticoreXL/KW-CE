module tb_RAM;
	reg tb_clk, tb_cen, tb_wen;
	reg [7:0] tb_addr;
	reg [63:0] tb_din;
	wire [63:0] tb_dout;
	
	always#10 tb_clk = ~tb_clk;
	
	RAM u0_RAM(.clk(tb_clk), .cen(tb_cen), .wen(tb_wen), .addr(tb_addr), .din(tb_din), .dout(tb_dout));
	
	initial
	begin
		tb_clk = 0; tb_cen = 0; tb_wen = 0; tb_addr = 0; tb_din = 0; #10;
		tb_cen = 1; #10;
		
		// test write 
		tb_wen = 1; tb_addr = 8'b0000_0000; tb_din = 64'hffff_ffff_ffff_ffff; #30;
		tb_wen = 1; tb_addr = 8'b0000_0001; tb_din = 64'h1234_5678_1234_5678; #30;
		
		// test read
		tb_wen = 0; #10;
		tb_addr = 8'b0000_0000; #30;
		tb_addr = 8'b0000_0001; #30;
		
		$stop;		
	end
endmodule
	