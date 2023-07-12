#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <math.h>

#ifndef FonteDeLuz_H
#define FonteDeLuz_H

//Função que calcula a cor dos objetos do cenário depois usando o modelo de iluminação phong
class FonteDeLuz {
private:
    glm::vec3 pontual;                    //Fonte de luz pontual
    glm::vec3 ambiente, difusa, especular;//Componentes de iluminação
    glm::vec3 posCamera;                  //Posição da câmera para a especular ser calculada
    glm::vec3 especularidade;             //Característica especular dos objetos da cena

public:
    FonteDeLuz(const glm::vec3& pontual)
        : pontual(pontual),
          ambiente(0.6),
          difusa(1.0),
          especular(1.0),
          especularidade(0.0) {}

    //construtor, getters e setters
    const glm::vec3& getpontual() const {
        return pontual;
    }

    void setpontual(const glm::vec3& novapontual) {
        pontual = novapontual;
    }

    void setposCamera(const glm::vec3& novapontual) {
        posCamera = novapontual;
    }

    void setAmbiente(const glm::vec3& novaAmbiente) {
        ambiente = glm::clamp(novaAmbiente, glm::vec3(0), glm::vec3(1));
    }

    void setDifusa(const glm::vec3& novaDifusa) {
        difusa = glm::clamp(novaDifusa, glm::vec3(0), glm::vec3(1));
    }

    void setEspecular(const glm::vec3& novaEspecular) {
        especular = glm::clamp(novaEspecular, glm::vec3(0), glm::vec3(1));
    }

    void setespecularidade(const glm::vec3& novaespecularidade) {
        especularidade = novaespecularidade;
    }

    //Método que calcula a cor resultante em um ponto específico,
    //levando em consideração a posição, a normal e a cor do ponto.
    glm::vec3 iluminacao(const glm::vec3& pos, const glm::vec3& normal, const glm::vec3& cor) {
        glm::vec3 N = glm::normalize(normal);
        glm::vec3 L = glm::normalize(pontual - pos);
        glm::vec3 V = glm::normalize(posCamera - pos);
        glm::vec3 R = glm::reflect(-L, N);

        float diffuseFactor = glm::max(glm::dot(L, N), 0.0f);
        float specularFactor = glm::max(glm::dot(V, R), 0.0f);

        glm::vec3 ambienteFonteDeLuz = ambiente * glm::vec3(0.2);
        glm::vec3 difusaFonteDeLuz = difusa * glm::clamp(diffuseFactor, 0.2f, 1.0f) * cor;
        glm::vec3 especularFonteDeLuz = especular * glm::pow(specularFactor, 16.0f) * especularidade;

        return ambienteFonteDeLuz + difusaFonteDeLuz + especularFonteDeLuz;
    }

    //Método que faz o calculo da nromal.
    glm::vec3 normal(const glm::vec3& ponto1, const glm::vec3& ponto2, const glm::vec3& ponto3) {
        glm::vec3 V1 = ponto2 - ponto1;
        glm::vec3 V2 = ponto3 - ponto1;
        glm::vec3 normal = glm::normalize(glm::cross(V1, V2));
        return normal;
    }
};

#endif
