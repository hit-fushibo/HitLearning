`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/10/07 18:47:52
// Design Name: 
// Module Name: regs
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


module regs(
input clk,
input resetn,
input [4:0]raddr1,
input [4:0]raddr2,
input [31:0]wdata,
input [4:0]waddr,
input wen,
output reg [31:0]rdata1,
output reg [31:0]rdata2
    );
    reg [31:0] registers [31:0];
    integer i;
    initial begin
        for (i=0;i<=31;i=i+1) begin
            registers[i]<=0;
        end
    end
    always @(*) begin
        if(resetn==0) begin
            for (i=0;i<=31;i=i+1) begin
                registers[i]<=0;
            end
        end
    end

    always @(*) begin
        rdata1=registers[raddr1];
    end
    always @(*) begin
        rdata2=registers[raddr2];
    end
    
    always @(posedge clk) begin
        if (wen==1) begin
            if (waddr==0) begin
                
            end
            else begin
                registers[waddr]=wdata;
            end
            
        end
        
    end


endmodule
