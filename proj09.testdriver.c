#include <stdio.h>
#include "/user/cse320/Projects/project09.support.h"

int main()
{
 int test;
 
 test = divide( 51, 10);
 
 printf( "Results: %08x\n", test );

 test = remain( 51, 10);
 
 printf( "Results: %08x\n", test );

 test = divide( -52, 10);
 
 printf( "Results: %08x\n", test );

 test = remain( -52, 10);
 
 printf( "Results: %08x\n", test );

 test = divide( 53, -10);
 
 printf( "Results: %08x\n", test );

 test = remain( 53, -10);
 
 printf( "Results: %08x\n", test );

 test = divide( -54, -10);
 
 printf( "Results: %08x\n", test );

 test = remain( -54, -10);
 
 printf( "Results: %08x\n", test );
}
