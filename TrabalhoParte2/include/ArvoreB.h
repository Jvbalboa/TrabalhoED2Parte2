#ifndef ARVOREB_H
#define ARVOREB_H

#include "NoB.h"
#include "Rating.h"

class ArvoreB
{
    private:
        NoB *raiz; //Ponteiro para o nó raiz
        int grau; //Grau da árvore

        void auxDelete(NoB *p);

    public:
        ArvoreB(int grau); //Construtor
        ~ArvoreB(); //Destrutor
        void insere(Rating k, double *comparacoes, double *copias); //Função para inserir uma chave na árvore
        NoB* busca(Rating k, double *comparacoes); //Função para buscar uma chave na árvore

        void imprime(); //Função para imprimir todos os nós da árvore


};

#endif // ARVOREB_H
