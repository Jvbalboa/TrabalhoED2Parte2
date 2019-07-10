#ifndef NOB_H
#define NOB_H
#include "Rating.h"

class NoB
{
    private:
        Rating *chaves; //Vetor de chaves
        NoB **filho; //Vetor para n�s filhos
        int grau; //Grau do n�
        int numChaves; //N�mero de chaves
        bool ehFolha; //True -> n� � folha, False -> n� n�o � folha

    public:
        //Construtor
        NoB(int grau, int ehFolha);

        void insere(Rating k, double *comparacoes, double *copias); //Fun��o para inserir chave quando o n�e n�o est� cheio
        void split(int i, NoB *antigo, double *comparacoes, double *copias); //Fun��o para fazer split quando n� est� cheio
        NoB* busca(Rating k, double *comparacoes); //Fun��o para buscar uma chave na sub�rvore

        void imprime(); //Fun��o para imprimir todos os n�s da sub�rvore

    friend class ArvoreB; //Permite que ArvoreB acesse os atributos privados do n�
};

#endif // NOB_H
