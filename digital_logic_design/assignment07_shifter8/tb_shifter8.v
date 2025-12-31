module tb_shifter8;
	reg tb_clk, tb_reset_n;
	reg [2:0] tb_op;
	reg [1:0] tb_shamt;
	reg [7:0] tb_d_in;
	wire [7:0] tb_d_out;
	
	shifter8 u0_shifter8(.clk(tb_clk), .reset_n(tb_reset_n), .op(tb_op), .shamt(tb_shamt), .d_in(tb_d_in), .d_out(tb_d_out));
	
	always #5 tb_clk = ~tb_clk;
	
	initial
	begin
		tb_clk = 0; tb_reset_n = 0; tb_op = 3'b0; tb_shamt = 2'b0; tb_d_in = 8'b0; #10;
		
		// test LOAD
		tb_op = 3'b001; tb_d_in = 8'b1111_1111; #20;
							 tb_d_in = 8'b0000_0000; #20;
		
		// test LSL
		tb_op = 3'b010; tb_d_in = 8'b0000_1100; tb_shamt = 2'b01; #20;
															 tb_shamt = 2'b10; #20;
															 tb_shamt = 2'b11; #20;
		
		// test LSR
		tb_op = 3'b011; tb_shamt = 2'b01; #20;
							 tb_shamt = 2'b10; #20;
							 tb_shamt = 2'b11; #20;
		
		// test ASR
		tb_op = 3'b100; tb_d_in = 8'b1111_0000; tb_shamt = 2'b01; #30;
															 tb_shamt = 2'b11; #30;
							 tb_d_in = 8'b0000_1111; tb_shamt = 2'b10; #30;
		
		#30; $stop;
	end
endmodule	
	