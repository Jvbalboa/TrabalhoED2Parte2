#ifndef NOB_H
#define NOB_H
#include "Rating.h"

class NoB
{
    private:
        Rating *chaves; //Vetor de chaves
        NoB **filho; //Vetor para nós filhos
        int grau; //Grau do nó
        int numChaves; //Número de chaves
        bool ehFolha; //True -> nó é folha, False -> nó não é folha

    public:
        //Construtor
        NoB(int grau, int ehFolha);

        void insere(Rating k, double *comparacoes, double *copias); //Função para inserir chave quando o nóe não está cheio
        void split(int i, NoB *antigo, double *comparacoes, double *copias); //Função para fazer split quando nó está cheio
        NoB* busca(Rating k, double *comparacoes); //Função para buscar uma chave na subárvore

        void imprime(); //Função para imprimir todos os nós da subárvore

    friend class ArvoreB; //Permite que ArvoreB acesse os atributos privados do nó
};

#endif // NOB_H
