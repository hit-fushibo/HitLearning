`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/09/02 09:04:27
// Design Name: 
// Module Name: ram_by_regs
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


module ram_by_regs(
    input [7:0] addr,
    input [31:0] wdata,
    input wen,
    output reg [31:0] rdata
    );
    reg [31:0] registers[0:255];
    always @(*) begin
        if(wen==1) begin
            registers[addr]=wdata;
        end
        else begin
            rdata=registers[addr];
        end
        
    end

endmodule
