/***********************************************************
*
* huffman.cc
* author: Weiwei Chen
* 01/18/13 initial version
*
*
***********************************************************/

#include "huffman.h"

extern unsigned int imageHeight;
extern unsigned int imageWidth;

const int Huffman::csize[256] = 
    { 0,1,2,2,3,3,3,3,4,4,4,4,4,4,4,4,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
      6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
      7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
      7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
      8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
      8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
      8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
      8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8 };
      
const int Huffman::LuminanceDCBits[16] = 
    { 0,1,5,1,1,1,1,1,1,0,0,0,0,0,0,0 };
    
const int Huffman::LuminanceDCValues[12] = 
    { 0,1,2,3,4,5,6,7,8,9,10,11 };
    
const int Huffman::LuminanceACBits[16] = 
    { 0,2,1,3,3,2,4,3,5,5,4,4,0,0,1,125 };
    
const int Huffman::LuminanceACValues[162] = 
    { 1,2,3,0,4,17,5,18,33,49,65,6,19,81,97,7,34,113,20,50,129,145,161,
      8,35,66,177,193,21,82,209,240,36,51,98,114,130,9,10,22,23,24,25,
      26,37,38,39,40,41,42,52,53,54,55,56,57,58,67,68,69,70,71,72,73,74,
      83,84,85,86,87,88,89,90,99,100,101,102,103,104,105,106,115,116,117,
      118,119,120,121,122,131,132,133,134,135,136,137,138,146,147,148,
      149,150,151,152,153,154,162,163,164,165,166,167,168,169,170,178,
      179,180,181,182,183,184,185,186,194,195,196,197,198,199,200,201,
      202,210,211,212,213,214,215,216,217,218,225,226,227,228,229,230,
      231,232,233,234,241,242,243,244,245,246,247,248,249,250 };

const int Huffman::CHROM_DCBits[16] = 
    { 0, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0 };
    
const int Huffman::CHROM_DCValues[12] = 
    { 0,1,2,3,4,5,6,7,8,9,10,11 };
    
const int Huffman::CHROM_ACBits[16] = 
    { 0, 2, 1, 3, 3, 2, 4, 3, 5, 5, 4, 4, 0, 0, 1, 0x7d };
    
const int Huffman::CHROM_ACValues[162] = 
    {
            0x01, 0x02, 0x03, 0x00, 0x04, 0x11, 0x05, 0x12,
            0x21, 0x31, 0x41, 0x06, 0x13, 0x51, 0x61, 0x07,
            0x22, 0x71, 0x14, 0x32, 0x81, 0x91, 0xa1, 0x08,
            0x23, 0x42, 0xb1, 0xc1, 0x15, 0x52, 0xd1, 0xf0,
            0x24, 0x33, 0x62, 0x72, 0x82, 0x09, 0x0a, 0x16,
            0x17, 0x18, 0x19, 0x1a, 0x25, 0x26, 0x27, 0x28,
            0x29, 0x2a, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39,
            0x3a, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49,
            0x4a, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59,
            0x5a, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69,
            0x6a, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79,
            0x7a, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89,
            0x8a, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98,
            0x99, 0x9a, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7,
            0xa8, 0xa9, 0xaa, 0xb2, 0xb3, 0xb4, 0xb5, 0xb6,
            0xb7, 0xb8, 0xb9, 0xba, 0xc2, 0xc3, 0xc4, 0xc5,
            0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xd2, 0xd3, 0xd4,
            0xd5, 0xd6, 0xd7, 0xd8, 0xd9, 0xda, 0xe1, 0xe2,
            0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xea,
            0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8,
            0xf9, 0xfa
        };


const unsigned int Huffman::lmask[17] = 
    { 0u,1u,3u,7u,15u,31u,63u,127u,255u,511u,1023u,2047u,4095u,8191u,16383u,
      32767u,65535u };
      
