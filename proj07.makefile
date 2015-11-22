# Alex Hill
# CSE 320
# Makefile
# Proj09

proj09: proj09.support.s
	gcc proj09.driver.c proj09.support.s -o proj09
