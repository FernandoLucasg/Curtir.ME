#include "testes_ManipuladorDeUsuario.h"



void testes_manipuladorDeUsuario::executaTestes(){
    manipuladorDeUsuario manipuladorUsuario;
    //Testes de cadastro e autenticação
    manipuladorUsuario.cadastrarUsuario("teste", "teste");
    manipuladorUsuario.cadastrarUsuario("teste2", "teste2");
    CHECK(manipuladorUsuario.autenticarUsuario("teste","teste") == true);
    CHECK(manipuladorUsuario.autenticarUsuario("teste2","teste2") == true);

    //Teste de controle de numeros de usuario
    CHECK(manipuladorUsuario.numeroDeUsuarios() == 2);
    manipuladorUsuario.cadastrarUsuario("teste3", "teste3");
    CHECK(manipuladorUsuario.numeroDeUsuarios() == 3);

    //Testes de procura de usuario
    CHECK(manipuladorUsuario.procuraUsuarioNome("teste").getId() == 1);
    CHECK(manipuladorUsuario.procuraUsuarioNome("teste2").getId() == 2);
    CHECK(strcmp(manipuladorUsuario.procuraUsuarioId(1).getNome(), "teste") == 0);
    CHECK(strcmp(manipuladorUsuario.procuraUsuarioId(2).getNome(), "teste2") == 0);

    //Testes de mudança de informações
    Usuario teste3 = manipuladorUsuario.procuraUsuarioId(1);
    teste3.setNome("testeMudanca");
    manipuladorUsuario.salvarUsuario(teste3);
    CHECK(strcmp(manipuladorUsuario.procuraUsuarioId(1).getNome(), "testeMudanca") == 0);
    teste3.setNome("teste2");
    manipuladorUsuario.salvarUsuario(teste3);
    CHECK(strcmp(manipuladorUsuario.procuraUsuarioId(1).getNome(), "teste2") == 0);

    //Teste para parte de seguir e deixar de seguir usuarios
    manipuladorUsuario.seguir(1,2);
    CHECK(manipuladorUsuario.segue(1,2) == true);
    manipuladorUsuario.deixarDeSeguir(1,2);
    CHECK(manipuladorUsuario.segue(1,2) == false);

}
