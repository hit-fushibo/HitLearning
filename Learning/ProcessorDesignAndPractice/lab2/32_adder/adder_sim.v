`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/08/29 12:13:42
// Design Name: 
// Module Name: adder_sim
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


module adder_sim();
   reg [31:0]A;
   reg [31:0]B;
   reg Cin;
   wire [31:0]F;
   wire Cout;
   adder adder_1(
   .A(A),
   .B(B),
   .Cin(Cin),
   .F(F),
   .Cout(Cout)
   );
   initial
    begin
        A=32'd0;
        B=32'd0;
        Cin=1'd0;
    end
   always #1 {A,B,Cin}={A+32'd11000000,B+32'd11000000,~Cin};
    
    
endmodule
