/***********************************************************
*
* stimulus.h
* author: Weiwei Chen
* 01/18/13 initial version
*
*
***********************************************************/
#ifndef _STIMULUS_H
#define _STIMULUS_H

#include "systemc.h"
#include "jpeg.h"

class Stimulus : public sc_core::sc_module
{
private:
	unsigned char *ch;
	unsigned int  yInput[64];
	unsigned int  cbInput[64];
	unsigned int  crInput[64];
	unsigned int  rInput[64]; 
	unsigned int  gInput[64]; 
	unsigned int  bInput[64];
	//int output_blocks[NUMENCODERS][NUMBLOCKS*64];
	Blocks output_blocks[NUMENCODERS];
	
	int bmpoffset;
	int pixellen;
	
	void ReadRGB(int n);	// read the nth block, assume that the picture has complete blocks (8x8)
    	
    	void RGB2YCC();
    	
    	void RGBAVER();
	
	void ReadPPM();
	
	void YCC2RGB();

	void writeRGBtoFile(int n);


	void writeYCCtoFile(int n);

	void ReadBMP();


public:
	sc_fifo_out<Blocks> pout1;
    	sc_fifo_out<Blocks> pout2;
      	sc_fifo_out<Blocks> pout3;
      	
  // Constructor
  	Stimulus( sc_core::sc_module_name _nm );
   
  // Method/Thread declarations
  	void main(void);

   
};


#endif