const int Huffman::IZgzgIndex[64] = 
    { 0,1,8,16,9,2,3,10,17,24,32,25,18,11,4,5,12,19,26,33,40,48,41,34,
      27,20,13,6,7,14,21,28,35,42,49,56,57,50,43,36,29,22,15,23,30,37,
      44,51,58,59,52,45,38,31,39,46,53,60,61,54,47,55,62,63 };
      
const int Huffman::LumiQuant[64] = 
    { 16,11,10,16,24,40,51,61,12,12,14,19,26,58,60,55,14,13,16,24,40,57,
      69,56,14,17,22,29,51,87,80,62,18,22,37,56,68,109,103,77,24,35,55,
      64,81,104,113,92,49,64,78,87,103,121,120,101,72,92,95,98,112,100,
      103,99 };
      
const int Huffman::CHROM_Quant[64] =  {
            17,  18,  24,  47,  99,  99,  99,  99,
            18,  21,  26,  66,  99,  99,  99,  99,
            24,  26,  56,  99,  99,  99,  99,  99,
            47,  66,  99,  99,  99,  99,  99,  99,
            99,  99,  99,  99,  99,  99,  99,  99,
            99,  99,  99,  99,  99,  99,  99,  99,
            99,  99,  99,  99,  99,  99,  99,  99,
            99,  99,  99,  99,  99,  99,  99,  99
        };


Huffman::Huffman( sc_core::sc_module_name _nm )
: sc_core::sc_module( _nm )
{
	iter = 0;
	f = 1.2;
	LastDC = 0;
	LastDC_Cb = 0;
	LastDC_Cr = 0;
	ofp_ptr = 0;
	ofp_ptr_pre = 0;
	imageheight;
	imagewidth;	
	SC_HAS_PROCESS(Huffman);
	SC_THREAD(main);
}  
      
void Huffman::SizeTable_DC()
{   
	int i;
	int j;
	int p;

	p = 0;
	for(i = 1; i < 17; i++ )
	{   
	    for(j = 1; j <= DCXhuff_bits[i]; j++ )
	    {   
		huffsize[p++ ] = i;
	    }
	}
	huffsize[p] = 0;
	lastp = p;
}

void Huffman::SizeTable_AC()
{   
	int i;
	int j;
	int p;

	p = 0;
	for(i = 1; i < 17; i++ )
	{   
	    for(j = 1; j <= ACXhuff_bits[i]; j++ )
	    {   
		huffsize[p++ ] = i;
	    }
	}
	huffsize[p] = 0;
	lastp = p;
}

void Huffman::CodeTable()
{   
	int code;
	int p;
	int size;
	int skip = 0;

	p = 0;
	code = 0;
	size = huffsize[0];
	while(0 == skip)
	{   
	    do 
	    {   
		huffcode[p++ ] = code++ ;
	    }
	    while((huffsize[p] == size) && (p < 257));
	    if (0 == huffsize[p])
	    {   
		skip = 1;
	    }
	    if ( !skip)
	    {   
		do 
		{   
		    code <<= 1;
		    size++ ;
		}
		while(huffsize[p] != size);
	    }
	}
}

void Huffman::OrderCodes_DC()
{   
	int Index;
	int p;

	for(p = 0; p < lastp; p++ )
	{   
	    Index = DCXhuff_huffval[p];
	    DCEhuff_ehufco[Index] = huffcode[p];
	    DCEhuff_ehufsi[Index] = huffsize[p];
	}
}

void Huffman::SpecifiedHuffman_DC()
{   
	int i;
	int accum = 0;
	int tmp;

	for(i = 0; i < 16; i++ )
	{   
	    tmp = LuminanceDCBits[i];
	    accum += tmp;
	    DCXhuff_bits[i + 1] = tmp;
	}
	for(i = 0; i < accum; i++ )
	{   
	    DCXhuff_huffval[i] = LuminanceDCValues[i];
	}
	SizeTable_DC();
	CodeTable();
	OrderCodes_DC();
}

