/***********************************************************
*
* dct.h
* author: Weiwei Chen
* 01/18/13 initial version
*
*
***********************************************************/

#ifndef _IDCT_H
#define _IDCT_H

#include "systemc.h"
#include "jpeg.h"

class ChenDCT1 : public sc_core::sc_module
{
private:
	int iter;
	
public:
	//sc_fifo_out<Blocks> in_blocks;
	//sc_fifo_out<Block> output_block;
      	
  // Constructor
  	ChenDCT1( sc_core::sc_module_name _nm );
  	ChenDCT1(){};
   
  // Method/Thread declarations
  	void main(int in_blocks[NUMBLOCKS*64], int output_block[64]);
};

class ChenDCT2 : public sc_core::sc_module
{
private:
	int iter;
	
public:
	//sc_fifo_out<Blocks> in_blocks;
    	//sc_fifo_out<Block> output_block;
      	
  // Constructor
  	ChenDCT2( sc_core::sc_module_name _nm );
   	ChenDCT2(){};
  // Method/Thread declarations
  	void main(int input_block[64], int output_block[64]);

   
};

#endif
