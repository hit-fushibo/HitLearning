`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/10/13 20:55:27
// Design Name: 
// Module Name: Select
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


module Select(
input clk,
input [31:0]EX_MEM_IR,
input [31:0]MEM_WB_IR,
input [31:0]ID_EX_IR,

output reg [2:0]A_select,
output reg [2:0]B_select,
output reg stall
    );
    reg [5:0] EM_OP;
    reg [5:0] MW_OP;
    reg [5:0] IE_OP;
    reg [4:0] EM_rd;
    reg [4:0] MW_rd;
    reg [4:0] MW_rt;
    reg [4:0] IE_rs;
    reg [4:0] IE_rt;
    always @(posedge clk) begin
        EM_OP<=EX_MEM_IR[31:26];
        MW_OP<=MEM_WB_IR[31:26];
        IE_OP<=ID_EX_IR[31:26];
        EM_rd<=EX_MEM_IR[15:11];
        MW_rd<=MEM_WB_IR[15:11];
        MW_rt<=MEM_WB_IR[20:16];
        IE_rs<=ID_EX_IR[25:21];
        IE_rt<=ID_EX_IR[20:16];


        stall<=0;
        if((EM_OP==6'b100011&&(IE_OP==6'b000000&&(IE_rs==EX_MEM_IR[20:16]||IE_rt==EX_MEM_IR[20:16])))||(EM_OP==6'b100011&&IE_OP==6'b101011&&IE_rt==EX_MEM_IR[20:16]))begin
            stall=1;
        end
        else begin
            //A
            //EX/MEM alu->alu_a
            if (EM_OP==6'b000000&&EM_rd==IE_rs)begin
                A_select<=3'b010;
            end
            //MEM/WB alu->alu_a
            else if(MW_OP==6'b000000&&MW_rd==IE_rs)begin
                A_select<=3'b011;
            end
            //MEM/WB LMD->alu_a
            else if(MW_OP==6'b100011&&MW_rt==IE_rs)begin
                A_select<=3'b100;
            end
            //base->alu_a
            else if(IE_OP==6'b101011||IE_OP==6'b100011)begin
                A_select<=3'b001;
            end
            //reg_a->alu_a
            else begin
                A_select<=3'b000;
            end
            

            //b
            //EX/MEM alu->alu_b
            if ((EM_OP==6'b000000&&IE_OP==6'b000000&&EM_rd==IE_rt)||(EM_OP==6'b000000&&IE_OP==6'b101011&&EM_rd==IE_rt))begin
                B_select<=3'b010;
            end
            //MEM/WB alu->alu_b
            else if((MW_OP==6'b000000&&IE_OP==6'b000000&&MW_rd==IE_rt)||(MW_OP==6'b000000&&IE_OP==6'b101011&&EM_rd==IE_rt))begin
                B_select<=3'b011;
            end
            //MEM/WB LMD->alu_b
            else if((MW_OP==6'b100011&&IE_OP==6'b000000&&MW_rt==IE_rt)||(MW_OP==6'b100011&&IE_OP==6'b101011&&EM_rd==IE_rt))begin
                B_select<=3'b100;
            end
            //Imm->alu_b
            else if(IE_OP==6'b101011||IE_OP==6'b100011)begin
                B_select<=3'b001;
            end
            //reg_b->alu_b
            else begin
                B_select<=3'b000;
            end
        
        end
    end
    


endmodule
