/*
 *  Copyright (C) 2019 Antonis Louca and Andreas Hadjivasili
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 * at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * Υou should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 *
 * @file image.c
 *
 * Contains functions that read and write the bit map image to a bmp
 * file and the usage prototype of the program.
 *  Created on: Nov 18, 2019
 *  Author: Antonis Louca
 */

#include "bmplib.h"


/**
 *@brief a function that prints the right usage of the program, and the gpl
 *preamble.
 */
public void correctUsage() {
	//preamble
	printf(
			"bmpengine.c Modifies bmp images Copyright \n"
					"(C) 2019 Antonis Louca and Andreas Hadjivasili"
					" This is free software; you can redistribute it and/or modify it under"
					" the terms of the GNU General Public*License, see the file COPYING.\n");
	//correct usage
	printf("Wrong input arguments.\n");
	printf("Usage: <-option> <number of bmp image files >.\n");
	printf("option can be -list, -hflip, -vflip, -right90,-left90, -zoomin,"
			"-zoomout, -gray, -sharpen,.\n");
	printf(
			"Number of bmp image files, is a number equal or bigger than one.\n\n");
}


/*
 *The function that loads the bitmap image from the given file. Read the bitmap
 *header file and info, and then the data. If the bmp image file does not exist
 *it returns null, same happens when the bmp image is not a 24 bit on or it is
 *compressed. NOTE: this function calculates the image biIMageSize
 *manually and sets that field to the calculated value.
 *@param filename the name of the bmp file
 *@return the image read form the file, returns null if file is not fount, if
 *			image is 24 bits or if image is compressed or is not a bmp image.
 */
public IMAGE* LoadBitmapFile(char *filename) {
	FILE *filePtr; //file pointer
	IMAGE *bmpimage = (IMAGE*) calloc(1,sizeof(IMAGE));

	int size = 0;
	filePtr = fopen(filename, "rb");
	if (filePtr == NULL) {
		printf("Bmp file name not available\n");
		return NULL;
	}
	//read  file header
	fread(&bmpimage->bmpFile, sizeof(BITMAPFILEHEADER), 1, filePtr);

	//check if its bitmap
	if (bmpimage->bmpFile.bfType1 != 'B' && bmpimage->bmpFile.bfType2 != 'M') {
		fclose(filePtr);
		printf("This is not a bmp image file.\n");
		return NULL;
	}

	//read  info header
	fread(&bmpimage->bmpInfo, sizeof(BITMAPINFOHEADER), 1, filePtr);

	//check if its a compressed image or not
	if (bmpimage->bmpInfo.biCompression != 0) {
		printf("Compressed image\n");
		fclose(filePtr);
		return NULL;
	}
	//checks 24 bitcount
	if (bmpimage->bmpInfo.biBitCount != 24) {
		printf("This is not a 24 bit bmp image.\n");
		fclose(filePtr);
		return NULL;

	}

	fseek(filePtr, bmpimage->bmpFile.bfOffBits, SEEK_SET);
	bmpimage->padding = (bmpimage->bmpInfo.biWidth * 3) % 4;
	size = bmpimage->bmpInfo.biHeight * bmpimage->bmpInfo.biWidth * 3;

	if (bmpimage->padding != 0) {
		size += (4 - bmpimage->padding) * bmpimage->bmpInfo.biHeight;
	}

	bmpimage->bmpInfo.biSizeImage = size;
	bmpimage->data = (unsigned char*) calloc(1,bmpimage->bmpInfo.biSizeImage);

	//printf("%d\n", bmpimage->bmpInfo.biSizeImage);
	if (!bmpimage->data) {
		fclose(filePtr);
		return NULL;
	}

	fread(bmpimage->data, (bmpimage->bmpInfo.biSizeImage), 1, filePtr);

	if (bmpimage->data == NULL) {
		printf("Could not read the data of the bmp image.\n");
		fclose(filePtr);
		return NULL;
	}

	fclose(filePtr);
	return bmpimage;
}

/**
 *A function that frees the image structure.
 *@param the  image to be freed
 */
public void freeImg(IMAGE *img) {
	free(img->data);
	free(img);
}

/*
 *A function that writes the given image to the file given as name.
 * First it writes the header, then the info header, and then the data part
 * of the image.
 * @param img image given for writing
 * @param name the name of the file of the new image.
 */
