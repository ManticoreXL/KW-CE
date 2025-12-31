module ram(clk, cen, wen, addr, din, dout);
	input clk;
	input cen, wen;
	input [4:0] addr;
	input [31:0] din;
	output reg [31:0] dout;
	
	// contains 32 * 32-bit memory 
	reg [31:0] mem [0:31];
	
	// initialize memory
	integer i;
	initial
	begin
		for(i=0; i<32; i=i+1)
			mem[i] = 32'h0000_0000;
	end
	
	// read/write operation
	always@(posedge clk)
	begin
		if(cen == 1) // chip enabled
			if(wen == 1)
				mem[addr] <= din; // write mode, no dout
			else
				dout <= mem[addr]; // read mode, no writing
		else dout = 32'b0; // chip disabled
	end
endmodule
