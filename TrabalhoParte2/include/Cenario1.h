#ifndef CENARIO1_H
#define CENARIO1_H

#include "ArvoreB.h"
#include "ArvoreVP.h"
#include "LeituraDaBase.h"
#include "Rating.h"

class Cenario1
{
    public:
        Cenario1();
        //Função que controla os loops de cada seed, a inserção e a busca nas árvores
        void execucao(int totalSeeds);

};

#endif // CENARIO1_H