void Huffman::OrderCodes_AC()
{   
	int Index;
	int p;

	for(p = 0; p < lastp; p++ )
	{   
	    Index = ACXhuff_huffval[p];
	    ACEhuff_ehufco[Index] = huffcode[p];
	    ACEhuff_ehufsi[Index] = huffsize[p];
	}
}

void Huffman::SpecifiedHuffman_AC()
{   
	int i;
	int accum = 0;
	int tmp;

	for(i = 0; i < 16; i++ )
	{   
	    tmp = LuminanceACBits[i];
	    accum += tmp;
	    ACXhuff_bits[i + 1] = tmp;
	}
	for(i = 0; i < accum; i++ )
	{   
	    ACXhuff_huffval[i] = LuminanceACValues[i];
	}
	SizeTable_AC();
	CodeTable();
	OrderCodes_AC();
}


void Huffman::CHROM_SizeTable_DC()
{   
	int i;
	int j;
	int p;

	p = 0;
	for(i = 1; i < 17; i++ )
	{   
	    for(j = 1; j <= CHROM_DCXhuff_bits[i]; j++ )
	    {   
		CHROM_huffsize[p++ ] = i;
	    }
	}
	CHROM_huffsize[p] = 0;
	CHROM_lastp = p;
}

void Huffman::CHROM_SizeTable_AC()
{   
	int i;
	int j;
	int p;

	p = 0;
	for(i = 1; i < 17; i++ )
	{   
	    for(j = 1; j <= CHROM_ACXhuff_bits[i]; j++ )
	    {   
		CHROM_huffsize[p++ ] = i;
	    }
	}
	CHROM_huffsize[p] = 0;
	CHROM_lastp = p;
}

void Huffman::CHROM_CodeTable()
{   
	int code;
	int p;
	int size;
	int skip = 0;

	p = 0;
	code = 0;
	size = CHROM_huffsize[0];
	while(0 == skip)
	{   
	    do 
	    {   
		CHROM_huffcode[p++ ] = code++ ;
	    }
	    while((CHROM_huffsize[p] == size) && (p < 257));
	    if (0 == CHROM_huffsize[p])
	    {   
		skip = 1;
	    }
	    if ( !skip)
	    {   
		do 
		{   
		    code <<= 1;
		    size++ ;
		}
		while(CHROM_huffsize[p] != size);
	    }
	}
}

void Huffman::CHROM_OrderCodes_DC()
{   
	int Index;
	int p;

	for(p = 0; p < CHROM_lastp; p++ )
	{   
	    Index = CHROM_DCXhuff_huffval[p];
	    CHROM_DCEhuff_ehufco[Index] = CHROM_huffcode[p];
	    CHROM_DCEhuff_ehufsi[Index] = CHROM_huffsize[p];
	}
}

void Huffman::CHROM_SpecifiedHuffman_DC()
{   
	int i;
	int accum = 0;
	int tmp;

	for(i = 0; i < 16; i++ )
	{   
	    tmp = CHROM_DCBits[i];
	    accum += tmp;
	    CHROM_DCXhuff_bits[i + 1] = tmp;
	}
	for(i = 0; i < accum; i++ )
	{   
	    CHROM_DCXhuff_huffval[i] = CHROM_DCValues[i];
	}
	CHROM_SizeTable_DC();
	CHROM_CodeTable();
	CHROM_OrderCodes_DC();
}

void Huffman::CHROM_OrderCodes_AC()
{   
	int Index;
	int p;

	for(p = 0; p < CHROM_lastp; p++ )
	{   
	    Index = CHROM_ACXhuff_huffval[p];
	    CHROM_ACEhuff_ehufco[Index] = CHROM_huffcode[p];
	    CHROM_ACEhuff_ehufsi[Index] = CHROM_huffsize[p];
	}
}

