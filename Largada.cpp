#include <iostream>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <math.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "FonteDeLuz.cpp"

using namespace std;
//Classe para instanciar a faixa de largada, e após passar uma vez pelo carro inimigo, se tornar a faixa de chegada
class Largada {
private:
    float PosX;
    float PosY;
    float PosZ;
    float velocidade;
    GLuint textID;

public:
    Largada(float PosX, float PosY, float PosZ)
        : PosX(PosX), PosY(PosY), PosZ(PosZ), velocidade(0.0), textID(0) {}

    //Definindo a velocidade do objeto em relação a velocidade do meu carro
    void DefineVelo(float velocidade, float MaxVelo) {
        this->velocidade = velocidade / (MaxVelo * 2);
    }

    //Fazendo a translação dele para sua posição correta
    void MoverObjetoOffPista() {
        PosY -= velocidade;
        if (PosY <= -40.0) {
            PosY += 80.0;
        }
    }

    //Ao passar pela primeira vez pelo carro, ela vai para a posição +600, assim tendo que fazer os carros percorrerem 600 para cruzar a faixa de chagada
    void MoverFaixaChegada() {
        PosY -= velocidade;
        if (PosY <= -40.0) {
            PosY += 640.0;
        }
    }

    //construtor, getters e setters
    const float& getPosX() const {
        return PosX;
    }

    const float& getPosY() const {
        return PosY;
    }

    const float& getPosZ() const {
        return PosZ;
    }

    void setPosX(const float& novoPosX) {
        PosX = novoPosX;
    }

    void setPosY(const float& novoPosY) {
        PosY = novoPosY;
    }

    void setPosZ(const float& novoPosZ) {
        PosZ = novoPosZ;
    }

    //Base do apoio da faixa
    void Desenhamastro(GLfloat x, GLfloat y, GLfloat z, GLfloat lado, GLfloat altura, GLfloat R, GLfloat G, GLfloat B) {
        glColor3f(R, G, B);
        glBegin(GL_QUADS);
        glVertex3f(0.5, 0.5, z);
        glVertex3f(-0.5, 0.5, z);
        glVertex3f(-0.5, -0.5, z);
        glVertex3f(0.5, -0.5, z);
        glEnd();
        glBegin(GL_QUAD_STRIP);
        glVertex3f(0.5, 0.5, z);
        glVertex3f(0.5, 0.5, altura);
        glVertex3f(-0.5, 0.5, z);
        glVertex3f(-0.5, 0.5, altura);
        glVertex3f(-0.5, -0.5, z);
        glVertex3f(-0.5, -0.5, altura);
        glVertex3f(0.5, -0.5, z);
        glVertex3f(0.5, -0.5, altura);
        glVertex3f(0.5, 0.5, z);
        glVertex3f(0.5, 0.5, altura);
        glEnd();
    }

    //Desenha o retangulo para a textura da largada
    void Retangulo(GLfloat Z, GLfloat R, GLfloat G, GLfloat B, GLuint text_ID) {
        glColor3f(R, G, B);
        glBindTexture(GL_TEXTURE_2D, text_ID);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0, 0.0); glVertex3f(0, 0, Z - 1);
        glTexCoord2f(1.0, 0.0); glVertex3f(50, 0, Z - 1);
        glTexCoord2f(1.0, 1.0); glVertex3f(50, 0, Z);
        glTexCoord2f(0.0, 1.0); glVertex3f(0, 0, Z);
        glEnd();
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    //Chamada para o desenho completo da largada
    void Faixa(GLfloat X, GLfloat Y, GLfloat Z, GLfloat lado, GLuint text_ID) {
        Desenhamastro(X, Y, Z, lado, 5, 1, 1, 1);
        Retangulo(5, 1, 1, 1, text_ID);
        glPushMatrix();
        glTranslatef(50, 0, 0);
        Desenhamastro(X, Y, Z, lado, 5, 1, 1, 1);
        glPopMatrix();
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        Desenhamastro(X, Y, Z, lado, 5, 0, 0, 0);
        Retangulo(5, 0, 0, 0, text_ID);
        glPushMatrix();
        glTranslatef(50, 0, 0);
        Desenhamastro(X, Y, Z, lado, 5, 0, 0, 0);
        glPopMatrix();
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

     //Desenha a faixa de largada no 0,0,0 e translada para a posição desejada
    void DesenharFaixa(GLuint text_ID) {
        glPushMatrix();
        glTranslatef(PosX, PosY, PosZ - 2.5);
        glScalef(0.2, 0.1, 1);
        Faixa(0, 0, 0, 0.1, text_ID);
        glPopMatrix();
    }
};
