#include <iostream>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <math.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

using namespace std;

class Largada {
private:
    float PosX;
    float PosY;
    float PosZ;
    float velocidade;
    GLuint textID;

public:

    // Construtor da classe Largada
    Largada(float PosX, float PosY, float PosZ)
        : PosX(PosX), PosY(PosY), PosZ(PosZ), velocidade(0.0), textID(0) {}

    // Função para definir a velocidade do objeto com base na velocidade máxima
    void DefineVelo(float velocidade, float MaxVelo) {
        // Normaliza a velocidade e atribui ao atributo velocidade
        this->velocidade = velocidade / (MaxVelo * 2);
    }

    // Função para mover o objeto fora da pista
    void MoverObjetoOffPista() {
        // Diminui a posição Y do objeto com base na velocidade
        PosY -= velocidade;
        
        // Verifica se a posição Y ficou menor ou igual a -40.0
        // Se sim, reposiciona o objeto no topo da pista, adicionando 80.0 à posição Y
        if (PosY <= -40.0) {
            PosY += 80.0;
        }
    }

    // Função para mover o objeto ao longo da faixa de chegada
    void MoverFaixaChegada() {
        // Diminui a posição Y do objeto com base na velocidade
        PosY -= velocidade;
        
        // Verifica se a posição Y ficou menor ou igual a -40.0
        // Se sim, reposiciona o objeto no topo da faixa de chegada, adicionando 640.0 à posição Y
        if (PosY <= -40.0) {
            PosY += 640.0;
        }
    }

    // Função para obter a posição X do objeto
    float getPosX() const {
        return PosX;
    }

    // Função para obter a posição Y do objeto
    float getPosY() const {
        return PosY;
    }

    // Função para obter a posição Z do objeto
    float getPosZ() const {
        return PosZ;
    }

    // Função para desenhar um mastro com dimensões e cor especificadas
    void Desenhamastro(GLfloat x, GLfloat y, GLfloat z, GLfloat lado, GLfloat altura, GLfloat R, GLfloat G, GLfloat B) {
        // Define a cor do mastro
        glColor3f(R, G, B);
        
        // Desenha a face frontal do mastro
        glBegin(GL_QUADS);
        glVertex3f(0.5, 0.5, z);
        glVertex3f(-0.5, 0.5, z);
        glVertex3f(-0.5, -0.5, z);
        glVertex3f(0.5, -0.5, z);
        glEnd();
        
        // Desenha os lados do mastro
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

    // Função para desenhar um retângulo com uma textura específica
    void Retangulo(GLfloat Z, GLfloat R, GLfloat G, GLfloat B, GLuint text_ID) {
        // Define a cor do retângulo
        glColor3f(R, G, B);
        
        // Vincula a textura com o ID especificado
        glBindTexture(GL_TEXTURE_2D, text_ID);
        
        // Desenha o retângulo usando coordenadas de textura
        glBegin(GL_QUADS);
        glTexCoord2f(0.0, 0.0); glVertex3f(0, 0, Z - 1);
        glTexCoord2f(1.0, 0.0); glVertex3f(50, 0, Z - 1);
        glTexCoord2f(1.0, 1.0); glVertex3f(50, 0, Z);
        glTexCoord2f(0.0, 1.0); glVertex3f(0, 0, Z);
        glEnd();
        
        // Desvincula a textura
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    // Função para desenhar uma faixa com uma textura específica

    void Faixa(GLfloat X, GLfloat Y, GLfloat Z, GLfloat lado, GLuint text_ID) {
        // Desenha o mastro da faixa com as dimensões e cor especificadas
        Desenhamastro(X, Y, Z, lado, 5, 1, 1, 1);
        // Desenha a parte retangular da faixa usando a textura especificada
        Retangulo(5, 1, 1, 1, text_ID);
        
        // Translada as coordenadas para desenhar o segundo mastro
        glPushMatrix();
        glTranslatef(50, 0, 0);
        Desenhamastro(X, Y, Z, lado, 5, 1, 1, 1);
        glPopMatrix();
        // Define o modo de polígono para desenhar o contorno da faixa
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        // Desenha o mastro para o contorno da faixa
        Desenhamastro(X, Y, Z, lado, 5, 0, 0, 0);
        // Desenha a parte retangular do contorno usando a cor preta
        Retangulo(5, 0, 0, 0, text_ID);
        
        // Translada as coordenadas para desenhar o segundo mastro do contorno
        glPushMatrix();
        glTranslatef(50, 0, 0);
        Desenhamastro(X, Y, Z, lado, 5, 0, 0, 0);
        glPopMatrix();
        
        // Restaura o modo de polígono para preenchimento para as demais operações de desenho
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    // Função para desenhar a faixa de largada com a textura especificada
    void DesenharFaixa(GLuint text_ID) {
        // Translada as coordenadas para a posição da faixa de largada
        glPushMatrix();
        glTranslatef(PosX, PosY, PosZ - 2.5);
        glScalef(0.2, 0.1, 1);
        
        // Desenha a faixa de largada chamando a função Faixa
        Faixa(0, 0, 0, 0.1, text_ID);
        
        // Restaura a matriz de transformação anterior
        glPopMatrix();
    }
};
