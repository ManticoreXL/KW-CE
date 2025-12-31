module tb_Register_file;
	reg tb_clk, tb_reset_n, tb_we;
	reg [2:0] tb_wAddr, tb_rAddr;
	reg [31:0] tb_wData;
	wire [31:0] tb_rData;
	
	Register_file u0_Register_file(.clk(tb_clk), .reset_n(tb_reset_n),
											 .wAddr(tb_wAddr), .wData(tb_wData),
											 .we(tb_we), 
											 .rAddr(tb_rAddr), .rData(tb_rData));

	always #10 tb_clk = ~tb_clk;
	
	initial
	begin
		tb_clk = 0; tb_reset_n = 1; tb_we = 0; tb_wAddr = 0; tb_rAddr = 0; tb_wData = 0;
		
		// test write operation
		#10; tb_we = 1;
		#10; tb_wAddr = 3'b010;
		#30; tb_wData = 32'hffff_ffff;
		#10; tb_wAddr = 3'b110;
		#30; tb_wData = 32'h1234_5678;
		#10; tb_wAddr = 3'b001;
		#30; tb_wData = 32'h3708_1534;
		
		// test read operation
		#10; tb_we = 0;
		#30; tb_rAddr = 3'b001;
		#30; tb_rAddr = 3'b110;
		#30; tb_rAddr = 3'b010;
		
		// test uninitialized area reading
		#30; tb_rAddr = 3'b100;
		
		#30; $stop;
	end
endmodule
