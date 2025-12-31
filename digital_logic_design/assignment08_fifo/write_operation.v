module write_operation(Addr, we, to_reg);
	input we;
	input [2:0] Addr;
	output [7:0] to_reg;
	
	wire [7:0] w_a;
	
	_3_to_8_decoder u0_3_to_8_decoder(.d(Addr), .q(w_a));
	_and2 u1_and2(.a(we), .b(w_a[0]), .y(to_reg[0]));
	_and2 u2_and2(.a(we), .b(w_a[1]), .y(to_reg[1]));
	_and2 u3_and2(.a(we), .b(w_a[2]), .y(to_reg[2]));
	_and2 u4_and2(.a(we), .b(w_a[3]), .y(to_reg[3]));
	_and2 u5_and2(.a(we), .b(w_a[4]), .y(to_reg[4]));
	_and2 u6_and2(.a(we), .b(w_a[5]), .y(to_reg[5]));
	_and2 u7_and2(.a(we), .b(w_a[6]), .y(to_reg[6]));
	_and2 u8_and2(.a(we), .b(w_a[7]), .y(to_reg[7]));
endmodule
