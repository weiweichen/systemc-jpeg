/***********************************************************
*
* dut.h
* author: Weiwei Chen
* 01/18/13 initial version
*
*
***********************************************************/
#ifndef _DUT_H
#define _DUT_H

#include "systemc.h"
#include "jpeg.h"
#include "encoder.h"
#include "huffman.h"

class DUT : public sc_core::sc_module
{
private:
	sc_fifo<Blocks> cout1;
	sc_fifo<Blocks> cout2;
	sc_fifo<Blocks> cout3;	
	
	Encoder enc1;
    	CHROM_Encoder enc2;
    	CHROM_Encoder enc3;
    	Huffman  huff;
    	
public:
	sc_fifo_in<Blocks> pin1;
	sc_fifo_in<Blocks> pin2;
	sc_fifo_in<Blocks> pin3;
	sc_fifo_out<Bytes> Portout;
	
	
	void main();
	
  // Constructor
  	DUT( sc_core::sc_module_name _nm );
   
};

#endif
