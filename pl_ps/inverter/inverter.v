`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////

module inverter#(parameter DATA_WIDTH=32)(
    input axi_clk,
    input axi_rst,
    
    input s_axis_valid,
    output s_axis_ready,
    input [DATA_WIDTH-1:0] s_axis_data,
    
    output reg m_axis_valid,
    input m_axis_ready,
    output reg [DATA_WIDTH-1:0] m_axis_data    
    );
    
    
    integer i;
    
    assign s_axis_ready=m_axis_ready;   //s_axis_ready is output because your module must tell the upstream block when it can take data.
    
    always@(posedge axi_clk)
    begin
    
        if(s_axis_ready&s_axis_valid)
        begin
            for(i=0;i<DATA_WIDTH/8;i=i+1)
            begin
                m_axis_data[i*8+:8]<=255-s_axis_data[8*i+:8];
            
            end
        end
    
    end
    
    
    
    always@(posedge axi_clk)
    begin
        m_axis_valid<=s_axis_valid;
    
    end
