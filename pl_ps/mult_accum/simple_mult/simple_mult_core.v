`timescale 1ns / 1ps

module simple_mult_core(
    input clk,
    input [15:0] a,
    input [15:0] b,
    output [31:0] result
    );
    
    reg [31:0] result_reg;
    
    always@(posedge clk)
    begin
    result_reg<=a*b;
    end
    
    assign result=result_reg;
    
endmodule
