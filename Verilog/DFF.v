module DFF(output reg q,input      Cl, Pr,  d, clk);

    always @( negedge clk ) begin
        if (Cl == 0)
            q <= 0;
        else if (Pr == 0)
            q <= 1;
        else
            q <= d;
    end
endmodule

module tg(input q, output reg  Cl, Pr, d,      clk);

    initial begin
        //$monitor($time,,, "clk:%b preset:%b clear:%b Q:%b  Data: %b\n", clk,Pr,Cl,q,d);
$dumpfile("DFF.vcd");
	$dumpvars(0, clk,Pr, Cl,q ,d);
           clk=1'b0;
	   {d,Cl,Pr}={1'b0,1'b0,1'b1};
        #02 {d,Cl,Pr}={1'b0,1'b1,1'b0};
 #02 {d,Cl,Pr}={1'b0,1'b1,1'b1};
 #02 {d,Cl,Pr}={1'b1,1'b0,1'b1};
 #02 {d,Cl,Pr}={1'b1,1'b1,1'b0};
 #02 {d,Cl,Pr}={1'b1,1'b1,1'b1};
        #04 $finish;
    end
always #01 clk=~clk;
endmodule

module wb();
wire q,d,Cl,Pr,clk;
DFF d1(q,Cl,Pr,d,clk);
tg tg1(q,Cl,Pr,d,clk);
endmodule
