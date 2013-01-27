/***********************************************************
*
* stimulus.cc
* author: Weiwei Chen
* 01/18/13 initial version
*
*
***********************************************************/

#include "stimulus.h"
FILE *fin, *fout;
unsigned char data[FILELENGTH + 100];
unsigned char dataout[FILELENGTH + 100];
unsigned int imageHeight = 0;
unsigned int imageWidth = 0;
int stridex;
int stridey;
int fileHeaderLength;
int numTotalBlocks;
int dataLength;
int zerocnt = 0;
char *fname;


void Stimulus:: ReadRGB(int n)	// read the nth block, assume that the picture has complete blocks (8x
{
	int x, y, i, j, pos;
	unsigned char* ptr;
	
	x = n % stridex * 8;
	y = n / stridex * 8;
	pos = (y * imageWidth + x) * pixellen;
	ptr = &data[fileHeaderLength + pos];

	for(i = 0; i < 8; i ++)
	{
		for(j = 0; j < 8; j ++)
		{
			bInput[i * 8 + j] = ptr[i * imageWidth * pixellen + j * pixellen];
			gInput[i * 8 + j] = ptr[i * imageWidth * pixellen + j * pixellen + 1];
			rInput[i * 8 + j] = ptr[i * imageWidth * pixellen + j * pixellen + 2];
		}
	}
}

void Stimulus::RGB2YCC()
{
	unsigned int i, j;
	unsigned char r, g, b;
	double y, cb, cr;
	
	for(i = 0; i < 8; i ++)
	{
		for(j = 0; j < 8; j ++)
		{
			r = rInput[i * 8 + j];
			g = gInput[i * 8 + j];
			b = bInput[i * 8 + j];
	
				y  = (77 * r + 150 * g + 29 * b) /256;
				cb = (-44 * r - 87 * g + 131 * b + 32768) / 256;
				cr = (131 * r - 110 * g - 21 * b + 32768) / 256;

				yInput[i * 8 + j] = (unsigned int) y ;
				cbInput[i * 8 + j] = (unsigned int) cb ;
				crInput[i * 8 + j] = (unsigned int) cr;
		}
	}
} 


void Stimulus::RGBAVER()
{
	int i, j, r, g, b;
	//double y, cb, cr;

	for(i = 0; i < 8; i ++)
	{
		for(j = 0; j < 8; j ++)
		{
			r = rInput[i * 8 + j];
			g = gInput[i * 8 + j];
			b = bInput[i * 8 + j];

			yInput[i * 8 + j] = (r + g + b) / 3;
			cbInput[i * 8 + j] = (r + g + b) / 3;
			crInput[i * 8 + j] = (r + g + b) / 3;
		}
	}
}

void Stimulus::ReadPPM()
{
	fin = fopen(fname, "rb");
	if(fin == NULL)
	{
		printf("Cannot open the file !!!\n");
		exit(0);
	}


	fseek(fin, 0L, SEEK_END);
	dataLength = ftell(fin);
	fseek(fin, 0L, SEEK_SET);


	fread(data, sizeof(char), dataLength, fin);
	
	ch = data;

	ch ++;			/*'P'*/
	ch ++;			/*'6'*/
	ch ++;			/*0x0a*/

	imageWidth = imageWidth * 10 + (*ch - 0x30);
	ch ++;
	imageWidth = imageWidth * 10 + (*ch - 0x30);
	ch ++;
	imageWidth = imageWidth * 10 + (*ch - 0x30);
	ch ++;
	imageWidth = imageWidth * 10 + (*ch - 0x30);
	ch ++;
	stridex = imageWidth >> 3;

	ch ++;	/*0x20*/

	imageHeight = imageHeight * 10 + (*ch - 0x30);
	ch ++;
	imageHeight = imageHeight * 10 + (*ch - 0x30);
	ch ++;
	imageHeight = imageHeight * 10 + (*ch - 0x30);
	ch ++;
	imageHeight = imageHeight * 10 + (*ch - 0x30);
	ch ++;
	stridey = imageHeight >> 3;

	numTotalBlocks = imageWidth * imageHeight / 64;

	ch ++;			/*0x0a*/
	ch ++;	/*0x32*/
	ch ++;	/*0x35*/
	ch ++;	/*0x35*/
	ch ++;	/*0x0a*/

	fileHeaderLength = 17;
	pixellen = 3;

	printf("imageWidth = %d, imageHeight = %d, numTotalBlocks = %d \n", imageWidth, imageHeight, numTotalBlocks);
}

