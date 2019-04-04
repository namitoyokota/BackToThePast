#include "../lib/image.h"

ImagePPM *readPPM(char *filename) {
  FILE *ImageFile=fopen(filename,"r");
  if (ImageFile == NULL) return 0;

  ImagePPM *pImagePPM = malloc(sizeof(ImagePPM));
  fscanf(ImageFile, "%s", pImagePPM->magic);
  fscanf(ImageFile, "%d", &pImagePPM->width);
  fscanf(ImageFile, "%d", &pImagePPM->height);
  fscanf(ImageFile, "%d", &pImagePPM->max_value);

  pImagePPM->pixels = malloc(sizeof(Pixel *) * pImagePPM->height);
  for (int i = 0; i < pImagePPM->height; i++) {
    pImagePPM->pixels[i] = malloc(sizeof(Pixel) * pImagePPM->width);
  }

  for (int j = 0; j < pImagePPM->height; j++) {
    for (int k = 0; k < pImagePPM->width; k++) {
      fscanf(ImageFile, "%d", &pImagePPM->pixels[j][k].red);
      fscanf(ImageFile, "%d", &pImagePPM->pixels[j][k].green);
      fscanf(ImageFile, "%d", &pImagePPM->pixels[j][k].blue);
    }
  }

  return pImagePPM;
}

int writePGM(ImagePGM *pImagePGM, char *filename) {

  FILE *ImageFile=fopen(filename,"w");
  if (ImageFile == NULL) return 0;
  fprintf(ImageFile, "%s %d %d %d\n", pImagePGM->magic, pImagePGM->width, pImagePGM->height, pImagePGM->max_value);
  for (int j = 0; j < pImagePGM->height; j++) {
    for (int k = 0; k < pImagePGM->width; k++) {
      fprintf(ImageFile, "%d ", pImagePGM->pixels[j][k]);
    }
    fprintf(ImageFile, "\n");
  }
  return 1;
}


void freeSpacePPM(ImagePPM *pImagePPM) {
  free(pImagePPM);
  return;
}

void freeSpacePGM(ImagePGM *pImagePGM) {
  free(pImagePGM);
  return;
}
