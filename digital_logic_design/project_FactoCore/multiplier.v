module multiplier(clk, reset_n, multiplier, multiplicand, op_start, op_clear, op_done, result);
	input clk, reset_n;
	input [63:0] multiplier, multiplicand;
	input op_start, op_clear;
	output reg op_done;
	output [127:0] result;

	// declare internal variables
	reg [1:0] state, next_state;
	reg [5:0] count, next_count;
	reg [5:0] shamt, next_shamt;
	reg [64:0] r_mulier, next_r_mulier;
	reg [127:0] result, next_result;
	wire [5:0] w_count;
	wire [5:0] w_shamt;
	wire [63:0] w_mulcand;
	wire [127:0] w_result;
	wire w_ci;
	
	// state encoding
	parameter IDLE = 2'b00;
	parameter CALC = 2'b01;
	parameter DONE = 2'b10;
	
	// maintain previous result's low area
	assign w_result[63:0] = result[63:0];
	// determine determine whether addition or subtraction
	assign w_mulcand = (r_mulier[2] == 1'b1 && (r_mulier[1] == 1'b0 || r_mulier[0] == 1'b0))? 
							  ~multiplicand : multiplicand;
	// w_ci will be used cla's carry in bit
	assign w_ci = r_mulier[2] == 1'b1 && (r_mulier[1] == 1'b0 || r_mulier[0] == 1'b0);
	
	// cla64 for addition or subtraction
	cla64 u0_cla64(.a(w_mulcand), .b(result[127:64]), .ci(w_ci), .co(), .s(w_result[127:64]));
	// u1_cla6 for setting count. w_count = count + shamt
	cla6 u1_cla6(.a(count), .b(shamt), .ci(1'b0), .co(), .s(w_count));
	// u2_cla6 for setting shamt. w_shamt = (01_1111) - count
	cla6 u2_cla6(.a(6'b01_1111), .b(~count), .ci(1'b1), .co(), .s(w_shamt));
	
	// register for states
	always@(posedge clk or negedge reset_n)
	begin
		if(reset_n == 0) begin// reset(IDLE)
			state <= 2'b0;
			count <= 6'b0;
			shamt <= 6'b0;
			r_mulier <= 64'b0;
			result <= 128'b0; end
		else begin // update (CALC, DONE)
			state <= next_state;
			count <= next_count;
			shamt <= next_shamt;
			r_mulier <= next_r_mulier;
			result <= next_result; end
	end
			
	// generate next result
	always@(state, count, shamt, r_mulier, multiplier, multiplicand, result, w_result, next_result, op_clear)
	begin
		case(state)
			IDLE:
				next_result = 128'b0;
				
			CALC:
				if(count >= 6'b100000)
					next_result = result;
				else if(shamt != 1)
					next_result = result >>> (shamt << 1);
				else
					// use booth algorithm
					// 011, 100 -> 2A, -2A
					// 001, 010, 101, 110 -> A, -A
					// 000, 111 -> 0
					if((~r_mulier[2]&r_mulier[1]&r_mulier[0]) || 
						(r_mulier[2]&~r_mulier[1]&~r_mulier[0])) // 011, 100 -> 2A, -2A
						if((~r_mulier[4]&r_mulier[3]&r_mulier[2]) || 
						   (r_mulier[4]&~r_mulier[3]&~r_mulier[2])) // next rule is 2A, -2A -> ASR w_result by 2
							next_result = {w_result[127], w_result[127], w_result[127:2]};
						else // ASR w_result by 1
							next_result = {w_result[127], w_result[127:1]};
						
					else if((r_mulier[2]&r_mulier[1]&r_mulier[0]) || 
							  (~r_mulier[2]&~r_mulier[1]&~r_mulier[0])) // 111, 000 -> 0
						if((~r_mulier[4]&r_mulier[3]&r_mulier[2]) || 
							(r_mulier[4]&~r_mulier[3]&~r_mulier[2])) // next rule is 2A, -2A -> ASR result by 3
							next_result = {result[127], result[127], result[127], result[127:3]};
						else // ASR result by 2
							next_result = {result[127], result[127], result[127:2]};
						
					else // 001 or 010 por 101 or 110 -> A, -A
						if((~r_mulier[4]&r_mulier[3]&r_mulier[2]) || 
							(r_mulier[4]&~r_mulier[3]&~r_mulier[2])) // next rule is 2A, -2A -> ASR w_result by 3
							next_result={w_result[127], w_result[127], w_result[127], w_result[127:3]};
						else // ASR w_result by 2
							next_result={w_result[127], w_result[127], w_result[127:2]};
					
			DONE:
				if(op_clear == 1)
					next_result = 128'b0;
				else
					next_result = result; 
				
			default: begin
				next_result = 128'bx; end	
		endcase
	end
		
	// next state logic
	always@(state, op_start, op_clear, op_done)
	begin
		case(state)
			IDLE:
				if(op_start == 1) // go CALC
					next_state = CALC;
				else // stay IDLE
					next_state = IDLE;
					
			CALC:
				if(op_clear == 1) // stop CALC
					next_state = IDLE;
				else if(op_done == 1) // CALCulation is DONE
					next_state = DONE;
				else // keep CALCulating
					next_state = CALC;
					
			DONE:
				if(op_clear == 1) // initialization
					next_state = IDLE;
				else // stay DONE
					next_state = DONE;
					
			default:
				next_state = 2'bx;
		endcase
	end
	
	// next count logic
	always@(state, count, w_count, next_count, op_clear)
	begin
		case(state)
			IDLE:
				next_count = 6'b0;
			CALC:
				next_count = w_count;
			DONE:
				if(op_clear == 1)
					next_count = 6'b0;
				else
					next_count = count;
			default:
				next_count = 6'bx;
		endcase
	end
	

	// next shamt logic
	always@(state, count, w_shamt, r_mulier, multiplicand)
	begin
		case(state)
			IDLE:
				next_shamt = 6'b1;
				
			CALC:
				if(r_mulier == 65'b0)
					next_shamt = w_shamt;
				else
					next_shamt = 6'b1;
					
			DONE:
				next_shamt = 6'b0;
			default:
				next_shamt = 6'bx;
		endcase
	end
	
	// next r_mulier logic
	always@(state, count, r_mulier, multiplier)
	begin
		case(state)
			IDLE:
				// set first r_mulier[0] to zero
				next_r_mulier = {multiplier[63:0], 1'b0};
				
			CALC:
				// logical shift right by 2
				next_r_mulier = {2'b00, r_mulier[64:2]};
				
			DONE:
				// maintain r_mulier
				next_r_mulier = r_mulier;
				
			default:
				next_r_mulier = 65'bx;
		endcase
	end
		
	// set op_done
	always@(count, op_clear)
	begin
		if(op_clear == 1)
			op_done = 0;
		else if(count[5] == 1) // set as DONE
			op_done = 1;
		else
			op_done = 0;
	end
endmodule
