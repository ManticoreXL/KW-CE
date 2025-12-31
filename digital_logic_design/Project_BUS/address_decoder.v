module address_decoder(address, s0_sel, s1_sel);
	input [15:0] address;
	output reg s0_sel, s1_sel;
	
	// get base address
	wire [7:0] upper_8bit = address[15:8];
	
	// decode
	always@(address)
		// select s0 (00~07)
		if(upper_8bit >= 0 && upper_8bit < 8'h08) begin
			s0_sel <= 1'b1;
			s1_sel <= 1'b0;end
		// select s1 (70~71)
		else if(upper_8bit >= 8'h70 && upper_8bit < 8'h72) begin
			s0_sel = 1'b0;
			s1_sel = 1'b1; end
		// select no slave
		else begin
			s0_sel <= 1'b0;
			s1_sel <= 1'b0; end
endmodule
