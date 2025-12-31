module fifo_ns(wr_en, rd_en, state, data_count, next_state);
	input wr_en, rd_en;
	input [2:0] state;
	input [3:0] data_count;
	output reg [2:0] next_state;
	
	// state encoding
	parameter INIT = 3'b000;
	parameter NO_OP = 3'b001;
	parameter WRITE = 3'b010;
	parameter WR_ERR = 3'b011;
	parameter READ = 3'b100;
	parameter RD_ERR = 3'b101;
	
	always@(state or wr_en or rd_en)
	begin
		casex(state)
			{INIT}:
				if(wr_en == 1 && data_count == 3'b111) next_state <= WRITE;
				else if(rd_en == 1 && data_count == 0) next_state <= RD_ERR;
				else next_state <= NO_OP;
			{NO_OP}:
				if(wr_en == 1 && data_count != 3'b111) next_state <= WRITE;
				else if(wr_en == 1 && data_count == 3'b111) next_state <= WR_ERR;
				else if(rd_en == 1 && data_count != 0) next_state <= READ;
				else if(rd_en == 1 && data_count == 0) next_state <= RD_ERR;
			{WRITE}:
				if(wr_en == 1 && data_count != 3'b111) next_state <= WRITE;
				else if(wr_en == 1 && data_count == 8) next_state <= WR_ERR;
				else if(rd_en == 1 && data_count == 0) next_state <= READ;
				else next_state <= NO_OP;
			{WR_ERR}:
				if(wr_en == 1 && data_count == 3'b111) next_state <= WR_ERR;
				else if(rd_en == 1 && data_count != 0) next_state <= READ;
				else next_state <= NO_OP;
			{READ}:
				if(wr_en == 1 && data_count != 3'b111) next_state <= WRITE;
				else if(rd_en == 1 && data_count != 0) next_state <= READ;
				else if(rd_en == 1 && data_count == 0) next_state <= RD_ERR;
				else next_state <= NO_OP;
			{RD_ERR}:
				if(rd_en == 1 && data_count == 0) next_state <= RD_ERR;
				else if(wr_en == 1 && data_count != 0) next_state <= WRITE;
				else next_state <= NO_OP;			
			default: next_state <= 3'bxxx;
		endcase
	end
endmodule			
			