void Huffman::CHROM_SpecifiedHuffman_AC()
{   
	int i;
	int accum = 0;
	int tmp;

	for(i = 0; i < 16; i++ )
	{   
	    tmp = CHROM_ACBits[i];
	    accum += tmp;
	    CHROM_ACXhuff_bits[i + 1] = tmp;
	}
	for(i = 0; i < accum; i++ )
	{   
	    CHROM_ACXhuff_huffval[i] = CHROM_ACValues[i];
	}
	CHROM_SizeTable_AC();
	CHROM_CodeTable();
	CHROM_OrderCodes_AC();
}

void Huffman::JpegDefaultHuffman()
{   
	SpecifiedHuffman_DC();
	SpecifiedHuffman_AC();
	CHROM_SpecifiedHuffman_DC();
	CHROM_SpecifiedHuffman_AC();
}

int Huffman::WriteBits(int n, int code)
{   
	static unsigned char write_byte = ((unsigned char)'\000');
	static int left_bits = 8;
	int p;
	int temp;

	temp = ofp_ptr;
	if (n < 0)
	{   
	    if (left_bits < 8)
	    {   
		n = left_bits;
		ofp[temp++ ] = write_byte;
		if (write_byte == 255)
		    ofp[temp++ ] = 0;
		write_byte = 0;
		left_bits = 8;
	    }
	    else 
		n = 0;
	}
	else 
	{   
	    code &= lmask[n];
	    p = n - left_bits;
	    if (n == left_bits)
	    {   
		write_byte |= code;
		ofp[temp++ ] = write_byte;
		if (write_byte == 255)
		    ofp[temp++ ] = 0;
		write_byte = 0;
		left_bits = 8;
	    }
	    else 
		if (n > left_bits)
		{   
		    write_byte |= (code >> p);
		    ofp[temp++ ] = write_byte;
		    if (write_byte == 255)
			ofp[temp++ ] = 0;
		    if (p > 8)
		    {   
			write_byte = (255 & (code >> (p - 8)));
			ofp[temp++ ] = write_byte;
			if (write_byte == 255)
			    ofp[temp++ ] = 0;
			p -= 8;
		    }
		    write_byte = (code & lmask[p]) << (8 - p);
		    left_bits = 8 - p;
		}
		else 
		{   
		    write_byte |= (code <<  -p);
		    left_bits -= n;
		}
	}
	ofp_ptr = temp;
	
	//printf("Huffman::WriteBits, ofp_ptr = %d\n", ofp_ptr);
	return n;
}

void Huffman::EncodeHuffman_DC(int value)
{   
	if (DCEhuff_ehufsi[value])
	{   
	    WriteBits(DCEhuff_ehufsi[value], DCEhuff_ehufco[value]);
	}
}

void Huffman::EncodeDC()
{   
	int cofac;
	int diff;
	int s;

	diff = input[0] - LastDC;
	LastDC = input[0];
	if (diff < 0)
	    cofac =  -diff;
	else 
	    cofac = diff;
	if (cofac < 256)
	{   
	    s = csize[cofac];
	}
	else 
	{   
	    cofac = cofac >> 8;
	    s = csize[cofac] + 8;
	}
	EncodeHuffman_DC(s);
	if (diff < 0)
	{   
	    diff-- ;
	}
	WriteBits(s, diff);
}
   
void Huffman::CHROM_EncodeHuffman_DC(int value)
{   
	if (CHROM_DCEhuff_ehufsi[value])
	{   
	    WriteBits(CHROM_DCEhuff_ehufsi[value], CHROM_DCEhuff_ehufco[value]);
	}
}


void Huffman::EncodeDC_Cb()
{   
	int cofac;
	int diff;
	int s;

	diff = input[0] - LastDC_Cb;
	LastDC_Cb = input[0];
	if (diff < 0)
	    cofac =  -diff;
	else 
	    cofac = diff;
	if (cofac < 256)
	{   
	    s = csize[cofac];
	}
	else 
	{   
	    cofac = cofac >> 8;
	    s = csize[cofac] + 8;
	}
	CHROM_EncodeHuffman_DC(s);
	if (diff < 0)
	{   
	    diff-- ;
	}
	WriteBits(s, diff);
}
   
