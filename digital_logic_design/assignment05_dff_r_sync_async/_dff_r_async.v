module _dff_r_async(clk, reset_n, d, q);
	input clk, reset_n, d;
	output q;
	reg q;
	
	// if reset_n become low, update q by 0.
	always@(posedge clk or negedge reset_n)
	begin
		if(reset_n == 0) q <= 1'b0;
		else q <= d;
	end
endmodule
