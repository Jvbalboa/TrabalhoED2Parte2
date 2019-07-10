#ifndef ARVOREVP_H
#define ARVOREVP_H

#include "NoVP.h"

class ArvoreVP
{
    private:
        NoVP *raiz; //Ponteiro para raiz

        //Rota��es
        void rotacaoEsquerda(NoVP *&raiz, NoVP *&p, double *comparacoes);
        void rotacaoDireita(NoVP *&raiz, NoVP *&p, double *comparacoes);

        //Ajuste da �rvore, fun��o que checaquais rota��o s�o necess�rias
        void ajustaArvore(NoVP *&raiz, NoVP *&p, double *comparacoes);

    public:
        //Construtor
        ArvoreVP();
        //Destutor
        ~ArvoreVP();

        void auxDelete(NoVP *p);

        //Inser��o
        void insere(Rating k, double *comparacoes); //Inser��o da AVP, faz a inser��o bin�ria e ajusta a �rvore
        NoVP* insereArvoreBinaria(NoVP* raiz, NoVP *p, double *comparacoes); //Inser��o como �rvore Bin�ria de Busca

        //Busca
        NoVP* busca(Rating k, double *comparacoes);

        //Impress�o
        //Fun��es que chamam as recursivas
        void imprime();
        void imprimePorNivel();
        //Impress�o recursiva
        void auxImprime(NoVP *raiz);
        void auxImprimePorNivel(NoVP *raiz);
};

#endif // ARVOREVP_H
