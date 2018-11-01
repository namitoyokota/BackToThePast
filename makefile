all:
	gcc main.c
	./a.out red Strawberry.ppm Strawberry_Red.pgm
	./a.out green Strawberry.ppm Strawberry_Green.pgm
	./a.out blue Strawberry.ppm Strawberry_Blue.pgm
	./a.out average Strawberry.ppm Strawberry_Average.pgm
	./a.out lightness Strawberry.ppm Strawberry_Lightness.pgm
	./a.out luminosity Strawberry.ppm Strawberry_Luminosity.pgm
