/***********************************************************
*
* encoder.h
* author: Weiwei Chen
* 01/18/13 initial version
*
*
***********************************************************/
#ifndef _ENCODER_H
#define _ENCODER_H

#include "systemc.h"
#include "jpeg.h"
#include "dct.h"
#include "zigzag.h"
#include "quantize.h"

class Encoder : public sc_core::sc_module
{
private:
	int block0[64];
	int block1[64];
	int block2[64];
	Blocks in_blocks;
	Blocks out_blocks;
	int i;
	
	ChenDCT1 dct1;
    	ChenDCT2 dct2;
    	Quantize quan;
    	Zigzag   zigz;
public:
	sc_fifo_in<Blocks> Port1;
	sc_fifo_out<Blocks> Port2;
	
	
  // Constructor
  	Encoder( sc_core::sc_module_name _nm );
   
  // Method/Thread declarations
  	void main();
};

class CHROM_Encoder : public sc_core::sc_module
{
private:
	int block0[64];
	int block1[64];
	int block2[64];
	Blocks in_blocks;
	Blocks out_blocks;
	int i;
	
	ChenDCT1 dct1;
    	ChenDCT2 dct2;
    	CHROM_Quantize quan;
    	Zigzag   zigz;
public:
	sc_fifo_in<Blocks> Port1;
	sc_fifo_out<Blocks> Port2;
	
	
  // Constructor
  	CHROM_Encoder( sc_core::sc_module_name _nm );
   
  // Method/Thread declarations
  	void main();
};

#endif
