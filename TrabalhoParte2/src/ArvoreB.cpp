#include "ArvoreB.h"
#include <cstddef>

//Constutor: raiz recebe nulo e seta o grau da �rvore
ArvoreB::ArvoreB(int grau)
{
    raiz = NULL;
    this->grau = grau;
}

ArvoreB::~ArvoreB()
{
    auxDelete(raiz);
}

void ArvoreB::auxDelete(NoB *p)
{
    for(int i=0; i<p->numChaves+1; i++)
    {
        if(p->filho[i]->ehFolha)
            delete p->filho[i];
        else
            auxDelete(p->filho[i]);
    }
    delete(p);
}

//Fun��o para imprimir todos os n�s da �rvore
void ArvoreB::imprime()
{
    //Se a raiz n�o � nula, imprime os n�s atrav�s dela
    if(raiz != NULL)
        raiz->imprime();
}

//Fun��o para buscar uma chave na �rvore
NoB* ArvoreB::busca(Rating k, double *comparacoes)
{
    //Se a raiz n�o � nula, retorna o resultado da busca do valor k atrav�s da raiz. Sen�o retorna NULL
    return (raiz == NULL)? NULL : raiz->busca(k, comparacoes);
}

//Fun��o para inserir uma chave na �rvore
void ArvoreB::insere(Rating k, double *comparacoes, double *copias)
{
    //Se a �rvore � vazia, insere na ra�z
    if (raiz == NULL)
    {
        raiz = new NoB(grau, true); //Aloca mem�ria para ra�z
        raiz->chaves[0] = k; (*copias)++; //Insere k
        raiz->numChaves = 1;
    }
    else //Se �rvore n�o � vazia
    {
        //Se a ra�z � cheia, faz split da ra�z
        if (raiz->numChaves == 2*grau-1)
        {
            //Cria novo n� ra�z
            NoB *aux = new NoB(grau, false);

            //Sobe a primeira chave da ra�z anterior
            aux->filho[0] = raiz; (*copias)++;

            //Faz split na antiga ra�z
            aux->split(0, raiz, comparacoes, copias);

            //Checa se a chave ser� inserida na esquerda ou direita
            int i = 0;
            (*comparacoes)++;
            if (aux->chaves[0].userID < k.userID || (aux->chaves[0].userID == k.userID && aux->chaves[0].movieID < k.movieID))
                i++;

            aux->filho[i]->insere(k, comparacoes, copias);
            raiz = aux;
        }
        else  //Se ra�z n�o est� cheia, insere
            raiz->insere(k, comparacoes, copias);
    }
}
