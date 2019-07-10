#include "LeituraDaBase.h"

#include <iostream>
#include <fstream>
#include <chrono>
#include <random>
#include <cstdlib>

using namespace std;
using namespace chrono;

LeituraDaBase::LeituraDaBase()
{
    //ctor
}

//L� base de movieID + userID
void LeituraDaBase::leBase(Rating *base, int n)
{
    srand(time(NULL)); //Inicializa o gerador de n�s aleat�rios
    FILE* arq = fopen("ratings.csv", "r");
    int pula = 0;
    if(arq)
    {
        int cont = 0; //Contadores da linha atual e do n�mero de linhas lido, respectivamente
        int userID, movieID, timestemp;
        char c;
        float rating;
        fscanf(arq, "%*[^\n]"); //pular linha
        while(!feof(arq) && cont<n)
        {
            int val = rand()%13; //Gera n� alet�rio val, sendo que 0 <= val <= 13
            if(val != 0 && !feof(arq)) //Enquanto a linha atual � diferente da linha a ser lida
            {
                fscanf(arq, "%d %c %d %c %f %c %d",&userID, &c, &movieID, &c, &rating, &c, &timestemp); //pular linha
                pula ++;
            }
            else if(!feof(arq))
            {
                fscanf(arq, "%d %c %d %c %f %c %d",&userID, &c, &movieID, &c, &rating, &c, &timestemp);
                base[cont].setUserID(userID); //Salva o userID
                base[cont].setMovieID(movieID); //Salva o movieID
                cont++;
            }
        }

        embaralha(base, n); //Embaralha
        fclose(arq);
    }
    else
        cout << "Nao foi poss�vel ler a base" << endl;
}

//Fun��o que embaralha o vetor de Ratings
void LeituraDaBase::embaralha(Rating *vet, int n)
{
    unsigned int seed = system_clock::now().time_since_epoch().count();

    default_random_engine gen( seed );
    std::uniform_int_distribution<int> dist( 0, n-1 );

    int aux, r;

    for (int i = 0; i < n; i++)
	{
	    r = dist(gen); //Gera posi��o aleat�ria

        //Troca posi��o i por posi��o aleat�ria gerada
		aux = vet[i].getUserID();
		vet[i].setUserID(vet[r].getUserID());
		vet[r].setUserID(aux);

		aux = vet[i].getMovieID();
		vet[i].setMovieID(vet[r].getMovieID());
		vet[r].setMovieID(aux);
	}
}

/*  Fun��o auxiliar para leitura das sinopses.
    Chama a fun��o de ler intercalado se N <= 10.000 e a de ler sequencial caso contr�rio.
    Garantindo assim que o arquivo n�o chegue no fim sem que se tenha lido a quantidade de linhas desejada.
*/
void LeituraDaBase::leArquivo(string *sinopse, int n)
{
    if(n > 10000)
        auxLeArquivoSequencial(sinopse, n);
    else
        auxLeArquivo(sinopse, n);
}

