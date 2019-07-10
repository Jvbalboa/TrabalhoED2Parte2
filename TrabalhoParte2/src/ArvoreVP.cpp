#include "ArvoreVP.h"

#include <iostream>
#include <cstddef>
#include <queue>

using namespace std;

#define VERMELHO 0
#define PRETO 1

//Construtor: raiz recebe NULL
ArvoreVP::ArvoreVP()
{
    raiz = NULL;
}

ArvoreVP::~ArvoreVP()
{
    auxDelete(raiz);
}

void ArvoreVP::auxDelete(NoVP *p)
{
    if(p->esquerda!=NULL)
        auxDelete(p->esquerda);
    if (p->direita!=NULL)
        auxDelete(p->direita);
    delete p;
}

//Funções auxiliares
//Chama função de imprimir recursivamente (ordenado)
void ArvoreVP::imprime()
{
    auxImprime(raiz);
}

//Chama função de imprimir recursivamente (por nível)
void ArvoreVP::imprimePorNivel()
{
    auxImprimePorNivel(raiz);
}

//Imprime na ordem: imprime esquerda, imprime raiz e imprime direita
void ArvoreVP::auxImprime(NoVP *raiz)
{

    if(raiz == NULL)
    {
        return;
    }

    auxImprime(raiz->esquerda);
    cout << "(" << raiz->chave.getUserID() << ","  << raiz->chave.getMovieID() << ")Cor:";
    raiz->cor? cout << "P" << " " : cout << "V" << " ";
    auxImprime(raiz->direita);
}

//Imprime por nível: imprime nó e enfileira filho à esquerda e à direita
void ArvoreVP::auxImprimePorNivel(NoVP *raiz)
{
	if (raiz == NULL)
		return;

	std::queue<NoVP *> q; //Cria fila de Nós
	q.push(raiz); //Insere a raiz

	//Enquanto fila é vazia, imprime nó da frente e enfileira seus filhos
	while (!q.empty())
	{
		NoVP *temp = q.front();
		cout << "(" << temp->chave.getUserID() << "," << temp->chave.getMovieID() << ")Cor:";
		temp->cor? cout << "P" << " " : cout << "V" << " ";
		q.pop();

		if (temp->esquerda != NULL)
			q.push(temp->esquerda);

		if (temp->direita != NULL)
			q.push(temp->direita);
	}
}

//Função que insere como se fosse uma àrvore Binária de Busca
NoVP* ArvoreVP::insereArvoreBinaria(NoVP* raiz, NoVP *p, double *comparacoes)
{
	//Se Árvore é vazia, retorna o nó
	if (raiz == NULL)
        return p;

	//Senão, acha a posição para inserção
	//Se userID de p é menor que o da raiz, insere à esquerda
	if (p->chave.getUserID() < raiz->chave.getUserID())
	{
	    (*comparacoes)++; //Acrescenta comparação do if
		raiz->esquerda = insereArvoreBinaria(raiz->esquerda, p, comparacoes);
		raiz->esquerda->pai = raiz;
	}

	//Se userID de p é maior que o da raiz, insere à direita
	else if (p->chave.getUserID() > raiz->chave.getUserID())
	{
	    (*comparacoes)+=2; //Comparou no if e no else if
		raiz->direita = insereArvoreBinaria(raiz->direita, p, comparacoes);
		raiz->direita->pai = raiz;
	}

	//Se userID de p é igual ao da raiz, compara pelo movieID
	else if (p->chave.getUserID() == raiz->chave.getUserID())
    {
        (*comparacoes)+=3; //Comparou 1° no if e nos 2 else if
        //Se movieID de p é menor que o da raiz, insere à esquerda
        if (p->chave.getMovieID() < raiz->chave.getMovieID())
        {
            (*comparacoes)++;
            raiz->esquerda = insereArvoreBinaria(raiz->esquerda, p, comparacoes);
            raiz->esquerda->pai = raiz;
        }

        //Se movieID de p é maior que o da raiz, insere à direita
        else if (p->chave.getMovieID() >= raiz->chave.getMovieID())
        {
            (*comparacoes)+=2;
            raiz->direita = insereArvoreBinaria(raiz->direita, p, comparacoes);
            raiz->direita->pai = raiz;
        }
    }
	return raiz;
}

//Rotação Esquerda
void ArvoreVP::rotacaoEsquerda(NoVP *&raiz, NoVP *&p, double *comparacoes)
{
	NoVP *p_direita = p->direita;

	p->direita = p_direita->esquerda;

	if (p->direita != NULL)
    {
		p->direita->pai = p;
    }

	p_direita->pai = p->pai;

	if (p->pai == NULL)
    {
		raiz = p_direita;
    }

	else if (p == p->pai->esquerda)
    {
		p->pai->esquerda = p_direita;
    }

	else
    {
		p->pai->direita = p_direita;
    }

	p_direita->esquerda = p;
	p->pai = p_direita;
}

