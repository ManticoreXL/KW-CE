module tb_fifo;
	reg tb_clk, tb_reset_n, tb_wr_en, tb_rd_en;
	reg [31:0] tb_d_in;
	wire [31:0] tb_d_out;
	wire [3:0] tb_data_count;
	wire tb_full, tb_empty, tb_wr_ack, tb_wr_err, tb_rd_ack, tb_rd_err;
	
	fifo u0_fifo(.clk(tb_clk), .reset_n(tb_reset_n), .wr_en(tb_wr_en), .rd_en(tb_rd_en), .d_in(tb_d_in),
					 .d_out(tb_d_out), .data_count(tb_data_count), .full(tb_full), .empty(tb_empty), 
					 .wr_ack(tb_wr_ack), .wr_err(tb_wr_err), .rd_ack(tb_rd_ack), .rd_err(tb_rd_err));
	
	// generate clock
	always #5 tb_clk = ~tb_clk;
	
	initial
	begin
		tb_clk = 0; tb_reset_n = 0; tb_wr_en = 0; tb_rd_en = 0; tb_d_in = 0; #30;
		
		tb_reset_n = 1; #30
		
		// test RD_ERR;
		tb_rd_en = 1; #30;
		tb_rd_en = 0; #30;
		
		// test WRITE
		tb_d_in = 32'hffff_ffff; tb_wr_en = 1; #30;
		tb_wr_en = 0; #30;
		
		tb_d_in = 32'h1111_1111; tb_wr_en = 1; #30;
		tb_wr_en = 0; #30;
		
		tb_d_in = 32'h1234_5678; tb_wr_en = 1; #30;
		tb_wr_en = 0; #30;
		
		tb_d_in = 32'h3708_1534; tb_wr_en = 1; #30;
		tb_wr_en = 0; #30;
		
		tb_d_in = 32'haaaa_aaaa; tb_wr_en = 1; #30;
		tb_wr_en = 0; #30;
		
		tb_d_in = 32'hbbbb_bbbb; tb_wr_en = 1; #30;
		tb_wr_en = 0; #30;
		
		tb_d_in = 32'hcccc_cccc; tb_wr_en = 1; #30;
		tb_wr_en = 0; #30;
		
		tb_d_in = 32'hdddd_dddd; tb_wr_en = 1; #30;
		tb_wr_en = 0; #30;
		
		// test WR_ERR
		tb_d_in = 32'heeee_eeee; tb_wr_en = 1; #30;
		tb_wr_en = 0; #30;
		
		// test READ
		tb_rd_en = 1; #30;
		tb_rd_en = 0; #30;
		
		tb_rd_en = 1; #30;
		tb_rd_en = 0; #30;
		
		tb_rd_en = 1; #30;
		tb_rd_en = 0; #30;
		
		tb_rd_en = 1; #30;
		tb_rd_en = 0; #30;
		
		tb_rd_en = 1; #30;
		tb_rd_en = 0; #30;
		
		tb_rd_en = 1; #30;
		tb_rd_en = 0; #30;
		
		tb_rd_en = 1; #30;
		tb_rd_en = 0; #30;
		
		tb_rd_en = 1; #30;
		tb_rd_en = 0; #30;
		
		// test RD_ERR
		tb_rd_en = 1; #30;
		tb_rd_en = 0; #30;		
		
		$stop;
	end
endmodule
