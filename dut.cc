/***********************************************************
*
* dut.cc
* author: Weiwei Chen
* 01/18/13 initial version
*
*
***********************************************************/

#include "dut.h"

DUT::DUT( sc_core::sc_module_name _nm )
: sc_core::sc_module( _nm ), enc1("enc1"), enc2("enc2"), enc3("enc3"), huff("huff")
	, cout1(2), cout2(2), cout3(2)
{
	SC_HAS_PROCESS(DUT);
  	SC_THREAD(main);
  	
	//sc_fifo<Blocks> cout1(1);
	//sc_fifo<Blocks> cout2(1);
	//sc_fifo<Blocks> cout3(1);
	
	enc1.Port1(pin1);
	enc1.Port2(cout1);
	
	enc2.Port1(pin2);
	enc2.Port2(cout2);
	
	enc3.Port1(pin3);
	enc3.Port2(cout3);
	
	huff.Port1(cout1);
	huff.Port2(cout2);
	huff.Port3(cout3);
	huff.PortOut(Portout);	
}

void DUT::main()
{
	int i = 1;
}
