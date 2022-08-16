##
# Project Title
#
# @file
# @version 0.1

compile:
	$(CC) -O3 -funroll-loops -march=native -c *\.c
	$(CC) *\.o -o engine -O3 -march=native
	# $(CC) -c *\.c
	# $(CC) *\.o -o engine
	rm *\.o


# end
