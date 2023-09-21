`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/09/01 16:11:47
// Design Name: 
// Module Name: alu
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


module alu(
input [31:0]A,
input [31:0]B,
input [10:0]Card,
output reg [31:0]F,
output reg Cout,
output reg Zero
    );
    reg [5:0] code;
    reg [4:0] sa;
    always@(*) begin
        code=Card[5:0];
        sa=Card[10:6];
        case(code)
            6'b100000:begin
                {Cout,F}=A+B;
            end
            6'b100010:begin
                {Cout,F}=A-B;
            end
            6'b100100:begin
                Cout=0;
                F=A&B;
            end
            6'b100101:begin
                Cout=0;
                F=A|B;            
            end
            6'b100110:begin
                Cout=0;
                F=A^B;            
            end
            6'b101010:begin
                if (A<B) begin
                    F=1;
                end
                else begin
                    F=0;
                end
            end
            6'b101010:begin
                if(A<B)begin
                    F=32'b1;
                end
                else begin
                    F=32'b0;
                end
            end
            6'b001010:begin
                if (B==0) begin
                    F=A;
                end
                
            end
            6'b000000:begin
                F=B<<sa;
            end  
        endcase
        if (F == 32'b0) begin
        Zero=1;
        end
        else
        Zero=0;
        end
   
endmodule

