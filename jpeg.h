/***********************************************************
*
* jpeg.h
* author: Weiwei Chen
* 01/18/13 initial version
*
*
***********************************************************/
#ifndef _JPEG_H
#define _JPEG_H

#include "systemc.h"

#define NUMENCODERS 3
#define BLOCKSIZE 64

#define WAITFORENC  172100167
#define WAITFORHUFF 49348944

#if 1
#define NUMBLOCKS (134*89)
//#define NUMPICS (134*89*9)
//#define NUMBLOCKS (2*89)
//#define NUMBLOCKS 1
#define NUMPICS (134*89*9)
#define HEIGHT 2136 
#define WIDTH 3216
//#define FILELENGTH 20608145
#define FILELENGTH 27477558
#endif

typedef int block[64];	/* define our communication data types */

typedef int blocks[NUMBLOCKS*64];

class Block {
  public:
    int data[BLOCKSIZE];
    
  public:

    // constructor
    
    Block () 
    {
	//memcpy(data, indata, sizeof(int) * BLOCKSIZE);
    }
    
    Block (int indata[BLOCKSIZE]) 
    {
	memcpy(data, indata, sizeof(int) * BLOCKSIZE);
    }

    inline bool operator == (const Block & rhs) const {
      return memcmp(data, rhs.data, sizeof(int) * BLOCKSIZE);
    }

    inline Block& operator = (const Block& rhs) {
    
      memcpy(data, rhs.data, sizeof(int) * BLOCKSIZE);
      return *this;
    }

    inline friend void sc_trace(sc_trace_file *tf, const Block & v,
    const std::string & NAME ) {
      //sc_trace(tf,v.info, NAME + ".info");
      //sc_trace(tf,v.flag, NAME + ".flag");
      
      assert(0);
    }

    inline friend ostream& operator << ( ostream& os,  Block const & v ) {
        int i;
        
    	for(i = 0; i < BLOCKSIZE; i++)
    	{
    		os << v.data[i] << " ";
    	}
    	os << endl;
      	return os;
    }

};

class Blocks {
  public:
    int data[NUMBLOCKS * BLOCKSIZE];
    
  public:

    // constructor
    
    Blocks () 
    {
	//memcpy(data, indata, sizeof(int) * BLOCKSIZE);
    }
    
    Blocks (int indata[NUMBLOCKS * BLOCKSIZE]) 
    {
	memcpy(data, indata, sizeof(int) * BLOCKSIZE * NUMBLOCKS);
    }

    inline bool operator == (const Blocks & rhs) const {
      return memcmp(data, rhs.data, sizeof(int) * BLOCKSIZE * NUMBLOCKS);
    }

    inline Blocks& operator = (const Blocks& rhs) {
    
      memcpy(data, rhs.data, sizeof(int) * BLOCKSIZE * NUMBLOCKS);
      return *this;
    }

    inline friend void sc_trace(sc_trace_file *tf, const Blocks & v,
    const std::string & NAME ) {
      //sc_trace(tf,v.info, NAME + ".info");
      //sc_trace(tf,v.flag, NAME + ".flag");
      
      assert(0);
    }

    inline friend ostream& operator << ( ostream& os,  Blocks const & v ) {
        int i;
        
    	for(i = 0; i < BLOCKSIZE * NUMBLOCKS; i++)
    	{
    		os << v.data[i] << " ";
    	}
    	os << endl;
      	return os;
    }

};

class Bytes {
  public:
    int n;
    unsigned char b[1024];
    
  public:

    // constructor
    
    Bytes () 
    {
	//memcpy(data, indata, sizeof(int) * BLOCKSIZE);
    }
    
    Bytes (int _n, unsigned char _b[1024]) 
    {
    	n = _n;
	memcpy(b, _b, sizeof(unsigned char) * 1024);
    }

    inline bool operator == (const Bytes& rhs) const {
      return (rhs.n == n && memcmp(b, rhs.b, sizeof(unsigned char) * 1024));
    }

    inline Bytes& operator = (const Bytes& rhs) {
      n = rhs.n;
      memcpy(b, rhs.b, sizeof(unsigned char) * 1024);
      return *this;
    }

    inline friend void sc_trace(sc_trace_file *tf, const Bytes & v,
    const std::string & NAME ) {
      //sc_trace(tf,v.info, NAME + ".info");
      //sc_trace(tf,v.flag, NAME + ".flag");
      
      assert(0);
    }

    inline friend ostream& operator << ( ostream& os,  Bytes const & v ) {
        int i;
        os << "n = " << v.n << endl;
        
    	for(i = 0; i < 1024; i++)
    	{
    		os << v.b[i] << " ";
    	}
    	os << endl;
      	return os;
    }

};





class dummy : public sc_core::sc_module
{
public:
  sc_fifo<Block> ch;
  // Constructor
  dummy( sc_core::sc_module_name _nm );
   
  // Method/Thread declarations
  void dummy_work();
   
};

#endif
