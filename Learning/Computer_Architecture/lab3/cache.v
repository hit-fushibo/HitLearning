`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/10/31 16:02:47
// Design Name: 
// Module Name: cache
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


module cache (
    input            clk             ,  // clock, 100MHz
    input            rst             ,  // active low

    //  Sram-Like接口信号，用于CPU访问Cache
    input         cpu_req      ,    //由CPU发送至Cache
    input  [31:0] cpu_addr     ,    //由CPU发送至Cache
    output [31:0] cache_rdata  ,    //由Cache返回给CPU
    output        cache_addr_ok,    //由Cache返回给CPU
    output        cache_data_ok,    //由Cache返回给CPU

    //  AXI接口信号，用于Cache访问主存
    output [3 :0] arid   ,              //Cache向主存发起读请求时使用的AXI信道的id号
    output [31:0] araddr ,              //Cache向主存发起读请求时所使用的地址
    output        arvalid,              //Cache向主存发起读请求的请求信号
    input         arready,              //读请求能否被接收的握手信号

    input  [3 :0] rid    ,              //主存向Cache返回数据时使用的AXI信道的id号
    input  [31:0] rdata  ,              //主存向Cache返回的数据
    input         rlast  ,              //是否是主存向Cache返回的最后一个数据
    input         rvalid ,              //主存向Cache返回数据时的数据有效信号
    output        rready                //标识当前的Cache已经准备好可以接收主存返回的数据
);

    /*TODO：完成指令Cache的设计代码*/
    // STORE 信号
    wire valid1_out;
    wire valid2_out;
    wire [19:0] tag1_out;
    wire [19:0] tag2_out;
    wire [31:0] data1_out;
    wire [31:0] data2_out;
    wire [31:0] cpu_addr_out;
    wire write_ok;

    // COMP 信号
    wire start_write;             // 是否要开始写
    wire [255:0] write_data;  // 需要写入的数据 (小端序)
    wire [31:0] write_addr;    // 原请求地址，STORE自己提取字地址

    STORE U_STORE(
        .clk(clk),
        .rst(rst),
        .store_in_en(cache_data_ok),
        // Sram-Like
        .cpu_req(cpu_req),
        .cpu_addr(cpu_addr),
        // reg
        .valid1_out(valid1_out),
        .valid2_out(valid2_out),
        .tag1_out(tag1_out),
        .tag2_out(tag2_out),
        .data1_out(data1_out),
        .data2_out(data2_out),
        .cpu_addr_out(cpu_addr_out),
        //COMP
        .write_en(start_write),
        .write_addr_in(write_addr),
        .write_data_in(write_data),
        .write_ok(write_ok)
    );


    COMP U_COMP(
        .clk(clk),
        .rst(rst),
        // Sram-Like
        .cache_rdata(cache_rdata),
        .cache_addr_ok(cache_addr_ok),
        .cache_data_ok(cache_data_ok),
        // reg
        .cpu_addr_in(cpu_addr_out),
        .valid1_in(valid1_out),
        .valid2_in(valid2_out),
        .tag1_in(tag1_out),
        .tag2_in(tag2_out),
        .data1_in(data1_out),
        .data2_in(data2_out),
        // STORE
        .ok_write(write_ok),
        .start_write(start_write),
        .write_data(write_data),
        .write_addr(write_addr),
        // MEM
        // add
        .arid(arid),
        .araddr(araddr),
        .arvalid(arvalid),
        .arready(arready),
        // data
        .rid(rid),
        .rdata(rdata),
        .rlast(rlast),
        .rvalid(rvalid),
        .rready(rready)
    );
    
endmodule
