#ifndef LEITURADABASE_H
#define LEITURADABASE_H

#include "Rating.h"
#include <iostream>

using namespace std;

class LeituraDaBase
{
    private:
        void embaralha(Rating *base, int n);
        //Funções para ler as sinopses
        void auxLeArquivo(string *vet, int n); //Lê aleatóriamente
        void auxLeArquivoSequencial(string *vet, int n); //Lê sequencialmente

    public:
        LeituraDaBase();
        void leBase(Rating *base, int n); //Lê base para vetor de objetos
        void leArquivo(string *vet, int n); //Chama a função de ler sinopse

};

#endif // LEITURADABASE_H
