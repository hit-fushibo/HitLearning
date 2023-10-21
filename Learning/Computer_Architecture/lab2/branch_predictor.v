`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/10/20 21:24:11
// Design Name: 
// Module Name: branch_predictor
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

module branch_predictor(
    input           clk,
    input           resetn,
    input[31:0]     old_PC,
    input           predict_en,
    output reg[31:0]new_PC,
    output reg      predict_jump,
    input           upd_en,
    input[31:0]     upd_addr,
    input           upd_jumpinst,
    input           upd_jump,
    input           upd_predfail,
    input[31:0]     upd_target
);



//BTB 128路直接映射 pc[8:2]索引
    integer i;
    reg [66:0] group [0:127];


    always @(*) begin
        if (resetn==0)begin
            for (i=0;i<128;i=i+1)begin
                group[i]=67'b0;
            end
            new_PC<=32'b0;
            predict_jump<=1'b0;
        end
        else begin//start
            //update
            if(upd_en==1&&upd_jumpinst==1)begin
                //hit
                if (group[upd_addr[8:2]][65]==1 && old_PC==group[old_PC[8:2]][65:34])begin
                    if(upd_predfail==0)begin
                        if(group[upd_addr[8:2]][1:0]==2'b00)begin
                        end
                        else begin
                            if(group[upd_addr[8:2]][1:0]==2'b01)begin
                                group[upd_addr[8:2]][1:0]=2'b00;
                            end
                            else begin
                                if(group[upd_addr[8:2]][1:0]==2'b10)begin
                                    group[upd_addr[8:2]][1:0]=2'b11;
                                end
                                else begin
                                    group[upd_addr[8:2]][1:0]=2'b11;
                                end
                            end
                            
                        end
                    end
                    else begin
                        if(group[upd_addr[8:2]][1:0]==2'b00)begin
                            group[upd_addr[8:2]][1:0]=2'b01;
                        end
                        else begin
                            if(group[upd_addr[8:2]][1:0]==2'b11)begin
                                group[upd_addr[8:2]][1:0]=2'b10;
                            end
                            else begin
                                if(group[upd_addr[8:2]][1:0]==2'b10)begin
                                    group[upd_addr[8:2]][1:0]=2'b00;
                                end
                                else begin
                                    group[upd_addr[8:2]][1:0]=2'b11;
                                end
                            end
                            
                        end
                    end
                end
                //not hit
                else begin
                    if(upd_jump==1)begin
                        group[upd_addr[8:2]]={1'b1,upd_addr,upd_target,2'b11};
                    end
                end
            end//update end

            if (predict_en==1)begin//predict
                //hit
                if (group[old_PC[8:2]][66]==1 && old_PC==group[old_PC[8:2]][65:34])begin
                    if(group[old_PC[8:2]][1]==1)begin
                        new_PC=group[old_PC[8:2]][33:2];
                        predict_jump=1'b1;
                    end
                    else begin
                        new_PC=old_PC+4;
                        predict_jump=1'b0;
                    end
                end
                //not hit
                else begin
                    new_PC=old_PC+4;
                    predict_jump=1'b0;
                end
            end//predict end

               
        end//end
    end
endmodule
