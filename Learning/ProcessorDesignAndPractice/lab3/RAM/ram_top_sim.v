`timescale 1ns / 1ps


module ram_top_sim();

/*参数声明*/

//ram

reg         clk;
reg         ram_wen;
reg  [15:0] ram_addr;
reg  [31:0] ram_wdata;


wire [31:0] ram_rdata;


//regs

reg  [4:0]  raddr1;
reg  [4:0]  raddr2;
reg  we;
reg  [4:0]  waddr;
reg  [31:0]  wdata;

wire [31:0]  rdata1;
wire [31:0]  rdata2;


//alu

reg  [31:0]  A;
reg  [31:0]  B;
reg  [4:0]  Card;
reg  Cin;

wire [31:0]  F;
wire  Cout;
wire  Zero;

/*模块例化*/

ram_top u_ram_top(
    .clk      (clk       ),
    .ram_wen  (ram_wen   ),
    .ram_addr (ram_addr  ),
    .ram_wdata(ram_wdata ),
    .ram_rdata(ram_rdata ) 
);


alu_1 alu(
	.A(A),
	.B(B),
	.Card(Card),
	.Cin(Cin),
	.F(F),
	.Cout(Cout),
	.Zero(Zero)
);


registers_1 regs(
	.clk(clk),
	.raddr1(raddr1),
	.raddr2(raddr2),
	.we(we),
	.waddr(waddr),
	.wdata(wdata),
	.rdata1(rdata1),
	.rdata2(rdata2)
);

initial 
begin
    clk = 1'b1;
end
always #5 clk = ~clk;


initial 
begin
	//00f0-00f4(0000ff00-0000ff44)
	ram_addr   = 16'd0;
	ram_wdata  = 32'd0;
	ram_wen    =  1'd0;
	#101;
	
	$display("RAM Test Begin");
	
	#10;
	ram_wen    = 1'b0;
	ram_addr   = 16'hf0;
	ram_wdata  = 32'hffffffff;

    #10;
	ram_wen    = 1'b1;
	ram_addr   = 16'hf0;
	ram_wdata  = 32'h11223344;

    #10;
	ram_wen    = 1'b0;
	ram_addr   = 16'hf1;

	#10;
	ram_wen    = 1'b0;
	ram_addr   = 16'hf0;
    
    #10;
	ram_wen    = 1'b1;
	ram_wdata  = 32'hff00;
	ram_addr   = 16'hf0;

	#10;
	ram_wdata  = 32'hff11;
	ram_addr   = 16'hf1;

	#10;
	ram_wdata  = 32'hff22;
	ram_addr   = 16'hf2;

	#10;
	ram_wdata  = 32'hff33;
	ram_addr   = 16'hf3;

	#10;
	ram_wdata  = 32'hff44;
	ram_addr   = 16'hf4;
	#10;

	#10;
	ram_wen    = 1'b0;
	ram_addr   = 16'hf0;
	ram_wdata  = 32'hffffffff;

	#10;
	ram_addr   = 16'hf1;

	#10;
	ram_addr   = 16'hf2;

	#10;
	ram_addr   = 16'hf3;

	#10;
	ram_addr   = 16'hf4;

	//ram(00f0)+ram(00f3) -> ram(00f5)

	//ram(00f0)->reg(1)
	#10;
	ram_addr=16'hf0;
	#10;
	wdata=ram_rdata;
	we=1;
	waddr=5'b1;
	//ram(00f3)->reg(2)
	#10;
	ram_addr=16'hf3;
	#10;
	wdata=ram_rdata;
	we=1;
	waddr=5'b10;
	//reg(1)->A,reg(2)->B,A+B->F
	#10;
	we=0;
	raddr1=1;
	raddr2=2;
	#10;
	Card=5'b00000;
	Cin=0;
	A=rdata1;
	B=rdata2;
	//F->reg(3)
	#10;
	wdata=F;
	waddr=3;
	we=1;
	//reg(3)->ram(00f5)
	#10;
	we=0;
	raddr1=3;
	ram_addr=16'h00f5;
	#10;
	ram_wdata=rdata1;
	ram_wen=1;

	#10;
	#10;
	ram_wen=0;





	#100;
	$display("RAM Test Success");
	$finish;
end

endmodule

