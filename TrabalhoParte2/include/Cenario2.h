#ifndef CENARIO2_H
#define CENARIO2_H

#include "ArvoreHuffman.h"
#include "NoHuffman.h"
#include "LZW.h"
#include "LeituraDaBase.h"

class Cenario2
{
    public:
        Cenario2();
        //Função que controla os loops de cada seed e a compressão
        void execucao(int totalSeeds);

};

#endif // CENARIO2_H
