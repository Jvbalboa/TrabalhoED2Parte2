#ifndef NOVP_H
#define NOVP_H

#include "Rating.h"

class NoVP
{
    private:
        Rating chave; //Combina��o de userID e movieID
        bool cor; //Cor do n�
        NoVP *esquerda, *direita, *pai; //Ponteiro para filho � esquerda, direita e pai

    public:
        //Construtor
        NoVP(Rating k);

    friend class ArvoreVP; //Permite que ArvoreVP acesse seus atributos privados
};

#endif // NOVP_H
