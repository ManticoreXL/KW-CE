module RAM(clk, cen, wen, addr, din, dout);
	input clk;
	input cen, wen;
	input [7:0] addr;
	input [63:0] din;
	output reg [63:0] dout;
	
	// contains 256 * 64-bit memory
	reg [63:0] mem [0:255];
	
	// initialize memory
	integer i;
	initial
	begin
		for(i=0; i<32; i=i+1)
			mem[i] = 64'b0;
	end
	
	always@(posedge clk)
	begin
		if(cen == 1)
			if(wen == 1) mem[addr] <= din;
			else dout <= mem[addr];
		else dout = 64'h0;
	end
endmodule
