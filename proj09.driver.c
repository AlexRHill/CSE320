#include <stdio.h>
#include "/user/cse320/Projects/project09.support.h"

int main()
{
 int test;
 
 test = negate( 51);
 
 printf( "51 negated is: %08x\n", test );
 
  test = negate(-51);
 
 printf( "-51 negated is: %08x\n", test );

 test = absolute(51);
 
 printf( "51's absolute value is: %08x\n", test );

 test = absolute(-51);
 
 printf( "-51's absolute value is: %08x\n", test );

 test = add(51,51);
 
 printf( "51 + 51 is: %08x\n", test );
 
 test = add(51, -51);
 
 printf( "51 + -51 is: %08x\n", test );

 test = add(51, 1);
 
 printf( "51 + 1 is: %08x\n", test );
 
 test = add(0x7fffffff, 2); //overflow
 
 printf( "7fffffff + 2 is: %08x\n", test );

 test = sub(51, 1);
 
 printf( "51 - 1 is: %08x\n", test );
 
 test = sub(-20, 0x7fffffff); //overflow
 
 printf( "-20 - 7fffffff   is: %08x\n", test );

 test = mul(51, 3);
 
 printf( "51 * 3 is: %08x\n", test );
 
 test = mul(-51, 3); 
 
 printf( "-51 * 3 is: %08x\n", test );
 
 //disclaimer, I never did work on error conditions for multiply
 
 test = divide(51, 10);
 
 printf( "51 / 10 is: %08x\n", test );
 
 test = remain(51, 2);
 
 printf( "The remainder of 51 / 2 is: %08x\n", test );

 //other disclaimer, some of the remainder and divide numbers aren't right and I was unable to debug it correctly
 //when I tried to fix it, the divide numbers became problematic so I left it
 
 test = divide(54, -10);
 
 printf( "54 / -10 is: %08x\n", test );
 
 test = remain(54, -10);
 
 printf( "The remainder of 54 / -10 is: %08x\n", test );

 test = power(3, 3);
 
 printf( "3^3 is: %08x\n", test );
 
 test = power(2,8);
 
 printf( "2^8 is: %08x\n", test );

 test = power(2,-8);
 
 printf( "2^-8 is: %08x\n", test ); //error, negative power
 
 test = power(-3,5);
 
 printf( "-3^5 is: %08x\n", test );
 
 test = factorial(5);
 
 printf( "5! is: %08x\n", test );

 test = factorial(-5);
 
 printf( "-5! is: %08x\n", test ); //error, negative factorial

 test = factorial(0);
 
 printf( "0! is: %08x\n", test );


 return 0;
}
