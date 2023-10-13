`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/10/07 10:58:34
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


module cpu(
    input  clk,
    input resetn,

    output [31:0] debug_wb_pc,
    output  debug_wb_rf_wen,
    output [4:0] debug_wb_rf_addr,
    output [31:0] debug_wb_rf_wdata  
    );
//---------------
    //PC_in
    wire [31:0] npc;
    wire stall;

    //PC_out
    wire [31:0] c_pc;

//---------------
    //PCadder4_in
    //c_pc

    //PCadder4_out
    //npc

//---------------
    //IMEM_in
    //c_pc

    //IMEM_out
    wire [31:0] inst;

//---------------
    //IF_ID_in
    //c_pc
    //stall
    //inst
    //npc

    //IF_ID_out
    wire [31:0] ID_IR;
    wire [31:0] ID_NPC;
    wire [31:0] ID_PC;

//---------------
    //regs_in
    //ID_IR[25:21]
    //ID_IR[20:16]
    wire [31:0] wb_data;
    wire [31:0] wb_addr;
    wire wb_wen;

    //regs_out
    wire [31:0] A;
    wire [31:0] B;

//---------------
    //Extender_in
    //ID_IR[15:0]

    //Extender_out
    wire [31:0] extendeImm;

//---------------
    //ID_EX_in
    //ID_PC
    //ID_NPC
    //A
    //B
    //ID_IR
    //extendeImm

    //ID_EX_out
    wire [31:0] EX_PC;
    wire [31:0] EX_NPC;
    wire [31:0] EX_A;
    wire [31:0] EX_B;
    wire [31:0] EX_Imm;
    wire [31:0] EX_IR;
    wire [10:0] ALUOP_code;

//---------------
    //MUX_A_in
    wire [2:0] select_a;
    //EX_A
    //EX_IR[25:21]
    wire [31:0] LMD;
    wire [31:0] EX_MEM_aluout;
    wire [31:0] MEM_WB_aluout;

    //MUX_A_out
    wire [31:0] A_output;

//---------------
    //MUX_B_in
    wire [2:0] select_b;
    //EX_B
    //EX_Imm
    //LMD
    //EX_MEM_aluout
    //MEM_WB_aluout

    //MUX_B_out
    wire [31:0]B_output;

//---------------
    //ALU_in
    //EX_IR[10:0]
    //A_output
    //B_output

    //ALU_out
    wire [31:0]aluoutput;
    wire Cond;
    wire Zero;
    wire Cout;

//---------------
    //EX_MEM_in
    //EX_PC
    //EX_IR
    //aluoutput
    //B_output
    //Cond

    //EX_MEM_out
    wire [31:0] MEM_PC;
    wire [31:0] MEM_ALUoutput;
    wire [31:0] MEM_B;
    wire [31:0] MEM_IR;
    wire [31:0] MEM_Cond;
    wire DMEM_wen;

//---------------
    //DMEM_in
    //MEM_ALUoutput
    //DMEM_wen
    //MEM_ALUoutput
    //MEM_B

    //DMEM_out
    wire [31:0] D_LMD;

//---------------
    //MEM_WB_in
    //MEM_PC
    //D_LMD
    //MEM_ALUoutput
    //MEM_IR
    //MEM_Cond

    //MEM_WB_out
    wire [31:0] WB_PC;
    //LMD
    wire [31:0] WB_ALUoutput;
    wire [31:0] WB_IR;
    //wbaddr
    //wb_wen

//---------------
    //WB_MUX_in
    //WB_IR[31:26]
    //WBALUoutput;
    //LMD

    //WB_MUX_out
    //wb_data

//---------------
    //Select_in
    //EX_IR
    //MEM_IR
    //ID_IR

    //Select_out
    //select_a
    //select_b
    //stall

assign debug_wb_pc=MEM_PC;
assign debug_wb_rf_wen=wb_wen;
assign debug_wb_rf_addr=wb_addr;
assign debug_wb_rf_wdata=wb_data;
 





    PC PC_u(
        .clk(clk),
        .resetn(resetn),
        .npc(npc),
        .stall(stall),
        .c_pc(c_pc)
    );

    PCadd4 PCadd4_u(
        .c_pc(c_pc),
        .npc(npc)
    );

    IMEM IMEM_u(
        .addr(c_pc),
        .output_ins(inst)
    );

    IF_ID IF_ID_u(
        .clk(clk),
        .resetn(resetn),
        .PC(c_pc),
        .stall(stall),
        .IR(inst),
        .NPC(npc),
        .O_IR(ID_IR),
        .O_NPC(ID_NPC),
        .o_PC(ID_PC)
    );

    regs regs_u(
        .clk(clk),
        .resetn(resetn),
        .raddr1(ID_IR[25:21]),
        .raddr2(ID_IR[20:16]),
        .wdata(wb_data),
        .waddr(wb_addr),
        .wen(wb_wen),
        .rdata1(A),
        .rdata2(B)
    );

    Extender Extender_u(
        .value(ID_IR[15:0]),
        .out_value(extendeImm)
    );

    ID_EX ID_EX_u(
        .clk(clk),
        .resetn(resetn),
        .PC(ID_PC),
        .NPC(ID_NPC),
        .A(A),
        .B(B),
        .IR(ID_IR),
        .Imm(extendeImm),
        .o_PC(EX_PC),
        .o_npc(EX_NPC),
        .o_A(EX_A),
        .o_B(EX_B),
        .o_Imm(EX_Imm),
        .o_IR(EX_IR),
        .o_ALUOPcode(ALUOP_code)
    );

    MUX_A MUX_A_u(
        .select(select_a),
        .A(EX_A),
        .base(EX_IR[25:21]),
        .LMD(LMD),
        .MEM_ALU(EX_MEM_aluout),
        .WB_ALU(MEM_WB_aluout),
        .A_output(A_output)
    );

    MUX_B MUX_B_u(
        .select(select_b),
        .B(EX_B),
        .Imm(EX_Imm),
        .LMD(LMD),
        .MEM_ALU(EX_MEM_aluout),
        .WB_ALU(MEM_WB_aluout),
        .B_output(B_output)
    );

    ALU ALU_u(
        .OP_code(ALUOP_code),
        .rs(A_output),
        .rt(B_output),
        .ALU_output(aluoutput),
        .Cond(Cond),
        .Zero(Zero),
        .Cout(Cout)
    );

    EX_MEM EX_MEM_u(
        .clk(clk),
        .resetn(resetn),
        .PC(EX_PC),
        .IR(EX_IR),
        .ALUoutput(aluoutput),
        .B(B_output),
        .cond(Cond),
        .o_PC(MEM_PC),
        .o_ALUoutput(MEM_ALUoutput),
        .o_B(MEM_B),
        .o_IR(MEM_IR),
        .o_cond(MEM_Cond),
        .DMEM_wen(DMEM_wen)
    );

    DMEM DMEM_u(
        .readaddr(MEM_ALUoutput),
        .wen(DMEM_wen),
        .waddr(MEM_ALUoutput),
        .wdata(MEM_B),
        .rdata(D_LMD)
    );

    MEM_WB MEM_WB_u(
        .clk(clk),
        .resetn(resetn),
        .PC(MEM_PC),
        .LMD(D_LMD),
        .ALUoutput(MEM_ALUoutput),
        .IR(MEM_IR),
        .MOVZ_cond(MEM_Cond),
        .o_PC(WB_PC),
        .o_LMD(LMD),
        .o_ALUoutput(WB_ALUoutput),
        .o_IR(WB_IR),
        .wb_addr(wbaddr),
        .reg_wen(wb_wen)
    );

    WB_MUX WB_MUX_u(
        .OP_code(WB_IR[31:26]),
        .aluoutpu(WBALUoutput),
        .LMD(LMD),
        .out(wb_data)
    );

    Select Select_u(
        .clk(clk),
        .EX_MEM_IR(EX_IR),
        .MEM_WB_IR(MEM_IR),
        .ID_EX_IR(ID_IR),
        .A_select(select_a),
        .B_select(select_b),
        .stall(stall)
    );




endmodule
