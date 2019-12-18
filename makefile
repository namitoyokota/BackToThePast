OBJS = ./src/main.o ./src/image.o ./src/grayscale.o ./src/contrast.o ./src/brightness.o ./src/blur.o
OOPTS = -Wall -Wextra -g -c
LOPTS = -Wall -Wextra -g

all: main

main : $(OBJS)
	gcc $(LOPTS) $(OBJS) -o ./bin/main

grayscale : 
	./bin/main red ./img/input/Strawberry.ppm ./img/output/Strawberry_Red.pgm
	./bin/main green ./img/input/Strawberry.ppm ./img/output/Strawberry_Green.pgm
	./bin/main blue ./img/input/Strawberry.ppm ./img/output/Strawberry_Blue.pgm
	./bin/main average ./img/input/Strawberry.ppm ./img/output/Strawberry_Average.pgm
	./bin/main lightness ./img/input/Strawberry.ppm ./img/output/Strawberry_Lightness.pgm
	./bin/main luminosity ./img/input/Strawberry.ppm ./img/output/Strawberry_Luminosity.pgm

main.o : ./src/main.c ./lib/main.h
		gcc $(OOPTS) ./src/main.c

image.o : ./src/image.c ./lib/image.h
		gcc $(OOPTS) ./src/image.c

grayscale.o : ./src/grayscale.c ./lib/grayscale.h
		gcc $(OOPTS) ./src/grayscale.c

contrast.o : ./src/constrast.c ./lib/contrast.h
		gcc $(OOPTS) ./src/contrast.c

brightness.o : ./src/brightness.c ./lib/brightness.h
		gcc $(OOPTS) ./src/brightness.c

blur.o : ./src/blur.c ./lib/blur.h
		gcc $(OOPTS) ./src/blur.c

setup : 
		mkdir -p bin
		mkdir -p ./img/output
help : 
clean :
		rm -f ./bin/main
		rm -f
