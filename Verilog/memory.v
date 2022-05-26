module dff(output reg Q, input Cl,Pr,d,clk);
	always @(posedge clk) begin
		if (Cl==0)
		Q <=0;
		else if (Pr==1)
		Q <=1;
		else
		Q <=d;
	end
endmodule

module register(output [7:0] Dout, input [7:0] Din, input Cl, Pr, clk);
	dff dff0(Dout[0], Cl, Pr, Din[0], clk);
	dff dff1(Dout[1], Cl, Pr, Din[1], clk);
	dff dff2(Dout[2], Cl, Pr, Din[2], clk);
	dff dff3(Dout[3], Cl, Pr, Din[3], clk);
	dff dff4(Dout[4], Cl, Pr, Din[4], clk);
	dff dff5(Dout[5], Cl, Pr, Din[5], clk);
	dff dff6(Dout[6], Cl, Pr, Din[6], clk);
	dff dff7(Dout[7], Cl, Pr, Din[7], clk);
endmodule

//module memory(input [7:0] Din, input [5:0] add, input Cl, Pr, clk, output [7:0] Dout);
	//register reg1(Dout[0], Din[0], Cl, Pr, clk);
	//endmodule

module tg(input [7:0] Dout, output reg clk, output reg [7:0] Din, output reg Cl, Pr);
	initial begin
		$monitor($time,,, "clock= %b, clear= %b, preset=%b,  Din=%b, Dout=%b\n",clk,Cl,Pr,Din,Dout);
		Pr=1'b0;
		Cl=1'b1;
		Din=8'b00000000;
		#05 Din=8'b10101010;
		#05 Din=8'b01010101;
		#05 $finish;
	end
endmodule

module wb();
	reg clk;
	wire Cl,Pr;
	wire [7:0] Dout; wire [7:0] Din;
	register register1(Dout, Din, Cl, Pr, clk);
	tg tg1(Dout, clk, Din, Cl, Pr);
	initial begin
		clk=1'b0;
	end
	always
	#02 clk <=~clk;
endmodule
