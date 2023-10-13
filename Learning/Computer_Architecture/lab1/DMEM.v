`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/10/13 10:08:49
// Design Name: 
// Module Name: DMEM
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module DMEM(
input [31:0]readaddr,
input wen,
input [31:0]waddr,
input [31:0]wdata,
output reg [31:0]rdata
    );
    reg [31:0] dmem[0:255];
    integer i;
    initial begin
        for (i=0;i<=255;i=i+1) begin
            // dmem[i]=i>>2;
            dmem[i]=i;
        end
    end
    always @(*) begin
        if (wen==1) begin
            dmem[waddr]<=wdata;
        end
        else begin
            rdata<=dmem[readaddr];
        end
    end

endmodule
