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

ImagePPM *readPPM(char *filename) {

  FILE *ImageFile=fopen(filename,"r");

  // image not found
  if (ImageFile == NULL) {
    return 0;
  }

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

void freeSpacePPM(ImagePPM *pImagePPM) {
  free(pImagePPM);
  return;
}

void freeSpacePGM(ImagePGM *pImagePGM) {
  free(pImagePGM);
  return;
}
