#ifndef MANIPULADORDEPOSTAGEM_H
#define MANIPULADORDEPOSTAGEM_H

#include "Postagem.h"
#include "Arquivo.h"
#include "manipuladorDeUsuario.h"
#include "manipuladorDeComentario.h"

class manipuladorDePostagem
{
    public:
        void criaArquivosNescessarios();
        void mostrarFeed();
        bool adicionaAoArquivo(Postagem post);
        bool aumentarNumeroDePostagens();
        bool ehMinhaPostagem(int idUsuario, int numeroPostagem);
        int numeroDePostagens();
        bool salvaPostagem(Postagem post);
        Postagem buscaPostagem(int id);
        bool adicionaCurtida(Postagem post);
        void detalhar(int id);

    private:
};

//Função que cria todos os documentos nescessarios para o funcionamento das postagens
void manipuladorDePostagem::criaArquivosNescessarios(){
    //Arquivo de numero de usuarios cadastrados
    ifstream ifs("Arquivos/numeroDePostagensCadastradas.bin");
    if (!ifs) { //Verifica se Existe o Arquivo
        ofstream arquivo("Arquivos/numeroDePostagensCadastradas.bin", ios::binary | ios::app);
        if (!arquivo.is_open()) {
            geraExcecao("Erro ao criar o arquivo de numero de usuarios.");
            return;
        }
        int numeroInicial = 0;
        arquivo.write((char*)&numeroInicial, sizeof(int));
        cout << "Arquivo de Numero De Postagens criado\n";
        arquivo.close();
    }


    //Arquivo de Postagens
    ifstream ifs3("Arquivos/postagens.bin");
    if (!ifs3) { //Verifica se Existe o Arquivo
        ofstream arquivo("Arquivos/postagens.bin", ios::binary | ios::app);
        if (!arquivo.is_open()) {
            geraExcecao("Erro ao criar o arquivo de postagens.");
            return;
        }
        cout << "Arquivo de Postagens criado\n";
        arquivo.close();
    }
}


void manipuladorDePostagem::mostrarFeed(){

    manipuladorDeUsuario mUsuario;
    manipuladorDeComentario mComentario;

    ifstream arquivo("Arquivos/postagens.bin", ios::binary);
    Postagem post;
    if (!arquivo.is_open()) {
        geraExcecao("Erro ao abrir o arquivo de postagens.");
    }else{

        while (arquivo.read((char*)&post, sizeof(Postagem))) {

            cout << "\n       Id da postagem: " << post.GetnumeroPostagem();
            cout << "  ||  Postado por: "<< mUsuario.procuraUsuarioId(post.GetIDusuario()).getNome() << endl;

            post.hashtag.Getexiste() ? cout << "       " << post.hashtag.Gethashtag() << endl : cout << "";

            cout << "       Conteúdo: " << post.Getconteudo()<< endl;
            cout << "       " << post.Getcurtidas() << "    ";

            if(post.Getcurtidas() == 1){
                cout <<"Curtida"<< endl;
            }else{
                cout <<"Curtidas"<< endl;

            }
            cout << "\n         ...............................................................................................................\n";

            cout << "\n\n           Comentários: " << endl;
            mComentario.exibirComentariosPorId(post.GetnumeroPostagem(), 2);

            cout << "\n         :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n\n";

        }
    }

}

