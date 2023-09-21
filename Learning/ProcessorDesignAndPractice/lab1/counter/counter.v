`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/08/28 18:33:30
// Design Name: 
// Module Name: counter
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


module counter(
input clk,
input rst,
output [4:0]T
    );
    reg [4:0] T_reg;
    reg[26:0] cnt;
    assign T=T_reg;
    always @(posedge clk) begin
    if (!rst) begin
    cnt=27'd0;
    T_reg <=4'b1000;
    end else if (cnt == 27'd10) begin
    cnt <= 27'd0;
    T_reg <= {T_reg[0],T_reg[3],T_reg[2],T_reg[1]};
    end else begin
    cnt <= cnt+27'd1;
    end
    end
    
endmodule
