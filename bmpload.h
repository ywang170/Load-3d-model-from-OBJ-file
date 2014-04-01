#ifndef _LOADER_H_
#define _LOADER_H_

#include<Windows.h>
#include<GL\glut.h>
#include<stdio.h>
#include<stdlib.h>

#define BITMAP_ID 0x4D42

class CBMPLoader
{
public:
	CBMPLoader();
	~CBMPLoader();

	bool LoadBMPFile(char * filename);
	void FreeImage();


	int type;
	bool textureExist;
	unsigned int ID;
	int imageWidth;
	int imageHeight;
	unsigned char * image;
	void GenerateTexture();
	unsigned char * LoadBitmap(char *file, BITMAPINFOHEADER *bitmapInfoHeader);
};
#endif