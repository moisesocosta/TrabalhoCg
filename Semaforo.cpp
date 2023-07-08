#ifndef Semaforo_H
#define Semaforo_H

#include <iostream>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <math.h>

// Classe para instanciar o semáforo que conterá as texturas "3"-"2"-"1"-"GO"
class Semaforo{
    private:
        float PosX; // Posição X do semáforo
        float PosY; // Posição Y do semáforo
        float PosZ; // Posição Z do semáforo

    public:
        // Construtor da classe Semaforo
        Semaforo(float posX, float posY, float posZ){
            PosX = posX;
            PosY = posY;
            PosZ = posZ;
        }

        // Desenha o cubo com a textura para representar o semáforo
        void Cubo(GLfloat X, GLfloat Y, GLfloat Z, GLuint text_ID){
            glColor3f(X, Y, Z); // Define a cor do cubo
            glBindTexture(GL_TEXTURE_2D, text_ID); // Associa a textura ao cubo
            glBegin(GL_QUADS); // Inicia o desenho do cubo
                glTexCoord2f(0.0, 0.0); glVertex3f(-1, -1, -1); // Define os vértices do cubo
                glTexCoord2f(1.0, 0.0); glVertex3f(1, -1, -1);
                glTexCoord2f(1.0, 1.0); glVertex3f(1, -1, 1);
                glTexCoord2f(0.0, 1.0); glVertex3f(-1, -1, 1);
            glEnd(); // Finaliza o desenho do cubo
            // Repete o mesmo processo para os outros lados do cubo
            glBegin(GL_QUADS);
                glTexCoord2f(0.0, 0.0); glVertex3f(-1, 1, -1);
                glTexCoord2f(1.0, 0.0); glVertex3f(1, 1, -1);
                glTexCoord2f(1.0, 1.0); glVertex3f(1, 1, 1);
                glTexCoord2f(0.0, 1.0); glVertex3f(-1, 1, 1);
            glEnd();
            glBegin(GL_QUADS);
                glTexCoord2f(0.0, 0.0); glVertex3f(1, -1, -1);
                glTexCoord2f(1.0, 0.0); glVertex3f(1, 1, -1);
                glTexCoord2f(1.0, 1.0); glVertex3f(1, 1, 1);
                glTexCoord2f(0.0, 1.0); glVertex3f(1, -1, 1);
            glEnd();
            glBegin(GL_QUADS);
                glTexCoord2f(0.0, 0.0); glVertex3f(-1, -1, -1);
                glTexCoord2f(1.0, 0.0); glVertex3f(-1, 1, -1);
                glTexCoord2f(1.0, 1.0); glVertex3f(-1, 1, 1);
                glTexCoord2f(0.0, 1.0); glVertex3f(-1, -1, 1);
            glEnd();
            glBegin(GL_QUADS);
                glVertex3f(-1, -1, -1);
                glVertex3f(1, -1, -1);
                glTexCoord2f(1.0, 1.0); glVertex3f(1, 1, -1);
                glTexCoord2f(0.0, 1.0); glVertex3f(-1, 1, -1);
            glEnd();
            glBegin(GL_QUADS);
                glVertex3f(-1, -1, 1);
                glVertex3f(1, -1, 1);
                glVertex3f(1, 1, 1);
                glVertex3f(-1, 1, 1);
            glEnd();
            glBindTexture(GL_TEXTURE_2D, 0); // Desassocia a textura do cubo
        }

        // Desenha o semáforo na posição definida, rotacionado para mostrar a textura de frente para a câmera
        void CriarSemaforoPartida(float rotacaoSemaforo, GLuint text_ID){
            glPushMatrix();
            glTranslatef(PosX, PosY, PosZ); // Translada o semáforo para a posição definida
            glRotatef(rotacaoSemaforo, 0, 0, 1); // Rotaciona o semáforo
            glScalef(2, 2, 1.5); // Redimensiona o semáforo
            Cubo(1, 1, 1, text_ID); // Desenha o corpo do semáforo com a textura definida
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Modo de renderização dos polígonos em linhas
            Cubo(0, 0, 0, text_ID); // Desenha o contorno do semáforo
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Modo de renderização dos polígonos preenchidos
            glPopMatrix();
        }
};

#endif
