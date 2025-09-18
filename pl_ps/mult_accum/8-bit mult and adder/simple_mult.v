`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Simple multiplier module

module simple_mult_code(
    input clk,
    input [7:0] a,
    input [7:0] b,
    output [15:0] result
    );
    
    reg [15:0] result_reg;  // register to store product
    
    always@(posedge clk)
    begin
    result_reg<=a*b;  //latch result on clock edge
    end
    
    assign result=result_reg;  // drive output from register
endmodule
