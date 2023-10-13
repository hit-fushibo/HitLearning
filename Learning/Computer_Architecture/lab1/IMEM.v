`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/10/13 10:08:49
// Design Name: 
// Module Name: IMEM
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
`define base "../../../lab_1.data/base_inst_data"
`define additional1 "../../../lab_1.data/additional_inst_data1"
`define additional2 "../../../lab_1.data/additional_inst_data2"


module IMEM(
input [31:0] addr,
output [31:0] output_ins
    );
    reg [31:0] imem[0:255];
    initial begin
        // $readmemh(`base,imem);
        // $readmemh(`additional1,imem);
        $readmemh(`additional2,imem);
    end

    assign output_ins=imem[addr/4];
endmodule
