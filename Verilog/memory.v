module clock (output reg clk);
    initial begin
	$dumpfile("clock.vcd");
	$dumpvars(0, clock);
        // $monitor($time,,, "%b", clk);
        clk = 1'b0;
	#05 $finish;
    end
    always
        #01 clk = ~clk;
endmodule

module DFF(output reg q, input clr, pr, d, clk);
	always @( posedge clk ) begin
        	if (pr == 0)
            	q <= 1;
        	else if (clr == 0)
            	q <= 0;
        	else
            	q <= d;
	end
endmodule

module register(output [7:0] dout,input [7:0] din,input clr, pr,input clk);
    DFF dff0(dout[0], clr, pr, din[0], clk);
    DFF dff1(dout[1], clr, pr, din[1], clk);
    DFF dff2(dout[2], clr, pr, din[2], clk);
    DFF dff3(dout[3], clr, pr, din[3], clk);
    DFF dff4(dout[4], clr, pr, din[4], clk);
    DFF dff5(dout[5], clr, pr, din[5], clk);
    DFF dff6(dout[6], clr, pr, din[6], clk);
    DFF dff7(dout[7], clr, pr, din[7], clk);
endmodule

module memory (output [7:0] dout,input [7:0] din,input [4:0] ad,input clk, pr, clr);
	reg [7:0] memory1[31:0];
	reg [4:0] ad_reg;
	always @ (posedge clk) begin
		memory1 [ad] <= din;
		ad_reg <= ad;
	end
	assign dout = memory1[ad_reg];
endmodule

module tg();

endmodule

module wb();

endmodule
