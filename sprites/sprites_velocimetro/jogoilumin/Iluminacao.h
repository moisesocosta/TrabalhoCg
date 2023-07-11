#ifndef Iluminacao_H
#define Iluminacao_H

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <math.h>

class Iluminacao {
private:
    glm::vec3 posicao;
    glm::vec3 ambiente, difusa, especular;
    glm::vec3 posicaoCamera;
    glm::vec3 especularMaterial;

public:
    Iluminacao(glm::vec3 posicao);
    glm::vec3 getPosicao();
    void setPosicao(glm::vec3 posicao);
    void setPosicaoCamera(glm::vec3 posicao);
    void setAmbiente(glm::vec3 ambiente);
    void setDifusa(glm::vec3 difusa);
    void setEspecular(glm::vec3 especular);
    void setEspecularMaterial(glm::vec3 especularMaterial);
    glm::vec3 ilumina(glm::vec3 pos, glm::vec3 normal, glm::vec3 color);
    glm::vec3 calculoNormal(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3);
};

#endif