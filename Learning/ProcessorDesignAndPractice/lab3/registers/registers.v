`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/08/30 13:57:44
// Design Name: 
// Module Name: registers
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


module registers(
input clk,
input [4:0] raddr1,
input [4:0] raddr2,
input we,
input [4:0] waddr,
input [31:0] wdata,
output reg[31:0] rdata1,
output reg[31:0] rdata2
    );

    reg[31:0] registers[1:31];//0号寄存器只保存0

    //raddr1
    always @(*) begin
        if (raddr1==5'b000000) begin
            rdata1<=32'b0;
        end
        else begin
            rdata1<=registers[raddr1];
        end
    end
    //raddr2
    always @(*) begin
        if (raddr2==5'b000000) begin
            rdata2<=32'b0;
        end
        else begin
            rdata2<=registers[raddr2];
        end
    end

    //write
    always @(posedge clk) begin
        if ((we == 1) && (waddr!=0)) begin
            registers[waddr]=wdata;
        end
    end


endmodule
