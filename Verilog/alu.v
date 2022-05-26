// Half Adder Module
module HalfAdder (
    output sum, carry,
    input  augend, addend, sub);

    wire w1;
    xor(w1, augend, sub);
    xor(sum, w1, addend);
    and(carry, w1, addend);
endmodule // HalfAdder

// Full Adder Module
module FullAdder (
    output sum, carry,
    input  augend, addend, cin, sub);

    wire p, g, r;
    HalfAdder hadd1(p, g, augend, addend, sub);
    HalfAdder hadd2(sum, r, p, cin, sub);
    or(carry, g, r);
endmodule // FullAdder

// 4-bit Adder Module
module Adder (
    output [3:0] c,
    output       carry,
    input  [3:0] a, b,
    input        sub);

    wire w1, w2, w3;
    FullAdder fadd1(c[0], w1, a[0], b[0], 1'b0, sub);
    FullAdder fadd2(c[1], w2, a[1], b[1], w1, sub);
    FullAdder fadd3(c[2], w3, a[2], b[2], w2, sub);
    FullAdder fadd4(c[3], carry, a[3], b[3], w3, sub);
endmodule // Adder

// 4-bit And Module
module myand (
    output [3:0] c,
    input  [3:0] a, b);

    and(c[0], a[0], b[0]);
    and(c[1], a[1], b[1]);
    and(c[2], a[2], b[2]);
    and(c[3], a[3], b[3]);
endmodule // myand

// 4-bit Or Module
module myor (
    output [3:0] c,
    input  [3:0] a, b);

    or(c[0], a[0], b[0]);
    or(c[1], a[1], b[1]);
    or(c[2], a[2], b[2]);
    or(c[3], a[3], b[3]);
endmodule // myor

// 4-bit Not Module
module mynot (
    output [3:0] c,
    input  [3:0] a);

    not(c[0], a[0]);
    not(c[1], a[1]);
    not(c[2], a[2]);
    not(c[3], a[3]);
endmodule // mynot


// 4-bit Xor Module
module myxor (
    output [3:0] c,
    input  [3:0] a, b);

    xor(c[0], a[0], b[0]);
    xor(c[1], a[1], b[1]);
    xor(c[2], a[2], b[2]);
    xor(c[3], a[3], b[3]);
endmodule // myxor

// 4-bit Nand Module
module mynand (
    output [3:0] c,
    input  [3:0] a, b);

    nand(c[0], a[0], b[0]);
    nand(c[1], a[1], b[1]);
    nand(c[2], a[2], b[2]);
    nand(c[3], a[3], b[3]);
endmodule // mynand

// 4-bit Nor Module
module mynor (
    output [3:0] c,
    input  [3:0] a, b);

    nor(c[0], a[0], b[0]);
    nor(c[1], a[1], b[1]);
    nor(c[2], a[2], b[2]);
    nor(c[3], a[3], b[3]);
endmodule // mynor

// 1-bit 8x1 Multiplexer Module
module Mux0 (
    output       out,
    input        d1, d2, d3, d4, d5, d6, d7, d8,
    input  [2:0] s);

    assign out = (
        (~s[0] & ~s[1] & ~s[2] & d1) | (s[0] & ~s[1] & ~s[2] & d2) | (~s[0] & s[1] & ~s[2] & d3) | (s[0] & s[1] & ~s[2] & d4) |
        (~s[0] & ~s[1] & s[2] & d5) | (s[0] & ~s[1] & s[2] & d6) | (~s[0] & s[1] & s[2] & d7) | (s[0] & s[1] & s[2] & d8));
endmodule // Mux0

// 4-bit 8x1 Multiplexer Module
module Mux (
    output [3:0] out,
    input  [3:0] d1, d2, d3, d4, d5, d6, d7, d8,
    input  [2:0] s);

    Mux0 mux0(out[0], d1[0], d2[0], d3[0], d4[0], d5[0], d6[0], d7[0], d8[0], s);
    Mux0 mux1(out[1], d1[1], d2[1], d3[1], d4[1], d5[1], d6[1], d7[1], d8[1], s);
    Mux0 mux2(out[2], d1[2], d2[2], d3[2], d4[2], d5[2], d6[2], d7[2], d8[2], s);
    Mux0 mux3(out[3], d1[3], d2[3], d3[3], d4[3], d5[3], d6[3], d7[3], d8[3], s);
endmodule // Mux

// Arithmetic and Logic Unit Module
module ALU (
    output [3:0] c,
    output       carry,
    input  [2:0] op,
    input  [3:0] a, b);

    wire [3:0] w1, w2, w3, w4, w5, w6, w7, w8;
    wire       wc1, wc2;
    Adder  add(w1, wc1, a, b, 1'b0);
    Adder  sub(w2, wc2, a, b, 1'b1);
    myand  mand(w3, a, b);
    myor   mor(w4, a, b);
    mynot  mnot(w5, a);
    myxor  mxor(w6, a, b);
    mynand mnand(w7, a, b);
    mynor  mnor(w8, a, b);
    Mux    mux(c, w1, w2, w3, w4, w5, w6, w7, w8, op);
    assign carry = (~op[0] & wc1) | (op[0] & wc2);
endmodule // ALU

// Test Genrator for ALU
module TestGen (
    input      [3:0] c,
    input            carry,
    output reg [2:0] op,
    output reg [3:0] a, b);

    // wire w1;
    // assign w1 = { op, a, b };
    initial begin
      //  $monitor($time,,, "Opcode: %b  A: %b  B: %b Output: %b  Carry: %b\n", op, a, b, c, carry);
	$dumpfile("alu.vcd");
	$dumpvars(0, op,a,b,c,carry);
            { op, a, b } = { 3'd0, 4'd8, 4'd4 };
        #02 op = 3'd1;
        #02 op = 3'd2;
        #02 op = 3'd3;
        #02 op = 3'd4;
        #02 op = 3'd5;
        #02 op = 3'd6;
        #02 op = 3'd7;
    end
endmodule // TestGen

// WorkBench Module
module wb;
    wire [3:0] a, b, c;
    wire [2:0] op;
    wire       carry;
    ALU myalu(c, carry, op, a, b);
    TestGen test(c, carry, op, a, b);
endmodule // wb
