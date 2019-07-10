/*
Autores:
    Braulio Silva Mendes Lucas
    João Victor Dutra Balboa
    Marcus Vinícius Vasconcelos de A. Cunha
*/

#include <iostream>

#include "Cenario1.h"
#include "Cenario2.h"

using namespace std;

int main()
{
    //Interface--------------------------------------------------------------------------------------------------------------------
    cout << "Autores: -------------------------------" << endl;
    cout << "Braulio Silva Mendes Lucas \nJoao Victor Dutra Balboa \nMarcus Vinicius Vasconcelos de A. Cunha" << endl;
    cout << "---------------------------------------\n\n" << endl;

    //Lendo o número de execuções desejado
    int n;
    char c[10];
    //Repete enquanto n não estiver entre 1 e 10
    do
    {
        cout << "Digite o numero desejado de execucoes para cada N (entre 1 e 10): ";
        cin >> c;
        n = atoi(c);
        cout << "execucoes: " << n << endl;

        if(n<1 || n>10)
            cout << "\nValor nao permitido" << endl;
    } while(n<1 || n>10);

    //Primeira Parte---------------------------------------------------------------------------------------------------------------
    cout << "Cenario 1:" << endl;
    Cenario1 cenario1;
    cenario1.execucao(n);

    //Segunda Parte----------------------------------------------------------------------------------------------------------------
    cout << "Cenario 2:" << endl;
    Cenario2 cenario2;
    cenario2.execucao(n);

    return 0;
}
