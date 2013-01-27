/***********************************************************
*
* dct.cc
* author: Weiwei Chen
* 01/18/13 initial version
*
*
***********************************************************/

#include "dct.h"

ChenDCT1::ChenDCT1( sc_core::sc_module_name _nm )
: sc_core::sc_module( _nm )
{
	SC_HAS_PROCESS(ChenDCT1);
	iter = 0;
}

void ChenDCT1::main(
	int in_blocks[NUMBLOCKS*64], 
	int output_block[64])
{   
	//static int iter = 0;
	int aptr;
	int i;
	int tval;
	int a0;
	int a1;
	int a2;
	int a3;
	int b0;
	int b1;
	int b2;
	int b3;
	int c0;
	int c1;
	int c2;
	int c3;
	int v0;
	int v1;
	int v2;
	int v3;
	int v4;
	int v5;
	int v6;
	int v7;
	//int in_blocks[NUMBLOCKS*64];
	int *in_block;
	int out_block[64];
	//int f = 1.2;
	//while(1)
	{   

	  // if(iter % NUMBLOCKS == 0){
	  //  Port1.receive( &in_blocks);
	  //  waitfor WAITFORENC;
	  // }
	   in_block = &in_blocks[(iter%NUMBLOCKS)*64];
	  // waitfor WAITFORENC;
	  // printf("this is dct1 %d\n", iter);
          

	    if (iter % 2 == 1)
	    {   
		//Port2.send(in_block);
		for(i = 0; i < 64; i ++)
		{
			output_block[i] = in_block[i];
		}
		iter++ ; 
	    }
	    else 
	    {   
	     
		for(i = 0; i < 64; i++ )
		{   
		    tval = in_block[i];
		    in_block[i] = tval - 128;
		}
	      
		for(i = 0; i < 8; i++ )
		{   
		    aptr = i;
		    v0 = in_block[aptr];
		    aptr += 8;
		    v1 = in_block[aptr];
		    aptr += 8;
		    v2 = in_block[aptr];
		    aptr += 8;
		    v3 = in_block[aptr];
		    aptr += 8;
		    v4 = in_block[aptr];
		    aptr += 8;
		    v5 = in_block[aptr];
		    aptr += 8;
		    v6 = in_block[aptr];
		    aptr += 8;
		    v7 = in_block[aptr];
		    a0 = (((v0 + v7)) << (2));
		    c3 = (((v0 - v7)) << (2));
		    a1 = (((v1 + v6)) << (2));
		    c2 = (((v1 - v6)) << (2));
		    a2 = (((v2 + v5)) << (2));
		    c1 = (((v2 - v5)) << (2));
		    a3 = (((v3 + v4)) << (2));
		    c0 = (((v3 - v4)) << (2));
		    b0 = a0 + a3;
		    b1 = a1 + a2;
		    b2 = a1 - a2;
		    b3 = a0 - a3;
		    out_block[i] = (((362l * (b0 + b1))) >> (9));
		    out_block[i + 32] = (((362l * (b0 - b1))) >> (9));
		    out_block[i + 16] = ((((196l * b2) + (473l * b3))) >> 
			(9));
		    out_block[i + 48] = ((((196l * b3) - (473l * b2))) >> 
			(9));
		    b0 = (((362l * (c2 - c1))) >> (9));
		    b1 = (((362l * (c2 + c1))) >> (9));
		    a0 = c0 + b0;
		    a1 = c0 - b0;
		    a2 = c3 - b1;
		    a3 = c3 + b1;
		    out_block[i + 8] = ((((100l * a0) + (502l * a3))) >> 
			(9));
		    out_block[i + 24] = ((((426l * a2) - (284l * a1))) >> 
			(9));
		    out_block[i + 40] = ((((426l * a1) + (284l * a2))) >> 
			(9));
		    out_block[i + 56] = ((((100l * a3) - (502l * a0))) >> 
			(9));
		}
		for(i = 0; i < 8; i++ )
		{   
		    aptr = ((i) << (3));
		    v0 = out_block[aptr];
		    aptr++ ;
		    v1 = out_block[aptr];
		    aptr++ ;
		    v2 = out_block[aptr];
		    aptr++ ;
		    v3 = out_block[aptr];
		    aptr++ ;
		    v4 = out_block[aptr];
		    aptr++ ;
		    v5 = out_block[aptr];
		    aptr++ ;
		    v6 = out_block[aptr];
		    aptr++ ;
		    v7 = out_block[aptr];
		    c3 = (((v0 - v7)) >> (1));
		    a0 = (((v0 + v7)) >> (1));
		    c2 = (((v1 - v6)) >> (1));
		    a1 = (((v1 + v6)) >> (1));
		    c1 = (((v2 - v5)) >> (1));
		    a2 = (((v2 + v5)) >> (1));
		    c0 = (((v3 - v4)) >> (1));
		    a3 = (((v3 + v4)) >> (1));
		    b0 = a0 + a3;
		    b1 = a1 + a2;
		    b2 = a1 - a2;
		    b3 = a0 - a3;
		    aptr = ((i) << (3));
		    out_block[aptr] = (((362l * (b0 + b1))) >> (9));
		    out_block[aptr + 4] = (((362l * (b0 - b1))) >> (9));
		    out_block[aptr + 2] = ((((196l * b2) + (473l * b3))) >> 
			(9));
		    out_block[aptr + 6] = ((((196l * b3) - (473l * b2))) >> 
			(9));
		    b0 = (((362l * (c2 - c1))) >> (9));
		    b1 = (((362l * (c2 + c1))) >> (9));
		    a0 = c0 + b0;
		    a1 = c0 - b0;
		    a2 = c3 - b1;
		    a3 = c3 + b1;
		    out_block[aptr + 1] = ((((100l * a0) + (502l * a3))) >> 
			(9));
		    out_block[aptr + 3] = ((((426l * a2) - (284l * a1))) >> 
			(9));
		    out_block[aptr + 5] = ((((426l * a1) + (284l * a2))) >> 
			(9));
		    out_block[aptr + 7] = ((((100l * a3) - (502l * a0))) >> 
			(9));
		}
		for(i = 0; i < 64; i++ )
		{   
		    tval = out_block[i];
		    tval = (((tval < 0) ? (tval - 4) : (tval + 4)) / 8);
		    if (tval <  -1023)
		    {   
			tval =  -1023;
		    }
		    else 
			if (tval > 1023)
			{   
			    tval = 1023;
			}
		    out_block[i] = tval;
		}
		iter++ ;
		for(i = 0; i < 64; i ++)
		{
			output_block[i] = out_block[i];
		}
	    }
	    
	}
}

