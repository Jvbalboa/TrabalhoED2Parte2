#include "NoHuffman.h"
#include <iostream>


using namespace std;

//Inicializa o caractere e a frequência com os valores recebidos. Já esq e dir recebem nulo
NoHuffman::NoHuffman(char chave, int frequencia)
{
    ch = chave; //Chave
    freq = frequencia; //Quantidade de vezes que ele aparece
    esq = NULL; //Nó a esquerda
    dir = NULL; //Nó a direita
}

//Retorna se é folha
bool NoHuffman::ehFolha()
{
    return (getEsq() == NULL) && (getDir() == NULL);
}

//gets e sets
char NoHuffman::getChave()
{
    return ch;
}

void NoHuffman::setChave(char c)
{
    ch = c;
}

int NoHuffman::getFreq()
{
    return freq;
}

void NoHuffman::setFreq(int f)
{
    freq = f;
}

NoHuffman* NoHuffman::getEsq()
{
    return esq;
}

void NoHuffman::setEsq(NoHuffman* p)
{
    esq = p;
}

NoHuffman* NoHuffman::getDir()
{
    return dir;
}

void NoHuffman::setDir(NoHuffman* p)
{
    dir = p;
}
