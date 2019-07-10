#ifndef LEITURADABASE_H
#define LEITURADABASE_H

#include "Rating.h"
#include <iostream>

using namespace std;

class LeituraDaBase
{
    private:
        void embaralha(Rating *base, int n);
        //Fun��es para ler as sinopses
        void auxLeArquivo(string *vet, int n); //L� aleat�riamente
        void auxLeArquivoSequencial(string *vet, int n); //L� sequencialmente

    public:
        LeituraDaBase();
        void leBase(Rating *base, int n); //L� base para vetor de objetos
        void leArquivo(string *vet, int n); //Chama a fun��o de ler sinopse

};

#endif // LEITURADABASE_H
