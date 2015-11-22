  #include <stdio.h>

  #include "/user/cse320/Projects/project07.hardware.h"
  #include "/user/cse320/Projects/project07.support.h"

  void execute()
  {
    signal2 op;
	op = IR;
	op = op >> 30;
	
	
	signal3 op2;
	op2 = IR;
	op2 = op2 >> 22;
	op2 = op2 & 0x00000007;
	
	
	signal6 op3;
	op3 = IR;
	op3 = op3 >> 19;
	op3 = op3 & 0x0000003f;
	
	
	signal5 rs1;
	rs1 = IR;
	rs1 = rs1 >> 14;
	rs1 = rs1 & 0x0000001f;
	
	
	signal5 rs2;
	rs2 = IR;
	rs2 = rs2 & 0x0000001f;
	
	
	signal5 rd;
	rd = IR;
	rd = rd >> 25;
	rd = rd & 0x0000001f;

	
	signal1 i;
	i = IR;
	i = i >> 13;
	i = i & 0x00000001;

	
	signal13 simm13;
	simm13 = IR;
	simm13 = simm13 & 0x00001fff;

	
	signal32 extsimm13;
	if(simm13 > 0x00000fff){
		extsimm13 = simm13;
		extsimm13 = extsimm13 | 0xffffe000;
	}
	else{
		extsimm13 = simm13;
	}
	
	
	signal22 imm22;
	imm22 = IR;
	imm22 = imm22 & 0x003fffff;
	
	signal32 RS1, RS2, RD;
	
	read_reg_file( rs1, rs2, &RS1, &RS2 );
	
	signal32 carry = PSR;
	carry = carry >> 20;
	carry = carry & 0x00000001;
	


	if(op == 0){
		if(op2 == 4){
			//sethi

			signal32 sethi;
			sethi = imm22;
			sethi = sethi << 10;
			RD = sethi;
			write_reg_file( rd, RD );
		}
		else{
			//illegal instruction
			PSR = PSR | 0x00000001;
		}
	}
	
	else if(op == 2){
		if(op3 == 0){
			//addition
			if(i == 0){
				int add = RS1 + RS2;
				RD = add;
				write_reg_file( rd, RD );
				return;
			}
			if(i == 1){
				int add = RS1 + extsimm13;
				RD = add;
				write_reg_file( rd, RD );
				return;

			}

		}
		else if(op3 == 1){
			//and
			if(i == 0){
				int and = RS1 & RS2;
				RD = and;
				write_reg_file( rd, RD );
				return;
			}
			
			if(i == 1){
				int and = RS1 & extsimm13;
				RD = and;
				write_reg_file( rd, RD );
				return;
			}


		}
		else if(op3 == 2){
			//or
			
			if(i == 0){
				int or = RS1 | RS2;
				RD = or;
				write_reg_file( rd, RD );
				return;
			}
			
			if(i == 1){
				int or = RS1 | extsimm13;
				RD = or;
				write_reg_file( rd, RD );
				return;
			}

		}
		else if(op3 == 3){
			//xor
			
			if(i == 0){
				int xor = RS1 ^ RS2;
				RD = xor;
				write_reg_file( rd, RD );
				return;
			}
			if(i == 1){
				int xor = RS1 ^ extsimm13;
				RD = xor;
				write_reg_file( rd, RD );
				return;

			}


		}
		else if(op3 == 4){
			//subtraction
			
			if(i == 0){
				int sub = RS1 - RS2;
				RD = sub;
				write_reg_file( rd, RD );
				return;
			}
			
			if(i == 1){
				int sub = RS1 - extsimm13;
				RD = sub;
				write_reg_file( rd, RD );
				return;

			}

		}
		else if(op3 == 5){
			//andn
			
			if(i == 0){
				signal32 notRS2 = ~RS2;
				int andn = RS1 & notRS2;
				RD = andn;
				write_reg_file( rd, RD );
				return;
			}
			if(i == 1){
				signal32 notRS2 = ~extsimm13;
				int andn = RS1 & notRS2;
				RD = andn;
				write_reg_file( rd, RD );
				return;

			}

		}
		else if(op3 == 6){
			//orn
			if(i == 0){
				signal32 notRS2 = ~RS2;
				int orn = RS1 | notRS2;
				RD = orn;
				write_reg_file( rd, RD );
				return;
			}
			if(i == 1){
				signal32 notRS2 = ~extsimm13;
				int orn = RS1 | notRS2;
				RD = orn;
				write_reg_file( rd, RD );
				return;

			}

		}
		else if(op3 == 7){
			//xnor
			
			if(i == 0){
				signal32 notRS2 = ~RS2;
				int xnor = RS1 ^ notRS2;
				RD = xnor;
				write_reg_file( rd, RD );
				return;
			}
			if(i == 1){
				signal32 notRS2 = ~extsimm13;
				int xnor = RS1 ^ notRS2;
				RD = xnor;
				write_reg_file( rd, RD );
				return;

			}

		}
		else if(op3 == 8){
			//addx
			if(i == 0){
				int addx = RS1 + RS2 + carry;
				RD = addx;
				write_reg_file( rd, RD );
				return;
			}
			if(i == 1){
				int addx = RS1 + extsimm13 + carry;
				RD = addx;
				write_reg_file( rd, RD );
				return;
			}

		}
		else if(op3 == 12){
			//subx
			if(i == 0){
				int sub = RS1 - RS2 - carry;
				RD = sub;
				write_reg_file( rd, RD );
				return;
			}
			if(i == 1){
				int sub = RS1 - extsimm13 - carry;
				RD = sub;
				write_reg_file( rd, RD );
				return;

			}

		}
		else{
			//illegal instruction
			PSR = PSR | 0x00000001;
		}
	}
	else{
		//illegal instruction
		PSR = PSR | 0x00000001;
	}
	
	
  };
