#ifndef NOVP_H
#define NOVP_H

#include "Rating.h"

class NoVP
{
    private:
        Rating chave; //Combinação de userID e movieID
        bool cor; //Cor do nó
        NoVP *esquerda, *direita, *pai; //Ponteiro para filho à esquerda, direita e pai

    public:
        //Construtor
        NoVP(Rating k);

    friend class ArvoreVP; //Permite que ArvoreVP acesse seus atributos privados
};

#endif // NOVP_H
