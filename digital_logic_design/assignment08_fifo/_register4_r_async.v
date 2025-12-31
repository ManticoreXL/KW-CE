module _register4_r_async(clk, reset_n, next_state, state);
	input clk, reset_n;
	input [3:0] next_state;
	output reg [3:0] state;
	
	always@(posedge clk or negedge reset_n)
	begin
		if(reset_n == 1'b0) state <= 4'b0;
		else state <= next_state;
	end
endmodule
