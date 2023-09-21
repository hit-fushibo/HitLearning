`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/09/01 16:00:07
// Design Name: 
// Module Name: cpu
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
/*
指令
8c010004
8c020008
00221820
00222022
00222824
00223025
00223826
0022402a
00014880
ac010008
ac020004
14060002
ac010000
08000000
08000010
ac010000
8c000000
00000000
08000000
00000000
08000000
00000000
*/
/*
数据
00000000
00000001
00000002
00000003
00000004
00000005
00000006
00000007
*/

module cpu(
    input            clk             ,  // clock, 100MHz
    input            resetn          ,  // active low

    // debug signals
    output reg [31:0]    debug_wb_pc     ,  // 当前正在执行指令的PC
    output reg           debug_wb_rf_wen ,  // 当前通用寄存器组的写使能信号
    output reg [4 :0]    debug_wb_rf_addr,  // 当前通用寄存器组写回的寄存器编号
    output reg [31:0]    debug_wb_rf_wdata  // 当前指令要写回的数据
    );
    //参数

    //cunter_in
    //none
    //cunter_out
    wire [4:0] T;


    //alu_in
    reg [31:0] alu_A,alu_B;
    reg [10:0] alu_Card;
    //alu_out
    wire [31:0] alu_F;
    wire alu_Cout,alu_Zero;


    //regs_in
    reg [4:0] regs_raddr1;
    reg [4:0] regs_raddr2;
    reg regs_we;
    reg [4:0] regs_waddr;
    reg [31:0] regs_wdata;
    //regs_out
    wire [31:0] regs_rdata1,regs_rdata2;


    //IRAM_in
    reg [7:0] iram_addr;
    reg [31:0] iram_wdata;
    reg iram_wen;
    //IRAM_out
    wire [31:0] iram_rdata;


    //DATARAM_in
    reg [7:0] dataram_addr;
    reg [31:0] dataram_wdata;
    reg dataram_wen;
    //DATARAM_out
    wire [31:0] dataram_rdata;


    //PC、IR、NPC、sa、A、B、aluout、cond、LMD
    reg [31:0] PC,IR,NPC,A,B,aluout,LMD;
    reg [4:0] sa;
    reg cond;

    //OP,R3,R2,R1,Imm
    reg [5:0] OP;
    reg [4:0] R3,R2,R1;
    reg [10:0] Imm;

    //模块
    cunter counter_U(
        .clk(clk),
        .rst(resetn),
        .T(T)
    );

    registers registers_U(
        .raddr1(regs_raddr1),
        .raddr2(regs_raddr2),
        .we(regs_we),
        .waddr(regs_waddr),
        .wdata(regs_wdata),
        .rdata1(regs_rdata1),
        .rdata2(regs_rdata2)
    );

    alu alu_U(
        .A(alu_A),
        .B(alu_B),
        .Card(alu_Card),
        .F(alu_F),
        .Cout(alu_Cout),
        .Zero(alu_Zero)
    );

    ram_by_regs iram(
        .wen  (iram_wen   ),
        .addr (iram_addr  ),
        .wdata(iram_wdata ),
        .rdata(iram_rdata ) 
    );


    ram_by_regs dataram(
        .wen  (dataram_wen   ),
        .addr (dataram_addr  ),
        .wdata(dataram_wdata ),
        .rdata(dataram_rdata ) 
    );
    reg i=1;

    //时钟上升沿触�?
    always @(posedge clk) begin
        
        if(!resetn) begin
            if(i==1) begin
                i=0;
                OP<=0;
                R3<=0;
                R2<=0;
                R1<=0;
                Imm<=0;
                PC<=0;
                IR<=0;
                NPC<=0;
                A<=0;
                B<=0;
                aluout<=0;
                LMD<=0;
                sa<=0;
                cond<=0;
                
                
                regs_raddr1<=0;
                regs_raddr2<=0;
                regs_we<=0;
                regs_waddr<=0;
                regs_wdata<=0;
                alu_A<=0;
                alu_B<=0;
                alu_Card<=0;

                //iram rst
                #10;
                iram_wen<=1;
                iram_wdata<=32'h8c010004;
                iram_addr<=32'd0;
                #10;
                iram_wdata<=32'h8c020008;
                iram_addr<=32'd4;
                #10;
                iram_wdata<=32'h00221820;
                iram_addr<=32'd8;
                #10;
                iram_wdata<=32'h00222022;
                iram_addr<=32'd12;
                #10;
                iram_wdata<=32'h00222824;
                iram_addr<=32'd16;
                #10;
                iram_wdata<=32'h00223025;
                iram_addr<=32'd20;
                #10;
                iram_wdata<=32'h00223826;
                iram_addr<=32'd24;
                #10;
                iram_wdata<=32'h0022402a;
                iram_addr<=32'd28;
                #10;
                iram_wdata<=32'h00014880;
                iram_addr<=32'd32;
                #10;
                iram_wdata<=32'hac010008;
                iram_addr<=32'd36;
                #10;
                iram_wdata<=32'hac020004;
                iram_addr<=32'd40;
                #10;
                iram_wdata<=32'h14060002;
                iram_addr<=32'd44;
                #10;
                iram_wdata<=32'hac010000;
                iram_addr<=32'd48;
                #10;
                iram_wdata<=32'h08000000;
                iram_addr<=32'd52;
                #10;
                iram_wdata<=32'h08000010;
                iram_addr<=32'd56;
                #10;
                iram_wdata<=32'hac010000;
                iram_addr<=32'd60;
                #10;
                iram_wdata<=32'h8c000000;
                iram_addr<=32'd64;
                #10;
                iram_wdata<=32'h00000000;
                iram_addr<=32'd68;
                #10;
                iram_wdata<=32'h08000000;
                iram_addr<=32'd72;
                #10;
                iram_wdata<=32'h00000000;
                iram_addr<=32'd76;
                #10;
                iram_wdata<=32'h08000000;
                iram_addr<=32'd80;
                #10;
                iram_wdata<=32'h00000000;
                iram_addr<=32'd84;
                #10;
                
                
                //dataram rst
                #10;
                dataram_wen<=1;
                dataram_wdata<=32'h00000000;
                dataram_addr<=32'd0;
                #10;
                dataram_wdata<=32'h00000001;
                dataram_addr<=32'd4;
                #10;
                dataram_wdata<=32'h00000002;
                dataram_addr<=32'd8;
                #10;
                dataram_wdata<=32'h00000003;
                dataram_addr<=32'd12;
                #10;
                dataram_wdata<=32'h00000004;
                dataram_addr<=32'd16;
                #10;
                dataram_wdata<=32'h00000005;
                dataram_addr<=32'd20;
                #10;
                dataram_wdata<=32'h00000006;
                dataram_addr<=32'd24;
                #10;
                dataram_wdata<=32'h00000007;
                dataram_addr<=32'd28;
                #10;
                
                



                iram_addr<=0;
                iram_wdata<=0;
                iram_wen<=0;
                dataram_addr<=0;
                dataram_wdata<=0;
                dataram_wen<=0;
            end


        end
        else begin
            i=1;
            case (T)
                5'b10000:begin
                    // $display("first");
                    debug_wb_rf_wen<=0;
                    
                    //取指
                    iram_addr=PC;
                    iram_wen=0;
                    #1;
                    IR=iram_rdata;
                    NPC=PC+4;
                end
                5'b01000:begin
                // $display("second");
                    //译码，读寄存器
                    OP=IR[31:26];
                    R2=IR[25:21];//rs
                    R3=IR[20:16];//rt
                    R1=IR[15:11];//rd
                    Imm=IR[10:0];
                    regs_raddr1=IR[25:21];
                    regs_raddr2=IR[20:16];
                    #1;
                    A=regs_rdata1;
                    B=regs_rdata2;              
                end
                5'b00100:begin
                // $display("third");
                    //执行、有效地址计算
                    case (OP)
                        6'b000000:begin//运算
                            alu_A=A;
                            alu_B=B;
                            alu_Card=Imm;
                            #1;
                            aluout=alu_F;    
                        end
                        6'b101011:begin//存数
                            aluout=IR[15:0]+R2;                            
                        end
                        6'b100011:begin//取数
                            aluout=IR[15:0]+R2;
                            dataram_addr=IR[15:0]+R2;                           
                        end
                        6'b000101:begin//不相等跳转
                            aluout=IR[15:0];
                        end
                        

                    endcase
                    
                end
                5'b00010:begin
                // $display("fourth");
                    //访存
                    case (OP)
                        6'b101011:begin//存数
                            dataram_wdata=B;
                            dataram_addr=aluout;
                            dataram_wen=1;
                            dataram_wen=0;
                        end
                        6'b100011:begin//取数
                            dataram_wen=0;
                            
                            LMD=dataram_rdata;
                            
                            
                        end
                    endcase
                    regs_we=1;
                    
                end
                5'b00001:begin
                // $display("fifth");
                //写回、更新PC
                    case (OP)
                        6'b000000:begin//运算
                        debug_wb_pc<=PC;
                        debug_wb_rf_wen<=1;
                        debug_wb_rf_addr<=R1;
                        debug_wb_rf_wdata<=aluout;
                        end
                        6'b100011:begin//取数
                        debug_wb_pc<=PC;
                        debug_wb_rf_wen<=1;
                        debug_wb_rf_addr<=R3;
                        debug_wb_rf_wdata<=LMD;
                            
                        end
                    endcase

                    //写回
                    case (OP)
                        6'b000000:begin//运算
                        #1;
                        regs_wdata=aluout;
                        regs_waddr=R1;
                        end
                        6'b100011:begin//取数
                        #1;
                        regs_wdata=LMD;
                        regs_waddr=R3;
                        end
                    endcase
                    regs_we=#5 0;

                    //更新PC
                    case (OP)
                        6'b101011:begin//存数
                            PC=NPC;
                        end
                        6'b100011:begin//取数                           
                            PC=NPC;
                            
                        end
                        6'b000101:begin//不相等跳转
                            if (A==B)begin
                                PC=NPC;
                            end
                            else begin
                                aluout=aluout<<2;
                                PC=NPC+aluout;
                            end
                        end
                        6'b000000:begin
                            PC=NPC;
                        end
                        6'b000010:begin//无条件转移
                            PC={NPC[31:28],IR[25:0]<<2};
                        end
                    endcase
                    
                    
                end 
            endcase
        end
        
    end




endmodule
