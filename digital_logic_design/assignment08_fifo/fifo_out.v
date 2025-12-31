module fifo_out(state, data_count, full, empty, wr_ack, wr_err, rd_ack, rd_err);
	input [2:0] state;
	input [3:0] data_count;
	output reg full, empty, wr_ack, wr_err, rd_ack, rd_err;
	
	// state encoding
	parameter INIT = 3'b000;
	parameter NO_OP = 3'b001;
	parameter WRITE = 3'b010;
	parameter WR_ERR = 3'b011;
	parameter READ = 3'b100;
	parameter RD_ERR = 3'b101;
	
	always@(state)
	begin
		casex(state)
			INIT: 
				begin 
					full = 1'b0;
					empty = 1'b1;
					wr_ack = 1'b0;
					wr_err = 1'b0;
					rd_ack = 1'b0;
					rd_err = 1'b0;
				end
				
			NO_OP:
				begin
					if(data_count === 3'b000) empty = 1'b1;
					else empty = 1'b0;
					if(data_count === 3'b111) full = 1'b1;
					else full = 1'b0;
				end
				
			WRITE:
				begin
					wr_ack = 1'b1;
					wr_err = 1'b0;
					rd_ack = 1'b0;
					rd_err = 1'b0;
					if(data_count === 3'b111) full = 1'b1;
					else full = 1'b0;
				end
				
			WR_ERR:
				begin
					wr_ack = 1'b0;
					wr_err = 1'b1;
					rd_ack = 1'b0;
					rd_err = 1'b0;
				end
				
			READ:
				begin
					wr_ack = 1'b0;
					wr_err = 1'b0;
					rd_ack = 1'b1;
					rd_err = 1'b0;
					if(data_count === 3'b000) empty = 1'b1;
					else empty = 1'b0;
				end
			
			RD_ERR:
				begin
					wr_ack = 1'b0;
					wr_err = 1'b0;
					rd_ack = 1'b0;
					rd_err = 1'b1;
				end					
		endcase
	end
endmodule
