#include <string.h>
#include <iostream>
#include <cstring>
#include <dirent.h>
#include <sys/stat.h>

//Classes principais
#include "../ClassesPrincipais/Usuario.cpp"
#include "../ClassesPrincipais/Usuario.h"
#include "../ClassesPrincipais/Postagem.cpp"
#include "../ClassesPrincipais/Postagem.h"
#include "../ClassesPrincipais/Comentario.cpp"
#include "../ClassesPrincipais/Comentario.h"
#include "../ClassesPrincipais/Hashtag.cpp"
#include "../ClassesPrincipais/Hashtag.h"

//Classes manipuladoras
#include "../Manipuladores/manipuladorDeUsuario.cpp"
#include "../Manipuladores/manipuladorDeUsuario.h"
#include "../Manipuladores/manipuladorDePostagem.cpp"
#include "../Manipuladores/manipuladorDePostagem.h"
#include "../Manipuladores/manipuladorDeComentario.cpp"
#include "../Manipuladores/manipuladorDeComentario.h"

//Classes de testes
#include "ClassesTestes/testes_usuario.cpp"
#include "ClassesTestes/testes_usuario.h"
#include "ClassesTestes/testes_postagem.cpp"
#include "ClassesTestes/testes_postagem.h"
#include "ClassesTestes/testes_comentario.cpp"
#include "ClassesTestes/testes_comentario.h"
#include "ClassesTestes/testes_hashtag.cpp"
#include "ClassesTestes/testes_hashtag.h"
#include "ClassesTestes/testes_manipuladorDeUsuario.cpp"
#include "ClassesTestes/testes_manipuladorDeUsuario.h"
#include "ClassesTestes/testes_manipuladorDeComentario.cpp"
#include "ClassesTestes/testes_manipuladorDeComentario.h"
#include "ClassesTestes/testes_manipuladorDePostagem.cpp"
#include "ClassesTestes/testes_manipuladorDePostagem.h"

#include "doctest/parts/doctest.cpp"
#include "doctest/doctest.h"
#include <cassert>

#define falha 1
#define sucesso 0

//Objetos para testes das classes principais
testes_postagem testesPostagens;
testes_usuario testeUsuario;
testes_comentario testeComentario;
testes_hashtag testeHashtag;

//Objetos para testes das classes manipuladoras
testes_manipuladorDeUsuario testeManipuladorUsuario;
testes_manipuladorDeComentario testeManipuladorComentario;
testes_manipuladorDePostagem testeManipuladorPostagem;

manipuladorDeArquivo manipulador;

void limparPastaSeguidores() {
    // Obtem o caminho do diretório anterior ao executável
    char caminho[PATH_MAX];
    if (getcwd(caminho, sizeof(caminho)) == NULL) {
        throw "Erro ao obter o diretório atual";
        return;
    }

    // Concatena o caminhp da pasta "Seguidores" ao caminho
    strcat(caminho, "/Arquivos/Seguidores");

    // Abre o diretório
    DIR* dir = opendir(caminho);
    if (dir == NULL) {
        throw "Erro ao abrir o diretório Seguidores";
        return;
    }

    // Le os arquivos no diretório e exclue eles
    struct dirent* ent;
    while ((ent = readdir(dir)) != NULL) {
        if (strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0) {
            // Concatena o nome do arquivo ao caminho
            char arquivo[PATH_MAX];
            strcpy(arquivo, caminho);
            strcat(arquivo, "/");
            strcat(arquivo, ent->d_name);

            if (remove(arquivo) != 0) { // Exclue o arquivo
                throw "Erro ao excluir o arquivo";
            }
        }
    }

    closedir(dir); // Fecha o diretório


}



/*Está função limpa ou zera todos os arquivos, para que os testes dos manipuladores possam ser feitos sem problemas*/
bool limpa_todos_arquivos(){
    manipulador.limparArquivoBinario("Arquivos/comentarios.bin");
    manipulador.limparArquivoBinario("Arquivos/hashtags.bin");
    manipulador.zeraArquivo("Arquivos/numeroDePostagensCadastradas.bin");
    manipulador.zeraArquivo("Arquivos/numeroDeUsuariosCadastrados.bin");
    manipulador.limparArquivoBinario("Arquivos/postagens.bin");
    manipulador.limparArquivoBinario("Arquivos/usuarios.bin");

    try{
        limparPastaSeguidores();
    }catch(const char* msg){
        cout << "ERRO: " << msg;
        return false;
    }

    return true;
}


int main(int argc, char* argv[]){
    doctest::Context context;
    limpa_todos_arquivos(); //Limpa arquivos

    context.run(); // Roda testes

    limpa_todos_arquivos(); //Limpa arquivos
    return sucesso;
}

//Testes
TEST_CASE("Testes da classe Usuario"){
    testeUsuario.executaTestes();
}

TEST_CASE("Testes das classe Postagem"){
    testesPostagens.executaTestes();
}

TEST_CASE("Testes da classe Hashtag"){
    testeHashtag.executaTeste();
}

TEST_CASE("Testes da classe Comentario"){
    testeComentario.executaTestes();
}

TEST_CASE("Testes da classe manipuladorDeUsuario"){
    testeManipuladorUsuario.executaTestes();
}

TEST_CASE("Testes da classe manipuladorDeComentario"){
    testeManipuladorComentario.executaTestes();
}

TEST_CASE("Testes da classe manipuladorDePostagem"){
    testeManipuladorPostagem.executaTestes();
}