void Huffman::EncodeDC_Cr()
{   
	int cofac;
	int diff;
	int s;

	diff = input[0] - LastDC_Cr;
	LastDC_Cr = input[0];
	if (diff < 0)
	    cofac =  -diff;
	else 
	    cofac = diff;
	if (cofac < 256)
	{   
	    s = csize[cofac];
	}
	else 
	{   
	    cofac = cofac >> 8;
	    s = csize[cofac] + 8;
	}
	CHROM_EncodeHuffman_DC(s);
	if (diff < 0)
	{   
	    diff-- ;
	}
	WriteBits(s, diff);
}

void Huffman::EncodeHuffman_AC(int value)
{   
	if (ACEhuff_ehufsi[value])
	{   
	    WriteBits(ACEhuff_ehufsi[value], ACEhuff_ehufco[value]);
	}
}
   
void Huffman::CHROM_EncodeHuffman_AC(int value)
{   
	if (CHROM_ACEhuff_ehufsi[value])
	{   
	    WriteBits(CHROM_ACEhuff_ehufsi[value], CHROM_ACEhuff_ehufco[value]);
	}
}

void Huffman::EncodeAC()
{   
	int cofac;
	int i;
	int k;
	int r;
	int ssss;

	r = 0;
	for(k = 1; k < 64; k++ )
	{   
	    if (input[k] < 0)
		cofac =  -input[k];
	    else 
		cofac = input[k];
	    if (cofac < 256)
		ssss = csize[cofac];
	    else 
	    {   
		cofac = cofac >> 8;
		ssss = csize[cofac] + 8;
	    }
	    if (input[k] == 0)
	    {   
		if (k == 63)
		{   
		    EncodeHuffman_AC(0);
		    k = 64;
		}
		else 
		    r++ ;
	    }
	    else 
	    {   
		while(r > 15)
		{   
		    EncodeHuffman_AC(240);
		    r -= 16;
		}
		i = 16 * r + ssss;
		r = 0;
		EncodeHuffman_AC(i);
		if (input[k] < 0)
		    WriteBits(ssss, input[k] - 1);
		else 
		    WriteBits(ssss, input[k]);
	    }
	}
}

void Huffman::CHROM_EncodeAC()
{   
	int cofac;
	int i;
	int k;
	int r;
	int ssss;

	r = 0;
	for(k = 1; k < 64; k++ )
	{   
	    if (input[k] < 0)
		cofac =  -input[k];
	    else 
		cofac = input[k];
	    if (cofac < 256)
		ssss = csize[cofac];
	    else 
	    {   
		cofac = cofac >> 8;
		ssss = csize[cofac] + 8;
	    }
	    if (input[k] == 0)
	    {   
		if (k == 63)
		{   
		    CHROM_EncodeHuffman_AC(0);
		    k = 64;
		}
		else 
		    r++ ;
	    }
	    else 
	    {   
		while(r > 15)
		{   
		    CHROM_EncodeHuffman_AC(240);
		    r -= 16;
		}
		i = 16 * r + ssss;
		r = 0;
		CHROM_EncodeHuffman_AC(i);
		if (input[k] < 0)
		    WriteBits(ssss, input[k] - 1);
		else 
		    WriteBits(ssss, input[k]);
	    }
	}
}

int Huffman::WriteWord(int code)
{   
	int temp;

	temp = ofp_ptr;
	ofp[temp] = (code >> 8);
	temp++ ;
	ofp[temp] = (code & 255);
	temp++ ;
	ofp_ptr = temp;
	
	//printf("Huffman::WriteWord, ofp_ptr = %d\n", ofp_ptr);
	return 2;
}

