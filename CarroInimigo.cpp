#include <iostream>
#include "Carro.cpp"
#include "FonteDeLuz.cpp"

using namespace std;

// Classe para instanciar cada um dos carros inimigos
class CarroInimigo {
private:
    float PosX;
    float PosY;
    float PosZ;
    float velocidadeFixa;        // Velocidade que vai ser somada com a aceleração do carro até a velocidade máxima
    float velocidadeRelativa;    // Vai servir para determinar a nova Posição, pois na velocidade relativa se sabe se o carro inimigo vai se mover para trás ou para frente do carro principal
    float velocidadeMax;         // Velocidade máxima do carro inimigo


public:
    CarroInimigo(float PosX, float PosY, float PosZ) : PosX(PosX), PosY(PosY), PosZ(PosZ), velocidadeFixa(0.0) {}

    // Determina a velocidade atual do carro inimigo, que vai variar com a aceleração até a velocidade máxima
    void DefineVeloFixa(float velocidade) {
        if (velocidade > velocidadeMax) {
            velocidadeFixa = velocidadeMax;
        } else {
            velocidadeFixa = velocidade;
        }
    }

    // Funções para definir a velocidade relativa do carro inimigo
    void DefineVeloRelativa(float velocidade, float MaxVelo) {
        velocidadeRelativa = (velocidadeFixa - velocidade) / MaxVelo;
    }

    // Função para mover os carros inimigos para suas Posições corretas, a partir da velocidade relativa
    void MoveCar() {
        PosY += velocidadeRelativa;
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

    const float& getVeloFixa() const {
        return velocidadeFixa;
    }

    void setVeloMax(const float& velocidade) {
        velocidadeMax = velocidade;
    }

    void setPosX(const float& novoPosX) {
        PosX = novoPosX;
    }

    // Comando para desenhar os carros + phong
    void CriarCarro(float RotacaoPneu, FonteDeLuz &phong) {
        Carro Car(RotacaoPneu);
        Car.desCarro(0, 0, 1,phong, PosX, PosY, PosZ);
        Car.desPneu(-0.15, 0.352, 0.115);
        Car.desPneu(-0.15, 0.122, 0.115);
    }
};
