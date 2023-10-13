`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/10/07 18:41:26
// Design Name: 
// Module Name: WB_MUX
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


module WB_MUX(
input [5:0]OP_code,
input [31:0]aluoutpu,
input [31:0]LMD,

output reg [31:0]out
    );
    always @(*) begin
        case (OP_code)
            6'b000000: begin
                out<=aluoutpu;
            end
            6'b100011: begin
                out<=LMD;
            end
        endcase
    end
endmodule
