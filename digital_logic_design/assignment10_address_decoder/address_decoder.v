module address_decoder(address, s0_sel, s1_sel);
	input [7:0] address;
	output reg s0_sel, s1_sel;
	
	wire [2:0] upper_3bit = address[7:5];
	
	// read base address and select slave
	always@(address)
		if(upper_3bit == 3'b000) begin
			s0_sel <= 1'b1;
			s1_sel <= 1'b0; end
		else if(upper_3bit == 3'b001) begin
			s0_sel <= 1'b0;
			s1_sel <= 1'b1; end
		else begin
			s0_sel <= 1'b0;
			s1_sel <= 1'b0; end
endmodule
