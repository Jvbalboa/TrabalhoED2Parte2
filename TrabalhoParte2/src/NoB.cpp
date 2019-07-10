#include "NoB.h"
#include<iostream>
#include <cstddef>

using namespace std;

/*Construtor: Seta o grau, a vari�vel booleana � folha e o n�mero de chaves como 0.
  Al�m de alocar mem�ria para o vetor de chaves e de filhos*/
NoB::NoB(int grau, int ehFolha)
{
    this->grau = grau;
    this->ehFolha = ehFolha;
    numChaves = 0;

    //Alocando mem�ria para o as chaves e n�s filho
    chaves = new Rating[2*grau-1];
    filho = new NoB* [2*grau];
}

//Fun��o para imprimir todos os n�s da sub�rvore
void NoB::imprime()
{
    int i;
    for (i = 0; i < numChaves; i++)
    {
        //Se n�o for folha, percorre e imprime os n�s da sub�rvore
        if (!ehFolha)
            filho[i]->imprime();
        cout << "(" << chaves[i].userID << ", " << chaves[i].movieID << ")";
    }

    //Imprime a sub�rvore do ultimo n�
    if (!ehFolha)
        filho[i]->imprime();
}

//Fun��o para buscar uma chave na sub�rvore
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

    //Se userID e movieID de chave[i] e k s�o iguais, retorna o n�
    (*comparacoes)++;
    if (chaves[i].userID == k.userID && chaves[i].movieID == k.movieID)
        return this;

    //Se a chave n�o foi encontrada e n�o h� mais n�s a percorrer (n� atual � folha), retorna nulo
    if (ehFolha)
        return NULL;

    //Chama fun��o recursivamente
    return filho[i]->busca(k, comparacoes);
}

//Fun��o para inserir chave quando o n�e n�o est� cheio
void NoB::insere(Rating k, double *comparacoes, double *copias)
{
    //Inicializa o �ndice como �ndice do elemento mais � direita
    int i = numChaves-1;

    //Se for um n� folha, acha a posi��o de inser��o e desoloca as chaves maiores para abrir espa�o
    if (ehFolha)
    {
        //Enquanto o userID da chave � maior do que o de k, empurra as chaves para direita
        (*comparacoes)++;
        while (i >= 0 && chaves[i].userID > k.userID)
        {
            chaves[i+1] = chaves[i];
            i--;
            (*comparacoes)++;
        }

        //Enquanto o userID da chave � igual ao de k e o movieID da chave � maior do que o de k, empurra as chaves para direita
        (*comparacoes)++;
        while(i >= 0 && chaves[i].userID == k.userID && chaves[i].movieID > k.movieID)
        {
            chaves[i+1] = chaves[i];
            i--;
            (*comparacoes)++;
        }

        //Insere a chave na posi��o em aberto
        chaves[i+1] = k;
        numChaves ++;
    }

    //Se o n� n�o � folha, acha o n� filho a se inserir a chave
    else
    {
        //Decrementa o �ndice enquanto o userID das chaves for maior que o de k
        (*comparacoes)++;
        while (i >= 0 && chaves[i].userID > k.userID)
        {
            i--;
            (*comparacoes)++;
        }

        //Decrementa o �ndice enquanto o userID das chaves for igual ao de k e o movieID das chaves for maior
        (*comparacoes)++;
        while(i >= 0 && chaves[i].userID == k.userID && chaves[i].movieID > k.movieID)
        {
            i--;
            (*comparacoes)++;
        }

        //Se o n� filho est� cheio, faz o split e decide em qual dos dois n�s inserir a chave depois do split
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

//Fun��o para fazer split quando n� est� cheio
void NoB::split(int i, NoB *antigo, double *comparacoes, double *copias)
{
    //Cria novo n� com grau-1 chaves
    NoB *novo = new NoB(antigo->grau, antigo->ehFolha);
    novo->numChaves = grau - 1;

    //Copia a �ltima metade do n� antigo (a se realizar split) para o novo
     for (int j = 0; j < grau-1; j++)
     {
        novo->chaves[j] = antigo->chaves[j+grau]; (*copias)++;
     }

    //Se o n� antigo n�o � folha, copia a �ltima metade de seus filhos para o novo
    if (!antigo->ehFolha)
    {
        for (int j = 0; j < grau; j++)
        {
            novo->filho[j] = antigo->filho[j+grau]; (*copias)++;
        }
    }

    //Reduz as chaves do antigo n� para grau - 1
    antigo->numChaves = grau - 1;

    //Abre espa�o no vetor de filhos para inserir o novo n�
    for (int j = numChaves; j >= i+1; j--)
    {
        filho[j+1] = filho[j]; (*copias)++;
    }

    //Insere o novo n� no vetor de filhos
    filho[i+1] = novo; (*copias)++;

    //Abre espa�o para subir a chave do meio do n� antigo
    for (int j = numChaves-1; j >= i; j--)
    {
        chaves[j+1] = chaves[j]; (*copias)++;
    }

    //Sube a chave do meio do n� antigo
    chaves[i] = antigo->chaves[grau-1]; (*copias)++;

    numChaves ++;
}
