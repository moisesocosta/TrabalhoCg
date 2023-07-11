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
    Buraco(float x, float y, float z, float tamanho, GLuint tex) {
        posX = x;
        posY = y;
        posZ = z;
        this->tamanho = tamanho;
        textura = tex;
    }

    void DesenharBuraco() {
        glColor3f(1.0, 1.0, 1.0);
        glBindTexture(GL_TEXTURE_2D, textura);
        // Desenhe o buraco usando quadriláteros
        glBegin(GL_QUADS);
        glTexCoord2f(0.0, 0.0);
        glVertex3f(posX - tamanho, posY - tamanho, posZ);
        glTexCoord2f(1.0, 0.0);
        glVertex3f(posX + tamanho, posY - tamanho, posZ);
        glTexCoord2f(1.0, 1.0);
        glVertex3f(posX + tamanho, posY + tamanho, posZ);
        glTexCoord2f(0.0, 1.0);
        glVertex3f(posX - tamanho, posY + tamanho, posZ);
        glEnd();
        glBindTexture(GL_TEXTURE_2D, 0);
    }

};

#endif