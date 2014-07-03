
#
#   make - all
#

    all:directories gnomonic-demo

#
#   make - gnomonic-demo
#

    gnomonic-demo:directories
	g++ gnomonic-demo.cpp -o gnomonic-demo -O3 -Wall `pkg-config --cflags --libs opencv` -lgnomonic

#
#   make - Directories
#

    directories:
	mkdir -p ../bin
