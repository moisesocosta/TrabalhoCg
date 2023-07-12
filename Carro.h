#ifndef Carro_H
#define Carro_H

#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <math.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "FonteDeLuz.cpp"

class Carro {
private:
    float RotacaoPneu;

public:
    Carro(float RotacaoPneu);

    void desCircunferencia(GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLfloat faces, GLfloat altura);
    void desPneu(GLfloat X, GLfloat Y, GLfloat Z);
    void desCarro(int R, int G, int B, FonteDeLuz & phong,float PosX, float PosY, float PosZ);
};

#endif