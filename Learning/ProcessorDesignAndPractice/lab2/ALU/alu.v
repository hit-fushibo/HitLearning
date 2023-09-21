`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/08/29 12:26:37
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
input [4:0]Card,
input Cin,
output reg [31:0]F,
output reg Cout,
output reg Zero
    );
    always@(*)
    begin
    case(Card)
    5'b00000:begin//F=A+B
    {Cout,F}=A+B;
    end
    5'b00001:begin//F=A+B+Cin
    {Cout,F}=A+B+Cin;
    end
    5'b00010:begin//F=A-B
    Cout=0;
    {Cout,F}=A-B;
    end
    5'b00011:begin//F=A-B-Cin
    Cout=0;
   {Cout,F}=A-B-Cin;
    end
    5'b00100:begin//F=B-A
    Cout=0;
    {Cout,F}=B-A;
    end
    5'b00101:begin//F=B-A-Cin
    Cout=0;
    {Cout,F}=B-A-Cin;
    end
    5'b00110:begin//F=A
    Cout=0;
    F=A;
    end
    5'b00111:begin//F=B
    Cout=0;
    F=B;
    end
    5'b01000:begin//F=~A
    Cout=0;
    F=~A;
    end
    5'b01001:begin//F=~B
    Cout=0;
    F=~B;
    end
    5'b01010:begin//F=A|B
    Cout=0;
    F=A|B;
    end
    5'b01011:begin//F=A&B
    Cout=0;
    F=A&B;
    end
    5'b01100:begin//F=Aͬ��B
    Cout=0;
    F=~(A^B);
    end
    5'b01101:begin//F=A���B
    Cout=0;
    F=(A^B);
    end
    5'b01110:begin//F=~(A&&B)
    Cout=0;
    F=~(A&B);
    end
    5'b01111:begin//F=0
    Cout=0;
    F<=32'b0;
    end
   endcase
   if (F == 32'b0) begin
   Zero=1;
   end
   else
   Zero=0;
   end
   
endmodule
