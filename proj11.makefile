# Alex Hill
# CSE 320
# Makefile
# Proj11

# Note: I know only did the first 5 terms of the power series for sine

proj11: proj11.support.s proj11.driver.c
	gcc proj11.driver.c proj11.support.s -o proj11
