module FactoCore(clk, reset_n, s_sel, s_wr, s_addr, s_din, s_dout, interrupt);
	input clk, reset_n;
	input s_sel, s_wr;
	input [15:0] s_addr;
	input [63:0] s_din;
	output reg [63:0] s_dout;
	output reg interrupt;
	
	// encoded state
	parameter INIT = 2'b00;
	parameter CHECK = 2'b01;
	parameter CALC = 2'b10;
	parameter DONE = 2'b11;
	
	// register file
	reg [1:0] state, next_state;
	reg [63:0] opstart, next_opstart;
	reg [63:0] opclear, next_opclear;
	reg [63:0] opdone, next_opdone;
	reg [63:0] intrEn;
	reg [63:0] operand, next_operand;
	reg [63:0] result_h, next_result_h;
	reg [63:0] result_l, next_result_l;
	
	// multiplier controller
	reg r_opstart;
	reg r_opclear;
	wire w_opdone;
	
	wire [63:0] w_operand, w_next_operand;
	wire [63:0] w_result_h;
	wire [63:0] w_result_l;
	wire [63:0] w_mulcand;
	
	assign w_operand = operand;
	assign w_mulcand = (result_l == 64'b0) ? result_h : result_l;
	
	// get offset from address
	wire [4:0] offset;
	assign offset = s_addr[7:3];
	
	// update register
	always@(posedge clk or negedge reset_n)
	begin
		if(reset_n == 0) begin
			state = 2'b0;
			
			opstart = 64'b0;
			opclear = 64'b0;
			intrEn = 64'b0;
			operand = 64'b0;
			
			opdone = 64'b0;
			result_h = 64'b0;
			result_l = 64'b0; end
			
		else if(s_sel == 1)
			if(s_wr == 1 && offset == 5'b0010_0)
				operand = s_din;
			else begin
				if(s_wr == 1)
					case(offset) // write operation 
						5'b0000_0: opstart = s_din;
						5'b0000_1: opclear = s_din;
						5'b0001_1: intrEn = s_din;
					endcase
				else begin
					case(offset) // read operation
						5'b0001_0: s_dout = opdone;
						5'b0010_1: s_dout = result_h;
						5'b0011_0: s_dout = result_l;
						default: s_dout = 64'bx;
					endcase	
					// update register
					state <= next_state;
					
					opstart <= next_opstart;
					opclear <= next_opclear;
					operand <= next_operand;
					
					opdone <= next_opdone;
					result_h <= next_result_h;
					result_l <= next_result_l; end
			end
	end
	
	
	
	// next state logic
	always@(*)
	begin
		case(state)
			INIT:
				if(opstart[0] == 1) next_state = CALC;
				else next_state = INIT;
				
			CHECK:
				if(opclear[0] == 1) next_state = INIT;
				else if(operand == 64'b1 || operand == 64'b0) next_state = DONE;
				else next_state = CALC;
				
			CALC:
				if(opclear[0] == 1) next_state = INIT;
				else if(w_opdone == 1) next_state = CHECK;
				else if(operand == 64'b1 || operand == 64'b0) next_state = DONE;
				else next_state = CALC;
				
			DONE:
				if(opclear[0] == 1) next_state = INIT;
				else next_state = DONE;
				
			default:
				next_state = 2'bx;
		endcase
	end
	
	
	
	// next operand logic
	always@(*)
	begin
		case(state)
			CHECK:
				if(operand == 64'b1) next_operand = 64'b1;
				else if(w_opdone == 1) next_operand = w_operand;
				else next_operand = w_next_operand;
				
			default:
				next_operand = w_operand;
		endcase
	end
	
	
	
	// multiplier controll section
	always@(*)
	begin
		case(state)
			INIT: begin
				r_opstart = 0;
				r_opclear = 0; end
			
			CHECK: begin
				if(w_opdone == 1) r_opclear = 1; end
			
			CALC: begin
				r_opclear = 0;
				r_opstart = 1;
				// ~ calculating...
				if(w_opdone == 1) r_opstart = 0; end
				
			DONE: begin
				r_opstart = 0;
				r_opclear = 0; end
				
			default: begin
				r_opstart = 1'bx;
				r_opclear = 1'bx; end
				
		endcase
	end
	
	
	
	// next result logic
	always@(w_opdone)
	begin
		case(state)
			INIT: begin
				next_result_h = 64'b0;
				next_result_l = 64'b1; end
	
			CHECK: begin
				next_result_h = w_result_h;
				next_result_l = w_result_l; end
			
			CALC: begin
				next_result_h = w_result_h;
				next_result_l = w_result_l; end
			
			DONE: begin
				next_result_h = result_h;
				next_result_l = result_l; end
			
			default: begin
				next_result_h = 64'bx;
				next_result_l = 64'bx; end
		endcase
	end

	
	
	// output controller
	always@(w_result_l, w_result_h)
	begin
		case(state)
			INIT: begin
				next_opstart = 64'b0;
				next_opclear = 64'b0;
				next_opdone = 64'b0;
				interrupt = 0; end
			
			CHECK:
				next_opdone = 64'b10; // mark as calculating
				
			CALC:
				next_opdone = 64'b10; // mark as calculating
				
			DONE: begin
				next_opdone = 64'b11; // mark as done
				interrupt = intrEn[0] & opdone[0]; end
				
				
			default: begin
				next_opstart = 64'bx;
				next_opdone = 64'bx; 
				interrupt = 1'bx; end
		endcase
	end
				
		

	
	// cla instance (decrease operand by 1)
	cla64 u0_cla64(.a(operand), .b(~64'b1), .ci(1'b1), .co(), .s(w_next_operand));

	// multiplier instance
	multiplier u1_multiplier(.clk(clk), .reset_n(reset_n), .multiplier(w_operand), .multiplicand(w_mulcand), 
									 .op_start(r_opstart), .op_clear(r_opclear), .op_done(w_opdone),
									 .result({w_result_h, w_result_l}));

endmodule
