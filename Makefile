##
# Project Title
#
# @file
# @version 0.1

compile:
	$(CXX) -c *.cpp #-fno-stack-protector
	$(CXX) *\.o -o engine


# end
