#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <math.h>
#ifndef IluminacaoSpot_H //Header guards para nao ocorrer redefinição e evitar erro na compilação.
#define IluminacaoSpot_H


class IluminacaoSpot{
    private:
        glm::vec3 posicao; //Posição da luz                
        glm::vec3 ambiente, difusa, especular; //As cores de iluminação ambiente.
        glm::vec3 posicaoApontaIluminacao; //Posição para onde a luz focal aponta.       
        glm::vec3 posicaoCamera;//A posição da câmera.              
        glm::vec3 especularMaterial; //As propriedades especulares do material.           
        glm::vec3 difusaMaterial;//As propriedades difusas do material.         
        int anguloAbertura;//Ângulo de abertura do foco da luz.

    //Inicializa os membros da classe com valores padrão.   
    public:
        IluminacaoSpot(glm::vec3 posicao){
            this->posicao = posicao;
            ambiente  = glm::vec3(0.1);
            difusa    = glm::vec3(0.8,0.8,0.0); 
            especular = glm::vec3(0.8,0.8,0.0);
            especularMaterial = glm::vec3(0.1);
            anguloAbertura = 20;
        }

        glm::vec3 getPosicao(){
            return posicao;
        }

        void setPosicao(glm::vec3 posicao){
            this->posicao = posicao;
        }

        void setPosicaoAponta(glm::vec3 posicao){
            this->posicaoApontaIluminacao = posicao;
        }

        void setPosicaoCamera(glm::vec3 posicao){
            this->posicaoCamera = posicao;
        }

        void setAmbiente(glm::vec3 ambiente){
            this->ambiente = glm::clamp(ambiente, glm::vec3(0), glm::vec3(1));
        }

        void setDifusa(glm::vec3 difusa){
            this->difusa = glm::clamp(difusa, glm::vec3(0), glm::vec3(1));
        }

        void setEspecular(glm::vec3 especular){
            this->especular = glm::clamp(especular, glm::vec3(0), glm::vec3(1));
        }

        void setEspecularMaterial(glm::vec3 especularMaterial){
            this->especularMaterial = especularMaterial;
        }

        void setDifusaMaterial(glm::vec3 difusaMaterial){
            this->difusaMaterial = difusaMaterial;
        }

        //Realiza o cálculo da iluminação para um determinado ponto em um objeto.
        glm::vec3 ilumina(glm::vec3 pos, glm::vec3 normal, glm::vec3 color){
            glm::vec3 Ia = this->ambiente;
            glm::vec3 Id = this->difusa;
            glm::vec3 Is = this->especular;

            
            glm::vec3 N = glm::normalize(normal);
            glm::vec3 L = glm::normalize(posicao - pos);
            
            glm::vec3 V = glm::normalize(posicaoCamera - pos);
            glm::vec3 R = 2*(glm::dot(N,L))*(N-L);
            float K = glm::dot(V,R);

            
            glm::vec3 Ra = glm::vec3(0.2);
            glm::vec3 Rd = glm::max(glm::dot(L,N),0.0f) * (difusaMaterial); 
            float Rs;
            if (K < 0){
                Rs = pow(0,2);
            }else{
                Rs = pow(K,2);
            }

            
            glm::vec3 ambiente = Ia * Ra;
            glm::vec3 difusa   = Id * Rd;
            glm::vec3 especular   = Is * Rs * especularMaterial;

            
            glm::vec3 corFinal = ambiente + difusa+ especular;

            return corFinal;
        }

        //Implementa os cálculos completos de iluminação.
        int calculoDefPointSpot(glm::vec3 point1){
            glm::vec3 l = posicao - point1;
            glm::vec3 d = posicaoApontaIluminacao - posicao;
            l = glm::normalize(l);
            d = glm::normalize(d);
            float resultado = (glm::dot(l,d))*(-1);
            if (resultado>= cos(anguloAbertura*(M_PI/180.0))){
                return 0; //Se o ponto está dentro do ângulo.
            }else{
                return -1;//Se o ponto está fora do ângulo. 
            }
        }

};

#endif