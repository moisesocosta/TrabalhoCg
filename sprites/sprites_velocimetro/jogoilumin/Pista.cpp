#include <iostream>
#include <glm/glm.hpp>
#include <GL/gl.h>
#include <GL/glu.h> // Inclusão da biblioteca GLU
#include <glm/ext.hpp>
#include <GL/glut.h>

using namespace std;

// Classe para instanciar cada uma das faixas centrais que se movem
class Pista {
private:
    float PosX;
    float PosY;
    float PosZ;
    float velocidade;

public:
    Pista(float PosX, float PosY, float PosZ) {
        this->PosX = PosX;
        this->PosY = PosY;
        this->PosZ = PosZ;
        this->velocidade = 0.0; // Tem velocidade 0, seu movimento se dá somente em relação a velocidade relativa ao meu carro
    }

    // Funções para definir a velocidade relativa das faixas centrais, com a velocidade do carro principal
    void DefineVelo(float velocidade, float MaxVelo) {
        this->velocidade = velocidade / MaxVelo;
    }

    // Função para mover as faixas para suas posições corretas, a partir da movimentação do carro principal
    void MoverPista() {
        this->PosY -= this->velocidade;
        if (PosY <= -40.0) {
            PosY += 100.0;
        }
    }

    // Função para desenhar os obstáculos
    void DesenharObstaculos() const {
        glColor3f(1.0, 0.0, 0.0); // Cor vermelha para os obstáculos

        // Desenhar obstáculos retangulares
        glPushMatrix();
        glTranslatef(0.0, 0.3, 0.0);
        glScalef(0.5, 0.2, 1.0);
        glutSolidCube(1.0);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0.0, -0.3, 0.0);
        glScalef(0.5, 0.2, 1.0);
        glutSolidCube(1.0);
        glPopMatrix();

        // Desenhar obstáculos circulares
        const int numSegments = 20;
        const float radius = 0.15;
        const float angleStep = 2 * glm::pi<float>() / numSegments;

        for (int i = 0; i < numSegments; i++) {
            float angle = i * angleStep;
            float x = radius * cos(angle);
            float y = radius * sin(angle);

            glPushMatrix();
            glTranslatef(x, y, 0.0);
            glutSolidSphere(0.1, 20, 20);
            glPopMatrix();
        }

    }

    

    // Desenha as faixas centrais e obstáculos
    float CriarPista() const {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glPushMatrix();
        glTranslatef(this->PosX, this->PosY, this->PosZ);

        // Chamar a função para desenhar os obstáculos
        DesenharObstaculos();


        glBegin(GL_QUADS);

        // Faixa central laranja
        glColor3f(1.0, 0.5, 0.0); // Cor laranja
        for (float x = -0.25; x <= 0.25; x += 0.1) {
            for (float y = -1; y <= 1; y += 0.1) {void DesenharPedregulhos() const {
        glColor3f(0.5, 0.5, 0.5); // Cor cinza para os pedregulhos

        // Desenhar pedregulhos retangulares
        glPushMatrix();
        glTranslatef(-0.3, 0.0, 0.0);
        glScalef(0.1, 0.3, 1.0);
        glutSolidCube(1.0);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0.3, 0.0, 0.0);
        glScalef(0.1, 0.3, 1.0);
        glutSolidCube(1.0);
        glPopMatrix();

        // Desenhar pedregulhos circulares
        const int numSegments = 20;
        const float radius = 0.15;
        const float angleStep = 2 * glm::pi<float>() / numSegments;

        for (int i = 0; i < numSegments; i++) {
            float angle = i * angleStep;
            float x = radius * cos(angle);
            float y = radius * sin(angle);

            glPushMatrix();
            glTranslatef(x - 0.3, y, 0.0);
            glutSolidSphere(0.1, 20, 20);
            glPopMatrix();

            glPushMatrix();
            glTranslatef(x + 0.3, y, 0.0);
            glutSolidSphere(0.1, 20, 20);
            glPopMatrix();
        }
    }
                glVertex3f(x, y, 0);
            }
        }

        glEnd();
        glPopMatrix();

        return 0.0;
    }

     
};