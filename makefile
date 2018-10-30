all:
	gcc main.c
	./a.out red Strawberry.ppm Strawberry1.pgm
	./a.out green Strawberry.ppm Strawberry2.pgm
	./a.out blue Strawberry.ppm Strawberry3.pgm
	./a.out average Strawberry.ppm Strawberry4.pgm
	./a.out lightness Strawberry.ppm Strawberry5.pgm
	./a.out luminosity Strawberry.ppm Strawberry6.pgm
