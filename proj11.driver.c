#include <stdio.h>
#include "/user/cse320/Projects/project11.support.h"

int main()
{
 double test;
 
 test = absolute(51);
 
 printf( "51's absolute value is: %f\n", test );

 test = absolute(-51);
 
 printf( "-51's absolute value is: %f\n", test );
 
 test = modulo(10,2);
 
 printf( "10 modulo 2 is: %f\n", test );

 test = modulo(10,3);
 
 printf( "10 modulo 3 is: %f\n", test );

 test = modulo(10,4);
 
 printf( "10 modulo 4 is: %f\n", test );
 
 test = modulo(10,0);
 
 printf( "10 modulo 0 is: %f\n", test );
 
 test = modulo(13,5);
 
 printf( "13 modulo 5 is: %f\n", test );
 
 test = modulo(13,-5);
 
 printf( "13 modulo -5 is: %f\n", test );
 
 test = modulo(-13,-5);
 
 printf( "-13 modulo -5 is: %f\n", test );

 test = modulo(-13,5);
 
 printf( "-13 modulo 5 is: %f\n", test );

 test = factorial(12);
 
 printf( "12! is: %f\n", test );
 
 test = factorial(0);
 
 printf( "0! is: %f\n", test );
 
 test = power(6,7);

 printf( "6^7 is: %f\n", test );
 
 test = power(10,3);

 printf( "10^3 is: %f\n", test );
 
 test = power(4,0);

 printf( "4^0 is: %f\n", test );

 test = sine(3.14);

 printf( "sin(pi) is: %f\n", test );
 
 test = sine((3.14/2));

 printf( "sin(pi/2) is: %f\n", test );


 
 return 0;
}
