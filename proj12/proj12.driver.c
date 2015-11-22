#include <stdio.h>

int main(){
	unsigned test;

	test = update(0x00000000, 0x00000001, 0x40000001, 0x00e00000);
	//this test is call, returns PC + (disp30 * 4)
	printf("new nPC = %X\n", test);
	
	test = update(0x00000000, 0x00000001, 0x81c04001, 0x00e00000);
	//this test is jmpl with i = 0, returns rs1 + rs2, both rs1 and rs2 are 01 so 01010101
	printf("new nPC = %X\n", test);
	
	test = update(0x00000000, 0x00000001, 0x81c06001, 0x00e00000);
	//this test is jmpl with i = 1, returns rs1 + simm13, rs1 = 01 so 01010101 and simm13 = 1;
	printf("new nPC = %X\n", test);
	
	test = update(0x00000010, 0x00000001, 0x04800002, 0x00000000);
	//this test is bicc, ble but doesn't satisfy the condition so nPC + 4
	printf("new nPC = %X\n", test);
	
	test = update(0x00000010, 0x00000001, 0x04800002, 0x00f00000);
	//this test is bicc, ble and does satisfy the condition so imm22 * 4 + PC. imm22 = 2, PC = 1
	printf("new nPC = %X\n", test);
	
	test = update(0x00000011, 0x00000001, 0x0e800001, 0x00000000);
	//this test is bicc, bvs but doesn't satisfy the condition so nPC + 4
	printf("new nPC = %X\n", test);
	
	test = update(0x00000010, 0x0000000f, 0x0e800001, 0x00200000);
	//this test is bicc, bvs and does satisfy the condition so imm22 * 4 + PC. imm22 = 1, PC = f
	printf("new nPC = %X\n", test);
	
	test = update(0x00000007, 0x00000000, 0x1480000f, 0x00400000);
	//this test is bicc, bg but doesn't satisfy the condition so nPC + 4
	printf("new nPC = %X\n", test);
	
	test = update(0x00000010, 0x0000000f, 0x1480000f, 0x00000000);
	//this test is bicc, bg and does satisfy the condition so imm22 * 4 + PC. imm22 = f, PC = f
	printf("new nPC = %X\n", test);

	test = update(0x12341234, 0x00000001, 0x1e000000, 0x00e00000);
	//this test is one of the "other" cases and just returns the nPC + 4
	printf("new nPC = %X\n", test);

	return 0;
}