void Stimulus::YCC2RGB()
{
	int i, j, y, cb, cr;
	double r, g, b;

	for(i = 0; i < 8; i ++)
	{
		for(j = 0; j < 8; j ++)
		{
			y = yInput[i * 8 + j];
			cb = cbInput[i * 8 + j];
			cr = crInput[i * 8 + j];

			r = y + 1.371 * (cr - 128);
			g = y - 0.698 * (cr - 128) - 0.336 * (cb - 128);
			b = y + 1.732 * (cb - 128);

			rInput[i * 8 + j] = (int) r;
			gInput[i * 8 + j] = (int) g;
			bInput[i * 8 + j] = (int) b;
		}
	}
}

void Stimulus::writeRGBtoFile(int n)
{
	int x, y, i, j, pos;
	unsigned char* ptr;

	x = n % stridex * 8;
	y = n / stridex * 8;

	pos = (y * imageWidth + x) * pixellen;
	ptr = &dataout[fileHeaderLength + pos];
	for(i = 0; i < 8; i ++)
	{
		for(j = 0; j < 8; j ++)
		{	
			ptr[i * imageWidth * pixellen + j * pixellen] =  rInput[i * 8 + j];
			ptr[i * imageWidth * pixellen + j * pixellen + 1] = gInput[i * 8 + j];
			ptr[i * imageWidth * pixellen + j * pixellen + 2] = bInput[i * 8 + j];
		}
	}
}


void Stimulus::writeYCCtoFile(int n)
{
	int x, y, i, j, pos;
	unsigned char* ptr;

	x = n % stridex * 8;
	y = n / stridex * 8;

	pos = (y * imageWidth + x) * 3;

	ptr = &dataout[fileHeaderLength + pos];

	for(i = 0; i < 8; i ++)
	{
		for(j = 0; j < 8; j ++)
		{
			ptr[i * imageWidth * 3 + j * 3] = 0;
			ptr[i * imageWidth * 3 + j * 3 + 1] = 0;
			ptr[i * imageWidth * 3 + j * 3 + 2] = 255;
		}
	}
}

void Stimulus::ReadBMP()
{
	int i;
	fin = fopen(fname, "rb");
	if(fin == NULL)
	{
		printf("Cannot open the file !!!\n");
		exit(0);
	}


	fseek(fin, 0L, SEEK_END);
	dataLength = ftell(fin);
	fseek(fin, 0L, SEEK_SET);


	fread(data, sizeof(char), dataLength, fin);
	
	ch = data;

	ch ++;			/*'B'*/
	ch ++;			/*'M'*/

	ch += 8;

	bmpoffset = 0;
	for(i = 3; i >= 0; i --){
		bmpoffset = (bmpoffset << 8) | ch[i];
	}

	ch += 8;

	imageWidth = 0;
	for(i = 3; i >= 0; i --){
		imageWidth = (imageWidth << 8) | ch[i];
	}
	stridex = imageWidth >> 3;
	ch += 4;

	imageHeight = 0;
	for(i = 3; i >= 0; i --){
		imageHeight = (imageHeight << 8) | ch[i];
	}
	if((int)imageHeight < 0){
		imageHeight = -((int)imageHeight);
	}
	stridey = imageHeight >> 3;
	ch += 6;

	pixellen = 0;
	for(i = 1; i >= 0; i --){
		pixellen = (pixellen << 8) | ch[i];
	}
	pixellen >>= 3;

	numTotalBlocks = imageWidth * imageHeight / 64;
	fileHeaderLength = bmpoffset;

	printf("imageWidth = %d, imageHeight = %d, numTotalBlocks = %d, fileHeaderLength = %d \n"
	, imageWidth, imageHeight, numTotalBlocks, fileHeaderLength);
}

void Stimulus::main(void)
{   
	int iter = 0;
	
	ReadBMP();
	

	while(iter < NUMPICS){
		ReadRGB(iter);
		RGB2YCC();
		
		//memcpy(&output_blocks[0][iter%NUMBLOCKS*64], yInput, sizeof(int) * 64);
		//memcpy(&output_blocks[1][iter%NUMBLOCKS*64], cbInput, sizeof(int) * 64);
		//memcpy(&output_blocks[2][iter%NUMBLOCKS*64], crInput, sizeof(int) * 64);
		memcpy(&output_blocks[0].data[iter%NUMBLOCKS*BLOCKSIZE], yInput, sizeof(int) * BLOCKSIZE);
		memcpy(&output_blocks[1].data[iter%NUMBLOCKS*BLOCKSIZE], cbInput, sizeof(int) * BLOCKSIZE);
		memcpy(&output_blocks[2].data[iter%NUMBLOCKS*BLOCKSIZE], crInput, sizeof(int) * BLOCKSIZE);
		
		iter ++;
		if(iter % NUMBLOCKS  == 0){
			pout1.write(output_blocks[0]);
			pout2.write(output_blocks[1]);
			pout3.write(output_blocks[2]);	
		}
	}
}

Stimulus::Stimulus( sc_core::sc_module_name _nm )
: sc_core::sc_module( _nm )
{
SC_HAS_PROCESS(Stimulus);
SC_THREAD(main);
}
