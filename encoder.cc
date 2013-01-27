/***********************************************************
*
* encoder.cc
* author: Weiwei Chen
* 01/18/13 initial version
*
*
***********************************************************/

#include "encoder.h"  


Encoder::Encoder( sc_core::sc_module_name _nm )
: sc_core::sc_module( _nm ), dct1("dct1"), dct2("dct2"), quan("quan"), zigz("zigz")
{
	SC_HAS_PROCESS(Encoder);
	SC_THREAD(main);
}  
      
void Encoder::main()
{
	while(1)
	{
		Port1.read(in_blocks);
		for(i = 0; i < NUMBLOCKS; i ++)
		{
			dct1.main(in_blocks.data, block0);
			dct2.main(block0, block1);
			quan.main(block1, block2);
			zigz.main(block2, out_blocks.data);
			//printf("%d th frame \n", i);
		}
		wait(WAITFORENC, SC_NS);
		printf("Encoder frame %d sending\n", i);
		Port2.write( out_blocks);
		printf("Encoder frame %d ending\n", i);
	}
}

CHROM_Encoder::CHROM_Encoder( sc_core::sc_module_name _nm )
: sc_core::sc_module( _nm ), dct1("dct1"), dct2("dct2"), quan("quan"), zigz("zigz")
{
	SC_HAS_PROCESS(CHROM_Encoder);
	SC_THREAD(main);
}  
      
void CHROM_Encoder::main()
{
	while(1)
	{
		Port1.read(in_blocks);
		for(i = 0; i < NUMBLOCKS; i ++)
		{
			dct1.main(in_blocks.data, block0);
			dct2.main(block0, block1);
			quan.main(block1, block2);
			zigz.main(block2, out_blocks.data);
			//printf("%d th frame \n", i);
		}
		wait(WAITFORENC, SC_NS);
		printf("CHROM_Encoder frame %d sending\n", i);
		Port2.write( out_blocks);
		printf("CHROM_Encoder frame %d ending\n", i);
	}
}
