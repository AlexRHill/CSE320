  #include <stdio.h>
  #include "/user/cse320/Projects/project05.support.h"

  int main(){
	int a;
	int b;
	char c[80];
	
	a = 100;
	b = 8;
	
	convert(a, b, c);
	
	printf("Array contains: %s", c); 
	printf("\n");
	
	a = 1000;
	b = 16;
	
	convert(a, b, c);
	
	printf("Array contains: %s", c); 
	printf("\n");
	
	a = -1001;
	b = 2;
	
	convert(a, b, c);
	
	printf("Array contains: %s", c); 
	printf("\n");

	a = 2345;
	b = 32;
	
	convert(a, b, c);
	
	printf("Array contains: %s", c); 
	printf("\n");
	
	a = -2344567;
	b = 16;
	
	convert(a, b, c);
	
	printf("Array contains: %s", c); 
	printf("\n");


  
  return 0;
  }
