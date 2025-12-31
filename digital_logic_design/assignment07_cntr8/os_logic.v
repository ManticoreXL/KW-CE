module os_logic(state, d_in, d_out);
	parameter IDLE_STATE = 3'b000;
	parameter LOAD_STATE = 3'b001;
	parameter INC_STATE = 3'b010;
	parameter INC2_STATE = 3'b011;
	parameter DEC_STATE = 3'b100;
	parameter DEC2_STATE = 3'b101;
	
	input [2:0] state;
	input [7:0] d_in;
	output [7:0] d_out;
	
	reg [7:0] d_out;
	wire [7:0] d_inc;
	wire [7:0] d_dec;
	
	always@(state, d_in)
	begin
		case(state)
			IDLE_STATE: d_out <= 8'h00;
			LOAD_STATE: d_out <= d_in;
			INC_STATE: 
			begin
				d_out <= d_inc; 
			end
			INC2_STATE: 
			begin
				d_out <= d_inc; 
			end
			DEC_STATE: 
			begin
				d_out <= d_dec;
			end
			DEC2_STATE: 
			begin
				d_out <= d_dec;
			end
			default: d_out <= 8'hxx;
		endcase
	end
	
	// using cla8 to add or sub d_out by 1.
	// d_out will be updated continuously in the always block.
	// so two cla8 use d_out to input.
	cla8 u0_cla8(.a(d_out), .b(8'b0000_0001), .ci(0), .s(d_inc));
	cla8 u1_cla8(.a(d_out), .b(8'b1111_1110), .ci(1), .s(d_dec));
endmodule
	