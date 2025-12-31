module cla_clk(clk, a, b, ci, co, s);
	input clk;
	input [31:0] a, b;
	input ci;
	output co;
	output [31:0] s;
	
	reg [31:0] reg_a, reg_b, reg_s;
	reg reg_ci, reg_co;
	
	wire [31:0] wire_s;
	wire wire_co;
	
	always@ (posedge clk)
	begin
		reg_a <= a;
		reg_b <= b;
		reg_ci <= ci;
		reg_co <= wire_co;
		reg_s <= wire_s;		
	end
	
	cla32 u0_cla32(.a(reg_a), .b(reg_b), .ci(reg_ci), .co(wire_co), .s(wire_s));
	
	assign co = reg_co; 
	assign s = reg_s; 
	
endmodule