int Huffman::WriteByte(int code)
{   
	int temp;

	temp = ofp_ptr;
	ofp[temp++ ] = code;
	ofp_ptr = temp;
	
	//printf("Huffman::WriteByte, ofp_ptr = %d\n", ofp_ptr);
	return code;
}

void Huffman::WriteMarker(int m)
{   
	ofp[ofp_ptr++ ] = 255;
	ofp[ofp_ptr++ ] = m;
	//printf("Huffman::WriteMarker, ofp_ptr = %d\n", ofp_ptr);
}

void Huffman::WriteAPP0()
{   

	WriteMarker(224);
	WriteWord(16);
	WriteByte((unsigned int)'J');
	WriteByte((unsigned int)'F');
	WriteByte((unsigned int)'I');
	WriteByte((unsigned int)'F');
	WriteByte(0);
	WriteByte(1);
	WriteByte(1);
	WriteByte(0);
	WriteWord(1);
	WriteWord(1);
	WriteByte(0);
	WriteByte(0);
}

void Huffman::WriteDQT()
{   
	int Pq = 0;
	int i;
	int start_p;
	
	WriteMarker(219);
	start_p = ofp_ptr;
	WriteWord(132);
	
	for(i = 0; i < 64; i++ )
	{   
	    if (LumiQuant[i] > 255)
		Pq = 16;
	}
		
        WriteByte(0|Pq);
	for(i = 0; i < 64; i++ )
	{   
		if(Pq){
			WriteWord(LumiQuant[IZgzgIndex[i]]);
		}
		else{
			WriteByte(LumiQuant[IZgzgIndex[i]]);
		}
	}

	Pq = 0;
	for(i = 0; i < 64; i++ )
	{   
	    if (CHROM_Quant[i] > 255)
		Pq = 16;
	}
	
        WriteByte(0x01|Pq);
	for(i = 0; i < 64; i++ )
	{   
		if(Pq){
			WriteWord(CHROM_Quant[IZgzgIndex[i]]);
		}
		else{
			WriteByte(CHROM_Quant[IZgzgIndex[i]]);
		}
	}
	
}

void Huffman::WriteHuffman_AC()
{   
	int accum = 0;
	int i;

	for(i = 1; i <= 16; i++ )
	{   
	    WriteByte(ACXhuff_bits[i]);
	    accum += ACXhuff_bits[i];
	}
	for(i = 0; i < accum; i++ )
	{   
	    WriteByte(ACXhuff_huffval[i]);
	}
}

void Huffman::WriteHuffman_DC()
{   
	int accum = 0;
	int i;

	for(i = 1; i <= 16; i++ )
	{   
	    WriteByte(DCXhuff_bits[i]);
	    accum += DCXhuff_bits[i];
	}
	for(i = 0; i < accum; i++ )
	{   
	    WriteByte(DCXhuff_huffval[i]);
	}
}


void Huffman::CHROM_WriteHuffman_AC()
{   
	int accum = 0;
	int i;

	for(i = 1; i <= 16; i++ )
	{   
	    WriteByte(CHROM_ACXhuff_bits[i]);
	    accum += CHROM_ACXhuff_bits[i];
	}
	for(i = 0; i < accum; i++ )
	{   
	    WriteByte(CHROM_ACXhuff_huffval[i]);
	}
}

void Huffman::CHROM_WriteHuffman_DC()
{   
	int accum = 0;
	int i;

	for(i = 1; i <= 16; i++ )
	{   
	    WriteByte(CHROM_DCXhuff_bits[i]);
	    accum += CHROM_DCXhuff_bits[i];
	}
	for(i = 0; i < accum; i++ )
	{   
	    WriteByte(CHROM_DCXhuff_huffval[i]);
	}
}


