##
# Project Title
#
# @file
# @version 0.1

compile:
	rm *\.o
	$(CXX) -c *.cpp #-fno-stack-protector
	$(CXX) *\.o -o engine


# end
