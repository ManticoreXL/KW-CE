module clb4(a, b, ci, c1, c2, c3, co);
	input [3:0] a, b;
	input ci;
	output c1, c2, c3, co;
	
	wire [3:0] g, p;
	wire w0_c1;
	wire w0_c2, w1_c2;
	wire w0_c3, w1_c3, w2_c3;
	wire w0_co, w1_co, w2_co, w3_co;
	
	// Generate of carry
	_and2 u0_and2(.a(a[0]), .b(b[0]), .y(g[0]));
	_and2 u1_and2(.a(a[1]), .b(b[1]), .y(g[1]));
	_and2 u2_and2(.a(a[2]), .b(b[2]), .y(g[2]));
	_and2 u3_and2(.a(a[3]), .b(b[3]), .y(g[3]));
	
	// Propagate of carry
	_or2 u4_or2(.a(a[0]), .b(b[0]), .y(p[0]));
	_or2 u5_or2(.a(a[1]), .b(b[1]), .y(p[1]));
	_or2 u6_or2(.a(a[2]), .b(b[2]), .y(p[2]));
	_or2 u7_or2(.a(a[3]), .b(b[3]), .y(p[3]));
	
	// c1 = g[0] | (p[0] & ci)
	_and2 u8_and2(.a(p[0]), .b(ci), .y(w0_c1));
	_or2 u9_or2(.a(g[0]), .b(w0_c1), .y(c1));
	
	// c2 = g[1] | (p[1] & g[0]) | (p[1] & p[0] & ci)
	_and2 u10_and2(.a(p[1]), .b(g[0]), .y(w0_c2));
	_and3 u11_and3(.a(p[1]), .b(p[0]), .c(ci), .y(w1_c2));
	_or3 u12_or3(.a(g[1]), .b(w0_c2), .c(w1_c2), .y(c2));
	
	// c3 = g[2] | (p[2] & g[1]) | (p[2] & p[1] & g[0]) | (p[2] & p[1] & p[0] & ci)
	_and2 u13_and2(.a(p[2]), .b(g[1]), .y(w0_c3));
	_and3 u14_and3(.a(p[2]), .b(p[1]), .c(g[0]), .y(w1_c3));
	_and4 u15_and4(.a(p[2]), .b(p[1]), .c(p[0]), .d(ci), .y(w2_c3));
	_or4 u16_or4(.a(g[2]), .b(w0_c3), .c(w1_c3), .d(w2_c3), .y(c3));
	
	// co = g[3] | (p[3] & g[2]) | (p[3] & p[2] & g[1]) | (p[3] & p[2] & p[1] & g[0]) 
	// | (p[3] & p[2] & p[1] & p[0] & ci)
	_and2 u17_and2(.a(p[3]),.b(g[2]),.y(w0_co));
	_and3 u18_and3(.a(p[3]),.b(p[2]),.c(g[1]),.y(w1_co));
	_and4 u19_and4(.a(p[3]),.b(p[2]),.c(p[1]),.d(g[0]),.y(w2_co));
	_and5 u20_and5(.a(p[3]),.b(p[2]),.c(p[1]),.d(p[0]),.e(ci),.y(w3_co));
	_or5 u21_or4(.a(g[3]),.b(w0_co),.c(w1_co),.d(w2_co),.e(w3_co),.y(co));

	// modified carry out function.
	// wire 
	// co = ((((p[1] & g[0]) | g[1]) & p[2]) | g[2]) & p[3]) | g[3])
	// _and2 u17_and2(.a(g[0]), .b(p[1]), .y(w0));
	// _or2 u18_or2(.a(w0), .b(g[1]), .y(w1));
	// _and2 u19_and2(.a(w1), .b(p[2]), .y(w2));
	// _or2 u20_or2(.a(w2), .b(g[2]), .y(w3));
	// _and2 u21_and2(.a(w3), .b(p[3]), .y(w4));
	// _or2 u22_or2(.a(w4), .b(g[3]), .y(wg));
	// _and4 u23_and4(.a(p[0]), .b(p[1]), .c(p[2]), .d(p[3]), .y(wp));
	// _and2 u24_and2(.a(wp), .b(ci), .y(w5));
	// _or2 u25_or2(.a(wg), .b(w5), .y(co));
endmodule
