#ifndef main_h
#define main_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../lib/image.h"
#include "../lib/grayscale.h"
#include "../lib/contrast.h"
#include "../lib/brightness.h"
#include "../lib/blur.h"

char *operation[4] = {"blur", "brightness", "contast", "grayscale"};
char *blur[0] = {};
char *brightness[0] = {};
char *contrast[0] = {};
char *grayscale[6] = { "red", "green", "blue", "average", "lightness", "luminosity"};

int getMethodID(char*);

#endif
