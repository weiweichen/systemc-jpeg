/***********************************************************
*
* quantize.h
* author: Weiwei Chen
* 01/18/13 initial version
*
*
***********************************************************/
#ifndef _QUANTIZE_H
#define _QUANTIZE_H

#include "systemc.h"
#include "jpeg.h"

class Quantize : public sc_core::sc_module
{
private:
	int iter;
	static const int LuminanceQuantization[64];	
public:

  // Constructor
  	Quantize( sc_core::sc_module_name _nm );
   	Quantize(){};
  // Method/Thread declarations
  	void main(int in_block[64], int out_block[64]);
};

class CHROM_Quantize : public sc_core::sc_module
{
private:
	int iter;
	static const int CHROM_Quantization[64];	
public:

  // Constructor
  	CHROM_Quantize( sc_core::sc_module_name _nm );
   	CHROM_Quantize(){};
  // Method/Thread declarations
  	void main(int in_block[64], int out_block[64]);
};

#endif
