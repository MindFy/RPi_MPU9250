# 
# Makefile for RPi_MPU9250 library
#
#
# Copyright (c) 2016 Simon D. Levy
#
# Permission is hereby granted, free of charge, to any person obtaining a copy of this software 
# and associated documentation files (the "Software"), to deal in the Software without restriction, 
# including without limitation the rights to use, copy, modify, merge, publish, distribute, 
# sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is 
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all copies or 
# substantial portions of the Software.
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING 
# BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
# DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

EXAMPLES = examples/Basic_I2C/Basic_I2C examples/Basic_SPI/Basic_SPI

all: libmpu9250.so $(EXAMPLES)

libmpu9250.so: MPU9250.o
	g++ -O3 -shared -o libmpu9250.so MPU9250.o

MPU9250.o: MPU9250.cpp MPU9250.h
	g++ -Wall -std=c++11 -c MPU9250.cpp

install: libmpu9250.so
	cp libmpu9250.so /usr/local/lib
	cp MPU9250.h /usr/local/include

examples/Basic_I2C/Basic_I2C: examples/Basic_I2C/Basic_I2C.cpp 
	g++ -Wall -I ../.. -o examples/Basic_I2C/Basic_I2C examples/Basic_I2C/Basic_I2C.cpp -lmpu9250 -lwiringPi

examples/Basic_SPI/Basic_SPI: examples/Basic_SPI/Basic_SPI.cpp 
	g++ -Wall -I ../.. -o examples/Basic_SPI/Basic_SPI examples/Basic_SPI/Basic_SPI.cpp -lmpu9250 -lwiringPi

clean:
	rm -f *.o *.so *~ $(EXAMPLES)
