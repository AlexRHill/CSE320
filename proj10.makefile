# Alex Hill
# CSE 320
# Makefile
# Proj10

# Note: my program might create a segmentation fault when it is done running
# I don't know why but it doesn't impact how my program runs (I think)

proj10: proj10.support.s
	gcc /user/cse320/Projects/project10.driver.o proj10.support.s -o proj10
