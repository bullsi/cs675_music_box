#include <GL/glut.h>
#include <stdio.h>
#include <iostream>

using namespace std;

struct Image {
    unsigned long sizeX;
    unsigned long sizeY;
    char *data;
};

int ImageLoad(const char *filename, Image *image);

void LoadGLTextures(const char* filename, GLuint& texture);
