`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/10/31 22:37:10
// Design Name: 
// Module Name: VALID_JUDGE
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


module VALID_JUDGE(
    input [31:0] valid_judge_cpu_addr_in,              // cpu请求地址
    input valid_judge_valid1_in,
    input valid_judge_valid2_in,
    input [19:0] valid_judge_tag1_in,           // 数据1 tag
    input [19:0] valid_judge_tag2_in,           // 数据2 tag
    output is_hitted,                           // 是否命中(0-N/1-Y)
    output hit_seq                            // 哪一路命中(0-1/1-2)
    );

    assign is_hitted = (valid_judge_valid1_in==1 && valid_judge_cpu_addr_in[31:12] == valid_judge_tag1_in) || (valid_judge_valid2_in==1 && valid_judge_cpu_addr_in[31:12] == valid_judge_tag2_in);

    assign hit_seq = (valid_judge_valid2_in==1 && valid_judge_cpu_addr_in[31:12] == valid_judge_tag2_in) ? 1 : 0;
    
endmodule
