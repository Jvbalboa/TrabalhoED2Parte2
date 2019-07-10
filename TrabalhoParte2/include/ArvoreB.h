#ifndef ARVOREB_H
#define ARVOREB_H

#include "NoB.h"
#include "Rating.h"

class ArvoreB
{
    private:
        NoB *raiz; //Ponteiro para o n� raiz
        int grau; //Grau da �rvore

        void auxDelete(NoB *p);

    public:
        ArvoreB(int grau); //Construtor
        ~ArvoreB(); //Destrutor
        void insere(Rating k, double *comparacoes, double *copias); //Fun��o para inserir uma chave na �rvore
        NoB* busca(Rating k, double *comparacoes); //Fun��o para buscar uma chave na �rvore

        void imprime(); //Fun��o para imprimir todos os n�s da �rvore


};

#endif // ARVOREB_H
