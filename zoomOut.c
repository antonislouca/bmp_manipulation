/*
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
 *
 * @file zoomOut.c
 * A file that contains the zoom out function that given an image
 * shrinks that image by 50%.
 *  Created on: Nov 19, 2019
 *  Author: Antonis Louca
 */

#include "bmplib.h"
/*
 *@brief Give a bmp image reduces its size by 50% keeping 1 pixel every four
 *
 *@param *img the image give to be zoomed out
 *@return the new image
 */
public IMAGE* zoomOut(IMAGE *img) {
	int width = (int)(img->bmpInfo.biWidth) / 2;
	int height =(int) img->bmpInfo.biHeight / 2;

	int newpad = (width * 3) % 4;
	int oldpad = img->padding;
	int nsize = (height * width * 3);
	int  counter = 0;
	int  start = (img->bmpInfo.biHeight - 1) * (img->bmpInfo.biWidth * 3);
	int  row = (img->bmpInfo.biHeight - 1) * (img->bmpInfo.biWidth * 3);
	int newrow = (height - 1) * (width * 3);
	int newstart = (height - 1) * (width * 3);

	if (newpad != 0) {
		nsize = nsize + (height * (4 - newpad));
		newrow = newrow + ((height - 1) * (4 - newpad));
		newstart = newstart + ((height - 1) * (4 - newpad));
	}
	unsigned char *temp =  calloc(1,nsize+1);

	if (oldpad != 0) {
		row = row + (4 - oldpad) * (img->bmpInfo.biHeight - 1);
		start = start + (4 - oldpad) * (img->bmpInfo.biHeight - 1);
	}

	while (row > 0) {

		while (counter <(int) img->bmpInfo.biWidth) {


				*(temp + newrow) = img->data[row];
				*(temp + newrow + 1) = img->data[row + 1];
				*(temp + newrow + 2) = img->data[row + 2];

				//printf("%u ,%u \n",newrow,row);

			counter += 2;
			row = row + 6;
			newrow = newrow + 3;

		}

		start = start - (2 * (img->bmpInfo.biWidth * 3));
		newstart = newstart - (width * 3);
		counter = 0;

		if (oldpad != 0) {
			start = start - (2 * (4 - oldpad));
		}

		if (newpad != 0) {
			newstart = newstart - (4 - newpad);
		}

		newrow = newstart;
		row = start;
		//printf("CHANGED %u ,%u \n",newrow,row);

	}

	free(img->data);
	img->data = temp;
	img->bmpInfo.biSizeImage = nsize;
	img->bmpInfo.biHeight = height;
	img->bmpInfo.biWidth = width;
	img->bmpFile.bfSize = img->bmpInfo.biSizeImage + 54;
	img->padding = newpad;
	return img;
}

#ifdef DEBUG_ZOOMOUT
int main() {
	IMAGE *img;
	img = LoadBitmapFile("image3.bmp");
	//listfun(img);
	zoomOut(img);
	WriteBitmapFile(img, "test1zoomOut.bmp");
	//listfun(img);
	return EXIT_SUCCESS;
}
#endif
