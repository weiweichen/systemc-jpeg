/**********************************************************
*
* monitor.cc
* author: Weiwei Chen
* 01/18/13 initial version
*
*
***********************************************************/

#include "monitor.h"

Monitor::Monitor( sc_core::sc_module_name _nm )
: sc_core::sc_module( _nm )
{
	SC_HAS_PROCESS(Monitor);
  	SC_THREAD(main);
 }

void Monitor::main(void)
{   
	FILE *f, *f2;
	//unsigned char gold;
	//int i, pics, j, numconflicts = 0;
	Bytes bb;
	int wlen, iter = 0;
	//int iter;
	//sim_time t;
	//sim_time t2;
	//sim_time_string buf;	// bug fix 11/11/08, RD
	//sim_time_string buf2;

	if (!(f = fopen("golden.jpg", "rb")))
	{   
	    printf("Cannot open file \"golden.jpg\" for reading.\n");
	    exit(10);
	}
	if (!(f2 = fopen("test.jpg", "wb")))
	{   
	    printf("Cannot open file \"test.jpg\" for writing.\n");
	    fclose(f);
	    exit(10);
	}

	while(1)
	{
	    Port.read(bb);
	    if(bb.n & 0x400)
	    {
	    	wlen = fwrite(bb.b, sizeof(unsigned char), (bb.n & 0x3ff), f2);
		fputc(0xff, f2);
		fputc(0xd9, f2);
		//cout << iter++ << ": wlen = " << wlen << " bb.n = " << bb.n << endl;
		break;
	    }
	    else{
		wlen = fwrite(bb.b, sizeof(unsigned char), bb.n, f2);
		//cout << iter++ << ": wlen = " << wlen << " bb.n = " << bb.n << endl;
	    }
	   
	}

	fclose(f);
	fclose(f2);
	//t = now() / TIME_BASE;
	
	cout << sc_time_stamp() << " Monitor exits simulation. \n" << endl;
	
	//printf("%8s: Monitor exits simulation.\n", time2str(buf,t));
	//printf("numconflicts in cTable = %d \n", numconflicts);

	exit(0);
}
