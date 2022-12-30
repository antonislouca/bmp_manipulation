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
 * @file bmpengine.c
 * The client module of the program contians the main function, reads, writes
 * the bmp images and calls the according functions of the program.
 *  Created on: Nov 18, 2019
 *  Author: Antonis Louca
 *
 *
 */
#include "bmplib.h"
#include "string.h"

/**
 *
 *@brief the main functions of the program calls every function and organizes
 *bmp image processes. Shows errors that may occur.
 *
 * @param argc number of arguments
 * @param argv arguments for main
 * @return should not return anything
 *
 */
public int main(int argc, char **argv) {

	printf(
			" bmpengine.c Copyright (C) 2019 Antonis Louca and Andreas Hadjivasili\n"
					"This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.\n"
					"This is free software, and you are welcome to redistribute it"
					"under certain conditions; type `show c' for details.\n\n");
	if (argc <= 2) {
		printf("Few input arguments.\n");
		correctUsage();
		exit(-1);
	}
	int option = 0;

	if (strcmp(argv[1], "-list") == 0) {
		option = 1;
	} else if (strcmp(argv[1], "-hflip") == 0) {
		option = 2;
	} else if (strcmp(argv[1], "-vflip") == 0) {
		option = 3;
	} else if (strcmp(argv[1], "-right90") == 0) {
		option = 4;
	} else if (strcmp(argv[1], "-left90") == 0) {
		option = 5;
	} else if (strcmp(argv[1], "-zoomin") == 0) {
		option = 6;
	} else if (strcmp(argv[1], "-zoomout") == 0) {
		option = 7;
	} else if (strcmp(argv[1], "-gray") == 0) {
		option = 8;
	} else if (strcmp(argv[1], "-sharpen") == 0) {
		option = 9;
	} else {
		correctUsage();
		exit(-1);
	}

	switch (option) {
	case 1:
		for (int i = 2; i < argc; i++) {
			IMAGE *img = LoadBitmapFile(argv[i]);
			if (img != NULL) {
				listfun(img);
				freeImg(img);
			}
		}
		break;
	case 2:
		for (int i = 2; i < argc; i++) {
			IMAGE *img = LoadBitmapFile(argv[i]);
			char *name = (char*) calloc(1,(6 + strlen(argv[i]) + 1));
			if (img != NULL) {
				horizontal_flip(img);
				strcpy(name, "hflip-");
				strcat(name, argv[i]);
				WriteBitmapFile(img, name);
				freeImg(img);
				free(name);
			} else {
				correctUsage();
			}

		}

		break;
	case 3:
		for (int i = 2; i < argc; i++) {
			IMAGE *img = LoadBitmapFile(argv[i]);
			char *name = (char*) calloc(1, (6 + strlen(argv[i]) + 1));
			if (img != NULL) {
				vertical_flip(img);
				strcpy(name, "vflip-");
				strcat(name, argv[i]);
				WriteBitmapFile(img, name);
				freeImg(img);
				free(name);
			} else {
				correctUsage();
			}

		}

		break;
	case 4:
		for (int i = 2; i < argc; i++) {
			IMAGE *img = LoadBitmapFile(argv[i]);
			char *name = (char*) calloc(1,(8 + strlen(argv[i]) + 1));
			if (img != NULL) {
				Rotate_Right(img);
				strcpy(name, "right90-");
				strcat(name, argv[i]);
				WriteBitmapFile(img, name);
				freeImg(img);
				free(name);
			} else {
				correctUsage();
			}

		}

		break;
	case 5:
		for (int i = 2; i < argc; i++) {
			IMAGE *img = LoadBitmapFile(argv[i]);
			char *name = (char*) calloc(1,(7 + strlen(argv[i]) + 1));
			if (img != NULL) {
				Rotate_Left(img);
				strcpy(name, "left90-");
				strcat(name, argv[i]);
				WriteBitmapFile(img, name);
				freeImg(img);
				free(name);
			} else {
				correctUsage();
			}

		}

		break;
	case 6:
		for (int i = 2; i < argc; i++) {
			IMAGE *img = LoadBitmapFile(argv[i]);
			char *name = (char*) calloc(1,(7 + strlen(argv[i]) + 1));
			if (img != NULL) {
				zoomIn(img);
				strcpy(name, "zoomIn-");
				strcat(name, argv[i]);
				WriteBitmapFile(img, name);
				freeImg(img);
				free(name);
			} else {
				correctUsage();
			}

		}

		break;
	case 7:

		for (int i = 2; i < argc; i++) {

			IMAGE *img = LoadBitmapFile(argv[i]);
			char *name =  calloc(1,(8 + strlen(argv[i]) +1));
			if (img != NULL) {
				zoomOut(img);
				strcpy(name, "zoomOut-");
				strcat(name, argv[i]);
//				for (int i = 0;
//						i < img2->bmpInfo.biWidth * img2->bmpInfo.biHeight * 3;
//						i += 3) {
//					printf("%u %u %u \n", img2->data[i], img2->data[i + 1],
//							img2->data[i + 2]);
//				}
				WriteBitmapFile(img, name);
				freeImg(img);
				free(name);
			} else {
				correctUsage();
			}

		}

		break;
	case 8:
		for (int i = 2; i < argc; i++) {
			IMAGE *img = LoadBitmapFile(argv[i]);
			char *name = (char*) calloc(1,(6 + strlen(argv[i]) + 1));
			if (img != NULL) {
				grayscale(img);
				strcpy(name, "gray-");
				strcat(name, argv[i]);
				WriteBitmapFile(img, name);
				freeImg(img);
				free(name);
			} else {
				correctUsage();
			}

		}

		break;
	case 9:
		for (int i = 2; i < argc; i++) {
			IMAGE *img = LoadBitmapFile(argv[i]);
			char *name = (char*) calloc(1,(8 + strlen(argv[i]) + 1));
			if (img != NULL) {
				sharpen(img);
				strcpy(name, "sharpen-");
				strcat(name, argv[i]);
				WriteBitmapFile(img, name);
				freeImg(img);
				free(name);
			} else {
				correctUsage();
			}

		}

		break;
	}

}