void Huffman::WriteDHT()
{   
	int start_p;

	WriteMarker(196);
	start_p = ofp_ptr;
	WriteWord(0x1a2);

	WriteByte(0);
	WriteHuffman_DC();
	WriteByte(16);
	WriteHuffman_AC();

	WriteByte(1);
	CHROM_WriteHuffman_DC();
	WriteByte(17);
	CHROM_WriteHuffman_AC();
}

void Huffman::WriteSOF()
{   
	WriteMarker(192);
	WriteWord(17);
	WriteByte(8);
	WriteWord(HEIGHT);
	WriteWord(WIDTH);
	WriteByte(3);
	WriteByte(1);
	WriteByte(17);
	WriteByte(0);

	WriteByte(2);
	WriteByte(17);
	WriteByte(1);

	WriteByte(3);
	WriteByte(17);
	WriteByte(1);
}

void Huffman::WriteSOS()
{   

	int start_p;

	WriteMarker(218);
	start_p = ofp_ptr;
	WriteWord(12);
	WriteByte(3);
	WriteByte(1);
	WriteByte(0);
	WriteByte(2);
	WriteByte(17);
	WriteByte(3);
	WriteByte(17);
	WriteByte(0);
	WriteByte(63);
	WriteByte(0);
}
 
void Huffman::main(void)
{   

#if 1
	int num_mdu;
	int n, i, k = 0;
	Bytes bb;
	

	 if (iter == 0)
	    {   
		imageheight = imageHeight;
		imagewidth = imageWidth;
		JpegDefaultHuffman();
		WriteMarker(216);
		WriteAPP0();
		WriteDQT();
		WriteDHT();
		WriteSOF();
		WriteSOS();
		num_mdu = ((imageheight + 7) >> 3) * ((imagewidth + 7) >> 3);
	    }

	while(1)
	{   

	if(iter % (NUMENCODERS * NUMBLOCKS) == 0){
		Port1.read(in_blocks[0]);
		Port2.read(in_blocks[1]);
		Port3.read(in_blocks[2]);
		//printf("finish huffman encoding %d blocks\n", iter);
	   }

	    do
	   {

	    	
		if(iter % NUMENCODERS == 0){
			input = &in_blocks[0].data[(iter/NUMENCODERS)%NUMBLOCKS*64];
			EncodeDC();
	    		EncodeAC();
		}
		if(iter % NUMENCODERS == 1){
			input = &in_blocks[1].data[(iter/NUMENCODERS)%NUMBLOCKS*64];
			EncodeDC_Cb();
			CHROM_EncodeAC();
		}
		if(iter % NUMENCODERS == 2){
			input = &in_blocks[2].data[(iter/NUMENCODERS)%NUMBLOCKS*64];
			EncodeDC_Cr();
			CHROM_EncodeAC();
		}  

	    n = ofp_ptr - ofp_ptr_pre;

	    if(n + k > 512)
	    {
		bb.n = k;
		PortOut.write(bb);
		k = 0;
	    }
	    //printf("0: Huffman sends %d bytes. ofp_ptr_pre = %d\n", n, ofp_ptr_pre);
	   // bb.n = n;
	    for(i=0; i<n; i++)
	    {
		bb.b[k ++] = ofp[ofp_ptr_pre++];
		if(k % 512 == 0)
		{
			bb.n = 512;

			//if(i == n - 1 && iter == NUMPICS * 3 - 1){
			//	bb.n |= 0x400;
			//}

			PortOut.write(bb);
			k = 0;
		}		
	    }
	    //printf("1: Huffman sends %d bytes. ofp_ptr_pre = %d, iter = %d\n", n, ofp_ptr_pre, iter);

	   
	    if(iter == NUMPICS * 3 - 1)
	    {
		bb.n |= 0x400;
		//exit(0);
		PortOut.write(bb);
	    }
	    iter++ ;
	
	  }while((iter %  (NUMENCODERS * NUMBLOCKS)) != 0);

          wait(WAITFORHUFF,SC_NS);
	  //waitfor WAITFORHUFF;
       }
#endif
}
