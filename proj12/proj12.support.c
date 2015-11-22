#include "/user/cse320/Projects/project12.support.h"


unsigned update( unsigned nPC, unsigned PC, unsigned IR, unsigned PSR ){

	unsigned op = IR >> 30;
	unsigned op2 = IR << 7;
	op2 = op2 >> 29;
	unsigned op3 = IR << 7;
	op3 = op3 >> 26;
	unsigned a = IR >> 29;
	
	unsigned rs1 = IR << 13;
	rs1 = rs1 >> 27;
	
	unsigned finalrs1;
	finalrs1 = rs1 << 24;
	finalrs1 = finalrs1 + (rs1 << 16);
	finalrs1 = finalrs1 + (rs1 << 8);
	finalrs1 = finalrs1 + rs1;
	//this computes rs1 to be the # of rs1 duplicated 4 times
	
	unsigned rs2 = IR << 27;
	rs2 = rs2 >> 27;
	
	unsigned finalrs2;
	finalrs2 = rs2 << 24;
	finalrs2 = finalrs2 + (rs2 << 16);
	finalrs2 = finalrs2 + (rs2 << 8);
	finalrs2 = finalrs2 + rs2;
	//this computes rs2 to be the # of rs2 duplicated 4 times
	
	unsigned cond;
	cond = IR << 3;
	cond = cond >> 28;
	
	unsigned NZVC;
	NZVC = PSR << 8;
	NZVC = NZVC >> 28;
	
	unsigned N;
	N = NZVC & 8;
	N = N >> 3;
	
	unsigned Z;
	Z = NZVC & 4;
	Z = Z >> 2;
	
	unsigned V;
	V = NZVC & 2;
	V = V >> 1;
	
	unsigned C;
	C = NZVC & 1;
	
	unsigned simm13;
	simm13 = IR << 19;
	simm13 = simm13 >> 19;
	
	unsigned i;
	i = IR << 18;
	i = i >> 31;
	

	if(op == 1){
		/*call*/
		IR = IR << 2;
		IR = IR >> 2;
		IR = IR * 4;
		unsigned val = PC + IR;
		return val;
	}
	
	else if(op == 2 && op3 == 56){
		/*jmpl*/
		unsigned operand2;
		if(i == 1){
			operand2 = simm13;
		}
		else{
			operand2 = finalrs2;
		}
		unsigned val = finalrs1 + operand2;
		return val;
	}
	
	else if(op == 0 && a == 0 && op2 == 2){
		/*bicc*/
		unsigned val;
		
		if(cond == 0){
			//bn
			val = nPC + 4;
			return val;
		}
		else if(cond == 1){
			//be
			if(Z == 1){
				IR = IR & 0x003fffff;
				IR = IR * 4;
				val = PC + IR;
				return val;
			}
			else{
				val = nPC + 4;
				return val;
			}
		}
		else if(cond == 2){
			//ble
			unsigned check = N ^ V;
			check = Z | check;
			if(check == 1){
				IR = IR & 0x003fffff;
				IR = IR * 4;
				val = PC + IR;
				return val;
			}
			else{
				val = nPC + 4;
				return val;
			}
		}
		else if(cond == 3){
			//bl
			unsigned check = N ^ V;
			if(check == 1){
				IR = IR & 0x003fffff;
				IR = IR * 4;
				val = PC + IR;
				return val;
			}
			else{
				val = nPC + 4;
				return val;
			}
		}
		else if(cond == 4){
			//bleu
			unsigned check = C | Z;
			if(check == 1){
				IR = IR & 0x003fffff;
				IR = IR * 4;
				val = PC + IR;
				return val;
			}
			else{
				val = nPC + 4;
				return val;
			}
		}
		else if(cond == 5){
			//bcs
			if(C == 1){
				IR = IR & 0x003fffff;
				IR = IR * 4;
				val = PC + IR;
				return val;
			}
			else{
				val = nPC + 4;
				return val;
			}
		}
		else if(cond == 6){
			//bneg
			if(N == 1){
				IR = IR & 0x003fffff;
				IR = IR * 4;
				val = PC + IR;
				return val;
			}
			else{
				val = nPC + 4;
				return val;
			}
		}
		else if(cond == 7){
			//bvs
			if(V == 1){
				IR = IR & 0x003fffff;
				IR = IR * 4;
				val = PC + IR;
				return val;
			}
			else{
				val = nPC + 4;
				return val;
			}
		}
		else if(cond == 8){
			//ba
			IR = IR & 0x003fffff;
			IR = IR * 4;
			val = PC + IR;
			return val;
		}
		else if(cond == 9){
			//bne
			unsigned check = !Z;
			if(check == 1){
				IR = IR & 0x003fffff;
				IR = IR * 4;
				val = PC + IR;
				return val;
			}
			else{
				val = nPC + 4;
				return val;
			}
		}
		else if(cond == 10){
			//bg
			unsigned check = N ^ V;
			check = check | Z;
			check = !check;
			if(check == 1){
				IR = IR & 0x003fffff;
				IR = IR * 4;
				val = PC + IR;
				return val;
			}
			else{
				val = nPC + 4;
				return val;
			}
		}
		else if(cond == 11){
			//bge
			unsigned check = N ^ V;
			check = !check;
			if(check == 1){
				IR = IR & 0x003fffff;
				IR = IR * 4;
				val = PC + IR;
				return val;
			}
			else{
				val = nPC + 4;
				return val;
			}
		}
		else if(cond == 12){
			//bgu
			unsigned check = C | Z;
			check = !check;
			if(check == 1){
				IR = IR & 0x003fffff;
				IR = IR * 4;
				val = PC + IR;
				return val;
			}
			else{
				val = nPC + 4;
				return val;
			}
		}
		else if(cond == 13){
			//bcc
			if(C == 0){
				IR = IR & 0x003fffff;
				IR = IR * 4;
				val = PC + IR;
				return val;
			}
			else{
				val = nPC + 4;
				return val;
			}
		}
		else if(cond == 14){
			//bpos
			if(N == 0){
				IR = IR & 0x003fffff;
				IR = IR * 4;
				val = PC + IR;
				return val;
			}
			else{
				val = nPC + 4;
				return val;
			}
		}
		else if(cond == 15){
			//bvc
			if(V == 0){
				IR = IR & 0x003fffff;
				IR = IR * 4;
				val = PC + IR;
				return val;
			}
			else{
				val = nPC + 4;
				return val;
			}
		}
	}
	
	else{
	//everything else
		unsigned val = nPC + 4;
		return val;
	}
}
	
