#include <iostream>
#include "Carro.cpp"
#include "Iluminacao.cpp"
#include "IluminacaoSpot.cpp"

using namespace std;

//Define cada carro inimigo.
class CarroInimigo{
    private:
        float PosX;
        float PosY;
        float PosZ;
        float velocidadeFixa;//Armazena a velocidade fixa do carro.
        float velocidadeRelativa;//Armazena a velocidade relativa do carro.
        float velocidadeMax;//Armazena a velocidade máxima do carro.

    //inicializa os membros PosX, PosY, PosZ com os valores passados como argumento.
    public:
        CarroInimigo(float PosX, float PosY, float PosZ){
            this->PosX = PosX;
            this->PosY = PosY;
            this->PosZ = PosZ;
            this->velocidadeFixa = 0.0;
        }

        //Calcula a velocidade relativa do carro.
        void DefineVeloFixa(float velocidade){
            if (velocidade > this->velocidadeMax){
                this->velocidadeFixa = velocidadeMax;
            }else{
                this->velocidadeFixa = velocidade;
            }
        }

        
        void DefineVeloRelativa(float velocidade, float MaxVelo){
            this->velocidadeRelativa = (this->velocidadeFixa-velocidade)/MaxVelo;
        }

        //Atualiza a posição do carro no eixo Y.
        void MoveCar(){
            this->PosY += this->velocidadeRelativa;
        }

        float getPosX(){
            return PosX;
        }

        float getPosY(){
            return PosY;
        }

        float getPosZ(){
            return PosZ;
        }

        float getVeloFixa(){
            return velocidadeFixa;
        }
        
        void setVeloMax(float velocidade){
            this->velocidadeMax = velocidade;
        }

        void setPosX(float PosX){
            this->PosX = PosX;
        }

        //Chama os métodos do carro para desenhar o carro inimigo.
        void CriarCarro(float RotacaoPneu){
            Carro Car = Carro(RotacaoPneu);
            Car.desCarro(1,1,1,PosX,PosY,PosZ);
            Car.desPneu(-0.15,0.352,0.115);
            Car.desPneu(-0.15,0.122,0.115);
        }
};