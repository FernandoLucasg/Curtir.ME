#include "testes_usuario.h"


void testes_usuario::executaTestes(){
        Usuario userTeste;
        userTeste.setId(1);
        userTeste.setNome("teste");
        userTeste.setSenha("senhaTeste");
        CHECK(userTeste.getId() == 1);
        CHECK(strcmp("teste", userTeste.getNome()) == 0);
        CHECK(strcmp("senhaTeste", userTeste.getSenha()) == 0);
        CHECK(userTeste.existe() == true);
        userTeste.limpaUsuario();
        CHECK(userTeste.existe() == false);
}

