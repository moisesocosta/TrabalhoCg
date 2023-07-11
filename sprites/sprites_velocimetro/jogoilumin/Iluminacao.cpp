#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <math.h>
#ifndef Iluminacao_H //Header guards para nao ocorrer redefinição e evitar erro na compilação.
#define Iluminacao_H


class Iluminacao{
    private:
        glm::vec3 posicao; //Ponto de iluminação.                
        glm::vec3 ambiente, difusa, especular; //Informações relacionadas à posição da luz.
        glm::vec3 posicaoCamera; //Posição da Camera para a propriedade especular.          
        glm::vec3 especularMaterial; //Propiedade especular do objeto. 

    //recebe a posição da luz como argumento e inicializa as variáveis membro com valores padrão.             
    public:
        Iluminacao(glm::vec3 posicao){
            this->posicao = posicao;
            ambiente  = glm::vec3(0.3);
            difusa    = glm::vec3(1.0); 
            especular = glm::vec3(1.0);
            especularMaterial = glm::vec3(0.0);
        }

        //Retorna a posição da luz.
        glm::vec3 getPosicao(){
            return posicao;
        }

        //Define a posição da luz.
        void setPosicao(glm::vec3 posicao){
            this->posicao = posicao;
        }

        //Define a posição da câmera.
        void setPosicaoCamera(glm::vec3 posicao){
            this->posicaoCamera = posicao;
        }

        //Define a cor de iluminação ambiente e a limita no intervalo [0, 1].
        void setAmbiente(glm::vec3 ambiente){
            this->ambiente = glm::clamp(ambiente, glm::vec3(0), glm::vec3(1));
        }

        //Define a cor de iluminação difusa e a limita no intervalo [0, 1].
        void setDifusa(glm::vec3 difusa){
            this->difusa = glm::clamp(difusa, glm::vec3(0), glm::vec3(1));
        }

        //Define a cor de iluminação especular e a limita no intervalo [0, 1].
        void setEspecular(glm::vec3 especular){
            this->especular = glm::clamp(especular, glm::vec3(0), glm::vec3(1));
        }

        //Define a cor especular do material.
        void setEspecularMaterial(glm::vec3 especularMaterial){
            this->especularMaterial = especularMaterial;
        }

        //Calcula a cor resultante da iluminação em um ponto específico. 
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
            glm::vec3 Rd = glm::max(glm::dot(L,N),0.2f) * color; 
            float Rs;
            if (K < 0){
                Rs = pow(0,16);
            }else{
                Rs = pow(K,16);
            }

            
            glm::vec3 ambiente = Ia * Ra;
            glm::vec3 difusa   = Id * Rd;
            glm::vec3 especular   = Is * Rs * especularMaterial;

            
            glm::vec3 corFinal = ambiente + difusa + especular;

            return corFinal;
        }

        //Calcula e retorna a normal de um triângulo definido por três pontos.
        glm::vec3 calculoNormal(glm::vec3 point1,glm::vec3 point2, glm::vec3 point3){
            glm::vec3 V1 = point2 - point1;
            glm::vec3 V2 = point3 - point1;
            glm::vec3 Normal = glm::cross(V2,V1);
            return Normal;
        }

};

#endif