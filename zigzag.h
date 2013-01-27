/***********************************************************
*
* zigzag.h
* author: Weiwei Chen
* 01/18/13 initial version
*
*
***********************************************************/
#ifndef _ZIGZAG_H
#define _ZIGZAG_H

#include "systemc.h"
#include "jpeg.h"

class Zigzag : public sc_core::sc_module
{
private:
	int iter;
	static const int ZigzagIndex[64];
	static const int IZigzagIndex[64];
public:

  // Constructor
  	Zigzag( sc_core::sc_module_name _nm );
   	Zigzag(){};
  // Method/Thread declarations
  	void main(int in_block[64], int out_blocks[NUMBLOCKS*64]);
};

#endif
