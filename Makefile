##
# Project Title
#
# @file
# @version 0.1

compile:
	$(CXX) -c *.cpp genmove/*.cpp -O3 -funroll-loops
	$(CXX) *\.o -o engine -O3
	rm *\.o


# end
