/*
 *
 * Copyright (C) 2019 Andreas Hadjivasili & Antonis Louca
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
 * @file module.h
 * Contains the structs for the bmp image process.
 *  Created on: Nov 17, 2019
 *      Author: antonis
 */

#ifndef BMPLIB_H_
#define BMPLIB_H_

#include <stdio.h>
#include <stdlib.h>

#define public
#define private static

typedef unsigned char byte;
typedef unsigned short int word;
typedef unsigned int dword;

typedef struct defBITMAPFILEHEADER {

	byte bfType1;
	byte bfType2;
	dword bfSize;  //bitmap file size
	word bfReserved1;
	word bfReserved2;
	dword bfOffBits;
} __attribute__ ((__packed__)) BITMAPFILEHEADER;

typedef struct defBITMAPINFOHEADER {
	dword biSize;  //number of bytes required by the struct
	dword biWidth;  //specifies width in pixels
	dword biHeight;  //specifies height in pixels
	word biPlanes;
	word biBitCount; //24 bits for assignment
	dword biCompression; //compressed or not
	dword biSizeImage;  //image size, bytes
	dword biXPelsPerMeter;
	dword biYPelsPerMeter;
	dword biClrUsed;
	dword biClrImportant;
} __attribute__ ((__packed__)) BITMAPINFOHEADER;

typedef struct defImage {
	BITMAPINFOHEADER bmpInfo;
	BITMAPFILEHEADER bmpFile;
	unsigned char *data;
	unsigned int padding;  // check about bits here
} IMAGE;

public void listfun(IMAGE *img);
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
public IMAGE* LoadBitmapFile(char *filename);
/**
 *@brief a function that prints the right usage of the program, and the gpl
 *preamble.
 */
public void correctUsage();
/**
 *A function that frees the image structure.
 *@param the  image to be freed
 */
public void freeImg(IMAGE *img);
/*
 *A function that writes the given image to the file given as name.
 * First it writes the header, then the info header, and then the data part
 * of the image.
 * @param img image given for writing
 * @param name the name of the file of the new image.
 */
public int WriteBitmapFile(IMAGE *img, char *name);
/*
 *@brief Give a bmp image reduces its size by 50% keeping 1 pixel every four
 *
 *@param *img the image give to be zoomed out
 *@return the new image
 */
public IMAGE* zoomOut();
/**
 *@brief Given an images zooms that image by 200% by multiplying each pixel
 *in the four neighboring positions.
 *@param image given for zooming
 *@return returns new image.
 *
 */
public IMAGE* zoomIn();
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
		int padding);
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
public unsigned char* convertBack(unsigned char *array, int width, int height,
		int padding);

/**
 *
 * @author Andreas Hadjivasili (AH)
 * @bug No known bugs.
 *
 * @brief Implements horizontal flip on a given bmp image.
 *
 * In this function we are getting the image given from the user and we
 * flip it based on the horizontal axis. This mean that on the implementation
 * we are just change the order of the rows. The dimensions of the image have
 * no changes.
 *
 * @param *im the image given from the user
 * @return the new image changed
 *
 */
public IMAGE* horizontal_flip(IMAGE *im);

/**
 *
 * @author Andreas Hadjivasili (AH)
 * @bug No known bugs.
 *
 * @brief Implements Vertical flip on a given bmp image.
 *
 * In this function we are getting the image given from the user and we
 * flip it based on the Vertical axis. This mean that on the implementation
 * we are just change the order of the columns.The dimensions of the image have
 * no changes.
 *
 * @param *im the image given from the user
 * @return the new image changed
 *
 */
public IMAGE* vertical_flip(IMAGE *im);

/**
 *
 * @author Andreas Hadjivasili (AH)
 * @bug No known bugs.
 *
 * @brief Implements Right Rotation on a given bmp image.
 *
 * In this function we are getting the image given from the user and we
 * Rotate it right by 90 degrees according to the direction of rotation of the
 * clock indicators.Because of the rotation our image has new dimensions that
 * are calculated and updated on the bmp header.
 *
 * @param *im the image given from the user
 * @return the new image changed
 *
 */
public IMAGE* Rotate_Right(IMAGE *im);

/**
 *
 * @author Andreas Hadjivasili (AH)
 * @bug No known bugs.
 *
 * @brief Implements Left Rotation on a given bmp image.
 *
 * In this function we are getting the image given from the user and we
 * Rotate it Left by 90 degrees according to the direction of rotation of the
 * clock indicators.Because of the rotation our image has new dimensions that
 * are calculated and updated on the bmp header.
 *
 * @param *im the image given from the user
 * @return the new image changed
 *
 */
public IMAGE* Rotate_Left(IMAGE *im);

/**
 *
 * @author Andreas Hadjivasili (AH)
 * @bug No known bugs.
 *
 * @brief Implements Grayscale Filter on a given bmp image.
 *
 * In this function we are getting the image given from the user and we
 * mask every pixel based on NTSC (National Television System Committee)
 * equation: 0.299*red + 0.587*green + 0.114*blue. The dimensions of the
 *  image have no changes.
 *
 * @param *im the image given from the user
 * @return the new image changed
 *
 */
public IMAGE* grayscale(IMAGE *im);

/**
 *
 * @author Andreas Hadjivasili (AH)
 * @bug No known bugs.
 *
 * @brief Implements Sharpen Filter on a given bmp image.
 *
 * In this function we are getting the image given from the user and we
 * sharpening it. Sharpening is a process of image editing in order to
 * sharpen the edges (boundaries) of objects (areas) depicted in an image and
 * belongs to the category of spatial filters. The term spatial filters
 * refers to transformations applied to the pixels of the image using a mask.
 * the mask that we used was based on this array:
 * {{-1,-1,-1} , {-1,9,-1} , {-1,-1,-1}}. The dimensions of the
 *  image have no changes.
 *
 * @param *im the image given from the user
 * @return the new image changed
 *
 */
public IMAGE* sharpen(IMAGE *im);

#endif /* BMPLIB_H_ */
