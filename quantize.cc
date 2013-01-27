/***********************************************************
*
* quantize.cc
* author: Weiwei Chen
* 01/18/13 initial version
*
*
***********************************************************/

#include "quantize.h"

const int Quantize::LuminanceQuantization[64] = 
{ 16,11,10,16,24,40,51,61,
  12,12,14,19,26,58,60,55,
  14,13,16,24,40,57,69,56,
  14,17,22,29,51,87,80,62,
  18,22,37,56,68,109,103,77,
  24,35,55,64,81,104,113,92,
  49,64,78,87,103,121,120,101,
  72,92,95,98,112,100,103,99 };
  
Quantize::Quantize( sc_core::sc_module_name _nm )
: sc_core::sc_module( _nm )
{
	SC_HAS_PROCESS(Quantize);
	iter = 0;
}  
      
void Quantize::main(int in_block[64], int out_block[64])
{
	int i;
	int m;
	int o;
	int q;
	//int in_block[64];
	//int out_block[64];

	//while(1)
	{   
	//    Port1.receive( &in_block);
	 //   waitfor 7839030000ull/180;
	//	printf("this is quant \n");
	    q = LuminanceQuantization[0];
	    for(i = 0; i < 64; i++ )
	    {   
		m = in_block[i];
		if (m > 0)
		{   
		    o = (m + q / 2) / q;
		}
		else 
		{   
		    o = (m - q / 2) / q;
		}
		if (i < 63)
		{   
		    q = LuminanceQuantization[i + 1];
		}
		out_block[i] = o;
	    }
	    //Port2.send(&out_block, sizeof(out_block));	// new
	}
}

const int CHROM_Quantize::CHROM_Quantization[64] = 
{ 
	    17,  18,  24,  47,  99,  99,  99,  99,
            18,  21,  26,  66,  99,  99,  99,  99,
            24,  26,  56,  99,  99,  99,  99,  99,
            47,  66,  99,  99,  99,  99,  99,  99,
            99,  99,  99,  99,  99,  99,  99,  99,
            99,  99,  99,  99,  99,  99,  99,  99,
            99,  99,  99,  99,  99,  99,  99,  99,
            99,  99,  99,  99,  99,  99,  99,  99};
  
CHROM_Quantize::CHROM_Quantize( sc_core::sc_module_name _nm )
: sc_core::sc_module( _nm )
{
	SC_HAS_PROCESS(CHROM_Quantize);
	iter = 0;
}  
      
void CHROM_Quantize::main(int in_block[64], int out_block[64])
{
	int i;
	int m;
	int o;
	int q;
	//int in_block[64];
	//int out_block[64];

	//while(1)
	{   
	//    Port1.receive( &in_block);
	 //   waitfor 7839030000ull/180;
	//	printf("this is quant \n");
	    q = CHROM_Quantization[0];
	    for(i = 0; i < 64; i++ )
	    {   
		m = in_block[i];
		if (m > 0)
		{   
		    o = (m + q / 2) / q;
		}
		else 
		{   
		    o = (m - q / 2) / q;
		}
		if (i < 63)
		{   
		    q = CHROM_Quantization[i + 1];
		}
		out_block[i] = o;
	    }
	    
	    iter ++;
	    //Port2.send(&out_block, sizeof(out_block));	// new
	}
}

