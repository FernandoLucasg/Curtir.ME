#ifndef HASHTAG_H
#define HASHTAG_H

#define tamanhoHashtag 51

#include "Arquivo.h"
#include <fstream>
#include <iostream>

class Hashtag
{
    public:
        Hashtag();
        bool criaArquivosNescessarios();
        bool adicionaHashtagArquivo(Hashtag hashtag);
        bool verificaExistencia(Hashtag hashtag);

        char* Gethashtag();
        void Sethashtag(char* Hashtag);
        bool verificaFormato(char* Hashtag);
        void Setexiste(bool valor);
        bool Getexiste();

    private:
        char hashtag[tamanhoHashtag];
        bool existe = false; //Fala se têm uma hashtag ou não
};
    /*Métodos para manipulação de arquivos*/

    //Função que cria todos os documentos nescessarios para o funcionamento das hashtags
    bool Hashtag::criaArquivosNescessarios(){
        ifstream ifs("Arquivos/hashtags.bin");
        if (!ifs) { //Verifica se Existe o Arquivo
            ofstream arquivo("Arquivos/hashtags.bin", ios::binary | ios::app);
            if (!arquivo.is_open()) {
                geraExcecao("Erro ao criar o arquivo de hashtags.");
                return false;
            }
            cout << "Arquivo de  hashtags criado\n";
            arquivo.close();
        }
        return true;
    }


    bool Hashtag::adicionaHashtagArquivo(Hashtag hashtag){
            ofstream arquivo("Arquivos/hashtags.bin", ios::binary | ios::app);
            if (!arquivo.is_open()) {
                geraExcecao("Erro ao abrir o arquivo de hashtags.");
                return false;
            }
            arquivo.write((char*)&hashtag, sizeof(Hashtag));
            arquivo.close();
            return true;
    }

    bool Hashtag::verificaExistencia(Hashtag hashtag){
        ifstream arquivo("Arquivos/hashtags.bin", ios::binary);
        Hashtag aux;
        bool encontrado = false;
        if (!arquivo.is_open()) {
            geraExcecao("Erro ao abrir o arquivo de hashtags.");
        }else{

            while (arquivo.read((char*)&aux, sizeof(Hashtag))) {
                if(strcmp(aux.Gethashtag(), hashtag.Gethashtag()) == 0){
                    cout << "encontrado";
                    encontrado = true;
                }
            }
        }
        return encontrado;
    }

    /*Métodos para manipulação da hashtag*/

    bool Hashtag::verificaFormato(char hashtag[]){
        if(hashtag[0] == '#'){
            return true;
        }
        return false;
    }

    void Hashtag::Sethashtag(char* Hashtag){
        strcpy( this->hashtag, Hashtag);
    }
    char* Hashtag::Gethashtag(){
        return this->hashtag;
    }

    void Hashtag::Setexiste(bool valor){
        this->existe = valor;
    }
    bool Hashtag::Getexiste(){
        return this->existe;
    }

    Hashtag::Hashtag()
    {
    }

#endif // HASHTAG_H
