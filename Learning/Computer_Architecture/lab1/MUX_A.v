`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/10/07 18:41:26
// Design Name: 
// Module Name: MUX_A
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


module MUX_A(
input [2:0]select,
input [31:0]A,
input [31:0]base,
input [31:0]LMD,
input [31:0]MEM_ALU,
input [31:0]WB_ALU,

output reg [31:0] A_output
    );
    always @(*) begin
        case (select)
            3'b000: begin
                A_output<=A;
            end
            3'b001: begin
                A_output<=A;
            end
            3'b010: begin
                A_output<=MEM_ALU;
            end
            3'b011: begin
                A_output<=WB_ALU;
            end
            3'b100: begin
                A_output<=LMD;
            end
        endcase
    end
endmodule
