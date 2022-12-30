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
 * @file Grayscale.c
 * Implements a Grayscale Filter on an image and returns the new image filtered.
 * Created on: Nov 17, 2019
 * Author: Andreas Hadjivasili
 *
 */
#include "bmplib.h"


public IMAGE *grayscale(IMAGE *im){

  int width = im->bmpInfo.biWidth;
  int i =0;
  int counter = 0;
  int pixelColor = 0;
  int pad = 4 - im->padding;

  while (i < im->bmpInfo.biSizeImage) {

    if((counter == width) && (im->padding!=0) ){
       i = i + pad;
       counter = 0;
      }

    counter ++;
    pixelColor = (*(im->data+i))* 0.114 + (*(im->data+i+1))* 0.587 + (*(im->data+i+2))* 0.299;

    *(im->data+i) = pixelColor;  //BLUE
    *(im->data+i+1) = pixelColor; //GREEN
    *(im->data+i+2) = pixelColor; //RED

    i = i +3;
  }

  return im;
}


#ifdef DEBUG_GRAYSCALE
int main(int argc, char const *argv[]) {

  IMAGE *im;
  im = LoadBitmapFile("image6.bmp");
  im = grayscale(im);
  WriteBitmapFile(im,"test6.bmp");

  return 0;
}
#endif
