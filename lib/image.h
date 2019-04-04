#ifndef image_h
#define image_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _pixel {
  int red;
  int green;
  int blue;
} Pixel;

typedef struct _imagePPM {
	char magic[3];  // magic identifier, "P3"
  int width;      // columns
  int height;     // rows
  int max_value;  // maximum intensity
  Pixel **pixels; // pixel data
} ImagePPM;

typedef struct _imagePGM {
	char magic[3];  // magic identifier, "P2"
  int width;      // columns
  int height;     // rows
  int max_value;  // maximum grayscale intensity
  int **pixels;   // grayscale pixel data
} ImagePGM;

ImagePPM *readPPM(char*);
int writePGM(ImagePGM*, char*);
void freeSpacePPM(ImagePPM*);
void freeSpacePGM(ImagePGM*);

#endif
