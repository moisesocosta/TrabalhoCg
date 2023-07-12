#include <iostream>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <math.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "FonteDeLuz.cpp"

using namespace std;

class StaticObjetos {
public:
    void EstaticObjects(float X, float Y, GLuint text_ID_Chao, FonteDeLuz &phong) {

        // Define o modo de preenchimento dos polígonos(preenchimento completo)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glm::vec3 P,C;
        // Desenha o chão
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, text_ID_Chao);
        glm::vec3 cor = glm::vec3(1, 1, 1);
        glColor3f(cor.r, cor.g, cor.b);
        phong.setespecularidade(glm::vec3(0.2));
        for (float x = -60; x < 120; x += 20) {
            for (float y = -40; y < 60; y += 20) {
                glBegin(GL_QUADS);

                // Define a cor do quadrado
                P = glm::vec3((x),(y),(10));
                C = phong.iluminacao(P,glm::vec3(0.0,0.0,1.0),cor);
                glColor3f(C.r, C.g, C.b);
                // Define a coordenada de textura inferior esquerda
                glTexCoord2f(0.0, 0.0);
                // Define o vértice inferior esquerdo do quadrado
                glVertex3f(x, y, 10);

                // Define a cor do quadrado
                P = glm::vec3((x+20),(y),(10));
                C = phong.iluminacao(P,glm::vec3(0.0,0.0,1.0),cor);
                glColor3f(C.r, C.g, C.b);
                // Define a coordenada de textura inferior direita
                glTexCoord2f(X, 0.0);
                // Define o vértice inferior direito do quadrado
                glVertex3f(x + 20, y, 10);

                // Define a cor do quadrado
                P = glm::vec3((x+20),(y+20),(10));
                C = phong.iluminacao(P,glm::vec3(0.0,0.0,1.0),cor);
                glColor3f(C.r, C.g, C.b);
                // Define a coordenada de textura superior direita
                glTexCoord2f(X, Y);
                // Define o vértice superior direito do quadrado
                glVertex3f(x + 20, y + 20, 10);

                // Define a cor do quadrado
                P = glm::vec3((x),(y+20),(10));
                C = phong.iluminacao(P,glm::vec3(0.0,0.0,1.0),cor);
                glColor3f(C.r, C.g, C.b);
                // Define a coordenada de textura superior esquerda
                glTexCoord2f(0.0, Y);
                // Define o vértice superior esquerdo do quadrado
                glVertex3f(x, y + 20, 10);

                glEnd();
            }
        }
        glBindTexture(GL_TEXTURE_2D, 0);
        glPopMatrix();

        // Desenha a faixa laranja
        glPushMatrix();
        cor = glm::vec3(1, 0.6, 0);
        glColor3f(cor.r, cor.g, cor.b);
        phong.setespecularidade(glm::vec3(0.05));

        for (float x = 25; x < 35; x += 1) {
            for (float y = -40; y < 60; y += 0.5) {
                glBegin(GL_QUADS);

                // Define a cor do quadrado
                C = cor;
                glColor3f(C.r, C.g, C.b);
                // Define o vértice inferior esquerdo do quadrado
                glVertex3f(x, y, 10.03);
                // Define o vértice inferior direito do quadrado
                glVertex3f(x + 1, y, 10.03);
                // Define o vértice superior direito do quadrado
                glVertex3f(x + 1, y + 0.5, 10.03);
                // Define o vértice superior esquerdo do quadrado
                glVertex3f(x, y + 0.5, 10.03);

                glEnd();
            }
        }
        glPopMatrix();

    }
};