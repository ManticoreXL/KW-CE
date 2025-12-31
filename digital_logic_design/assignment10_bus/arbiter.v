module arbiter(clk, state, m0_req, m1_req, m0_grant, m1_grant, next_state);
	input clk;
	input state;
	input m0_req, m1_req;
	output m0_grant, m1_grant;
	output reg next_state;
	
	// encoded state
	parameter M0_GRANT = 1'b0;
	parameter M1_GRANT = 1'b1;
	
	always@(posedge clk)
	begin
		case(state)
			M0_GRANT:
				if(m0_req == 0 && m1_req == 1) 
					next_state = M1_GRANT;
				else if((m0_req == 0 && m1_req == 0) || m0_req == 1)
					next_state = M0_GRANT;
					
			M1_GRANT:
				if(m1_req == 1) 
					next_state = M1_GRANT;
				else if(m1_req == 0) 
					next_state = M0_GRANT;
				
			default: next_state = 1'bx;
		endcase
	end
	
	// output grant
	assign m0_grant = (next_state == M0_GRANT)? 1'b1 : 1'b0;
	assign m1_grant = (next_state == M1_GRANT)? 1'b1 : 1'b0;
endmodule
