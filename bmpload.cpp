/*
   Class Name:

      CBMPLoader.

   Created by:

      Allen Sherrod (Programming Ace of www.UltimateGameProgramming.com).

   Description:

      This class loads a .bmp texture into this object.
*/


#include"bmpLoad.h"


CBMPLoader::CBMPLoader()
{
   // Give everything default values.
  image = 0;
  textureExist = false;
  type = 0;
}


CBMPLoader::~CBMPLoader()
{
   FreeImage();                  // Delete all images and dynamic memory.
   //glDeleteTextures(1, &ID);不要删掉创造好的贴图啊喂喂= =！     // Release the image from OpenGL memory.
}


bool CBMPLoader::LoadBMPFile(char *file)
{

	FILE * ff = fopen(file, "r");
	
	//fclose(ff);
	BITMAPINFOHEADER biHeader;    // This will hold the info header of the bitmap.

   if(textureExist)
      FreeImage();

	// Load the image.
	image = LoadBitmap(file, &biHeader);

   // Make sure the image loaded.
	if(image == 0)
	   {
         return false;
	   }

   imageWidth = biHeader.biWidth;
   imageHeight = biHeader.biHeight;

   GenerateTexture();

   textureExist = true;

   return true;
}


void CBMPLoader::GenerateTexture()
{
   // Generate the texture and text the id to the images id.
	glGenTextures(1, &ID);
   
   // Here we bind the texture and set up the filtering.
   glBindTexture(GL_TEXTURE_2D, ID);
   glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	gluBuild2DMipmaps(GL_TEXTURE_2D, type, imageWidth, imageHeight,
                     type, GL_UNSIGNED_BYTE, image);
   glTexImage2D(GL_TEXTURE_2D, 0, type, imageWidth, imageHeight, 
                0, type, GL_UNSIGNED_BYTE, image);
}


unsigned char* CBMPLoader::LoadBitmap(char *file, BITMAPINFOHEADER *bitmapInfoHeader)
{
	FILE *pFile = 0;              // Need this to open a file.
	BITMAPFILEHEADER header;      // This will hold the bitmap header information.

	unsigned char *textureData = 0;  // This will hold the bitmap image itself.

   // This will be used to swap the image colors from BGR to RGB.
	unsigned char textureColors = 0;

	pFile = fopen(file, "rb");    // Open the file.

	if(pFile == 0) return 0;      // Check and make sure there are no errors.

	// Read in the bitmap header info into the BITMAPFILEHEADER variable.
	fread(&header, sizeof(BITMAPFILEHEADER), 1, pFile);
	
	// Make sure this is a real bitmap by checking the ID.
	if(header.bfType != BITMAP_ID)
	   {
		   fclose(pFile);
		   return 0;
	   }

	// Read in the second header info into the BITMAPINFOHEADER variable.
	fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, pFile);

   if(bitmapInfoHeader->biSizeImage == 0)
      bitmapInfoHeader->biSizeImage = bitmapInfoHeader->biWidth * bitmapInfoHeader->biHeight * 3;

	// Place the pointer in front of where the image data starts.
	fseek(pFile, header.bfOffBits, SEEK_SET);

	// Dynamically create enough memory for the image.
	textureData = (unsigned char*)malloc(bitmapInfoHeader->biSizeImage);

	// Error checking.  Make sure the memory was allocated.
	if(!textureData)
	   {
		   free(textureData);
		   fclose(pFile);
		   return 0;
	   }

	// Read in the image.
	fread(textureData, 1, bitmapInfoHeader->biSizeImage, pFile);

	// Error checking.  Make sure an image was loaded.
	if(textureData == 0)
	   {
		   fclose(pFile);
		   return 0;
	   }

	// Bitmaps are saved in BGR format so we will make the image RGB by...
	for(int index = 0; index < (int)bitmapInfoHeader->biSizeImage; index+=3)
	   {
		   textureColors = textureData[index];
		   textureData[index] = textureData[index + 2];
		   textureData[index + 2] = textureColors;
	   }

   type = GL_RGB;

	fclose(pFile);     // We are done with the file so close it.
	return textureData;  // Send the image to the function that called this.
}


void CBMPLoader::FreeImage()
{
   // When the application is done delete all dynamically allocated memory.
   if(image)
      {
         free(image);
         image = 0;
         textureExist = false;
         type = 0;
      }
}


// Copyright September 2003
// All Rights Reserved!
// Allen Sherrod
// ProgrammingAce@UltimateGameProgramming.com
// www.UltimateGameProgramming.com