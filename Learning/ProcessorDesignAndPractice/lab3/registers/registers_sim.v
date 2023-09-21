`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/08/30 14:16:05
// Design Name: 
// Module Name: registers_sim
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


module registers_sim();

    //变量声明
    reg clk;
    // clk<=0;
    reg [4:0]raddr1,raddr2;
    reg we;
    reg [4:0]waddr;
    reg [31:0]wdata;
    wire [31:0]rdata1,rdata2;

    //模块例化
    registers registers_u(
        clk,raddr1,raddr2,we,waddr,wdata,rdata1,rdata2
    );


    //初始�?
    initial begin
        clk=0;
        raddr1=5'b0;
        raddr2=5'b0;
        waddr=5'b0;
        wdata=32'b10111000_11011110_00001111_10100101;
    end

    //时钟信号
    always #5 clk=~clk;

    //仿真
    initial begin
        //�?0号寄存器


        //�?1�?2号寄存器
        #6;
        we=1;
        waddr=5'b1;
        
       
        //读端�?1�?1号寄存器。端�?2�?1号寄存器，后�?2号寄存器
        raddr1=5'b1;
        
        
        //没有写使能的情况下的测试
        wdata=32'b0;
        waddr=5'b1;
        #10;

        //�?0号寄存器测试
        we=1;
        waddr=0;
        wdata=32'b111;
        #10;
        raddr1=0;
    end

    //80ns stop
    initial begin
        forever begin
            #80;
            if ($time >= 80) begin
                $finish;
            end
        end
    end
    
endmodule
