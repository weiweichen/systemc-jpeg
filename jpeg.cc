/***********************************************************
*
* jpeg.cc
* author: Weiwei Chen
* 01/18/13 initial version
*
*
***********************************************************/

#include "jpeg.h"
#include "systemc.h"
#include "encoder.h"
#include "dut.h"
#include "monitor.h"
#include "stimulus.h"

extern char *fname;

dummy::dummy( sc_core::sc_module_name _nm )
: sc_core::sc_module( _nm )
{
  SC_HAS_PROCESS( dummy);
  SC_THREAD( dummy_work );
}
 
void dummy::dummy_work()
{    
    int i;
    Block in, out;
    
    for(i = 0; i < BLOCKSIZE; i ++)
    {
    	in.data[i] = i;
    }
    
    memset(out.data, 0, sizeof(int) * BLOCKSIZE);
    
    ch.write(in);
    
    ch.read(out);
    
    cout << out;
    
    cout << endl; 
}


int sc_main(int argc, char *argv[])
{	
    sc_core::sc_set_time_resolution( 1.0, sc_core::SC_NS );
    // Elaboration -- Instantiate top level modules
    //dummy ins1("dummy1");
    //dummy ins2("dummy2");
    //dummy ins3("dummy3");
    
  // dummy ins1("dummy1");  
   if(argc != 2)
   {
   	cout << "Please provide the image filename" << endl;
   	exit(10);
   }
   
   fname = argv[1];
   
   sc_fifo<Blocks> chStimToDut1(1), chStimToDut2(1), chStimToDut3(1);
   sc_fifo<Bytes> chDutToMonitor(1);
   
   DUT dut("dut"); 
   Monitor monitor("monitor");
   Stimulus stimulus("stimulus");
   
   stimulus.pout1(chStimToDut1);
   stimulus.pout2(chStimToDut2);
   stimulus.pout3(chStimToDut3);   
   dut.pin1(chStimToDut1);
   dut.pin2(chStimToDut2);
   dut.pin3(chStimToDut3);
   dut.Portout(chDutToMonitor);
   monitor.Port(chDutToMonitor);
   
   sc_core::sc_start();
     
    return 0;
}
