#include "NoVP.h"

#include <cstddef>
using namespace std;

//Construtor: inicializa tudo com NULL, exceto chave.
NoVP::NoVP(Rating k)
{
    chave = k;
    esquerda = NULL;
    direita = NULL;
    pai = NULL;
    cor = NULL;
}
