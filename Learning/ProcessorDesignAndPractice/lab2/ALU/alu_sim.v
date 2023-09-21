`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/08/29 13:01:54
// Design Name: 
// Module Name: alu_sim
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


module alu_sim();
reg [31:0]A,B;
reg [4:0]Card;
reg Cin;
wire [31:0]F;
wire Cout,Zero;

alu alu_u(
.A(A),
.B(B),
.Card(Card),
.Cin(Cin),
.F(F),
.Cout(Cout),
.Zero(Zero)
);
initial begin
A=32'b11110000_00001111_10101010_01010101;
B=~A;
Cin=1'b0;
Card=5'b00000;
end
always #10 {Card,Cin}={Card+1'b1,~Cin};

endmodule
