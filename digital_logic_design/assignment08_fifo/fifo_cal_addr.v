module fifo_cal_addr(state, head, tail, data_count, we, re, next_head, next_tail, next_data_count);
	input [2:0] state, head, tail;
	input [3:0] data_count;
	output reg we, re;
	output reg [2:0] next_head, next_tail;
	output reg [3:0] next_data_count;
	
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
			// initialize head, tail, count
			INIT: begin
				next_head = 3'b0;
				next_tail = 3'b0;
				next_data_count = 4'b0;	
			end
			// mem[tail] = d_in; tail++;
			WRITE: begin
				we = 1'b1;
				re = 1'b0;
				next_tail = tail + 4'b001;
				if(data_count < 3'b111) next_data_count = data_count + 4'b0001;
			end
			// wR_ERR
			WR_ERR: begin
				we = 1'b0;
				re = 1'b0;
			end
			// d_out = mem[head]; head++'
			READ: begin
				we = 1'b0;
				re = 1'b1;
				next_head = head + 4'b0001;
				if(data_count > 3'b0) next_data_count = data_count - 4'b0001;	
			end
			// RD_ERR
			RD_ERR: begin
			we = 1'b0;
				re = 1'b0;
			end			
		endcase
	end

endmodule
