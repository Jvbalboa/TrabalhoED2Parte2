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
        //Fun��o que controla os loops de cada seed, a inser��o e a busca nas �rvores
        void execucao(int totalSeeds);

};

#endif // CENARIO1_H
