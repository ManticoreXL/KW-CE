module _dff_r_sync(clk, reset_n, d, q);
	input clk, reset_n, d;
	output q;
	reg q;
	
	// even if reset is high, 
	// rising edge of clock is required to update q.
	always@(posedge clk)
	begin
		if(reset_n == 0) q <= 1'b0;
		else q <= d;
	end
endmodule
