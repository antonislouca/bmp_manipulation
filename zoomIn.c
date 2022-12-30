/*
 *
 *
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
 * @file zoom.c
 * The file that contains the zoom in function that enlarges the given image by
 * 200%.
 *  Created on: Nov 21, 2019
 *  Author: Antonis Louca
 */

#include"bmplib.h"
/**
 *@brief Given an images zooms that image by 200% by multiplying each pixel
 *in the four neighboring positions.
 *@param image given for zooming
 *@return returns new image.
 *
 */
public IMAGE* zoomIn(IMAGE *img) {

	int width = (img->bmpInfo.biWidth) * 2;
	int height = img->bmpInfo.biHeight * 2;

	int newpad = (width * 3) % 4;
	int oldpad = img->padding;

	int size = (height * width * 3);
	int oldsize = img->bmpInfo.biHeight * 3 * img->bmpInfo.biWidth;
	if (oldpad != 0) {
		oldsize += (4 - oldpad) * img->bmpInfo.biHeight;
	}
	if (newpad != 0) {
		size = size + ((4 - newpad) * height);
	}


	//printf("%d\n",oldsize);
	unsigned char *temp = calloc(1,size);

	int row1 = 0;
	int row2 = width * 3;

	if (newpad != 0) {
		row2 += (4 - newpad);
	}

	int counter = 0, i = 0;

	while (i < oldsize) {

		counter++;
		//printf("%d ,%d \n ", row1, row2);
		*(temp + row1) = img->data[i];         //B
		*(temp + row1 + 1) = img->data[i + 1]; //G
		*(temp + row1 + 2) = img->data[i + 2]; //R

		*(temp + row1 + 3) = img->data[i];     //B
		*(temp + row1 + 4) = img->data[i + 1]; //G
		*(temp + row1 + 5) = img->data[i + 2]; //R

		//for row 2
		*(temp + row2) = img->data[i];         //B
		*(temp + row2 + 1) = img->data[i + 1]; //G
		*(temp + row2 + 2) = img->data[i + 2]; //R

		*(temp + row2 + 3) = img->data[i];     //B
		*(temp + row2 + 4) = img->data[i + 1]; //G
		*(temp + row2 + 5) = img->data[i + 2]; //R

		if (counter == img->bmpInfo.biWidth) {
			counter = 0;
			if (oldpad != 0) {
				i = i + (4 - oldpad);
			}

			if (newpad != 0) {
				row1 = row1 + 2 * (4 - newpad); //end of row 1
				row2 = row2 + 2 * (4 - newpad); //end of row 2

			}
			row1 = row1 + (width * 3);
			row2 = row2 + (width * 3);

		}
		row1 = row1 + 6;
		row2 = row2 + 6;
		i = i + 3;
	}

	free(img->data);
	img->data = temp;
	img->bmpInfo.biSizeImage = size;
	img->bmpInfo.biHeight = height;
	img->bmpInfo.biWidth = width;
	img->bmpFile.bfSize = img->bmpInfo.biSizeImage + sizeof(BITMAPFILEHEADER)
			+ sizeof(BITMAPINFOHEADER);
	img->padding = newpad;
	return img;
}

#ifdef DEBUG_ZOOMIN
int main() {

	IMAGE *img;
	img = LoadBitmapFile("image7.bmp");
	//listfun(img);
	//printf(img->bmpInfo.biSizeImage);
	img = zoomIn(img);
	WriteBitmapFile(img, "zoomin7-test.bmp");
//listfun(img);
	return EXIT_SUCCESS;
}
#endif
