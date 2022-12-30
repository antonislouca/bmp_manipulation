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
 * @file Sharpen.c
 * Implements a Sharpen filter on an image and returns the new image filtered.
 * Created on: Nov 17, 2019
 * Author: Andreas Hadjivasili
 *
 */
#include "bmplib.h"


IMAGE *sharpen(IMAGE *im){

    int width = im->bmpInfo.biWidth;
    int height = im->bmpInfo.biHeight;
    int pad = im->padding;
    int w = width*3;
    int size = width * height * 3;
    int color=0;
    int i=0;
    int j=0;
    int counter = 0;
    int m1,m2,m3,m4,m6,m7,m8,m9;
    m1 = m2 = m3 = m4 = m6 = m7 = m8 = m9 = -1;
    int m5 = 9;

    unsigned char *temp = (unsigned char*) calloc(1,size);
	  temp =convertFrom(im->data, width, height, pad);

    while(i<height){
	     while(j<w){

      //BLUE
      color = m1*temp[ (((i-1 + height) % height) *w) + ((j-3 + w)% w)]+
              m2*temp[ (((i-1 + height) % height) *w) + ((j + w)% w)]+
              m3*temp[ (((i-1 + height) % height) *w) + ((j+3 + w)% w)]+
              m4*temp[ (((i + height) % height) *w) + ((j-3 + w)% w)]+
              m5*temp[ (((i + height) % height) *w) + ((j + w)% w)]+
              m6*temp[ (((i + height) % height) *w) + ((j+3 + w)% w)]+
              m7*temp[ (((i+1 + height) % height) *w) + ((j-3 + w)% w)]+
              m8*temp[ (((i+1 + height) % height) *w) + ((j + w)% w)]+
              m9*temp[ (((i+1 + height) % height) *w) + ((j+3 + w)% w)];


      if(color<0)
        temp[ (((i + height) % height) *w) + ((j + w)% w)] = (char)0;
      else if(color>255)
        temp[ (((i + height) % height) *w) + ((j + w)% w)] = (char)255;
      else {
        temp[ (((i + height) % height) *w) + ((j + w)% w)] =(char)color;
      }
        j = j +1;


        //GREEN
        color = m1*temp[ (((i-1 + height) % height) *w) + ((j-3 + w)% w)]+
                m2*temp[ (((i-1 + height) % height) *w) + ((j + w)% w)]+
                m3*temp[ (((i-1 + height) % height) *w) + ((j+3 + w)% w)]+
                m4*temp[ (((i + height) % height) *w) + ((j-3 + w)% w)]+
                m5*temp[ (((i + height) % height) *w) + ((j + w)% w)]+
                m6*temp[ (((i + height) % height) *w) + ((j+3 + w)% w)]+
                m7*temp[ (((i+1 + height) % height) *w) + ((j-3 + w)% w)]+
                m8*temp[ (((i+1 + height) % height) *w) + ((j + w)% w)]+
                m9*temp[ (((i+1 + height) % height) *w) + ((j+3 + w)% w)];

     if(color<0)
       temp[ (((i + height) % height) *w) + ((j + w)% w)] = (char)0;
     else if(color>255)
       temp[ (((i + height) % height) *w) + ((j + w)% w)] = (char)255;
     else{
       temp[ (((i + height) % height) *w) + ((j + w)% w)] =(char)color;
     }
       j = j +1;

       //RED
       color = m1*temp[ (((i-1 + height) % height) *w) + ((j-3 + w)% w)]+
               m2*temp[ (((i-1 + height) % height) *w) + ((j + w)% w)]+
               m3*temp[ (((i-1 + height) % height) *w) + ((j+3 + w)% w)]+
               m4*temp[ (((i + height) % height) *w) + ((j-3 + w)% w)]+
               m5*temp[ (((i + height) % height) *w) + ((j + w)% w)]+
               m6*temp[ (((i + height) % height) *w) + ((j+3 + w)% w)]+
               m7*temp[ (((i+1 + height) % height) *w) + ((j-3 + w)% w)]+
               m8*temp[ (((i+1 + height) % height) *w) + ((j + w)% w)]+
               m9*temp[ (((i+1 + height) % height) *w) + ((j+3 + w)% w)];

    if(color<0)
      temp[ (((i + height) % height) *w) + ((j + w)% w)] = (char)0;
    else if(color>255)
      temp[ (((i + height) % height) *w) + ((j + w)% w)] = (char)255;
    else {
      temp[ (((i + height) % height) *w) + ((j + w)% w)] =(char)color;
    }
      j = j +1;

    }

       j=0;
       i=i+1;
 }

  //free(im->data);
  im->data = convertBack(temp,width, height,pad);

  return im;

}

#ifdef DEBUG_SHARPEN
int main(int argc, char const *argv[]) {

  IMAGE *im;
  im = LoadBitmapFile("image1.bmp");
  im = sharpen(im);
  WriteBitmapFile(im,"test1.bmp");

  return 0;
}
#endif
