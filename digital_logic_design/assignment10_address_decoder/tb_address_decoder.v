module tb_address_decoder;
	reg [7:0] tb_address;
	wire tb_s0_sel, tb_s1_sel;
	
	address_decoder u0_address_decoder(.address(tb_address), .s0_sel(tb_s0_sel), .s1_sel(tb_s1_sel));
	
	initial
	begin
		tb_address = 8'b0001_1111; #20;
		tb_address = 8'b0000_0000; #20;
		tb_address = 8'b0010_0000; #20;
		tb_address = 8'b0011_1111; #20;
		tb_address = 8'b1111_1111; #20;
		
		$stop;
	end
endmodule
	