/*  M�todo que l� as linhas de acordo com uma fun��o de escolha aleat�ria.
    Gera um n�mero aleat�rio, se este for par l� a linha, sen�o pula.
*/
void LeituraDaBase::auxLeArquivo(string *sinopse, int n)
{
    //Abre arquivo para leitura
    fstream arq;
        arq.open("movies_metadata.csv");
        if(arq)
        {
            //Inicia a semente para a gerar n�meros aleat�rios
            unsigned int seed = system_clock::now().time_since_epoch().count();
            //Inicializa o gerador
            default_random_engine gen( seed );
            //Define o intervalo de n�meros gerados: de 0 at� n
            uniform_int_distribution<int> dist( 0, n );

            string linha, aux; //Auxiliares para leitura da linha e separa��o da sinopse
            char c1, c2; //Auxiliares para leitura de um caractere da linha
            const char *aspas = "\"", *ponto = "."; //Auxiliares que representam os caracteres " e .
            const char *letra_A = "A", *letra_Z = "Z", *letra_a = "a", *letra_z = "z"; //Controlam os intervalos de "A" a "Z" e de "a" a "z"
            int aMaiusculo = *letra_A, zMaiusculo = *letra_Z, aMinusculo = *letra_a, zMinusculo = *letra_z; //Controlam os intervalos de acordo com o valor na tabela ascii

            int cont = 0; //Contador de linhas lidas
            //Enquanto n�o foram lidas o n�mero desejada de linhas e o arquivo n�o chegou ao fim, l� as linhas aleat�riamente
            while(!arq.eof() && cont<=n)
            {
                int val = dist(gen)%2; //Gera n� alet�rio val, sendo que 0 <= val <= 1
                if(val != 0 && !arq.eof()) //Se o valor gerado � �mpar, pula a linha
                {
                    getline(arq, aux); //pular linha
                }
                else if(!arq.eof()) //Se o valor gerado � par, l� a linha
                {
                    cont++;
                    getline(arq, linha);

                    //Loop que percorre a string da linha lida at� achar a parte referente a sinopse
                    for(unsigned int i=0; i<linha.size()-1; i++)
                    {
                        c1 = linha[i];
                        c2 = linha[i+1];
                        //Se o caractere na posi��o atual � " (abre aspas) e o pr�ximo � uma letra, significa que � o in�cio da sinopse
                        if(c1 == *aspas && ((c2 >= aMaiusculo && c2 <= zMaiusculo) || (c2 >= aMinusculo && c2 <= zMinusculo)))
                        {
                            //Guarda os caracteres da sinopse at� achar o ." (ponto final seguido de fecha aspas)
                            for(unsigned int j=i+1; ((linha[j] != *ponto || linha[j+1] != *aspas) && j<linha.size()-1); j++)
                                *sinopse += linha[j];
                            break; //Com a sinopse j� lida, para de percorrer a linha (restante n�o importa)
                        }
                    }
                }

            }

            //cout << *sinopse << endl;
            //cout << "\nContador: " << cont << endl;

            arq.close();
        }
        else
            cout << "Nao foi possivel abrir o arquivo de entrada" << endl;
}

//M�todo que l� linhas de forma sequencial
void LeituraDaBase::auxLeArquivoSequencial(string *sinopse, int n)
{
    //Abre arquivo para leitura
    fstream arq;
    arq.open("movies_metadata.csv");
    if(arq)
    {
        string linha, aux; //Auxiliares para leitura da linha e separa��o da sinopse
        char c1, c2; //Auxiliares para leitura de um caractere da linha
        const char *aspas = "\"", *ponto = "."; //Auxiliares que representam os caracteres " e .
        const char *letra_A = "A", *letra_Z = "Z", *letra_a = "a", *letra_z = "z"; //Controlam os intervalos de "A" a "Z" e de "a" a "z"
        int aMaiusculo = *letra_A, zMaiusculo = *letra_Z, aMinusculo = *letra_a, zMinusculo = *letra_z; //Controlam os intervalos de acordo com o valor na tabela ascii

        int cont = 0; //Contador de linhas lidas
        //Enquanto n�o foram lidas o n�mero desejada de linhas e o arquivo n�o chegou ao fim, l� as linhas sequencialmente
        while(!arq.eof() && cont<=n)
        {
            cont++;
            getline(arq, linha);

            //Loop que percorre a string da linha lida at� achar a parte referente a sinopse
            for(unsigned int i=0; i<linha.size()-1; i++)
            {
                c1 = linha[i];
                c2 = linha[i+1];
                //Se o caractere na posi��o atual � " (abre aspas) e o pr�ximo � uma letra, significa que � o in�cio da sinopse
                if(c1 == *aspas && ((c2 >= aMaiusculo && c2 <= zMaiusculo) || (c2 >= aMinusculo && c2 <= zMinusculo)))
                {
                    //Guarda os caracteres da sinopse at� achar o ." (ponto final seguido de fecha aspas)
                    for(unsigned int j=i+1; ((linha[j] != *ponto || linha[j+1] != *aspas) && j<linha.size()-1); j++)
                        *sinopse += linha[j];
                    break; //Com a sinopse j� lida, para de percorrer a linha (restante n�o importa)
                }
            }

        }

        //cout << *sinopse << endl;
        //cout << "\nContador: " << cont << endl;

        arq.close();
    }
    else
        cout << "Nao foi possivel abrir o arquivo de entrada" << endl;
}
