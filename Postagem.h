#ifndef POSTAGEM_H
#define POSTAGEM_H

#define tamanhoTextoPostagens 201

#include "Hashtag.h"

class Postagem
{
    public:

        int GetIDusuario();
        void SetIDusuario(int val);
        char* Getconteudo();
        void Setconteudo(char conteudo[]);
        int GetnumeroPostagem();
        void SetnumeroPostagem(int val);
        int Getcurtidas();
        void Setcurtidas(int val);
        bool Getapagada();
        void Setapagada(bool val);
        Postagem(int ID, int numeroP, char conteudo[]);
        Postagem();
        bool existe();

        Hashtag hashtag;

    private:
        int IDusuario;
        int numeroPostagem;
        char conteudo[tamanhoTextoPostagens];
        int curtidas = 0;
        bool apagada=false;
};

        int Postagem::GetIDusuario() {
            return IDusuario;
        }

        void Postagem::SetIDusuario(int val) {
            IDusuario = val;
        }

        int Postagem::GetnumeroPostagem() {
            return numeroPostagem;
        }

        void Postagem::SetnumeroPostagem(int val) {
            numeroPostagem = val;
        }

        int Postagem::Getcurtidas() {
            return curtidas;
        }

        void Postagem::Setcurtidas(int val) {
            curtidas = val;
        }

        bool Postagem::Getapagada() {
            return apagada;
        }

        void Postagem::Setapagada(bool val) {
            apagada = val;
        }

        char* Postagem::Getconteudo(){
            char * copia = new char[tamanhoTextoPostagens];
            strcpy(copia, this->conteudo);
            return copia;
        }

        void Postagem::Setconteudo(char conteudo[]){
            strcpy(this->conteudo, conteudo);
        }

        Postagem::Postagem(int ID, int numeroP, char conteudo[]){
            this->SetIDusuario(ID);
            this->SetnumeroPostagem(numeroP);
            this->Setconteudo(conteudo);
        }

        Postagem::Postagem(){
            this->Setconteudo("");
            this->SetIDusuario(0);
            this->SetnumeroPostagem(0);
        }
        bool Postagem::existe(){
            if(strcmp(this->Getconteudo(),"") == 0 && this->GetnumeroPostagem() == 0){
                return false;
            }
            return true;
        }
#endif // POSTAGEM_H
