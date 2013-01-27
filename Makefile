
SYSTEMC_HOME	= /home/weiweic/local/systemc-2.3.0
CMPOPTS		= -g
LNKOPTS		= -Wl,-rpath -Wl,$(SYSTEMC_HOME)/lib-linux
INC		= -I. -I$(SYSTEMC_HOME)/include
LIBS		= -L. -L$(SYSTEMC_HOME)/lib-linux
DESIGN		= jpeg


all: jpeg.o stimulus.o dct.o quantize.o zigzag.o huffman.o encoder.o dut.o monitor.o
	g++  jpeg.o monitor.o dut.o encoder.o  stimulus.o dct.o quantize.o zigzag.o huffman.o -lsystemc -o $(DESIGN) $(INC) $(LIBS) $(LNKOPTS)
	
jpeg.o: jpeg.cc jpeg.h
	g++ -c jpeg.cc $(INC) $(CMPOPTS)
	
stimulus.o: stimulus.cc stimulus.h jpeg.h
	g++ -c stimulus.cc $(INC) $(CMPOPTS)

dct.o: dct.cc dct.h jpeg.h
	g++ -c dct.cc $(INC) $(CMPOPTS)
	
quantize.o: quantize.cc quantize.h jpeg.h
	g++ -c quantize.cc $(INC) $(CMPOPTS)
	
zigzag.o: zigzag.cc zigzag.h jpeg.h
	g++ -c zigzag.cc $(INC) $(CMPOPTS)

huffman.o: huffman.cc huffman.h jpeg.h
	g++ -c huffman.cc $(INC) $(CMPOPTS)
	
encoder.o: encoder.cc encoder.h jpeg.h dct.h quantize.h zigzag.h
	g++ -c encoder.cc $(INC) $(CMPOPTS)
	
dut.o: dut.cc dut.h encoder.cc encoder.h huffman.cc huffman.h
	g++ -c dut.cc $(INC) $(CMPOPTS)
	
monitor.o: monitor.cc monitor.h 
	g++ -c monitor.cc $(INC) $(CMPOPTS)
	
systemc-clang:
	 systemc-clang jpeg.cc -- -D__STDC_CONSTANT_MACROS -D__STDC_LIMIT_MACROS \
	 -I/usr/include -I$(SYSTEMC_HOME)/include -x c++ -w -c
	
clean:
	rm *.o $(DESIGN) -rf