public int WriteBitmapFile(IMAGE *img, char *name) {
	FILE *filePtr;
	filePtr = fopen(name, "wb");

	if (filePtr == NULL)
		return EXIT_FAILURE;

	fwrite(&img->bmpFile, sizeof(BITMAPFILEHEADER), 1, filePtr);
	fwrite(&img->bmpInfo, sizeof(BITMAPINFOHEADER), 1, filePtr);
	//int size = (img->bmpInfo.biWidth+img->padding)* img->bmpInfo.biHeight*3;
	fwrite(img->data, img->bmpInfo.biSizeImage, 1, filePtr);

	fclose(filePtr);

	return EXIT_SUCCESS;
}


/*
 * A function that converts a given array to a linear array in increasing order
 * , while also removing the padding.
 * @param array the array to be converted
 * @param width the width of the array
 * @param height the height of the array
 * @param padding the padding of the array
 * @return the new linear character array.
 */
public unsigned char* convertFrom(unsigned char *array, int width, int height,
		int padding) {

	int size = width * height * 3;

	unsigned char *temp = (unsigned char*) calloc(1,size);

	if (temp == NULL) {
		printf("memory allocation failed\n");
	}

//	int j = 1;
	int start = (height - 1) * (width * 3);
	int row = (height - 1) * (width * 3);

	if (padding != 0) {
		row = row + (4 - padding) * (height - 1);
		start = start + (4 - padding) * (height - 1);
	}

	//int col = 0;
	int counter = 0;
	//  width=width*3;
	int i = 0;

	while (i < size) {
		counter++;

		*(temp + i) = array[row];
		*(temp + i + 1) = array[row + 1];
		*(temp + i + 2) = array[row + 2];

		if (counter == width) {

			counter = 0;

			start = start - (width * 3);

			if (padding != 0) {
				start = start - (4 - padding);
			}

			row = start - 3;

		}

		row = row + 3;
		i = i + 3;

	}

	free(array);
	return temp;

}

/**
 *A function that converts back the linear array given to decresing order in
 *little endian as the pixels of bmp images. This function also adds the padding
 *back to the array.
 *@param array the array to be converted
 *@param width the width of the array
 *@param height the height of the array
 *@param padding the padding to be added in the array
 *@return the new character array with padding
 */
public unsigned char* convertBack(unsigned char *array,int width, int height,
		int padding) {

	int size = width * height * 3;
	int len = size; //old size

	if (padding != 0) {
		size = size + (height * (4 - padding));
	}

	int counter = 0;
	unsigned char *temp = NULL;
	temp = (unsigned char*) calloc(1,size);

	if (temp == NULL) {
		printf("failed to allocate memory");
	}

	int row = (height - 1) * (width * 3);
	int start = (height - 1) * (width * 3);
	int i = 0;

	if (padding != 0) {
		row = row + (4 - padding) * (height - 1);
		start = start + (4 - padding) * (height - 1);
	}

	while (i < len) {
		counter++;

		*(temp + row) = array[i];
		*(temp + row + 1) = array[i + 1];
		*(temp + row + 2) = array[i + 2];

		if (counter == width) {

			counter = 0;

			start = start - (width * 3);

			if (padding != 0) {
				start = start - (4 - padding);
			}

			row = start - 3;

		}

		row = row + 3;
		i = i + 3;

	}

	free(array);

	return temp;
}

#ifdef DEBUG_IMAGE
int main(int argc, char **argv) {
	IMAGE *img = LoadBitmapFile("image1.bmp");

	int counter = 0;
	for (int i = 0; i < img->bmpInfo.biSizeImage; i += 3) {
//		if (counter == img->bmpInfo.biWidth) {
//			counter = 0;
//			if (img->padding != 0) {
//				i = i + (4 - img->padding);
//			}
//		}
		printf("%u %u %u \n", img->data[i], img->data[i + 1], img->data[i + 2]);
	}

	printf("DONE\n");
//convert From
	img->data = convertFrom(img->data, img->bmpInfo.biWidth,
			img->bmpInfo.biHeight, img->padding);
	for (int i = 0; i < img->bmpInfo.biWidth * img->bmpInfo.biHeight * 3; i +=
			3) {
		printf("%u %u %u \n", img->data[i], img->data[i + 1], img->data[i + 2]);
	}
	printf("DONE\n");
	//Convert Back
	img->data = convertBack(img->data, img->bmpInfo.biWidth,
			img->bmpInfo.biHeight, img->padding);

	int size = img->bmpInfo.biWidth * img->bmpInfo.biHeight * 3;

	if (img->padding != 0) {
		size = size + (4 - img->padding) * img->bmpInfo.biHeight;

	}
	for (int i = 0; i < size; i += 3) {
		printf("%u %u %u \n", img->data[i], img->data[i + 1], img->data[i + 2]);
	}

	//listfun(img);
	WriteBitmapFile(img, "image2test.bmp");
	freeImg(img);
	return EXIT_SUCCESS;
}
#endif
