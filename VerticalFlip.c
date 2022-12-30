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
 * @file VerticalFlip.c
 * Implements a Vertical flip of an image and returns the new image flipped.
 * Created on: Nov 18, 2019
 * Author: Andreas Hadjivasili
 *
 */
#include "bmplib.h"


public IMAGE *vertical_flip(IMAGE *im){

  int width = im->bmpInfo.biWidth;
  int height = im->bmpInfo.biHeight;
  int i=0;
  int j= width*3 -3;
  int counter = 0;
  int c = 0;
  int size = (width * height * 3)+ (4- im->padding)*height;
  unsigned char *temp = calloc(1,size);
  int ext = 0;
  int pad =im->padding;
  int temppad =4 - im->padding;
  int h = 0;

  if (pad!=0) {
    ext = temppad;
  }

    while (i < im->bmpInfo.biSizeImage) {

    if((counter == width) && (pad!=0) ){
      i = i + temppad;
      counter = 0;
    }

    counter ++;
    c++;

    if (j < 0) {
      j = (width*3)-3;
    }

    if ((j+h)<size) {
    *(temp+j+h) = *(im->data+i); //BLUE
    *(temp+j+1+h) = *(im->data+i+1); //GREEN
    *(temp+j+2+h) = *(im->data+i+2); //RED
    }

    if(c == width ){
      h = h + (width*3)+ ext;
      c=0;
    }

    j = j - 3;
    i = i +3;

  }

  free(im->data);
  im->data = temp;
  return im;

}

#ifdef DEBUG_VERTICALFLIP
int main(int argc, char const *argv[]) {

  IMAGE *im;
  im = LoadBitmapFile("image7.bmp");
  im = vertical_flip(im);
  WriteBitmapFile(im,"test7.bmp");
  return 0;

}
#endif
