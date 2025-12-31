module tb_rca4;
	reg [3:0] tb_a, tb_b;
	reg tb_ci;
	wire tb_co;
	wire [3:0] tb_s;
	
	rca4 u0_rca4(.a(tb_a), .b(tb_b), .ci(tb_ci), .co(tb_co), .s(tb_s));
	
	initial
	begin
		// tests a, b, ci addition
		tb_a = 4'b1111; tb_b = 4'b0000; tb_ci = 0; #10; // 0, 1111
		tb_a = 4'b0000; tb_b = 4'b1111; tb_ci = 0; #10; // 0, 1111
		tb_a = 4'b0000; tb_b = 4'b0000; tb_ci = 1; #10; // 0, 0001
		
		// tests sum
		tb_a = 4'b0101; tb_b = 4'b1010; tb_ci = 0; #10; // 0, 1111
		
		// tests sum and carry in
		tb_a = 4'b0010; tb_b = 4'b0010; tb_ci = 0; #10; // 0, 0100
		tb_a = 4'b0001; tb_b = 4'b0001; tb_ci = 1; #10; // 0, 0011
		
		// tests overflow (carry out)
		tb_a = 4'b1111; tb_b = 4'b0001; tb_ci = 0; #10; // 1, 0000
		
		$finish;
		
	end
endmodule
