#ifndef Semaforo_H
#define Semaforo_H

#include <iostream>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <math.h>

class Semaforo {
private:
    float PosX;
    float PosY;
    float PosZ;

public:
    Semaforo(float PosX, float PosY, float PosZ);
    void Cubo(GLfloat X, GLfloat Y, GLfloat Z, GLuint text_ID);
    void drawSemaphore(float RotacaoSemaforo, GLuint text_ID);
};

#endif
