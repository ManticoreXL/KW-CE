module fifo(clk, reset_n, wr_en, rd_en, d_in,
				d_out, full, empty, data_count,
				wr_ack, wr_err, rd_ack, rd_err);
	input clk, reset_n, wr_en, rd_en;
	input [31:0] d_in;
	output reg [31:0] d_out;
	output [3:0] data_count;
	output full, empty, wr_ack, wr_err, rd_ack, rd_err;
	
	wire [2:0] next_state, state;
	wire [2:0] next_head, head;
	wire [2:0] next_tail, tail;
	wire [3:0] next_data_count;
	_register3_r_async u0_register3_r_async(.clk(clk), .reset_n(reset_n), .next_state(next_state), .state(state)); // state
	_register3_r_async u1_register3_r_async(.clk(clk), .reset_n(reset_n), .next_state(next_head), .state(head)); // head
	_register3_r_async u2_register3_r_async(.clk(clk), .reset_n(reset_n), .next_state(next_tail), .state(tail)); // tail
	_register4_r_async u2_register4_r_async(.clk(clk), .reset_n(reset_n), .next_state(next_data_count), .state(data_count)); // data_counter
														 
	fifo_ns u1_fifo_ns(.wr_en(wr_en), .rd_en(rd_en), .state(state), .data_count(data_count), .next_state(next_state));
	
	wire we, re;							 
	fifo_cal_addr u2_fifo_cal_addr(.state(state), .head(head), .tail(tail), .data_count(data_count),
											 .we(we), .re(re), .next_head(next_head), .next_tail(next_tail),
										    .next_data_count(next_data_count));
												
	fifo_out u3_fifo_out(.state(state), .data_count(data_count), .full(full), .empty(empty), 
								.wr_ack(wr_ack), .wr_err(wr_err), .rd_ack(rd_ack), .rd_err(rd_err));
	
	wire [31:0] w_d_out;
	Register_file u4_Register_file(.clk(clk), .reset_n(reset_n), .wAddr(tail), .wData(d_in), .we(we), .rAddr(head), .rData(w_d_out));
	
	always@(posedge clk)
	begin
		if(re == 1'b0) d_out <= 32'b0;
		else d_out <= w_d_out;
	end
endmodule
