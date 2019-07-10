/*
Autores:
    Braulio Silva Mendes Lucas
    João Victor Dutra Balboa
    Marcus Vinícius Vasconcelos de A. Cunha
*/

#include "Cenario1.h"
#include "Cenario2.h"

using namespace std;

int main()
{
    //Interface--------------------------------------------------------------------------------------------------------------------
    cout << "Autores: -------------------------------" << endl;
    cout << "Braulio Silva Mendes Lucas \nJoao Victor Dutra Balboa \nMarcus Vinicius Vasconcelos de A. Cunha" << endl;
    cout << "---------------------------------------\n\n" << endl;


    //Primeira Parte---------------------------------------------------------------------------------------------------------------
    cout << "Cenario 1:" << endl;
    Cenario1 cenario1;
    cenario1.execucao(5);

    //Segunda Parte----------------------------------------------------------------------------------------------------------------
    cout << "Cenario 2:" << endl;
    Cenario2 cenario2;
    cenario2.execucao(5);

    return 0;
}
