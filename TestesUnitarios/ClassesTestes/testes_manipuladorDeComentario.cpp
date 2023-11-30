#include "testes_manipuladorDeComentario.h"



void testes_manipuladorDeComentario::executaTestes(){
    manipuladorDeComentario manipuladorComentarios;
    Comentario coment(1,"teste",1,1,"Comentario Teste");
    CHECK(manipuladorComentarios.adicionaAoArquivo(coment) == true);
}
