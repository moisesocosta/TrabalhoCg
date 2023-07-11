#ifndef Buraco_H
#define Buraco_H

#include <iostream>
#include <glm/glm.hpp>
#include <GL/gl.h>
#include <GL/glu.h>
#include <glm/ext.hpp>
#include <GL/glut.h>

class Buraco {
private:
    float posX;
    float posY;
    float posZ;
    float tamanho;
    GLuint textura;

public:
    Buraco(float x, float y, float z, float tamanho, GLuint tex);
    void DesenharBuraco();
};

#endif