void manipuladorDePostagem::detalhar(int id){

    manipuladorDeUsuario mUsuario;
    manipuladorDeComentario mComentario;

    ifstream arquivo("Arquivos/postagens.bin", ios::binary);
    Postagem post;
    if (!arquivo.is_open()) {
        geraExcecao("Erro ao abrir o arquivo de postagens.");
    }else{

        while (arquivo.read((char*)&post, sizeof(Postagem))) {
            if(post.GetnumeroPostagem() == id){
                cout << "\n         ...............................................................................................................\n";

                cout << "\n       Id da postagem: " << post.GetnumeroPostagem();
                cout << "  ||  Postado por: "<< mUsuario.procuraUsuarioId(post.GetIDusuario()).getNome() << endl;
                cout << "       " << post.Getconteudo()<< endl;
                cout << "       " << post.Getcurtidas() << "    ";

                if(post.Getcurtidas() == 1){
                    cout <<"Curtida"<< endl;
                }else{
                    cout <<"Curtidas"<< endl;

                }
                cout << "\n\n           Comentários: " << endl;
                mComentario.exibirComentariosPorId(post.GetnumeroPostagem(), mostrarTodos);

                cout << "\n         ...............................................................................................................\n\n";
            }


        }
    }

}
bool manipuladorDePostagem::adicionaAoArquivo(Postagem post){
    ofstream arquivo("Arquivos/postagens.bin", ios::binary | ios::app);

    if (!arquivo.is_open()) {
        geraExcecao("Erro ao abrir o arquivo de postagens.");
        return false;
    }

    this->aumentarNumeroDePostagens();
    post.SetnumeroPostagem(this->numeroDePostagens());

    arquivo.write((char*)&post, sizeof(Postagem));
    arquivo.close();

    cout << "Postagem cadastrada com sucesso." << endl;

    return true;
}

bool manipuladorDePostagem::ehMinhaPostagem(int idUsuario, int numeroPostagem){
    Postagem post = this->buscaPostagem(numeroPostagem);

    if(post.GetIDusuario() == idUsuario){
        return true;
    }else{
        return false;
    }
}


int manipuladorDePostagem::numeroDePostagens(){
    ifstream arquivo("Arquivos/numeroDePostagensCadastradas.bin", ios::binary);
    int numero;
    if (!arquivo.is_open()) {
        geraExcecao("Erro ao abrir o arquivo.");
        return -1;
    }else{
        arquivo.read((char*)&numero, sizeof(int));
    }
    return numero;
}


bool manipuladorDePostagem::aumentarNumeroDePostagens(){
    int numero = this->numeroDePostagens();

    ofstream arquivo("Arquivos/numeroDePostagensCadastradas.bin", ios::binary | ios::app);

    if (!arquivo.is_open()) {
        geraExcecao("Erro ao abrir o arquivo de postagens.");
        return false;
    }

    limparArquivoBinario("Arquivos/numeroDePostagensCadastradas.bin");

    numero++;
    arquivo.write((char*)&numero, sizeof(int));
    arquivo.close();

    return true;
}

bool manipuladorDePostagem::salvaPostagem(Postagem post){
    fstream arquivo("Arquivos/postagens.bin", ios::binary | std::ios::in | std::ios::out);
    Postagem postAux;
    int i = 0;
    if (!arquivo.is_open()) {
        geraExcecao("Erro ao abrir o arquivo de postagens.");
        return false;
    }else{

        while (arquivo.read((char*)&postAux, sizeof(Postagem))) {
            if (postAux.GetnumeroPostagem() == post.GetnumeroPostagem()) {
                break;
            }
            i++;
        }

    }

    arquivo.seekg(i*sizeof(Postagem), ios_base::beg);
    arquivo.write((char*)&post, sizeof(Postagem));
    arquivo.close();
    return true;
}

bool manipuladorDePostagem::adicionaCurtida(Postagem post){
    post.Setcurtidas(post.Getcurtidas()+1);
    this->salvaPostagem(post);
    return true;
}

Postagem manipuladorDePostagem::buscaPostagem(int id){
    ifstream arquivo("Arquivos/postagens.bin", ios::binary | std::ios::in);
    Postagem post;
    Postagem vazio;

    if (!arquivo.is_open()) {
        geraExcecao("Erro ao abrir o arquivo de usuários.");
        return vazio;
    }else{

        while (arquivo.read((char*)&post, sizeof(Postagem))) {
            if (post.GetnumeroPostagem() == id) {
                arquivo.close();
                return post;
            }
        }
    }

    arquivo.close();
    return vazio;
}

#endif // MANIPULADORDEPOSTAGEM_H
