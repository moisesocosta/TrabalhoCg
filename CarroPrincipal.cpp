#include <iostream>
#include "Carro.cpp"

using namespace std;

//Define o carro principal.
class CarroPrincipal{
    private:
        float PosX;
        float PosY;
        float PosZ;
        float Velocidade;//Armazena a velocidade atual do carro.

    //inicializa os membros PosX, PosY, PosZ com os valores passados como argumento.
    public:
        CarroPrincipal(float PosX, float PosY, float PosZ, float velocidade){
            this->PosX = PosX;
            this->PosY = PosY;
            this->PosZ = PosZ;
            this->Velocidade = velocidade;
        }

        //Recebe a velocidade como argumento e atribui o valor à variável Velocidade. 
        //Verifica se a velocidade ultrapassa um limite máximo de 200.0 e se é menor ou igual a zero.
        void DefineVelo(float velocidade){
            this->Velocidade = velocidade;
            if (this->Velocidade > 200){
                this->Velocidade = 200.0;
            }
            if (this->Velocidade <= 0.0){
                this->Velocidade = 0.0;
            }
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

        float getVelocidade(){
            return Velocidade;
        }

        void setPosX(float PosX){
            this->PosX = PosX;
        }

        void setPosY(float PosY){
            this->PosY = PosY;
        }

        void setPosZ(float PosZ){
            this->PosZ = PosZ;
        }

        //Chama os métodos do carro para desenhar o carro principal.
        void CriarCarro(float RotacaoPneu){
            Carro Car = Carro(RotacaoPneu);
            Car.desCarro(1,0,0,PosX,PosY,PosZ);
            Car.desPneu(-0.15,0.352,0.115);
            Car.desPneu(-0.15,0.122,0.115);
        }
};