/***********************************************************
*
* huffman.h
* author: Weiwei Chen
* 01/18/13 initial version
*
*
***********************************************************/
#ifndef _HUFFMAN_H
#define _HUFFMAN_H

#include "systemc.h"
#include "jpeg.h"

class Huffman : public sc_core::sc_module
{
private:
    int ACXhuff_bits[36];
    int ACXhuff_huffval[257];
    int DCXhuff_bits[36];
    int DCXhuff_huffval[257];
    int ACEhuff_ehufco[257];
    int ACEhuff_ehufsi[257];
    int DCEhuff_ehufco[257];
    int DCEhuff_ehufsi[257];
    int huffsize[257];
    int huffcode[257];
    unsigned char ofp[2000*NUMPICS];
    int *input;
    int lastp;

    int CHROM_ACXhuff_bits[36];
    int CHROM_ACXhuff_huffval[257];
    int CHROM_DCXhuff_bits[36];
    int CHROM_DCXhuff_huffval[257];
    int CHROM_ACEhuff_ehufco[257];
    int CHROM_ACEhuff_ehufsi[257];
    int CHROM_DCEhuff_ehufco[257];
    int CHROM_DCEhuff_ehufsi[257];
    int CHROM_huffsize[257];
    int CHROM_huffcode[257];
    int CHROM_lastp;

    int LastDC;
    int LastDC_Cb;
    int LastDC_Cr;
    int ofp_ptr;
    int ofp_ptr_pre;
    int imageheight;
    int imagewidth;
    
    static const int csize[256];
    static const int LuminanceDCBits[16];
    static const int LuminanceDCValues[12];
    static const int LuminanceACBits[16];
    static const int LuminanceACValues[162];
    static const int CHROM_DCBits[16];
    static const int CHROM_DCValues[12];
    static const int CHROM_ACBits[16];
    static const int CHROM_ACValues[162];
    static const unsigned int lmask[17];
    static const int IZgzgIndex[64];
    static const int LumiQuant[64];
    static const int CHROM_Quant[64];
   
    Blocks in_blocks[NUMENCODERS];
    
    int f;
    int iter;
public:
    sc_fifo_in<Blocks> Port1;
    sc_fifo_in<Blocks> Port2;
    sc_fifo_in<Blocks> Port3;
    sc_fifo_out<Bytes> PortOut;

  // Constructor
  	Huffman( sc_core::sc_module_name _nm );
   
  // Method/Thread declarations
  	void main();
  	
  // Functions
    void SizeTable_DC();
    void SizeTable_AC();
    void CodeTable();
    void OrderCodes_DC();

    void SpecifiedHuffman_DC();

    void OrderCodes_AC();

    void SpecifiedHuffman_AC();

    void CHROM_SizeTable_DC();

    void CHROM_SizeTable_AC();

    void CHROM_CodeTable();

    void CHROM_OrderCodes_DC();

    void CHROM_SpecifiedHuffman_DC();

    void CHROM_OrderCodes_AC();
    void CHROM_SpecifiedHuffman_AC();

    void JpegDefaultHuffman();

    int WriteBits(int n, int code);

    void EncodeHuffman_DC(int value);

    void EncodeDC();
   
    void CHROM_EncodeHuffman_DC(int value);

    void EncodeDC_Cb();
   
    void EncodeDC_Cr();

    void EncodeHuffman_AC(int value);
   
    void CHROM_EncodeHuffman_AC(int value);

    void EncodeAC();

    void CHROM_EncodeAC();

    int WriteWord(int code);

    int WriteByte(int code);
    void WriteMarker(int m);

    void WriteAPP0();

    void WriteDQT();

    void WriteHuffman_AC();

    void WriteHuffman_DC();
    void CHROM_WriteHuffman_AC();
    void CHROM_WriteHuffman_DC();

    void WriteDHT();

    void WriteSOF();

    void WriteSOS();
  	
};

#endif
