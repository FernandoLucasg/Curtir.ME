#include "testes_manipuladorDePostagem.h"


void testes_manipuladorDePostagem::executaTestes(){
    //Testes de adição e procura de uma postagem
    manipuladorDePostagem manipuladorPostagens;
    Postagem post(1,1,"Conteudo teste");
    CHECK(manipuladorPostagens.adicionaAoArquivo(post) == true);
    CHECK(strcmp(manipuladorPostagens.buscaPostagem(1).Getconteudo(), "Conteudo teste") == 0);

    //Testes de verificação do dono da postagem
    CHECK(manipuladorPostagens.ehMinhaPostagem(1,1) == true);
    CHECK(manipuladorPostagens.ehMinhaPostagem(2,1) == false);

    //Testes de verificação da conatagem de numero de postagens
    CHECK(manipuladorPostagens.numeroDePostagens() == 1);
    Postagem post2(2,2,"Conteudo teste");
    CHECK(manipuladorPostagens.adicionaAoArquivo(post2) == true);
    CHECK(manipuladorPostagens.numeroDePostagens() == 2);

    //Teste de mudança de postagem
    post.Setconteudo("Conteudo teste 2");
    manipuladorPostagens.salvaPostagem(post);
    CHECK(strcmp(manipuladorPostagens.buscaPostagem(1).Getconteudo(), "Conteudo teste 2") == 0);

    //Testes de adição de curtidas
    CHECK(manipuladorPostagens.buscaPostagem(post.GetnumeroPostagem()).Getcurtidas() == 0);
    CHECK(manipuladorPostagens.adicionaCurtida(post) == true);
    CHECK(manipuladorPostagens.buscaPostagem(post.GetnumeroPostagem()).Getcurtidas() == 1);
    post = manipuladorPostagens.buscaPostagem(post.GetnumeroPostagem());
    CHECK(manipuladorPostagens.adicionaCurtida(post) == true);
    CHECK(manipuladorPostagens.buscaPostagem(post.GetnumeroPostagem()).Getcurtidas() == 2);
    post = manipuladorPostagens.buscaPostagem(post.GetnumeroPostagem());

    //Testes de apagar postagens
    CHECK(post.Getapagada() == false);
    manipuladorPostagens.apagarPostagem(post.GetnumeroPostagem());
    post = manipuladorPostagens.buscaPostagem(post.GetnumeroPostagem());
    CHECK(post.Getapagada() == true);
}
