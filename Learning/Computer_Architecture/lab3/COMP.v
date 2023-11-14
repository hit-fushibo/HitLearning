`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/10/31 16:39:38
// Design Name: 
// Module Name: COMP
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


module COMP(
    input clk,  // 时钟
    input rst,  // 复位

    // Sram-Like接口
    output [31:0] cache_rdata,      // 指令输出
    output cache_addr_ok,           // 通告cpu地址收到信号
    output cache_data_ok,           // 通告cpu数据准备好

    // 段间寄存器接口
    input [31:0] cpu_addr_in,       // 当前需要取的地址，用于比较tag以及miss时向memory发出请求
    input valid1_in,                // 数据1有效位
    input valid2_in,                // 数据2有效位
    input [19:0] tag1_in,           // 数据1 tag
    input [19:0] tag2_in,           // 数据2 tag
    input [31:0] data1_in,          // 数据1
    input [31:0] data2_in,          // 数据2
    
    // 与STORE交互接口
    input ok_write,                 // 是否已写入完成
    output reg start_write,             // 是否要开始写
    output reg [255:0] write_data,  // 需要写入的数据 (小端序)
    output reg [31:0] write_addr,    // 原请求地址，STORE自己提取字地址


    // 与memory交互接口
    // 地址握手信号
    output reg [3 :0] arid   ,              //Cache向主存发起读请求时使用的AXI信道的id号
    output reg [31:0] araddr ,              //Cache向主存发起读请求时所使用的地址
    output reg        arvalid,              //Cache向主存发起读请求的请求信号
    input             arready,              //读请求能否被接收的握手信号
    // 数据握手信号
    input  [3 :0] rid    ,              //主存向Cache返回数据时使用的AXI信道的id号
    input  [31:0] rdata  ,              //主存向Cache返回的数据
    input         rlast  ,              //是否是主存向Cache返回的最后一个数据
    input         rvalid ,              //主存向Cache返回数据时的数据有效信号
    output reg    rready                //标识当前的Cache已经准备好可以接收主存返回的数据

    );
    
    // 初步选择
    wire is_hitted;     // 是否有命中
    wire hit_seq;     // 哪个命中
    wire [31:0] mux_data_out;  // 选出的数据
    
    // 处理不命中
    reg [1:0] miss;         // 不命中状态(0-初态/1-不命中/2-数据接收完成/3-数据装载完成)
    
    // 与主存交互状态state
    // 0-初态(发地址和请求,置araddr和arvalid);
    // 1-握手成功(拉低arvalid,拉高rready)，开始接收数据;
    reg state;   

    // 接收数据计数器
    reg [2:0] recv_counter;  
    // 接收数据暂存器
    reg [255:0] recv_buffer;
    // 需要送给cpu的数据
    reg [31:0] cache_rdata_tosend;

    reg first_beat;

    // cpu接口
    assign cache_addr_ok = (first_beat == 1) ? 1 : ((miss==3) ? 1 : is_hitted);       // 装载完成时置1，其他时候为is_hitted的值
    assign cache_data_ok = (first_beat == 1) ? 1 : ((miss==3) ? 1 : is_hitted);
    assign cache_rdata = (first_beat == 1) ? 32'b0 : ((miss == 3) ? cache_rdata_tosend : mux_data_out);



    VALID_JUDGE U_VALID_JUDGE(
        .valid_judge_cpu_addr_in(cpu_addr_in),              // cpu请求地址
        .valid_judge_valid1_in(valid1_in),
        .valid_judge_valid2_in(valid2_in),
        .valid_judge_tag1_in(tag1_in),           // 数据1 tag
        .valid_judge_tag2_in(tag2_in),           // 数据2 tag
        .is_hitted(is_hitted),                           // 是否命中(0-N/1-Y)
        .hit_seq(hit_seq)                            // 哪一路命中(0-1/1-2)
    );

    MUX_DATA_IN U_MUX_DATA_IN(
        .mux_data_in_data1(data1_in),
        .mux_data_in_data2(data2_in),
        .mux_data_hit_seq(hit_seq),
        .mux_data_out(mux_data_out)
    );

    always @(posedge clk) begin
        if (first_beat == 1 && rst == 1) begin
            first_beat <= 0;
        end else if (rst == 1 && first_beat ==0) begin
          if (miss == 0) begin
            if (is_hitted == 0) begin
                miss <= 1;  // 进入交互状态
                araddr <= {cpu_addr_in[31:5], 5'b0};  // 置地址
                arvalid <= 1;                           // 置请求位
            end else begin
                miss <= 0;
            end   
        // 与主存交互
        end else if (miss == 1) begin
            // 状态0-发出地址握手请求
            if (state == 0) begin
                // 主存响应了请求，拉低arvalid，拉高rready，开始准备接收数据
                if (arvalid == 1 && arready == 1) begin
                    state <= 1;
                    arvalid <= 0;
                    rready <= 1;
                    recv_counter <= 0;
                end else begin
                    state <= 0;
                end
            // 状态1-接收数据
            end else if (state == 1) begin
                if (rvalid == 1 && rlast != 1) begin
                    if (recv_counter == 0) begin
                        if (recv_counter == cpu_addr_in[4:2]) begin // 判断是否是当前cpu请求的数据，如果是，存入tosend中准备送出
                            cache_rdata_tosend <= rdata;
                        end
                        recv_buffer[31:0] <= rdata;
                        recv_counter = recv_counter + 1;
                    end else if (recv_counter == 1) begin
                        if (recv_counter == cpu_addr_in[4:2]) begin
                            cache_rdata_tosend <= rdata;
                        end
                        recv_buffer[63:32] <= rdata;
                        recv_counter = recv_counter + 1;
                    end else if (recv_counter == 2) begin
                        if (recv_counter == cpu_addr_in[4:2]) begin
                            cache_rdata_tosend <= rdata;
                        end
                        recv_buffer[95:64] <= rdata;
                        recv_counter = recv_counter + 1;
                    end else if (recv_counter == 3) begin
                        if (recv_counter == cpu_addr_in[4:2]) begin
                            cache_rdata_tosend <= rdata;
                        end
                        recv_buffer[127:96] <= rdata;
                        recv_counter = recv_counter + 1;
                    end else if (recv_counter == 4) begin
                        if (recv_counter == cpu_addr_in[4:2]) begin
                            cache_rdata_tosend <= rdata;
                        end
                        recv_buffer[159:128] <= rdata;
                        recv_counter = recv_counter + 1;
                    end else if (recv_counter == 5) begin
                        if (recv_counter == cpu_addr_in[4:2]) begin
                            cache_rdata_tosend <= rdata;
                        end
                        recv_buffer[191:160] <= rdata;
                        recv_counter = recv_counter + 1;
                    end else if (recv_counter == 6) begin
                        if (recv_counter == cpu_addr_in[4:2]) begin
                            cache_rdata_tosend <= rdata;
                        end
                        recv_buffer[223:192] <= rdata;
                        recv_counter = recv_counter + 1;
                    end
                end else if (rvalid == 1 && rlast == 1) begin
                    if (recv_counter == cpu_addr_in[4:2]) begin
                            cache_rdata_tosend <= rdata;
                    end
                    recv_buffer[255:224] <= rdata;  // 记录数据
                    state <= 0;         // 最后一个数据，改变状态
                    miss <= 2;          // 置miss，表示接收数据完成
                    recv_counter <= 0;  // counter回零
                end               
            end
        // 向cache中装载数据
        end else if (miss == 2) begin
            if (start_write == 0) begin
                start_write <= 1;           // 通知store开始存数据
                write_addr <= cpu_addr_in;  // 置地址
                write_data <= recv_buffer;  // 置数据
            end

            if (ok_write == 1) begin
                miss <= 3;                                  // 置miss为3，完成数据装载
                start_write <= 0;
                rready <= 0;
            end
        // 装载完成
        end else if (miss == 3) begin
            miss <= 0;      // miss归零
        end
        end
    end


    // 复位逻辑
    always @(posedge clk) begin
        if (rst == 0) begin
            miss <= 0;
            state <= 0;
            arid <= 0;
            recv_counter <= 0;
            cache_rdata_tosend <= 0;
            recv_buffer <= 0;
            rready <= 0;
            write_addr <= 0;
            start_write <= 0;
            write_data <= 0;
            arvalid <= 0;
            first_beat <= 1;
        end
    end

endmodule
