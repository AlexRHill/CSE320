# Alex Hill
# CSE 320
# Makefile
# Proj05

proj05: proj05.driver.o proj05.support.o
	gcc proj05.driver.o proj05.support.o -o proj05

proj05.driver.o: proj05.driver.c
	gcc -c -Wall proj05.driver.c -o proj05.driver.o

proj05.support.o: proj05.support.c
	gcc -c -Wall proj05.support.c -o proj05.support.o
