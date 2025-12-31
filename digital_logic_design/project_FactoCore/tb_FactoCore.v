module tb_FactoCore;
	reg tb_clk, tb_reset_n;
	reg tb_s_sel, tb_s_wr;
	reg [15:0] tb_s_addr;
	reg [63:0] tb_s_din;
	wire [63:0] tb_s_dout;
	wire tb_interrupt;
	
	always#5 tb_clk = ~tb_clk;
	
	FactoCore u0_FactoCore(.clk(tb_clk), .reset_n(tb_reset_n), 
								  .s_sel(tb_s_sel), .s_wr(tb_s_wr),
								  .s_addr(tb_s_addr), .s_din(tb_s_din), .s_dout(tb_s_dout), 
								  .interrupt(tb_interrupt));
								  
	initial
	begin
		tb_clk = 0; tb_reset_n = 0; tb_s_sel = 0; tb_s_wr = 0; tb_s_addr = 0; tb_s_din = 0; #10;
		tb_reset_n = 1; #10;
		
		tb_s_sel = 1; tb_s_wr = 1; #10
		
		// set operand
		tb_s_addr = 16'h7020; tb_s_din = 64'h0000_0000_0000_0005; #50;
		
		// set opstart
		tb_s_addr = 16'h7000; tb_s_din = 64'h0000_0000_0000_0001; #50;
		
		tb_s_wr = 0; tb_s_addr = 16'h7030; 
		#50000;

		$stop;
	end
endmodule
	