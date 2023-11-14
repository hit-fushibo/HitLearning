`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/10/31 16:07:29
// Design Name: 
// Module Name: STORE
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


module STORE(
    input clk,  // 时钟
    input rst,  // 复位
    input cpu_req,  // cpu请求信号
    input store_in_en,  // 输入使能
    input [31:0] cpu_addr,  // cpu请求地址，后两位恒0，因为4字节是一个字

    output reg valid1_out,      // 有效位1
    output reg valid2_out,      // 有效位2
    output reg [19:0] tag1_out,     // tag1
    output reg [19:0] tag2_out,     // tag2
    output [31:0] data1_out,    // data1
    output [31:0] data2_out,    // data2
    output reg [31:0] cpu_addr_out,  // cpu请求地址(用于带入下一阶段)

    //与COMP连接的控制信号，用于数据读写
    input write_en,     // 写使能，由COMP给出，标志需要写
    input [31:0] write_addr_in,   // 写地址
    input [255:0] write_data_in,   // 写数据    给数据的顺序：低位存低地址数据，高位存高地址数据，小端法
    output reg write_ok     // 写完成信号

    );

    // 相关存储体定义
    reg[19:0] tags1[127:0]; // 第一路标志位
    reg[19:0] tags2[127:0]; // 第二路标志位
    reg[127:0] valid1;  // 第一路有效位
    reg[127:0] valid2;  // 第二路有效位
    reg[127:0] fifo;        // 替换记录位，使用FIFO方式进行替换

    // 信号定义
    reg wen1;  // 第一路ram写使能信号
    reg wen2;  // 第二路ram写使能信号

    // 写状态信号，用于在8个时钟内写入传来的数据
    // 使用方法：在0-8之间循环，为8时置ok位，翻转fifo，置valid位并回零。写入的数据由state决定
    reg [3:0] state_write;  
    reg [2:0] write_addr_suffix;        // 写地址后缀，用于分时写入一块的8个字
    // 接收到的要写入的数据和地址
    reg [31:0] write_addr;
    reg [255:0] write_data_total;       // 所有要写入的数据
    reg [31:0] write_data;              // 当前要写入的数据

    // 读逻辑：
    
    // 第一路ram(需要按字寻址)
    // BRAM的en端口是整体的使能端口，置位时才响应读写操作，置零时不响应
    dataram_1 u_dataram_1(
        .addrb(cpu_addr[11:2]),
        .clkb(clk),
        .doutb(data1_out),
        .enb(1'b1),
        .addra({write_addr[11:5], write_addr_suffix}),
        .dina(write_data),
        .clka(clk),
        .wea(wen1)
    );

    // 第二路ram
    dataram_1 u_dataram_2(
        .addrb(cpu_addr[11:2]),
        .clkb(clk),
        .doutb(data2_out),
        .enb(1'b1),
        .addra({write_addr[11:5], write_addr_suffix}),
        .dina(write_data),
        .clka(clk),
        .wea(wen2)
    );

    always @(posedge clk) begin
        if (store_in_en == 1 && rst == 1) begin
            // 有效位输出
            valid1_out <= valid1[cpu_addr[11:5]];
            valid2_out <= valid2[cpu_addr[11:5]];

            // 标志位输出(只需使用index，找到对应行即可)
            tag1_out <= tags1[cpu_addr[11:5]];
            tag2_out <= tags2[cpu_addr[11:5]];

            // 请求地址输出
            cpu_addr_out <= cpu_addr;
        end
    end

    // 写逻辑
    // fifo为1时，写第一路；fifo为2时，写第二路
    // 状态一共轮转10次，第一次接收数据和置写使能位，最后一次完成其他部分的写和写使能复位
    always @(posedge clk) begin
        if (write_en == 1 && state_write == 0) begin    // 接收到写入信号，将写入地址和数据存下来，进入写状态
            write_addr <= write_addr_in;
            write_addr_suffix <= 3'h0;
            write_data_total <= write_data_in;
            write_data <= write_data_in[31:0];
            state_write <= state_write + 1;
            wen1 <= ~fifo[write_addr_in[11:5]];
            wen2 <= fifo[write_addr_in[11:5]];
        end else if (state_write == 1) begin
            state_write <= state_write + 1;
            write_addr_suffix <= 3'h1;
            write_data <= write_data_total[63:32];
        end else if (state_write == 2) begin
            state_write <= state_write + 1;
            write_addr_suffix <= 3'h2;
            write_data <= write_data_total[95:64];
        end else if (state_write == 3) begin
            state_write <= state_write + 1;
            write_addr_suffix <= 3'h3;
            write_data <= write_data_total[127:96];
        end else if (state_write == 4) begin
            state_write <= state_write + 1;
            write_addr_suffix <= 3'h4;
            write_data <= write_data_total[159:128];
        end else if (state_write == 5) begin
            state_write <= state_write + 1;
            write_addr_suffix <= 3'h5;
            write_data <= write_data_total[191:160];
        end else if (state_write == 6) begin
            state_write <= state_write + 1;
            write_addr_suffix <= 3'h6;
            write_data <= write_data_total[223:192];
        end else if (state_write == 7) begin
            state_write <= state_write + 1;
            write_addr_suffix <= 3'h7;
            write_data <= write_data_total[255:224];
        end else if (state_write == 8) begin  // 当状态轮转到8时，已写入全部数据
            write_ok <= 1;
            state_write = state_write + 1;
            fifo[write_addr[11:5]] <= ~fifo[write_addr[11:5]];   // 翻转fifo标志，下次写入另一路
            // 修改tag和valid
            if (fifo[write_addr[11:5]]==0) begin
                tags1[write_addr[11:5]] <= write_addr[31:12];
                valid1[write_addr[11:5]] <= 1;
            end else begin
                tags2[write_addr[11:5]] <= write_addr[31:12];
                valid2[write_addr[11:5]] <= 1;
            end
        end else if (state_write == 9) begin
            wen1 <= 0;  // 写使能复位
            wen2 <= 0;  // 写使能复位
            state_write <= 0;           // 状态回零
        end

        // ok只持续一个周期，一定能接收到，不需要握手，发出通告即可
        if (state_write == 9 && write_ok==1) begin
            write_ok <= 0;
        end
    end
    

    // 复位逻辑
    // tag 不需要清零，只要将valid清零即可
    always @(posedge clk) begin
        if (rst==0) begin
            valid1 <= 128'b0;
            valid2 <= 128'b0;
            fifo   <= 128'b0;
            write_ok <= 0;
            state_write <= 0;
            write_data_total <= 0;
            write_data <= 0;
            write_addr_suffix <= 0;
            // first_beat <= 1;
        end
    end

endmodule
