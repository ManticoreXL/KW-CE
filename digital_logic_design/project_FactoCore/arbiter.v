module arbiter(clk, state, m_req, m_grant, next_state);
	input clk;
	input state;
	output m_req, m_grant;
	output reg next_state;
	
	// encoded state
	parameter IDLE = 1'b0;
	parameter GRANT = 1'b1;
	
	// get next state
	always@(posedge clk)
	begin
		case(state)
			IDLE:
				if(m_req == 1) next_state = GRANT;
				else next_state = IDLE;
			
			GRANT:
				if(m_req == 1) next_state = GRANT;
				else next_state = IDLE;
		
			default: next_state = 1'bx;
		endcase
	end
	
	// output grant
	assign m_grant = state;
endmodule
