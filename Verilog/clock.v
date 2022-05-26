module clock (output reg clock);
    initial begin
	$dumpfile("clock.vcd");
	$dumpvars(0, clock);
        // $monitor($time,,, "%b", clk);
        clock = 0;
	#100 $finish;
    end
    always
        #5 clock = ~clock;
endmodule

