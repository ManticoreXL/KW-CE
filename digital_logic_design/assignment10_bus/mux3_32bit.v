module mux3_32bit(d00, d01, d10, s, y);
	input [31:0] d00, d01, d10;
	input [1:0] s;
	output reg [31:0] y;	
	
	always@(s)
	begin
		case(s)
			2'b00: y <= d00;
			2'b01: y <= d01;
			2'b10: y <= d10;
			default: y <= 32'h0;
		endcase
	end
endmodule
