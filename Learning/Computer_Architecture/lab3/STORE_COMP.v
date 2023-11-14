`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/11/01 16:22:55
// Design Name: 
// Module Name: STORE_COMP
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


module STORE_COMP(
    input clk,
    input rst,

    input store_comp_in_en,          // 输入使能，连接cache_data_ok

    // 入口
    input store_comp_valid1_in,      // 有效位1
    input store_comp_valid2_in,      // 有效位2
    input [19:0] store_comp_tag1_in,     // tag1
    input [19:0] store_comp_tag2_in,     // tag2
    input [31:0] store_comp_data1_in,    // data1
    input [31:0] store_comp_data2_in,    // data2
    input [31:0] store_comp_cpu_addr_in,  // cpu请求地址

    // 出口
    output reg store_comp_valid1_out,      // 有效位1
    output reg store_comp_valid2_out,      // 有效位2
    output reg[19:0] store_comp_tag1_out,     // tag1
    output reg [19:0] store_comp_tag2_out,     // tag2
    output reg [31:0] store_comp_data1_out,    // data1
    output reg [31:0] store_comp_data2_out,    // data2
    output reg [31:0] store_comp_cpu_addr_out  // cpu请求地址(用于带入下一阶段)

    );

    reg first_peat;
    always @(posedge clk) begin
        if (first_peat == 0) begin  // 第一拍要加载数据
            first_peat <= 1;
            store_comp_valid1_out <= store_comp_valid1_in;
            store_comp_valid2_out <= store_comp_valid2_in;
            store_comp_tag1_out <= store_comp_tag1_in;
            store_comp_tag2_out <= store_comp_tag2_in;
            store_comp_data1_out <= store_comp_data1_in;
            store_comp_data2_out <= store_comp_data2_in;
            store_comp_cpu_addr_out <= store_comp_cpu_addr_in;
        end
        if (store_comp_in_en == 1) begin
            store_comp_valid1_out <= store_comp_valid1_in;
            store_comp_valid2_out <= store_comp_valid2_in;
            store_comp_tag1_out <= store_comp_tag1_in;
            store_comp_tag2_out <= store_comp_tag2_in;
            store_comp_data1_out <= store_comp_data1_in;
            store_comp_data2_out <= store_comp_data2_in;
            store_comp_cpu_addr_out <= store_comp_cpu_addr_in;
        end
    end

    always @(posedge clk) begin
        if (rst == 0) begin
            store_comp_valid1_out <= 1;
            store_comp_valid2_out <= 0;
            store_comp_tag1_out <= 0;
            store_comp_tag2_out <= 0;
            store_comp_data1_out <= 0;
            store_comp_data2_out <= 0;
            store_comp_cpu_addr_out <= 0;
            first_peat <= 0;
        end
    end
    
endmodule
