#ifndef ARVOREVP_H
#define ARVOREVP_H

#include "NoVP.h"

class ArvoreVP
{
    private:
        NoVP *raiz; //Ponteiro para raiz

        //Rotações
        void rotacaoEsquerda(NoVP *&raiz, NoVP *&p, double *comparacoes);
        void rotacaoDireita(NoVP *&raiz, NoVP *&p, double *comparacoes);

        //Ajuste da árvore, função que checaquais rotação são necessárias
        void ajustaArvore(NoVP *&raiz, NoVP *&p, double *comparacoes);

    public:
        //Construtor
        ArvoreVP();
        //Destutor
        ~ArvoreVP();

        void auxDelete(NoVP *p);

        //Inserção
        void insere(Rating k, double *comparacoes); //Inserção da AVP, faz a inserção binária e ajusta a árvore
        NoVP* insereArvoreBinaria(NoVP* raiz, NoVP *p, double *comparacoes); //Inserção como Árvore Binária de Busca

        //Busca
        NoVP* busca(Rating k, double *comparacoes);

        //Impressão
        //Funções que chamam as recursivas
        void imprime();
        void imprimePorNivel();
        //Impressão recursiva
        void auxImprime(NoVP *raiz);
        void auxImprimePorNivel(NoVP *raiz);
};

#endif // ARVOREVP_H