ChenDCT2::ChenDCT2( sc_core::sc_module_name _nm )
: sc_core::sc_module( _nm )
{
	SC_HAS_PROCESS(ChenDCT2);
	iter = 0;
}

void ChenDCT2::main(
	int input_block[64], 
	int output_block[64]
	)
{
	//static int iter = 0;
	int aptr;
	int i;
	int tval;
	int a0;
	int a1;
	int a2;
	int a3;
	int b0;
	int b1;
	int b2;
	int b3;
	int c0;
	int c1;
	int c2;
	int c3;
	int v0;
	int v1;
	int v2;
	int v3;
	int v4;
	int v5;
	int v6;
	int v7;
	int in_block[64];
	int out_block[64];

	//while(1)
	{   
	//    Port1.receive( &in_block);
	 //   waitfor 10411200000ull/180;
	//printf("this is dct2 iter= %d\n", iter);
	    for(i = 0; i < 64; i ++)
		{
			in_block[i] = input_block[i];
		}
	
	    if (iter % 2 == 0)
	    {   
		//Port2.send(in_block);
		for(i = 0; i < 64; i ++)
		{
			output_block[i] = in_block[i];
		}
		iter++ ;
	    }
	    else 
	    {   
		for(i = 0; i < 64; i++ )
		{   
		    tval = in_block[i];
		    in_block[i] = tval - 128;
		}
		for(i = 0; i < 8; i++ )
		{   
		    aptr = i;
		    v0 = in_block[aptr];
		    aptr += 8;
		    v1 = in_block[aptr];
		    aptr += 8;
		    v2 = in_block[aptr];
		    aptr += 8;
		    v3 = in_block[aptr];
		    aptr += 8;
		    v4 = in_block[aptr];
		    aptr += 8;
		    v5 = in_block[aptr];
		    aptr += 8;
		    v6 = in_block[aptr];
		    aptr += 8;
		    v7 = in_block[aptr];
		    a0 = (((v0 + v7)) << (2));
		    c3 = (((v0 - v7)) << (2));
		    a1 = (((v1 + v6)) << (2));
		    c2 = (((v1 - v6)) << (2));
		    a2 = (((v2 + v5)) << (2));
		    c1 = (((v2 - v5)) << (2));
		    a3 = (((v3 + v4)) << (2));
		    c0 = (((v3 - v4)) << (2));
		    b0 = a0 + a3;
		    b1 = a1 + a2;
		    b2 = a1 - a2;
		    b3 = a0 - a3;
		    out_block[i] = (((362l * (b0 + b1))) >> (9));
		    out_block[i + 32] = (((362l * (b0 - b1))) >> (9));
		    out_block[i + 16] = ((((196l * b2) + (473l * b3))) >> 
			(9));
		    out_block[i + 48] = ((((196l * b3) - (473l * b2))) >> 
			(9));
		    b0 = (((362l * (c2 - c1))) >> (9));
		    b1 = (((362l * (c2 + c1))) >> (9));
		    a0 = c0 + b0;
		    a1 = c0 - b0;
		    a2 = c3 - b1;
		    a3 = c3 + b1;
		    out_block[i + 8] = ((((100l * a0) + (502l * a3))) >> 
			(9));
		    out_block[i + 24] = ((((426l * a2) - (284l * a1))) >> 
			(9));
		    out_block[i + 40] = ((((426l * a1) + (284l * a2))) >> 
			(9));
		    out_block[i + 56] = ((((100l * a3) - (502l * a0))) >> 
			(9));
		}
		for(i = 0; i < 8; i++ )
		{   
		    aptr = ((i) << (3));
		    v0 = out_block[aptr];
		    aptr++ ;
		    v1 = out_block[aptr];
		    aptr++ ;
		    v2 = out_block[aptr];
		    aptr++ ;
		    v3 = out_block[aptr];
		    aptr++ ;
		    v4 = out_block[aptr];
		    aptr++ ;
		    v5 = out_block[aptr];
		    aptr++ ;
		    v6 = out_block[aptr];
		    aptr++ ;
		    v7 = out_block[aptr];
		    c3 = (((v0 - v7)) >> (1));
		    a0 = (((v0 + v7)) >> (1));
		    c2 = (((v1 - v6)) >> (1));
		    a1 = (((v1 + v6)) >> (1));
		    c1 = (((v2 - v5)) >> (1));
		    a2 = (((v2 + v5)) >> (1));
		    c0 = (((v3 - v4)) >> (1));
		    a3 = (((v3 + v4)) >> (1));
		    b0 = a0 + a3;
		    b1 = a1 + a2;
		    b2 = a1 - a2;
		    b3 = a0 - a3;
		    aptr = ((i) << (3));
		    out_block[aptr] = (((362l * (b0 + b1))) >> (9));
		    out_block[aptr + 4] = (((362l * (b0 - b1))) >> (9));
		    out_block[aptr + 2] = ((((196l * b2) + (473l * b3))) >> 
			(9));
		    out_block[aptr + 6] = ((((196l * b3) - (473l * b2))) >> 
			(9));
		    b0 = (((362l * (c2 - c1))) >> (9));
		    b1 = (((362l * (c2 + c1))) >> (9));
		    a0 = c0 + b0;
		    a1 = c0 - b0;
		    a2 = c3 - b1;
		    a3 = c3 + b1;
		    out_block[aptr + 1] = ((((100l * a0) + (502l * a3))) >> 
			(9));
		    out_block[aptr + 3] = ((((426l * a2) - (284l * a1))) >> 
			(9));
		    out_block[aptr + 5] = ((((426l * a1) + (284l * a2))) >> 
			(9));
		    out_block[aptr + 7] = ((((100l * a3) - (502l * a0))) >> 
			(9));
		}
		for(i = 0; i < 64; i++ )
		{   
		    tval = out_block[i];
		    tval = (((tval < 0) ? (tval - 4) : (tval + 4)) / 8);
		    if (tval <  -1023)
		    {   
			tval =  -1023;
		    }
		    else 
			if (tval > 1023)
			{   
			    tval = 1023;
			}
		    out_block[i] = tval;
		}
		//Port2.send(out_block);
		for(i = 0; i < 64; i ++)
		{
			output_block[i] = out_block[i];
		}
		iter++ ;
	    
	    }
	  
	}
}

