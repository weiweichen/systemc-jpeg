/**********************************************************
*
* monitor.h
* author: Weiwei Chen
* 01/18/13 initial version
*
*
***********************************************************/
#ifndef _MONITOR_H
#define _MONITOR_H

#include "systemc.h"
#include "jpeg.h"

class Monitor : public sc_core::sc_module
{
private:
	
    	
public:
	sc_fifo_in<Bytes> Port;
	
	void main();
	
  // Constructor
  	Monitor( sc_core::sc_module_name _nm );
   
};


#endif
