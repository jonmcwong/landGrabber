#ifndef IMAGE_H
#define IMAGE_H

struct segment {
	char * data; //is rows * cols
	static unsigned short rows;
	static unsigned short cols;

	struct segment * up;
	struct segment * down;
	struct segment * left;
	struct segment * right;
};

struct image {
	struct segment * map; //is a 2D cyclic array of segment pointers. is NULL when doesn't exist
}

void generateMap();		//generates empty segments given dimensions of image;

char * fetchArea(); //called by draw to get data for certain area of image. returns string of image within mask

void setChar(char data, int x, int y, struct image * pic); //sets the character indexed by x and y in image to data

#endif