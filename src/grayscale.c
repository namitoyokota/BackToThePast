#include "../lib/grayscale.h"

// grayscale = R
ImagePGM *extractRed(ImagePPM *pImagePPM) {

  ImagePGM *pImagePGM = malloc(sizeof(ImagePGM));
  strcpy(pImagePGM->magic, "P2");
  pImagePGM->width = pImagePPM->width;
  pImagePGM->height = pImagePPM->height;
  pImagePGM->max_value = pImagePPM->max_value;

  pImagePGM->pixels = malloc(sizeof(int*) * pImagePGM->height);
  for (int i = 0; i < pImagePGM->height; i++) {
    pImagePGM->pixels[i] = malloc(sizeof(int) * pImagePGM->width);
  }

  for (int j = 0; j < pImagePGM->height; j++) {
    for (int k = 0; k < pImagePGM->width; k++) {
      pImagePGM->pixels[j][k] = pImagePPM->pixels[j][k].red;
    }
  }

  return pImagePGM;
}

// grayscale = G
ImagePGM *extractGreen(ImagePPM *pImagePPM) {

  ImagePGM *pImagePGM = malloc(sizeof(ImagePGM));
  strcpy(pImagePGM->magic, "P2");
  pImagePGM->width = pImagePPM->width;
  pImagePGM->height = pImagePPM->height;
  pImagePGM->max_value = pImagePPM->max_value;

  pImagePGM->pixels = malloc(sizeof(int*) * pImagePGM->height);
  for (int i = 0; i < pImagePGM->height; i++) {
    pImagePGM->pixels[i] = malloc(sizeof(int) * pImagePGM->width);
  }

  for (int j = 0; j < pImagePGM->height; j++) {
    for (int k = 0; k < pImagePGM->width; k++) {
      pImagePGM->pixels[j][k] = pImagePPM->pixels[j][k].green;
    }
  }

  return pImagePGM;
}

// grayscale = B
ImagePGM *extractBlue(ImagePPM *pImagePPM) {

  ImagePGM *pImagePGM = malloc(sizeof(ImagePGM));
  strcpy(pImagePGM->magic, "P2");
  pImagePGM->width = pImagePPM->width;
  pImagePGM->height = pImagePPM->height;
  pImagePGM->max_value = pImagePPM->max_value;

  pImagePGM->pixels = malloc(sizeof(int*) * pImagePGM->height);
  for (int i = 0; i < pImagePGM->height; i++) {
    pImagePGM->pixels[i] = malloc(sizeof(int) * pImagePGM->width);
  }

  for (int j = 0; j < pImagePGM->height; j++) {
    for (int k = 0; k < pImagePGM->width; k++) {
      pImagePGM->pixels[j][k] = pImagePPM->pixels[j][k].blue;
    }
  }

  return pImagePGM;
}
// grayscale = (R + G + B) / 3
ImagePGM *computeAverage(ImagePPM *pImagePPM) {

  ImagePGM *pImagePGM = malloc(sizeof(ImagePGM));
  strcpy(pImagePGM->magic, "P2");
  pImagePGM->width = pImagePPM->width;
  pImagePGM->height = pImagePPM->height;
  pImagePGM->max_value = pImagePPM->max_value;

  pImagePGM->pixels = malloc(sizeof(int*) * pImagePGM->height);
  for (int i = 0; i < pImagePGM->height; i++) {
    pImagePGM->pixels[i] = malloc(sizeof(int) * pImagePGM->width);
  }

  for (int j = 0; j < pImagePGM->height; j++) {
    for (int k = 0; k < pImagePGM->width; k++) {
      pImagePGM->pixels[j][k] = (pImagePPM->pixels[j][k].red + pImagePPM->pixels[j][k].green + pImagePPM->pixels[j][k].blue);
      pImagePGM->pixels[j][k] /= 3;
    }
  }

  return pImagePGM;
}

// grayscale = (max(R, G, B) + min(R, G, B)) / 2
ImagePGM *computeLightness(ImagePPM *pImagePPM) {

  ImagePGM *pImagePGM = malloc(sizeof(ImagePGM));
  strcpy(pImagePGM->magic, "P2");
  pImagePGM->width = pImagePPM->width;
  pImagePGM->height = pImagePPM->height;
  pImagePGM->max_value = pImagePPM->max_value;

  pImagePGM->pixels = malloc(sizeof(int*) * pImagePGM->height);
  for (int i = 0; i < pImagePGM->height; i++) {
    pImagePGM->pixels[i] = malloc(sizeof(int) * pImagePGM->width);
  }

  for (int j = 0; j < pImagePGM->height; j++) {
    for (int k = 0; k < pImagePGM->width; k++) {
      int max = 0, min = pImagePGM->max_value;
      if (pImagePPM->pixels[j][k].red > max) max = pImagePPM->pixels[j][k].red;
      if (pImagePPM->pixels[j][k].green > max) max = pImagePPM->pixels[j][k].green;
      if (pImagePPM->pixels[j][k].blue > max) max = pImagePPM->pixels[j][k].blue;
      if (pImagePPM->pixels[j][k].red < min) min = pImagePPM->pixels[j][k].red;
      if (pImagePPM->pixels[j][k].green < min) min = pImagePPM->pixels[j][k].green;
      if (pImagePPM->pixels[j][k].blue < min) min = pImagePPM->pixels[j][k].blue;
      pImagePGM->pixels[j][k] = (max + min) / 2;
    }
  }

  return pImagePGM;
}

// grayscale = 0.21 R + 0.72 G + 0.07 B
ImagePGM *computeLuminosity(ImagePPM *pImagePPM) {

  ImagePGM *pImagePGM = malloc(sizeof(ImagePGM));
  strcpy(pImagePGM->magic, "P2");
  pImagePGM->width = pImagePPM->width;
  pImagePGM->height = pImagePPM->height;
  pImagePGM->max_value = pImagePPM->max_value;

  pImagePGM->pixels = malloc(sizeof(int*) * pImagePGM->height);
  for (int i = 0; i < pImagePGM->height; i++) {
    pImagePGM->pixels[i] = malloc(sizeof(int) * pImagePGM->width);
  }

  for (int j = 0; j < pImagePGM->height; j++) {
    for (int k = 0; k < pImagePGM->width; k++) {
      pImagePGM->pixels[j][k] = pImagePPM->pixels[j][k].red * 0.21;
      pImagePGM->pixels[j][k] += pImagePPM->pixels[j][k].green * 0.72;
      pImagePGM->pixels[j][k] += pImagePPM->pixels[j][k].blue * 0.07;
      pImagePGM->pixels[j][k] /= 3;
    }
  }

  return pImagePGM;
}
