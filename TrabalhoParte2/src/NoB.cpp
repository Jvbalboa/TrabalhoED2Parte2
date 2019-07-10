#include "NoB.h"
#include<iostream>
#include <cstddef>

using namespace std;

/*Construtor: Seta o grau, a variável booleana é folha e o número de chaves como 0.
  Além de alocar memória para o vetor de chaves e de filhos*/
NoB::NoB(int grau, int ehFolha)
{
    this->grau = grau;
    this->ehFolha = ehFolha;
    numChaves = 0;

    //Alocando memória para o as chaves e nós filho
    chaves = new Rating[2*grau-1];
    filho = new NoB* [2*grau];
}

//Função para imprimir todos os nós da subárvore
void NoB::imprime()
{
    int i;
    for (i = 0; i < numChaves; i++)
    {
        //Se não for folha, percorre e imprime os nós da subárvore
        if (!ehFolha)
            filho[i]->imprime();
        cout << "(" << chaves[i].userID << ", " << chaves[i].movieID << ")";
    }

    //Imprime a subárvore do ultimo nó
    if (!ehFolha)
        filho[i]->imprime();
}

//Função para buscar uma chave na subárvore
NoB* NoB::busca(Rating k, double *comparacoes)
{
    //Acha chave igual com userID igaul ao userID de k, ou a maior mais perto de k
    int i = 0;
    (*comparacoes)++;
    while (i < numChaves && k.userID > chaves[i].userID)
    {
        i++;
        (*comparacoes)++;
    }

    //Se userID de chave = userID de k, retorna procura o movieID igual
    (*comparacoes)++;
    while(i < numChaves && chaves[i].userID == k.userID && k.movieID > chaves[i].movieID)
    {
        i++;
        (*comparacoes)++;
    }

    //Se i ultrapassou o limite, decrementa
    if(i == numChaves)
        i--;

    //Se userID e movieID de chave[i] e k são iguais, retorna o nó
    (*comparacoes)++;
    if (chaves[i].userID == k.userID && chaves[i].movieID == k.movieID)
        return this;

    //Se a chave não foi encontrada e não há mais nós a percorrer (nó atual é folha), retorna nulo
    if (ehFolha)
        return NULL;

    //Chama função recursivamente
    return filho[i]->busca(k, comparacoes);
}

//Função para inserir chave quando o nóe não está cheio
void NoB::insere(Rating k, double *comparacoes, double *copias)
{
    //Inicializa o índice como índice do elemento mais à direita
    int i = numChaves-1;

    //Se for um nó folha, acha a posição de inserção e desoloca as chaves maiores para abrir espaço
    if (ehFolha)
    {
        //Enquanto o userID da chave é maior do que o de k, empurra as chaves para direita
        (*comparacoes)++;
        while (i >= 0 && chaves[i].userID > k.userID)
        {
            chaves[i+1] = chaves[i];
            i--;
            (*comparacoes)++;
        }

        //Enquanto o userID da chave é igual ao de k e o movieID da chave é maior do que o de k, empurra as chaves para direita
        (*comparacoes)++;
        while(i >= 0 && chaves[i].userID == k.userID && chaves[i].movieID > k.movieID)
        {
            chaves[i+1] = chaves[i];
            i--;
            (*comparacoes)++;
        }

        //Insere a chave na posição em aberto
        chaves[i+1] = k;
        numChaves ++;
    }

    //Se o nó não é folha, acha o nó filho a se inserir a chave
    else
    {
        //Decrementa o índice enquanto o userID das chaves for maior que o de k
        (*comparacoes)++;
        while (i >= 0 && chaves[i].userID > k.userID)
        {
            i--;
            (*comparacoes)++;
        }

        //Decrementa o índice enquanto o userID das chaves for igual ao de k e o movieID das chaves for maior
        (*comparacoes)++;
        while(i >= 0 && chaves[i].userID == k.userID && chaves[i].movieID > k.movieID)
        {
            i--;
            (*comparacoes)++;
        }

        //Se o nó filho está cheio, faz o split e decide em qual dos dois nós inserir a chave depois do split
        (*comparacoes)++;
        if (filho[i+1]->numChaves == 2*grau-1)
        {
            split(i+1, filho[i+1], comparacoes, copias);

            //Checa onde inserir a chave depois do split
            (*comparacoes)++;
            if (chaves[i+1].userID < k.userID || (chaves[i+1].userID == k.userID && chaves[i+1].movieID < k.movieID ))
                i++;
        }
        filho[i+1]->insere(k, comparacoes, copias);
    }
}

//Função para fazer split quando nó está cheio
void NoB::split(int i, NoB *antigo, double *comparacoes, double *copias)
{
    //Cria novo nó com grau-1 chaves
    NoB *novo = new NoB(antigo->grau, antigo->ehFolha);
    novo->numChaves = grau - 1;

    //Copia a última metade do nó antigo (a se realizar split) para o novo
     for (int j = 0; j < grau-1; j++)
     {
        novo->chaves[j] = antigo->chaves[j+grau]; (*copias)++;
     }

    //Se o nó antigo não é folha, copia a última metade de seus filhos para o novo
    if (!antigo->ehFolha)
    {
        for (int j = 0; j < grau; j++)
        {
            novo->filho[j] = antigo->filho[j+grau]; (*copias)++;
        }
    }

    //Reduz as chaves do antigo nó para grau - 1
    antigo->numChaves = grau - 1;

    //Abre espaço no vetor de filhos para inserir o novo nó
    for (int j = numChaves; j >= i+1; j--)
    {
        filho[j+1] = filho[j]; (*copias)++;
    }

    //Insere o novo nó no vetor de filhos
    filho[i+1] = novo; (*copias)++;

    //Abre espaço para subir a chave do meio do nó antigo
    for (int j = numChaves-1; j >= i; j--)
    {
        chaves[j+1] = chaves[j]; (*copias)++;
    }

    //Sube a chave do meio do nó antigo
    chaves[i] = antigo->chaves[grau-1]; (*copias)++;

    numChaves ++;
}
