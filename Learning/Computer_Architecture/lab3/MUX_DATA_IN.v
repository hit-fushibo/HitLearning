`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/10/31 22:46:11
// Design Name: 
// Module Name: MUX_DATA_IN
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


module MUX_DATA_IN(
    input [31:0] mux_data_in_data1,
    input [31:0] mux_data_in_data2,
    input mux_data_valid_seq,
    output [31:0] mux_data_out
    );

    assign mux_data_out = mux_data_valid_seq==0 ? mux_data_in_data1 : mux_data_in_data2;

endmodule
