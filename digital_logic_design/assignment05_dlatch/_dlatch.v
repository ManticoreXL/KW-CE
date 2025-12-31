module _dlatch(clk, d, q, q_bar);
	input clk;
	input d;
	output q, q_bar;
	reg q;
	
	// if clock is high, update q.
	always@(clk or d)
	begin
		if(clk == 1) q <= d;
	end
	
	// return inverted value of q.
	assign q_bar = ~q;
endmodule
