#include "ArvoreB.h"
#include <cstddef>

//Constutor: raiz recebe nulo e seta o grau da árvore
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

//Função para imprimir todos os nós da árvore
void ArvoreB::imprime()
{
    //Se a raiz não é nula, imprime os nós através dela
    if(raiz != NULL)
        raiz->imprime();
}

//Função para buscar uma chave na árvore
NoB* ArvoreB::busca(Rating k, double *comparacoes)
{
    //Se a raiz não é nula, retorna o resultado da busca do valor k através da raiz. Senão retorna NULL
    return (raiz == NULL)? NULL : raiz->busca(k, comparacoes);
}

//Função para inserir uma chave na árvore
void ArvoreB::insere(Rating k, double *comparacoes, double *copias)
{
    //Se a árvore é vazia, insere na raíz
    if (raiz == NULL)
    {
        raiz = new NoB(grau, true); //Aloca memória para raíz
        raiz->chaves[0] = k; (*copias)++; //Insere k
        raiz->numChaves = 1;
    }
    else //Se árvore não é vazia
    {
        //Se a raíz é cheia, faz split da raíz
        if (raiz->numChaves == 2*grau-1)
        {
            //Cria novo nó raíz
            NoB *aux = new NoB(grau, false);

            //Sobe a primeira chave da raíz anterior
            aux->filho[0] = raiz; (*copias)++;

            //Faz split na antiga raíz
            aux->split(0, raiz, comparacoes, copias);

            //Checa se a chave será inserida na esquerda ou direita
            int i = 0;
            (*comparacoes)++;
            if (aux->chaves[0].userID < k.userID || (aux->chaves[0].userID == k.userID && aux->chaves[0].movieID < k.movieID))
                i++;

            aux->filho[i]->insere(k, comparacoes, copias);
            raiz = aux;
        }
        else  //Se raíz não está cheia, insere
            raiz->insere(k, comparacoes, copias);
    }
}
