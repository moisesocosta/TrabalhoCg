#include <iostream>
#include <glm/glm.hpp>
#include <GL/gl.h>
#include <GL/glu.h>
#include <glm/ext.hpp>
#include <GL/glut.h>

using namespace std;

// Definição da classe Pista
class Pista {
private:
    float PosX;         // Coordenada X da pista
    float PosY;         // Coordenada Y da pista
    float PosZ;         // Coordenada Z da pista
    float velocidade;   // Velocidade da pista

public:

    Pista(float PosX, float PosY, float PosZ) {
            this->PosX = PosX;
            this->PosY = PosY;
            this->PosZ = PosZ;
            this->velocidade = 0.0;
    }

        // Função para definir a velocidade da pista
    void DefineVelo(float velocidade, float MaxVelo) {
        this->velocidade = velocidade / MaxVelo;
    }

        // Função para mover a pista
    void MoverPista() {
            this->PosY -= this->velocidade;
            if (PosY <= -40.0) {
                PosY += 100.0;
            }
    }

    // Função para criar e desenhar a pista
    float CriarPista() const {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glPushMatrix();
            glTranslatef(this->PosX, this->PosY, this->PosZ);

            // Desenhar pista
            glColor3f(0.0, 0.0, 0.0); // Define a cor da pista
            glBegin(GL_QUADS);
            // Loop para criar os quadrados que formam a pista
            for (float x = -0.25; x <= 0.25; x += 0.1) {
                for (float y = -1; y <= 1; y += 0.1) {
                    glVertex3f(x, y, 0);
                }
            }
            glEnd();

            glPopMatrix();
            return 0.0;
        }
};