#ifndef IluminacaoSpot_H
#define IluminacaoSpot_H

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <math.h>

class IluminacaoSpot {
private:
    glm::vec3 posicao;
    glm::vec3 ambiente, difusa, especular;
    glm::vec3 posicaoApontaIluminacao;
    glm::vec3 posicaoCamera;
    glm::vec3 especularMaterial;
    glm::vec3 difusaMaterial;
    int anguloAbertura;

public:
    IluminacaoSpot(glm::vec3 posicao);
    glm::vec3 getPosicao();
    void setPosicao(glm::vec3 posicao);
    void setPosicaoAponta(glm::vec3 posicao);
    void setPosicaoCamera(glm::vec3 posicao);
    void setAmbiente(glm::vec3 ambiente);
    void setDifusa(glm::vec3 difusa);
    void setEspecular(glm::vec3 especular);
    void setEspecularMaterial(glm::vec3 especularMaterial);
    void setDifusaMaterial(glm::vec3 difusaMaterial);
    glm::vec3 ilumina(glm::vec3 pos, glm::vec3 normal, glm::vec3 color);
    int calculoDefPointSpot(glm::vec3 point1);
};

#endif
