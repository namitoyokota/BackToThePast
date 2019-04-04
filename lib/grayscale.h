#ifndef grayscale_h
#define grayscale_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../lib/image.h"

ImagePGM *extractRed(ImagePPM*);
ImagePGM *extractGreen(ImagePPM*);
ImagePGM *extractBlue(ImagePPM*);
ImagePGM *computeAverage(ImagePPM*);
ImagePGM *computeLightness(ImagePPM*);
ImagePGM *computeLuminosity(ImagePPM*);

#endif