//Rotação Direita
void ArvoreVP::rotacaoDireita(NoVP *&raiz, NoVP *&p, double *comparacoes)
{
	NoVP *p_esquerda = p->esquerda;

	p->esquerda = p_esquerda->direita;

	if (p->esquerda != NULL)
    {
		p->esquerda->pai = p;
    }

	p_esquerda->pai = p->pai;

	if (p->pai == NULL)
    {
		raiz = p_esquerda;
    }

	else if (p == p->pai->esquerda)
    {
		p->pai->esquerda = p_esquerda;
    }

	else
    {
		p->pai->direita = p_esquerda;
    }

	p_esquerda->direita = p;
	p->pai = p_esquerda;
}

//Ajusta árvore após a insercção binária, checando quais ações devem ser executadas
void ArvoreVP::ajustaArvore(NoVP *&raiz, NoVP *&p, double *comparacoes)
{
	NoVP *p_pai = NULL;
	NoVP *p_avo = NULL;

	while ((p != raiz) && (p->cor != PRETO) && (p->pai->cor == VERMELHO))
	{

		p_pai = p->pai;
		p_avo = p->pai->pai;

		//Caso 1: pai de p é filho à esquerda de avô de p
		if (p_pai == p_avo->esquerda)
		{
			NoVP *p_tio = p_avo->direita;

			//Se o tio de p é vermelho, recolore
			if (p_tio != NULL && p_tio->cor == VERMELHO)
			{
				p_avo->cor = VERMELHO;
				p_pai->cor = PRETO;
				p_tio->cor = PRETO;

				p = p_avo;
			}

			else
			{
				//Se p é filho à direita, rotaciona à esquerda
				if (p == p_pai->direita)
				{
					rotacaoEsquerda(raiz, p_pai, comparacoes);

					p = p_pai;
					p_pai = p->pai;
				}

				//Se p é filho a esquerda, rotaciona à direita
				rotacaoDireita(raiz, p_avo, comparacoes);
				bool aux = p_pai->cor;
				p_pai->cor = p_avo->cor;
				p_avo->cor = aux;

				p = p_pai;
			}
		}

		//Caso 2: pai de p é filho à direita de avô de p
		else
		{
			NoVP *p_tio = p_avo->esquerda;

			//Se o tio de p é vermelho, recolore
            (*comparacoes)++;
			if ((p_tio != NULL) && (p_tio->cor == VERMELHO))
			{
				p_avo->cor = VERMELHO;
				p_pai->cor = PRETO;
				p_tio->cor = PRETO;

				p = p_avo;
			}
			else
			{
				//Se p é filho à esquerda, rotaciona à direita
				(*comparacoes)++;
				if (p == p_pai->esquerda)
				{
					rotacaoDireita(raiz, p_pai, comparacoes);

					p = p_pai;
					p_pai = p->pai;
				}

				//Se p é filho à direita, rotaciona à esquerda
				rotacaoEsquerda(raiz, p_avo, comparacoes);
				bool aux = p_pai->cor;
				p_pai->cor = p_avo->cor;
				p_avo->cor = aux;

				p = p_pai;

			}

		}
	}

	raiz->cor = PRETO;
}

//Função que insere nó na AVP e chama método para ajustá-la
void ArvoreVP::insere(Rating k, double *comparacoes)
{
	NoVP *p = new NoVP(k);

	//Inserção da Árvore Binária de Busca
	raiz = insereArvoreBinaria(raiz, p, comparacoes);

	//Ajusta e corrige Árvore
	ajustaArvore(raiz, p, comparacoes);
}

//Função que busca pela nó combinação de userID e movieID, se não encontrar, retorna o nó mais próximo
NoVP* ArvoreVP::busca(Rating k, double *comparacoes)
{
    NoVP *temp = raiz;
    //Enquanto temporário não é nulo, faz a busca
    while (temp != NULL)
    {
        //Se o userID buscado é menor do que o de temp, anda para esquerda
        if (k.getUserID() < temp->chave.getUserID())
        {
            (*comparacoes)+=2;
            if (temp->esquerda == NULL)
                break;
            else
                temp = temp->esquerda;
        }

        //Se o userID buscado é igual ao de temp, verifica pelo movieID
        else if (k.getUserID() == temp->chave.getUserID())
        {
            (*comparacoes)+=2;

            //Se o movieID buscado é menor do que o de temp, anda para esquerda
            (*comparacoes)++;
            if(k.getMovieID() < temp->chave.getMovieID())
            {
                (*comparacoes)++;
                if (temp->esquerda == NULL)
                    break;
                else
                    temp = temp->esquerda;
            }

            //Se o movieID buscado é igaul ao de temp, o valor foi encontrado
            else if(k.getMovieID() == temp->chave.getMovieID())
            {
                (*comparacoes)+=2;
                break;
            }

            //Se o movieID buscado é maior do que o de temp, anda para direita
            else
            {
                (*comparacoes)+=2;

                (*comparacoes)++;
                if (temp->direita == NULL)
                    break;
                else
                    temp = temp->direita;
            }

        }

        //Se o userID buscado é maior do que o de temp, anda para direita
        else
        {
            (*comparacoes)+=2;

            (*comparacoes)++;
            if (temp->direita == NULL)
                break;
            else
                temp = temp->direita;
        }
    }
    return temp;
}
