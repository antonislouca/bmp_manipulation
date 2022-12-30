/*
 *
 * Copyright (C) 2019 Antonis Louca and Andreas Hadjivasili
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
 * @file list.c
 * Contains the list function that prints the header of the
 * bitmap image.
 *  Created on: Nov 17, 2019
 *  Author: Antonis Louca
 */

#include "bmplib.h"

/*
 *This function prints the two sections of the header of the bitmap image.
 * FIrst the file header is printed  then the info header is printed.
 * @param img the bitmap image to be printed.
 */
public void listfun(IMAGE *img) {
	printf("BITMAP_FILE_HEADER\n");
	printf("====================\n");
	printf("bfType: %c%c\n", img->bmpFile.bfType1, img->bmpFile.bfType2);
	printf("bfSize: %u\n", img->bmpFile.bfSize);
	printf("bfReserved1: %u\n", img->bmpFile.bfReserved1);
	printf("bfReserved2: %u\n", img->bmpFile.bfReserved2);
	printf("bfOffBits: %u\n\n", img->bmpFile.bfOffBits);

	printf("BITMAP_INFO_HEADER\n");
	printf("====================\n");
	printf("biSize: %u\nbiWidth: %u\nbiHeight: %u\nbiPlanes: %u\n"
			"biBitCount: %u\nbiCompression: %u\n", img->bmpInfo.biSize,
			img->bmpInfo.biWidth, img->bmpInfo.biHeight, img->bmpInfo.biPlanes,
			img->bmpInfo.biBitCount, img->bmpInfo.biCompression);
	printf("biSizeImage: %u\nbiXPelsPerMeter: %u\nbiYPelsPerMeter: %u\n"
			"biClrUsed: %u\nbiClrImportant: %u\n", img->bmpInfo.biSizeImage,
			img->bmpInfo.biXPelsPerMeter, img->bmpInfo.biYPelsPerMeter,
			img->bmpInfo.biClrUsed, img->bmpInfo.biClrImportant);
	printf("**************************************\n\n");
}

#ifdef DEBUG_LIST
int main(int argc,char **argv){
	//BITMAPINFOHEADER bitmapInfoHeader;
	//char *bitmapData = LoadBitmapFile(argv[1],&bitmapInfoHeader);
	IMAGE *img=LoadBitmapFile(argv[1]);
	listfun(img);
	WriteBitmapFile(img,"image2test.bmp");

}
#endif
